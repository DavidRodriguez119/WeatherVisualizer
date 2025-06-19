#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>

class WeatherData
{
	public:
		/** Create a Weather data object using a Date, Time and a map of countries with temperatures*/
		WeatherData(const std::string& date, const std::string& time, const std::map<std::string, double>& temps);

		/** Get the date of the weather data*/
		std::string getDate() {
			return date;
		};
		/** Get the time of the weather data*/
		std::string getTime() {
			return time;
		};
		/** Get the temperature for a specific country, returns 0 if country not found*/
		double getOneTemperature(const std::string& country);



	private:
		std::string date;
		std::string time;
		std::map<std::string, double> temperatures; 

};
