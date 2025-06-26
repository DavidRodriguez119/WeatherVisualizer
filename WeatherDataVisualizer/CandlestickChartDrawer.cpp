#include "CandlestickChartDrawer.h"
#include <cmath>

CandlestickChartDrawer::CandlestickChartDrawer(std::vector<Candlestick>inputCandlesticks) {
	candlesticks = inputCandlesticks;
	calculateMinMaxValues();
	drawChart();
};

void CandlestickChartDrawer::drawChart() {
	std::cout << "Drawing Candlestick Chart..." << std::endl;
};

void CandlestickChartDrawer::calculateMinMaxValues() {
	//////////////////////////	THE FOLLOWING CODE IS NOT COMPLETE YET & IT IS NOT WORKING 	//////////////////////////
	////Calculate the minimum and maximum values of temperature
	//if (candlesticks.empty())
	//{
	//	std::cerr << "No candlesticks available to calculate min/max values. Chart will be empty." << std::endl;
	//	minTemp = 0;
	//	maxTemp = 0;
	//	minTime = 0;
	//	maxTime = 0;
	//	return;
	//};

	//for (const Candlestick& candlestick : candlesticks) {
	//	if (candlestick.low < minTemp) {
	//		minTemp = candlestick.low;
	//	};
	//	if (candlestick.high > maxTemp) {
	//		maxTemp = candlestick.high;
	//	};
	//};

	////Add some padding to the min and max values
	//minTemp += 0.5;
	//maxTemp += 0.5;

	////Calculate the step size for the y-axis
	//int numberOfSteps = std::floor(CHART_HEIGHT/2);
	//double stepSize = (maxTemp - minTemp) / numberOfSteps;

	//for (int i = 0; i <= numberOfSteps; ++i) {
	//	stepsTemp.push_back(minTemp + i * (std::round(stepSize * 10) / 10));
	//	std::cout << "Step " << i << ": " << stepsTemp[i] << std::endl;
	//	return;
	//};

	//Calculate the minimum and maximum values of time

};
