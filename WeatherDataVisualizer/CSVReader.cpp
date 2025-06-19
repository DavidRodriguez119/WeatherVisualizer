#include "CSVReader.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

const std::vector<std::string> countryCodes = { "AT", "BE", "BG", "CH", "CZ", "DE", "DK", "EE", "ES", "FI", "FR", "GB", "GR", "HR", "HU",
    "IE", "IT", "LT", "LU", "LV", "NL", "NO", "PL", "PT", "RO", "SE", "SI", "SK" };

CSVReader::CSVReader() {

};

std::vector<WeatherData> CSVReader::readCSV(const std::string& csvFile) {
    std::vector<WeatherData> entries;
    std::ifstream file{ csvFile };
    std::string line;
    if (file.is_open()) {
        //SKipping the header line (code obtained from geminiAI)
        if (std::getline(file, line)) {
            /*std::cout << "Skipped header: " << line << std::endl;*/
        }
        while (std::getline(file, line))
        {
            try {
                std::vector<std::string> tokens = tokenize(line, ',');
                if (tokens.size() == 29) {
                    WeatherData entry = stringsToWeatherData(tokens);
                    entries.push_back(entry);
                }
                else {
                    std::cout << "CSVReader::readCSV: Skipping line because of incorrect number of tokens" << std::endl;
                }

            }
            catch (const std::exception& e) {
                std::cout << "CSVReader::readCSV: Error while reading line: " << line << std::endl;
            };
        };
        file.close();
    }
    else {
        std::cerr << "CSVReader::readCSV: Could not open file: " << csvFile << std::endl;
    };

    std::cout << "Entries Number: " << entries.size() << std::endl;
    return entries;
};

std::vector<std::string> CSVReader::tokenize(std::string csvLine, char separator) {
    //Vector: name - tokens, input - strings
    std::vector<std::string> tokens;

    //Initialize variables: start, end & token
    signed int start, end;
    std::string token;

    //Find the first non-separator character in csvLine
    start = csvLine.find_first_not_of(separator, 0);

    do {
        //Find the next separator character after start
        end = csvLine.find_first_of(separator, start);

        //Condition to break the loop
        if (start == csvLine.length() || start == end) {
            break;
        }
        //Token found!
        if (end != std::string::npos) {
            token = csvLine.substr(start, end - start);
        }
        else { //when there is a word but no separator at the end
            token = csvLine.substr(start, csvLine.length() - start);
        };

        //Add the token to the vector
        tokens.push_back(token);

        //Update start to the next character after the separator
        start = end + 1;

    } while (end != std::string::npos);
    {
        return tokens;
    }

    return tokens;
};

WeatherData CSVReader::stringsToWeatherData(std::vector<std::string> strings) {
	//Create the variables that are going to be used to fill the WeatherData object
    std::string date;
    std::string time;
    std::map<std::string, double> temps;
    if (strings.size() != (countryCodes.size() + 1) || strings.empty()) {
        std::cerr << "CSVReader::stringsToWeatherData - Error: Invalid line format!" << std::endl;
        throw std::exception{};
    };

    try {
        //Divide the first string into date and time
		size_t foundTPos = strings[0].find_first_of('T');
        date = strings[0].substr(0, foundTPos);
		time = strings[0].substr(foundTPos + 1);
		time.pop_back(); //Remove the last character 'Z' from the time string
        //Fill the temps map with the country codes and their corresponding temperatures
        for (int i = 0; i < countryCodes.size(); ++i) {
			temps[countryCodes[i]] = std::stod(strings[i + 1]);
        };
    }
    catch (const std::exception& error) {
        std::cout << "CSVReader::stringsToWeatherData - Error: " << std::endl;
        throw;
    };

	WeatherData entry{date, time, temps};   
    return entry;
};