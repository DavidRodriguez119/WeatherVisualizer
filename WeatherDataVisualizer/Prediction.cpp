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