#include "CandlestickChartDrawer.h"
#include <cmath>


CandlestickChartDrawer::CandlestickChartDrawer(const std::vector<Candlestick>& inputCandlesticks)
	:candlesticks(inputCandlesticks), 
	minTemp(std::numeric_limits<double>::max()), 	//Initialize method for min and max values suggested by Gemini AI
	maxTemp(std::numeric_limits<double>::lowest()), //Initialize method for min and max values suggested by Gemini AI
	tempRange(0.0)
{
	calculateMinMaxValues();
	drawTitleAndYAxis();
	drawCandlestick();
};

void CandlestickChartDrawer::drawChart() {
	std::cout << "Drawing Candlestick Chart..." << std::endl;
};

void CandlestickChartDrawer::calculateMinMaxValues() {
	//Calculate the minimum and maximum values of temperature
	if (candlesticks.empty())
	{
		std::cerr << "No candlesticks available to calculate min/max values. Chart will be empty." << std::endl;
		minTemp = 0;
		maxTemp = 0;
		tempRange = 0;
		return;
	};

	for (const Candlestick& candlestick : candlesticks) {
		if (candlestick.low < minTemp) {
			minTemp = candlestick.low;
		};
		if (candlestick.high > maxTemp) {
			maxTemp = candlestick.high;
		};
	};

	tempRange = maxTemp - minTemp;

	//Add some padding to the min and max values
	minTemp -= 1;
	maxTemp += 1;

	std::cout << "Min Temp: " << minTemp << ", Max Temp: " << maxTemp << std::endl;
};

void CandlestickChartDrawer::drawTitleAndYAxis() {

};

void CandlestickChartDrawer::drawCandlestick() {
	
};

