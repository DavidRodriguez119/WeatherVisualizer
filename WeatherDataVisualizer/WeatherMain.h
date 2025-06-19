#pragma once
#include <iostream>
#include <string>

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
		/** Process the user option and call the appropriate function */
		void processUserOption(int option);
};

