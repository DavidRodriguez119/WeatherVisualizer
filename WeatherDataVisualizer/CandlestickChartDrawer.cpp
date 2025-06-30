#include "CandlestickChartDrawer.h"
#include <limits>
#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

CandlestickChartDrawer::CandlestickChartDrawer(const std::vector<Candlestick>& input)
    : candlesticks(input),
    minTemp(std::numeric_limits<double>::max()),
    maxTemp(std::numeric_limits<double>::lowest()),
    tempRange(0.0)
{
    calculateMinMaxValues();
}

void CandlestickChartDrawer::drawChart() {
    //Total amount of Candlesticks to be drawn
    int totalCandles = candlesticks.size();

    //Calculate the amount of graphs or "pages" based on the amount of candlesticks that need to be drawn
    int pages = (totalCandles + CANDLES_PER_PAGE - 1) / CANDLES_PER_PAGE;

    //Repeat the following code the same amount of times as pages required
    for (int page = 0; page < pages; ++page) {
        //start and end indexes of the candlesticks that are going to be drawn in the current page
        int start = page * CANDLES_PER_PAGE;
        int end = std::min(start + CANDLES_PER_PAGE, totalCandles);
        //Isolate the Candlesticks of the current page
        std::vector<Candlestick> pageCandles(
            candlesticks.begin() + start,
            candlesticks.begin() + end
        );

        std::cout << "\n--- Page " << page + 1 << " of " << pages << " ---\n";
        drawTitle(pageCandles.size());
        drawCandlestick(pageCandles);

        //User typing Enter is required to proceed to the next page
        //The following 4 lines of code were suggested by Gemini AI
        if (page + 1 < pages) {
            std::cout << "\nPress ENTER to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    //Display Legend to better explain the information shown in the graph
    std::cout << "\nLegend:\n"
        << " " << CANDLESTICK_BODY_UP << " Bullish (Open <= Close)\n"
        << " " << CANDLESTICK_BODY_DOWN << " Bearish (Open >  Close)\n"
        << " " << CANDLESTICK_SHADOW << " Range (Highest to Lowest value)\n"
        << "Candlestick Chart drawn successfully!\n\n";
}

void CandlestickChartDrawer::calculateMinMaxValues() {
    if (candlesticks.empty()) {
        minTemp = maxTemp = tempRange = 0;
        return;
    }
    for (const auto& candlestick : candlesticks) {
        minTemp = std::min(minTemp, candlestick.low);
        maxTemp = std::max(maxTemp, candlestick.high);
    }
    minTemp -= 2;
    maxTemp += 2;
    tempRange = maxTemp - minTemp;
}

void CandlestickChartDrawer::drawTitle(int numCandles) {
    //Calculate the total width of the graph
    int totalWidth = numCandles * (CANDLE_WIDTH + CANDLE_PADDING);
    std::string title = "CANDLESTICK TEMPERATURE CHART";
    //Calculate the starting point of the title
    int center = CHART_LEFT_MARGIN + totalWidth / 2 - title.size() / 2;
    std::cout << std::string(center, ' ') << title << "\n\n";
}

void CandlestickChartDrawer::drawCandlestick(const std::vector<Candlestick>& pageCandles) {
    //Get the number of candles in the chart and the corresponding width
    int numCandles = pageCandles.size();
    int totalW = numCandles * (CANDLE_WIDTH + CANDLE_PADDING);

    // Prepare empty grid based on the graph dimensions
    std::vector<std::string> grid(CHART_HEIGHT + 1, std::string(totalW, ' '));

    //Lambda function suggested by Gemini AI to properly assign a row within the graph grid
    auto mapRow = [&](double t) {
        return int((maxTemp - t) / tempRange * CHART_HEIGHT);
    };

    // Draw each candle
    //Loop over the same amount as the number of candles to be drawn in the current page
    for (int i = 0; i < numCandles; ++i) {
        //Get the Candle of the current iteration
        const Candlestick& candle = pageCandles[i];
        //Assign a row to every component of the current Candlestick
        int openRow = mapRow(candle.open), highRow = mapRow(candle.high),
            lowRow = mapRow(candle.low), closeRow = mapRow(candle.close);
        //Assign a column based on the index, graph width and added padding around the candlestick
        int col = i * (CANDLE_WIDTH + CANDLE_PADDING) + CANDLE_PADDING / 2;

        // Draw the Shadow
        for (int row = std::min(highRow, lowRow); row <= std::max(highRow, lowRow); ++row) {
            if (row >= 0 && row <= CHART_HEIGHT) {
                for (int w = 0; w < CANDLE_WIDTH; ++w) {
                    grid[row][col + w] = CANDLESTICK_SHADOW;
                };
            };
        };

        // Define the Character that is going to be used for the body based on the Candlestick type
        char bodyCharacter;
        if (candle.type == CandlestickType::Bullish) {
            bodyCharacter = CANDLESTICK_BODY_UP;
        }
        else {
            bodyCharacter = CANDLESTICK_BODY_DOWN;
        };

        //Draw the body of the Candlestick
        for (int row = std::min(openRow, closeRow); row <= std::max(openRow, closeRow); ++row) {
            if (row >= 0 && row <= CHART_HEIGHT) {
                for (int w = 0; w < CANDLE_WIDTH; ++w) {
                    grid[row][col + w] = bodyCharacter;
                };
            };
        };
    };

    // Print Y‑axis + grid
    for (int row = 0; row <= CHART_HEIGHT; ++row) {
        //Calculate the temperature to display
        double temp = maxTemp - row * (tempRange / CHART_HEIGHT);
        std::cout << std::setw(CHART_LEFT_MARGIN - 1)
            << std::fixed << std::setprecision(1) << temp << " |";
        for (char ch : grid[row]) {
            if (ch == CANDLESTICK_BODY_UP) {
                std::cout << COLOR_GREEN << ch << COLOR_RESET;
            }
            else if (ch == CANDLESTICK_BODY_DOWN) {
                std::cout << COLOR_RED << ch << COLOR_RESET;
            }
            else {
                std::cout << ch;
            };
        };
        std::cout << "\n";
    };

    // X‑axis markers
    std::cout << std::setw(CHART_LEFT_MARGIN) << " ";
    for (int i = 0; i < numCandles; ++i)
        std::cout << std::string(CANDLE_WIDTH / 2, ' ')
        << '+'
        << std::string(CANDLE_WIDTH - CANDLE_WIDTH / 2 + CANDLE_PADDING - 1, ' ');
    std::cout << "\n";

    // Year labels (last two digits)
    std::cout << std::setw(CHART_LEFT_MARGIN) << " ";
    for (int i = 0; i < numCandles; ++i) {
        auto s = std::to_string(pageCandles[i].date).substr(2);
        int lp = (CANDLE_WIDTH + CANDLE_PADDING - 2) / 2;
        int rp = CANDLE_WIDTH + CANDLE_PADDING - 2 - lp;
        std::cout << std::string(lp, ' ') << s << std::string(rp, ' ');
    }
    std::cout << "\n";
}
