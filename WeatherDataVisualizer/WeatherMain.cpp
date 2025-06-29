#include "WeatherMain.h"
#include "WeatherMain.h"
#include "CSVReader.h"
#include "WeatherData.h"
#include <iomanip>
#include <limits>
#include "CandlestickChartDrawer.h"

//Constructor
WeatherMain::WeatherMain() {
}

void WeatherMain::init() {
    while (true) {
        printMenu();
        int input = getIntegerInput("Please enter your choice (1-6): ", 1, 6);
        processUserOption(input);
    }
}

void WeatherMain::printMenu() {
    std::cout << "=======================================" << std::endl;
    std::cout << "1. Print Help" << std::endl;
    std::cout << "2. See Available Countries" << std::endl;
    std::cout << "3. Plot Candlestick Chart " << std::endl;
    std::cout << "4. Generate Candlestick Graph" << std::endl;
    std::cout << "5. Predict Temperature Trend " << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "=======================================" << std::endl;
}

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
        generateCandlestickGraph();
        break;
    case 5:
        generatePrediction();
        break;
    case 6:
        std::cout << "Exiting application. Goodbye!" << std::endl;
        exit(0);
    default:
        std::cout << "Invalid choice. Please type a number between 1 and 6." << std::endl;
        break;
    }
}

void WeatherMain::printHelp() {
    std::cout << "Help - you can use this app to visualize (table or graph) weather data for a particular country in Europe." << std::endl;
}

void WeatherMain::seeAvailableCountries() {
    std::cout << "Available countries: " << std::endl;
    std::map<std::string, std::string> countries = dataToCandlestick.getAvailableCountries();
    for (const auto& country : countries) {
        std::cout << country.first << " - " << country.second << std::endl;
    }
}

std::vector<Candlestick> WeatherMain::getYearlyCandlestickInfo() {
    std::map<std::string, std::string> availableCountries = dataToCandlestick.getAvailableCountries();
    std::string inputCountry;
    while (true) {
        std::cout << "=======================================" << std::endl;
        std::cout << "Please enter a country code (e.g. AT for Austria, FR for France): ";
        std::getline(std::cin, inputCountry);
        if (inputCountry.empty()) continue;
        for (auto& c : inputCountry) c = std::toupper(c);
        if (availableCountries.count(inputCountry)) {
            std::cout << "You selected: " << availableCountries[inputCountry]
                << " (" << inputCountry << ")" << std::endl;
            break;
        }
        std::cout << "Invalid input. Please enter one of the following available countries:" << std::endl;
        for (const auto& country : availableCountries) {
            std::cout << country.first << " - " << country.second << std::endl;
        }
    }

    std::vector<int> yearsRange = dataToCandlestick.getTotalYearsRange();
    std::string startPrompt = "Please enter a start year between and including "
        + std::to_string(yearsRange[0]) + " - " + std::to_string(yearsRange[1]) + ": ";
    int startYear = getIntegerInput(startPrompt, yearsRange[0], yearsRange[1]);

    int endYear;
    if (startYear == yearsRange[1]) {
        endYear = startYear;
    }
    else {
        std::string endPrompt = "Please enter an end year between and including "
            + std::to_string(startYear) + " - " + std::to_string(yearsRange[1]) + ": ";
        endYear = getIntegerInput(endPrompt, startYear, yearsRange[1]);
    }

    std::cout << "Processing data for: " << inputCountry
        << " from " << startYear << " to " << endYear << std::endl;

    return dataToCandlestick.generateYearlyCandlesticks(inputCountry, startYear, endYear);
}

void WeatherMain::generateCandlestickTable() {
    std::vector<Candlestick> candlesticks = getYearlyCandlestickInfo();
    printCandlestickTable(candlesticks);
}

