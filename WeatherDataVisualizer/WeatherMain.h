#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "DataToCandlestick.h"
#include "Prediction.h"
#include "Candlestick.h"

class WeatherMain
{
public:
    WeatherMain();
    void init();

private:

    /** Print the menu to the user */
    void printMenu();

    /** Process the user option and call the appropriate function */
    void processUserOption(int option);

    /** Access help */
    void printHelp();

    /** Print a list of all the available countries with abbreviations */
    void seeAvailableCountries();

    /** Input the user for information to print the yearly candlestick table */
    std::vector<Candlestick> getYearlyCandlestickInfo();

    /** Asks the user for input and then calls the function to print the table */
    void generateCandlestickTable();

    /** Print candlestick table */
    void printCandlestickTable(const std::vector<Candlestick>& candlesticks);

    /** Collects information from the user to print a candlestick graph */
    void generateCandlestickGraph();

    /** Generates a yearly temperature prediction based on the three previous years of data */
    void generatePrediction();

    /** Get an integer input from the user with a prompt and range validation */
    int getIntegerInput(const std::string& prompt, int min, int max);

    /** Get all the raw data as WeatherData objects
      * Initialize the class in charge of filtering and translating into candlestick data */
    DataToCandlestick dataToCandlestick{ "weather_data_EU_1980-2019_temp_only.csv" };
};

