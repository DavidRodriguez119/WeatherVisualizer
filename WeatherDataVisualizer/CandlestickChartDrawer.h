#pragma once

#include <vector>
#include "Candlestick.h"

constexpr int  CHART_HEIGHT = 30;
constexpr int  CHART_LEFT_MARGIN = 10;
constexpr int  CANDLE_PADDING = 2;
constexpr int  CANDLE_WIDTH = 2;
constexpr int  CANDLES_PER_PAGE = 20;

constexpr char CANDLESTICK_SHADOW = '|';
constexpr char CANDLESTICK_BODY_UP = '#';
constexpr char CANDLESTICK_BODY_DOWN = '$';

constexpr const char* COLOR_RED = "\x1b[31m";
constexpr const char* COLOR_GREEN = "\x1b[32m";
constexpr const char* COLOR_RESET = "\x1b[0m";

class CandlestickChartDrawer {
public:

    /**Constructor: Obtain the Candlestick data necessary to draw the graph. Initialize function to calculate min & max values*/
    explicit CandlestickChartDrawer(const std::vector<Candlestick>& data);
    /**Draw the Candlestick Graph using the data that was passed to the constructor*/
    void drawChart();

private:
    std::vector<Candlestick> candlesticks;
    double minTemp, maxTemp, tempRange;
    /**Using the data that was saved in candlesticks, determine the min and max Temperature values to which the graph will be drawn*/
    void calculateMinMaxValues();
    /**Determine the y-axis labels */
    void drawTitle(int numCandles);
    /**Draw all the Candlesticks that fit in one graph. Create a second graph if necessary*/
    void drawCandlestick(const std::vector<Candlestick>& pageCandles);
};