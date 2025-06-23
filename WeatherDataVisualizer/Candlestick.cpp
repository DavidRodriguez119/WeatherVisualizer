#include "Candlestick.h"

Candlestick::Candlestick(int _date,
	CandlestickType _type,
	double _open,
	double _high,
	double _low,
	double _close)
	:date(_date),
	type(_type),
	open(_open),
	high(_high),
	low(_low),
	close(_close)
{

};