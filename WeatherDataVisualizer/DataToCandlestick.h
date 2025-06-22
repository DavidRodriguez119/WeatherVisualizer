#pragma once
#include <string>
#include <vector>
#include "Candlestick.h"
#include "WeatherData.h"

class DataToCandlestick
{
	public:
		/** Constructor*/
		DataToCandlestick(std::string fileName);
		std::vector<Candlestick> generateYearlyCandlesticks(const std::string countryCode, const std::string startYear, const std::string endYear);

	private:
		std::vector<WeatherData> weatherData;
		/** Generate Candlestick*/
		Candlestick assignType(std::string date, double open, double high, double low, double close);

};

