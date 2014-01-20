#include "../solutions.h"
#include <iostream>
#include <string>
#include <iomanip>

enum Day: long
{
	Sunday		= 1,
	Monday		= 2,
	Tuesday		= 3,
	Wednesday	= 4,
	Thursday	= 5,
	Friday		= 6,
	Saturday	= 7,
	DAY_END		= 8
};
Day& operator++(Day& d)
{
	d = static_cast<Day>(static_cast<long>(d)+1);
	return d;
}

enum Month :long
{
	January	= 1,
	Febuary	= 2,
	March	= 3,
	April	= 4,
	May		= 5,
	June	= 6,
	July	= 7,
	August	= 8,
	September	= 9,
	October		= 10,
	November	= 11,
	December	= 12,
	MONTH_END	= 13
};
Month& operator++(Month& m)
{
	m = static_cast<Month>(static_cast<long>(m) + 1);
	return m;
}

static bool isLeap(const long year)
{
	if(year % 4 == 0){
		if(year % 100 == 0){
			if(year % 400 == 0)
				return true;
			return false;
		}
		return true;
	}

	return false;
}


static long solution()
{
	long result = 0;
	Day day = Monday;

	for(long year=1900; year < 2001; ++year)
	{
		for(Month month = January; month != MONTH_END; ++month)
		{
			long monthLength = 31;
			switch(month){
			case September:
			case April:
			case June:
			case November:
				monthLength = 30;
				break;

			case Febuary:
				monthLength = isLeap(year) ? 29 : 28;
				break;

			default:
				//all other months have 31 days (as the default value).
				break;
			}

			for(long d = 1; d <= monthLength; ++d){
				/*
				std::string strDay = "";
				switch(day){
				case Sunday:	strDay = "Sunday";	break;
				case Monday:	strDay = "Monday";	break;
				case Tuesday:	strDay = "Tuesday";	break;
				case Wednesday:	strDay = "Wednesday";	break;
				case Thursday:	strDay = "Thursday";	break;
				case Friday:	strDay = "Friday";		break;
				case Saturday:	strDay = "Saturday";	break;
				case DAY_END:	strDay = "--------";	break;
				}
				// */
				// we don't want the dated of 1900	
				if(year > 1900 && d == 1 && day == Sunday)
				{
					// std::cout <<  d << "/" << std::setw(2) << std::setfill('0') << month << '/' << year << "\t- " << strDay << '\n';
					++result;
				}

				++day;
				if(day == DAY_END)
					day = Sunday;
			}
		}
	}
	return result;
}

RegisterSolution(19, solution);


