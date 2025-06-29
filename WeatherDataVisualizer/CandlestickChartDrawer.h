#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include "Candlestick.h"

constexpr int  CHART_WIDTH = 80;
constexpr int  CHART_HEIGHT = 30;
constexpr int  CHART_LEFT_MARGIN = 10;
constexpr int  CANDLE_PADDING = 2;
constexpr int  CANDLE_WIDTH = 2;
constexpr int  CANDLES_PER_PAGE = 20;

constexpr char CANDLESTICK_SHADOW = '|';
constexpr char CANDLESTICK_BODY_UP = '█';
constexpr char CANDLESTICK_BODY_DOWN = '#';

constexpr const char* COLOR_RED = "\x1b[31m";
constexpr const char* COLOR_GREEN = "\x1b[32m";
constexpr const char* COLOR_RESET = "\x1b[0m";

class CandlestickChartDrawer {
public:
    explicit CandlestickChartDrawer(const std::vector<Candlestick>& data);
    void drawChart();

private:
    std::vector<Candlestick> candlesticks;
    double minTemp, maxTemp, tempRange;

    void calculateMinMaxValues();
    void drawTitleAndYAxis(int numCandles);
    void drawCandlestick(const std::vector<Candlestick>& pageCandles);
};
