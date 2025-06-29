#include "CandlestickChartDrawer.h"
#include <limits>
#include <cmath>

CandlestickChartDrawer::CandlestickChartDrawer(const std::vector<Candlestick>& input)
    : candlesticks(input),
    minTemp(std::numeric_limits<double>::max()),
    maxTemp(std::numeric_limits<double>::lowest()),
    tempRange(0.0)
{
    calculateMinMaxValues();
}

void CandlestickChartDrawer::drawChart() {
    int totalCandles = (int)candlesticks.size();
    int pages = (totalCandles + CANDLES_PER_PAGE - 1) / CANDLES_PER_PAGE;

    for (int page = 0; page < pages; ++page) {
        int start = page * CANDLES_PER_PAGE;
        int end = std::min(start + CANDLES_PER_PAGE, totalCandles);
        std::vector<Candlestick> pageCandles(
            candlesticks.begin() + start,
            candlesticks.begin() + end
        );

        std::cout << "\n--- Page " << page + 1 << " of " << pages << " ---\n";
        drawTitleAndYAxis((int)pageCandles.size());
        drawCandlestick(pageCandles);

        if (page + 1 < pages) {
            std::cout << "\nPress ENTER to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::cout << "\nLegend:\n"
        << " " << CANDLESTICK_BODY_UP << " Bullish (Open ≥ Close)\n"
        << " " << CANDLESTICK_BODY_DOWN << " Bearish (Open <  Close)\n"
        << " " << CANDLESTICK_SHADOW << " Range (High–Low)\n"
        << "Candlestick Chart drawn successfully!\n\n";
}

void CandlestickChartDrawer::calculateMinMaxValues() {
    if (candlesticks.empty()) {
        minTemp = maxTemp = tempRange = 0;
        return;
    }
    for (const auto& c : candlesticks) {
        minTemp = std::min(minTemp, c.low);
        maxTemp = std::max(maxTemp, c.high);
    }
    minTemp -= 2;
    maxTemp += 2;
    tempRange = maxTemp - minTemp;
}

void CandlestickChartDrawer::drawTitleAndYAxis(int numCandles) {
    int totalW = numCandles * (CANDLE_WIDTH + CANDLE_PADDING);
    std::string title = "CANDLESTICK TEMPERATURE CHART";
    int center = CHART_LEFT_MARGIN + totalW / 2 - (int)title.size() / 2;
    std::cout << std::string(center, ' ') << title << "\n\n";
}

void CandlestickChartDrawer::drawCandlestick(const std::vector<Candlestick>& pageCandles) {
    int numCandles = (int)pageCandles.size();
    int totalW = numCandles * (CANDLE_WIDTH + CANDLE_PADDING);

    // Prepare empty grid
    std::vector<std::string> grid(CHART_HEIGHT + 1, std::string(totalW, ' '));
    auto mapRow = [&](double t) {
        return int((maxTemp - t) / tempRange * CHART_HEIGHT);
        };

    // Draw each candle
    std::vector<int> avgRows;
    for (int i = 0; i < numCandles; ++i) {
        const auto& c = pageCandles[i];
        int oR = mapRow(c.open), hR = mapRow(c.high),
            lR = mapRow(c.low), cR = mapRow(c.close);
        int col = i * (CANDLE_WIDTH + CANDLE_PADDING) + CANDLE_PADDING / 2;

        // Shadow
        for (int r = std::min(hR, lR); r <= std::max(hR, lR); ++r)
            if (r >= 0 && r <= CHART_HEIGHT)
                for (int w = 0; w < CANDLE_WIDTH; ++w)
                    grid[r][col + w] = CANDLESTICK_SHADOW;

        // Body
        char body = (c.type == CandlestickType::Bullish)
            ? CANDLESTICK_BODY_UP
            : CANDLESTICK_BODY_DOWN;
        for (int r = std::min(oR, cR); r <= std::max(oR, cR); ++r)
            if (r >= 0 && r <= CHART_HEIGHT)
                for (int w = 0; w < CANDLE_WIDTH; ++w)
                    grid[r][col + w] = body;

        // Average line
        avgRows.push_back(mapRow((c.high + c.low) / 2.0));
    }

    // Dashed average lines
    for (int r : avgRows)
        if (r >= 0 && r <= CHART_HEIGHT)
            for (int x = 0; x < totalW; x += 2)
                grid[r][x] = '-';

    // Print Y‑axis + grid
    for (int r = 0; r <= CHART_HEIGHT; ++r) {
        double temp = maxTemp - r * (tempRange / CHART_HEIGHT);
        std::cout << std::setw(CHART_LEFT_MARGIN - 1)
            << std::fixed << std::setprecision(1) << temp << " |";
        for (char ch : grid[r]) {
            if (ch == CANDLESTICK_BODY_UP)
                std::cout << COLOR_GREEN << ch << COLOR_RESET;
            else if (ch == CANDLESTICK_BODY_DOWN)
                std::cout << COLOR_RED << ch << COLOR_RESET;
            else
                std::cout << ch;
        }
        std::cout << "\n";
    }

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