void WeatherMain::printCandlestickTable(const std::vector<Candlestick>& candlesticks) {
    if (candlesticks.empty()) {
        std::cout << "No candlestick data to display for the selected range." << std::endl;
        return;
    }
    std::cout << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(6) << std::left << "Year"
        << std::setw(10) << std::right << "Open"
        << std::setw(10) << std::right << "High"
        << std::setw(10) << std::right << "Low"
        << std::setw(10) << std::right << "Close"
        << std::setw(10) << std::right << "Type"
        << std::endl;
    std::cout << std::string(56, '-') << std::endl;

    for (const auto& candle : candlesticks) {
        std::cout << std::setw(6) << std::left << candle.date
            << std::setw(10) << std::right << candle.open
            << std::setw(10) << std::right << candle.high
            << std::setw(10) << std::right << candle.low
            << std::setw(10) << std::right << candle.close;
        std::string typeStr = (candle.type == CandlestickType::Bullish) ? "Bullish" : "Bearish";
        std::cout << std::setw(10) << std::right << typeStr
            << std::endl;
    }
    std::cout << std::endl;
}

void WeatherMain::generateCandlestickGraph() {
    std::vector<Candlestick> candlesticks = getYearlyCandlestickInfo();
    if (candlesticks.empty()) return;
    CandlestickChartDrawer chart{ candlesticks };
    chart.drawChart();
}

void WeatherMain::generatePrediction() {
    std::cout << "\n--- Generate Temperature Prediction ---" << std::endl;
    std::vector<Candlestick> candlesticks = getYearlyCandlestickInfo();
    if (candlesticks.size() < 3) {
        std::cout << "Not enough data for prediction. Please select at least 3 years of data." << std::endl;
        return;
    }
    std::cout << "\nSelect a prediction model:" << std::endl;
    std::cout << "1. Simple Moving Average (SMA) - Gives equal weight to all past periods." << std::endl;
    std::cout << "2. Exponential Moving Average (EMA) - Gives more weight to recent periods." << std::endl;
    int modelChoice = getIntegerInput("Enter your choice (1-2): ", 1, 2);

    int maxPeriod = static_cast<int>(candlesticks.size());
    std::string periodPrompt = "Enter the period (number of years) for the average (2-"
        + std::to_string(maxPeriod) + "): ";
    int period = getIntegerInput(periodPrompt, 2, maxPeriod);

    std::vector<double> predictions;
    std::string modelName;
    if (modelChoice == 1) {
        modelName = "SMA";
        predictions = Prediction::calculateSMA(candlesticks, period);
    }
    else {
        modelName = "EMA";
        predictions = Prediction::calculateEMA(candlesticks, period);
    }

    std::cout << "\n--- Prediction Results (" << modelName << " over " << period << " years) ---" << std::endl;
    std::cout << std::fixed << std::setprecision(3);
    std::cout << std::setw(6) << std::left << "Year"
        << std::setw(15) << std::right << "Actual Close"
        << std::setw(20) << std::right << "Predicted (" << modelName << ")"
        << std::endl;
    std::cout << std::string(41, '-') << std::endl;

    for (size_t i = 0; i < candlesticks.size(); ++i) {
        std::cout << std::setw(6) << std::left << candlesticks[i].date
            << std::setw(15) << std::right << candlesticks[i].close;
        if (i < predictions.size() && predictions[i] != 0.0) {
            std::cout << std::setw(20) << std::right << predictions[i];
        }
        else {
            std::cout << std::setw(20) << std::right << "N/A";
        }
        std::cout << std::endl;
    }
}

int WeatherMain::getIntegerInput(const std::string& prompt, int min, int max) {
    int value;
    std::string line;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, line);
        if (line.empty()) continue;
        try {
            value = std::stoi(line);
            if (value >= min && value <= max) return value;
            std::cout << "Invalid range. Please enter a number between "
                << min << " and " << max << "." << std::endl;
        }
        catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a whole number." << std::endl;
        }
        catch (const std::out_of_range&) {
            std::cout << "Input is out of range. Please enter a smaller number." << std::endl;
        }
    }
}
