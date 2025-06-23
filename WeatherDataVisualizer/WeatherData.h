#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>

class WeatherData
{
	public:
		/** Create a Weather data object using a Date, Time and a map of countries with temperatures*/
		WeatherData(const int year, const int month, const int day, const std::string& time, const std::map<std::string, double>& temps);

		/** Get the year of the weather data*/
		int getYear() {
			return year;
		};
		/** Get the date of the weather data*/
		int getMonth() {
			return month;
		};
		/** Get the date of the weather data*/
		int getDay() {
			return day;
		};

		/** Get the time of the weather data*/
		std::string getTime() {
			return time;
		};
		/** Get the temperature for a specific country, returns 0 if country not found*/
		double getOneTemperature(const std::string& country);



	private:
		int year;
		int month;
		int day;
		std::string time;
		std::map<std::string, double> temperatures; 

};