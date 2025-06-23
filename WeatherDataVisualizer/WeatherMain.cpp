#include "WeatherMain.h"
#include "CSVReader.h"
#include "WeatherData.h"

//Constructor
WeatherMain::WeatherMain() {

};

void WeatherMain::init() {
    int input;

    std::vector<Candlestick> tesdtVector = dataToCandlestick.generateYearlyCandlesticks("AT", 1980, 1982);
	std::cout << "Candlesticks Generated: " << tesdtVector.size() << std::endl;
    std::cout << "Candlesticks Generated:" << tesdtVector[0].open << " " << tesdtVector[tesdtVector.size() - 1].open << std::endl;

	//Initialize the menu and ask the user for input
    //while (true) {
    //    printMenu();
    //    input = getUserOption();
    //    processUserOption(input);
    //};
};

void WeatherMain::printMenu() {
    // 1. print help
    std::cout << "1. Print help" << std::endl;
    // 2. print exchange stats
    std::cout << "2. See Countries" << std::endl;
    // 3. make an offer
    std::cout << "3. Plot Candlestick Chart " << std::endl;
    // Get user input
    std::cout << "===================" << std::endl;
    std::cout << "Type in 1-3:" << std::endl;
};

int WeatherMain::getUserOption() {
    int userOption = 0;
    std::string line;
    std::getline(std::cin, line);
    try {
        userOption = std::stoi(line);
    }
    catch (const std::exception& e) {
        std::cout << "Invalid input. Please enter a number between 1 and 3." << std::endl;
    };

    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
};

void WeatherMain::processUserOption(int option) {
    switch (option) {
    case 1:
        //function for option 1
        break;
    case 2:
		//function for option 2
        break;
    case 3:
		//function for option 3
        break;
    default:
        std::cout << "Invalid choice. Please type a number between 1 and 6." << std::endl;
        break;
    }
};


