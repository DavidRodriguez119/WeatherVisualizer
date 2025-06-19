#include "WeatherData.h"

WeatherData::WeatherData(const std::string& _date,
						const std::string& _time,
						const std::map<std::string,double>& _temps)
						:date(_date), time(_time), temperatures(_temps)
{

};

double WeatherData::getOneTemperature(const std::string& country) {
	auto index = temperatures.find(country);
	if (index != temperatures.end()) {
		return index->second;
	}
	return 0; // Return 0 if country not found
};




