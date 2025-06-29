#pragma once
#include <vector>
#include "Candlestick.h"

//A class to handle prediction calculations on candlestick data.
class Prediction
{
public:
	static std::vector<double> calculateSMA(const std::vector<Candlestick>& candlesticks, int period); // Calculate Simple Moving Average (SMA)
	static std::vector<double> calculateEMA(const std::vector<Candlestick>& candlesticks, int period); // Calculate Exponential Moving Average (EMA) idea suggested by inbuilt copilot
};

