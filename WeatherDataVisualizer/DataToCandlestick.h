#pragma once
#include <string>
#include <vector>
#include "Candlestick.h"
#include "WeatherData.h"
#include <limits>

struct TemporaryStats
{
	int date = 0;
	double open = 0;
	double high = std::numeric_limits<double>::lowest();
	double low = std::numeric_limits<double>::max();
	double close = 0;
};

class DataToCandlestick
{
	public:
		/** Constructor*/
		DataToCandlestick(std::string fileName);
		std::vector<Candlestick> generateYearlyCandlesticks(const std::string countryCode, const int startYear, const int endYear);
		const std::map<std::string, std::string> getAvailableCountries() {
			return availableCountries;
		};

	private:
		std::map<std::string, std::string> availableCountries;
		std::vector<WeatherData> weatherData;

		/** Generate Candlestick*/
		CandlestickType assignType(double open, double close);

		/**Load Available Countries*/
		std::map<std::string, std::string> loadAvailableCountries();
};

