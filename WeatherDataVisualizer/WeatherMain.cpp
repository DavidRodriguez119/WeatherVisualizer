#include "WeatherMain.h"
#include "CSVReader.h"
#include "WeatherData.h"
#include <iomanip>


//Constructor
WeatherMain::WeatherMain() {

};

void WeatherMain::init() {
    int input;

 //   std::vector<Candlestick> tesdtVector = dataToCandlestick.generateYearlyCandlesticks("AT", 1980, 1982);
	//std::cout << "Candlesticks Generated: " << tesdtVector.size() << std::endl;
 //   std::cout << "Candlesticks Generated:" << tesdtVector[0].open << " " << tesdtVector[tesdtVector.size() - 1].open << std::endl;

	//Initialize the menu and ask the user for input
    while (true) {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    };
};

void WeatherMain::printMenu() {
    std::cout << "=======================================" << std::endl;
    // 1. print help
    std::cout << "1. Print Help" << std::endl;
	// 2. print a list of available countries and abreviations
    std::cout << "2. See Available Countries" << std::endl;
	// 3. print a table with candlestick data for a given country and year range
    std::cout << "3. Plot Candlestick Chart " << std::endl;
	// 4. generate a candlestick graph for a given country and year range
	std::cout << "4. Generate Candlestick Graph" << std::endl;
    // Get user input
    std::cout << "=======================================" << std::endl;
    std::cout << "Type in 1-4:" << std::endl;
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

void WeatherMain::printHelp() {
    std::cout << "Help - you can use this app to visualize (table or graph) weather data for a particular country in Europe." << std::endl;
};

void WeatherMain::seeAvailableCountries() {
	std::cout << "Available countries: " << std::endl;
	std::map<std::string, std::string> countries = dataToCandlestick.getAvailableCountries();
    for(const auto& country : countries) {
        std::cout << country.first << " - " << country.second << std::endl;
	};
};

std::vector<Candlestick> WeatherMain::getYearlyCandlestickInfo() {
	std::map<std::string, std::string> availableCountries = dataToCandlestick.getAvailableCountries();
    //Get the input country
	std::string inputCountry;
	bool validCountry = false;
    
    while (!validCountry) {
        std::cout << "=======================================" << std::endl;
		std::cout << "Please enter a country code (e.g. AT for Austria, FR for France): ";
        std::getline(std::cin, inputCountry);
		//Convert to uppercase to match the keys in the map
        for (auto& character : inputCountry) {
			character = std::toupper(character);
        };
		//Validate the input country
        if (availableCountries.count(inputCountry)) {
			validCountry = true;
			std::cout << "You selected: " << availableCountries[inputCountry] << " (" << inputCountry << ")" << std::endl;
        }
        else {
            std::cout << "Invalid input. Please enter one of the following available countries:" << std::endl;
            for (const auto& country : availableCountries) {
                std::cout << country.first << " - " << country.second << std::endl;
			};
        }
    };
    
	//Get the input year range
	int startYear, endYear;
	bool validStartYear = false;
	bool validEndYear = false;
	std::string startYearStr, endYearStr;
	//Get the smallest and largest year from the data
	std::vector<int> yearsRange = dataToCandlestick.getTotalYearsRange();
	//Validate the smallest year and largest year
    while (!validStartYear) {
        std::cout << "=======================================" << std::endl;
        std::cout << "Please enter a start year between and including " << yearsRange[0] << " - " << yearsRange[1] << ":" << std::endl;
        std::getline(std::cin, startYearStr);
        try {
            startYear = std::stoi(startYearStr);
            if (startYear >= yearsRange[0] && startYear <= yearsRange[1]) {
                validStartYear = true;
                std::cout << "Start Year Selected: " << startYear << std::endl;
            }
            else {
                std::cout << "Invalid start year. Please enter a year between" << yearsRange[0] << " and " << yearsRange[1] << std::endl;
            }
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Invalid input. Please enter a valid year between" << yearsRange[0] << " and " << yearsRange[1] << "." << std::endl;
        };
    };
    if (startYear == yearsRange[1]) {
        endYear = startYear;
        validEndYear = true;
        std::cout << "Processing Candlestick Table for " << endYear << std::endl;
    };
    while(!validEndYear){
        std::cout << "=======================================" << std::endl;
        std::cout << "Please enter an end year between and including " << startYear << " - " << yearsRange[1] << ":" << std::endl;
        std::getline(std::cin, endYearStr);
        try {
            endYear = std::stoi(endYearStr);
            if (endYear >= startYear && endYear <= yearsRange[1]) {
                validEndYear = true;
            }
            else {
                std::cout << "Invalid start year. Please enter a year between " << startYear << " and " << yearsRange[1] << "." << std::endl;
            }
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Invalid input. Please enter a valid year between ." << startYear << " and " << yearsRange[1] << "." << std::endl;
        };
    };
    if (startYear !=yearsRange[1]) {
        std::cout << "Processing data for: " << inputCountry << " from " << startYear << " to " << endYear << std::endl;
    };    

	//Get the candlestick data
	std::vector<Candlestick> candlesticks = dataToCandlestick.generateYearlyCandlesticks(inputCountry, startYear, endYear);

	return candlesticks;
};

void WeatherMain::generateCandlestickTable() {
    std::vector<Candlestick> candlesticks = getYearlyCandlestickInfo();
    printCandlestickTable(candlesticks);
};

//The following function was written with the help of Gemini
void WeatherMain::printCandlestickTable(std::vector<Candlestick>& candlesticks) {
    if (candlesticks.empty()) {
        std::cout << "No candlestick data to display for the selected range." << std::endl;
        return;
    };
    std::cout << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(6) << std::left << "Year";
    std::cout << std::setw(10) << std::right << "Open";
    std::cout << std::setw(10) << std::right << "High";
    std::cout << std::setw(10) << std::right << "Low";
    std::cout << std::setw(10) << std::right << "Close";
    std::cout << std::setw(10) << std::right << "Type";   
    std::cout << std::endl;

    std::cout << std::string(56, '-') << std::endl;

    for (const auto& candle : candlesticks) {
        // Accessing candle.date directly works because it's now an 'int'.
        std::cout << std::setw(6) << std::left << candle.date;
        std::cout << std::setw(10) << std::right << candle.open;
        std::cout << std::setw(10) << std::right << candle.high;
        std::cout << std::setw(10) << std::right << candle.low;
        std::cout << std::setw(10) << std::right << candle.close;

        // Convert CandlestickType enum to a displayable string
        std::string typeStr;
        if (candle.type == CandlestickType::Bullish) {
            typeStr = "Bullish";
        }
        else { // Based on your logic, if not Bullish, it's Bearish
            typeStr = "Bearish";
        }
        std::cout << std::setw(10) << std::right << typeStr;

        std::cout << std::endl; // Move to the next line after each row
    }
    std::cout << std::endl;
};

void WeatherMain::processUserOption(int option) {
    switch (option) {
    case 1:
		printHelp();
        break;
    case 2:
		seeAvailableCountries();
        break;
    case 3:
		generateCandlestickTable();
        break;
	case 4:
		break;
    default:
        std::cout << "Invalid choice. Please type a number between 1 and 6." << std::endl;
        break;
    }
};


