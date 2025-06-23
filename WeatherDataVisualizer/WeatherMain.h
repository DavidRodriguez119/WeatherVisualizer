#pragma once
#include <iostream>
#include <string>
#include "DataToCandlestick.h"

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

		//Individual functions for each user option
		
		/**Access help*/
		void printHelp();
		/**Print a list of all the available countries with abreviations*/
		void seeAvailableCountries();


		/** Process the user option and call the appropriate function */
		void processUserOption(int option);

		/** Get all the raw data as WeatherData objects
		  * Initialize the class in charge of filtering and translating into candlestick data*/
		DataToCandlestick dataToCandlestick{"testData.csv"};
};

