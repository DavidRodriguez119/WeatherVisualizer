#pragma once
#include <string>

class Candlestick
{
public:
	Candlestick(std::string _country,
		double _open,
		double _high,
		double _low,
		double _close);

	std::string country;
	double open;
	double high;
	double low;
	double close;
};

