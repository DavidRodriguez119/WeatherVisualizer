#pragma once
#include <vector>
#include "Candlestick.h"

//A class to handle prediction calculations on candlestick data.
class Prediction
{
public:
    static std::vector<double> calculateSMA(const std::vector<Candlestick>& candlesticks, int period);
};

