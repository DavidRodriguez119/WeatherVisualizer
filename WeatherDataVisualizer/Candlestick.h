#pragma once
#include <string>

//Create an enum class for the type of candlestick
enum class CandlestickType
{
	Bullish, // price went up
	Bearish  // price went down
};

class Candlestick
{
	public:
		Candlestick(std::string _date,
			CandlestickType _type,
			double _open,
			double _high,
			double _low,
			double _close);

		std::string date;
		CandlestickType type; // "bullish" or "bearish"
		double open; // first temp in the range
		double high; // highest temp in the range
		double low; // lowest temp in the range
		double close; // last temp in the range
};

