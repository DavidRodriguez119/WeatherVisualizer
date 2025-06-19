#pragma once

#include "WeatherData.h"
#include <vector>
#include <string>

class CSVReader
{
public:
	//Constructor
	CSVReader();

	static std::vector<WeatherData> readCSV(const std::string& csvFile);
	static std::vector<std::string> tokenize(std::string csvLine, char separator);

private:
	static WeatherData stringsToWeatherData(std::vector<std::string> string);
};