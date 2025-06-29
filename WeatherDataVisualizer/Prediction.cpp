#include "Prediction.h"
#include <numeric> 

std::vector<double> Prediction::calculateSMA(const std::vector<Candlestick>& candlesticks, int period)
{
    std::vector<double> smaValues;
    if (period <= 0 || candlesticks.size() < period) {
        // Not enough data to calculate SMA for the given period.
        return smaValues; 
    }

    // The first 'period - 1' values cannot be calculated, so we can represent them as 0 or another indicator.
    for (int i = 0; i < period - 1; ++i) {
        smaValues.push_back(0.0); 
    }

    for (size_t i = period - 1; i < candlesticks.size(); ++i) {
        double sum = 0.0;
        // Sum the 'close' prices of the previous 'period' candlesticks.
        for (int j = 0; j < period; ++j) {
            sum += candlesticks[i - j].close;
        }
        smaValues.push_back(sum / period);
    }

    return smaValues;
}

std::vector<double> Prediction::calculateEMA(const std::vector<Candlestick>& candlesticks, int period)
{
    std::vector<double> emaValues;
    if (period <= 0 || candlesticks.size() < period) {
        return emaValues; // Not enough data
    }

    // The multiplier for weighting the EMA
    double multiplier = 2.0 / (period + 1);

    // Start with the SMA of the first period as the initial EMA
    double initialSma = 0.0;
    for (int i = 0; i < period; ++i) {
        initialSma += candlesticks[i].close;
    }
    initialSma /= period;

    // Pad the beginning of the vector
    for (int i = 0; i < period - 1; ++i) {
        emaValues.push_back(0.0);
    }
    emaValues.push_back(initialSma);

    // Calculate EMA for the rest of the data
    for (size_t i = period; i < candlesticks.size(); ++i) {
        double ema = (candlesticks[i].close - emaValues.back()) * multiplier + emaValues.back();
        emaValues.push_back(ema);
    }

    return emaValues;
}