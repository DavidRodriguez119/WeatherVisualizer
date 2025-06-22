#include "DataToCandlestick.h"
#include "CSVReader.h"
#include <iostream>

//Constructor
DataToCandlestick::DataToCandlestick(std::string fileName) {
	//Obtain all the RAW Data from the CSV file
	weatherData = CSVReader::readCSV(fileName);
};

Candlestick DataToCandlestick::assignType(std::string date, double open, double high, double low, double close) {
	CandlestickType type;
	//Determine the type of candlestick based on open and close values
	if (open <= close)
	{
		type = CandlestickType::Bearish;
	}
	else {
		type = CandlestickType::Bullish;
	};
	return Candlestick(date, type, open, high, low, close);
};

std::vector<Candlestick> DataToCandlestick::generateYearlyCandlesticks(const std::string countryCode, const std::string startYear, const std::string endYear) {
	std::vector<Candlestick> candlesticks;

	return candlesticks;
};