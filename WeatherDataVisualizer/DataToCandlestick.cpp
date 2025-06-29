#include "DataToCandlestick.h"
#include "CSVReader.h"
#include <iostream>

//Constructor
DataToCandlestick::DataToCandlestick(std::string fileName) {
	//Obtain all the RAW Data from the CSV file
	weatherData = CSVReader::readCSV(fileName);
	availableCountries = loadAvailableCountries();
};

CandlestickType DataToCandlestick::assignType(double open, double close) {
	CandlestickType type;
	//Determine the type of candlestick based on open and close values
	if (open <= close)
	{
		type = CandlestickType::Bearish;
	}
	else {
		type = CandlestickType::Bullish;
	};
	return type;
};

//Contry code is assumed to exist in the WeatherData object
std::vector<Candlestick> DataToCandlestick::generateYearlyCandlesticks(const std::string countryCode, const int startYear, const int endYear) {
	std::vector<Candlestick> candlesticks;
	std::vector<WeatherData> filteredData;

	//Trim data from the weatherData vector to only include the specified country and year range
	for (WeatherData& entry : weatherData) {
		if (entry.getYear() >= startYear && entry.getYear() <= endYear) {
			if (entry.getOneTemperature(countryCode)) {
				filteredData.push_back(entry);
			};
		};
	};

	//Get all the years that need to be processed
	std::vector<int> years;
	std::map<int, bool> yearMap;
	for (WeatherData& filteredEntry : filteredData) {
		yearMap[filteredEntry.getYear()] = true;
	};
	for (const auto& yearPair : yearMap) {
		years.push_back(yearPair.first);
	};

	int yearCount = years.size();
	int index = 0;

	//Create a candlestick for each year
	for (int i = 0; i < yearCount; ++i) {
		TemporaryStats currentCandlestick;
		//Add Date
		currentCandlestick.date = years[i];
		//Add open
		currentCandlestick.open = filteredData[index].getOneTemperature(countryCode);
		while (filteredData[index].getYear() == years[i]) {
			//Find the highest and lowest temperatures for the year
			if (filteredData[index].getOneTemperature(countryCode) > currentCandlestick.high) {
				currentCandlestick.high = filteredData[index].getOneTemperature(countryCode);
			};
			if (filteredData[index].getOneTemperature(countryCode) < currentCandlestick.low) {
				currentCandlestick.low = filteredData[index].getOneTemperature(countryCode);
			};
			if (index >= filteredData.size() - 1 || filteredData.size() == 1) {
				break; //Prevent out of bounds access
			};
			index++;
		}
		//Add close
		currentCandlestick.close = filteredData[index - 1].getOneTemperature(countryCode);
		//Create a candlestick object and add it to the vector
		Candlestick finishedCandlestick{ currentCandlestick.date,
			assignType(currentCandlestick.open, currentCandlestick.close),
			currentCandlestick.open,
			currentCandlestick.high,
			currentCandlestick.low,
			currentCandlestick.close,
		};
		candlesticks.push_back(finishedCandlestick);
	};

	return candlesticks;
};

std::map<std::string, std::string> DataToCandlestick::loadAvailableCountries() {
	std::map<std::string, std::string> countriesMap;
	const std::vector<std::string> countryCodes = { "AT", "BE", "BG", "CH", "CZ", "DE", "DK", "EE", "ES", "FI", "FR", "GB", "GR", "HR", "HU",
		"IE", "IT", "LT", "LU", "LV", "NL", "NO", "PL", "PT", "RO", "SE", "SI", "SK" };
	const std::vector<std::string> countryNames = { "Austria", "Belgium", "Bulgaria", "Switzerland", "Czech Republic", "Germany", "Denmark",
		"Estonia", "Spain", "Finland", "France", "United Kingdom", "Greece", "Croatia", "Hungary", "Ireland", "Italy", "Lithuania", "Luxembourg",
		"Latvia", "Netherlands", "Norway", "Poland", "Portugal", "Romania", "Sweden", "Slovenia", "Slovakia" };
	for (int i = 0; i < countryCodes.size(); ++i) {
		countriesMap[countryCodes[i]] = countryNames[i];
	};
	return countriesMap;
};

const std::vector <int> DataToCandlestick::getTotalYearsRange() {
	std::vector<int> yearsRange;
	int startYear = 9999;
	int endYear = 0;
	for (WeatherData& entry : weatherData) {
		if (entry.getYear() < startYear) {
			startYear = entry.getYear();
		};
		if (entry.getYear() > endYear) {
			endYear = entry.getYear();
		};
	};
	yearsRange.push_back(startYear);
	yearsRange.push_back(endYear);
	return yearsRange;
};