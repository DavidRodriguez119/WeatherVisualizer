#include "CandlestickChartDrawer.h"
#include <cmath>
#include <iomanip>



CandlestickChartDrawer::CandlestickChartDrawer(const std::vector<Candlestick>& inputCandlesticks)
	:candlesticks(inputCandlesticks),
	minTemp(std::numeric_limits<double>::max()), 	//Initialize method for min and max values suggested by Gemini AI
	maxTemp(std::numeric_limits<double>::lowest()), //Initialize method for min and max values suggested by Gemini AI
	tempRange(0.0)
{
	calculateMinMaxValues();
};

void CandlestickChartDrawer::drawChart() {
    std::cout << "Drawing Candlestick Chart..." << std::endl;
    drawTitleAndYAxis();
    drawCandlestick();
    std::cout << "Candlestick Chart drawn successfully!\n" << std::endl;

    // Add legend
    std::cout << "Legend:\n";
    std::cout << " " << CANDLESTICK_BODY_UP << "  Bullish (Open > Close)\n";
    std::cout << " " << CANDLESTICK_BODY_DOWN << "  Bearish (Open < Close)\n";
    std::cout << " " << CANDLESTICK_SHADOW << "  Range (High to Low)\n";
}

void CandlestickChartDrawer::calculateMinMaxValues() {
    if (candlesticks.empty()) {
        std::cerr << "No candlesticks available to calculate min/max values.\n";
        minTemp = maxTemp = tempRange = 0;
        return;
    }

    for (const Candlestick& candle : candlesticks) {
        if (candle.low < minTemp) minTemp = candle.low;
        if (candle.high > maxTemp) maxTemp = candle.high;
    }

    // Add padding for better spacing
    minTemp -= 2;
    maxTemp += 2;
    tempRange = maxTemp - minTemp;

    std::cout << "Min Temp: " << minTemp << ", Max Temp: " << maxTemp << std::endl;
}

void CandlestickChartDrawer::drawTitleAndYAxis() {
    std::string title = "CANDLESTICK TEMPERATURE CHART";
    int center = CHART_LEFT_MARGIN + (CHART_WIDTH / 2) - (title.size() / 2);
    std::cout << std::string(center, ' ') << title << "\n\n";
}

void CandlestickChartDrawer::drawCandlestick() {
    int numCandles = std::min((int)candlesticks.size(), CHART_WIDTH / (CANDLE_WIDTH + CANDLE_PADDING));
    int totalChartWidth = numCandles * (CANDLE_WIDTH + CANDLE_PADDING);
    std::vector<std::string> grid(CHART_HEIGHT + 1, std::string(totalChartWidth, ' '));

    for (int i = 0; i < numCandles; ++i) {
        const Candlestick& candle = candlesticks[i];
        auto mapTempToRow = [&](double temp) {
            return static_cast<int>((maxTemp - temp) / tempRange * CHART_HEIGHT);
        };

        int colStart = i * (CANDLE_WIDTH + CANDLE_PADDING) + (CANDLE_PADDING / 2);
        int highRow = mapTempToRow(candle.high);
        int lowRow = mapTempToRow(candle.low);
        int openRow = mapTempToRow(candle.open);
        int closeRow = mapTempToRow(candle.close);

        // Draw shadow
        for (int row = std::min(highRow, lowRow); row <= std::max(highRow, lowRow); ++row) {
            for (int w = 0; w < CANDLE_WIDTH; ++w) {
                int col = colStart + w;
                if (row >= 0 && row <= CHART_HEIGHT && col < totalChartWidth) {
                    grid[row][col] = CANDLESTICK_SHADOW;
                }
            }
        }

        // Draw body
        char bodyChar = (candle.type == CandlestickType::Bullish) ? CANDLESTICK_BODY_UP : CANDLESTICK_BODY_DOWN;
        for (int row = std::min(openRow, closeRow); row <= std::max(openRow, closeRow); ++row) {
            for (int w = 0; w < CANDLE_WIDTH; ++w) {
                int col = colStart + w;
                if (row >= 0 && row <= CHART_HEIGHT && col < totalChartWidth) {
                    grid[row][col] = bodyChar;
                }
            }
        }
    }

    // Draw Y-axis + chart rows
    for (int row = 0; row <= CHART_HEIGHT; ++row) {
        double temp = maxTemp - row * (tempRange / CHART_HEIGHT);
        std::cout << std::setw(CHART_LEFT_MARGIN - 1)
                  << std::fixed << std::setprecision(1) << temp << " |";
        std::cout << grid[row] << std::endl;
    }

    // Draw X-axis markers
    std::cout << std::setw(CHART_LEFT_MARGIN) << " ";
    for (int i = 0; i < numCandles; ++i) {
        for (int c = 0; c < CANDLE_WIDTH + CANDLE_PADDING; ++c) {
            std::cout << ((c == CANDLE_WIDTH / 2) ? '+' : ' ');
        }
    }
    std::cout << std::endl;

    // Draw year labels
    std::cout << std::setw(CHART_LEFT_MARGIN) << " ";
    for (int i = 0; i < numCandles; ++i) {
        std::string year = std::to_string(candlesticks[i].date);
        for (int c = 0; c < CANDLE_WIDTH + CANDLE_PADDING; ++c) {
            std::cout << ((c == CANDLE_WIDTH / 2) ? year.substr(2) : " ");
        }
    }
    std::cout << std::endl;
}