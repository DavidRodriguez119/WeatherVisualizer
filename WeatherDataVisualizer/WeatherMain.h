#pragma once
#include <iostream>
#include <string>
#include "DataToCandlestick.h"
#include "Prediction.h"

class WeatherMain
{
	public:
		WeatherMain();
		void init();

	private:

		/** Print the menu to the user */
		void printMenu();
		/** Obtain the option selected by the user and use appropriatly */
		int getUserOption();

		//////////////Individual functions for each user option//////////////////
		
		/**Access help*/
		void printHelp();

		/**Print a list of all the available countries with abreviations*/
		void seeAvailableCountries();

		/** Input the user for information to print the yearly candlestick table*/
		std::vector<Candlestick> getYearlyCandlestickInfo();

		/**Asks the user for input and then calls the function to print the table*/
		void generateCandlestickTable();

		/**Print candlestick table*/
		void printCandlestickTable(std::vector<Candlestick>& candlesticks);

		/**Collects information from the user to print a candlestick graph*/
		void generateCandlestickGraph();

		/**Prints a candlestick graph*/
		void generatePrediction();

		/** Process the user option and call the appropriate function */
		void processUserOption(int option);

		/** Get all the raw data as WeatherData objects
		  * Initialize the class in charge of filtering and translating into candlestick data*/
		DataToCandlestick dataToCandlestick{"weather_data_EU_1980-2019_temp_only.csv"};
};

