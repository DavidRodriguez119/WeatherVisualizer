#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "Candlestick.h"

//Constants for chart dimensions 
//One unit represents one character in the console
const int CHART_WIDTH = 80; 
const int CHART_HEIGHT = 30;
const int CHART_LEFT_MARGIN = 10;

//Constants for candlestick representation characters
const char CANDLESTICK_SHADOW = '|';   // Represents the stalk used to show the highest and lowest values
const char CANDLESTICK_BODY_UP = '█';  // Represents the body of an upward candlestick

class CandlestickChartDrawer
{
	public:
		CandlestickChartDrawer(std::vector<Candlestick>inputCandlesticks);
		void drawChart();

	private:
		std::vector<Candlestick> candlesticks;

		//Variables necessary for drawing
		double minTemp;
		double maxTemp;
		std::vector<double> stepsTemp;
		double minTime;
		double maxTime;
		std::vector<int> stepSizeTime;

		void calculateMinMaxValues();
};
