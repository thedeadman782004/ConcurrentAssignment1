/*Matthew Babb		CIS-126		CH.4 Q.7
The following program is designed to get two times form the user: A current time and a future
time. After recieving all info, it sets boolean flags for am or pm. When the code runs its calculations,
it calls recursively, incrementing until the desired time is found. All code is original and was
typed by me.*/

#include <iostream>

//Function Declarations
void current(int& hour, int& minute, bool& isPM);
void future(int& futureHour, int& futureMinute, bool& futurePM);
void dateLine(int& hour, int futureHour, int minute, int futureMinute, bool& isPM, bool futurePM, int& total);

int main()
{

	//Declares all neccessary variables
	int hour = 0, minute = 0, futureHour = 0, futureMinute = 0, total = 0;
	bool isPM = false, futurePM = false;

	//calls information functions
	current(hour, minute, isPM);
	future(futureHour, futureMinute, futurePM);

	//calls calculation function
	dateLine(hour, futureHour, minute, futureMinute, isPM, futurePM, total);

	//outputs the number of minutes.
	std::cout << "The number of minutes you wish to travel into the future is "
		<< total << " minutes." << std::endl;

	return 0;
}

void current(int& hour, int& minute, bool& isPM)
{

	//char array used for determining am or pm
	char isMorning[4] = {};

	//gets time info from user
	std::cout << "Please enter the current time." << std::endl;
	std::cout << "Hour: ";
	std::cin >> hour;
	std::cout << std::endl;
	std::cout << "Minutes: ";
	std::cin >> minute;
	std::cout << std::endl;
	std::cout << "AM/PM: ";
	std::cin >> isMorning;
	std::cout << std::endl;

	//validation of am/pm
	if (strcmp(isMorning, "pm") == 0 || strcmp(isMorning, "PM") == 0 || strcmp(isMorning, "Pm") == 0)
	{

		//sets boolean flag
		isPM = true;
	}
}

void future(int& futureHour, int& futureMinute, bool& futurePM)
{

	//char array used for determining am or pm
	char isMorning[4] = {};

	//gets time info from user
	std::cout << "Please enter the future time." << std::endl;
	std::cout << "Hour: ";
	std::cin >> futureHour;
	std::cout << std::endl;
	std::cout << "Minutes: ";
	std::cin >> futureMinute;
	std::cout << std::endl;
	std::cout << "AM/PM: ";
	std::cin >> isMorning;
	std::cout << std::endl;

	//validation of am/pm
	if (strcmp(isMorning, "pm") == 0 || strcmp(isMorning, "PM") == 0 || strcmp(isMorning, "Pm") == 0)
	{

		//sets boolean flag
		futurePM = true;
	}
}

void dateLine(int& hour, int futureHour, int minute, int futureMinute, bool& isPM, bool futurePM, int& total)
{

	//Recursive function which will loop until the correct time is found.

	//constant to this function...
	int MinHr = 60, clock = 12, notClock = 13;

	//Compares the hour
	if (hour == futureHour)
	{

		//compares the boolean flags
		if (isPM == futurePM)
		{

			//the time has been found, add the minutes
			total += futureMinute;
			if (minute != 0)
			{
				total += (MinHr - minute);
			}

			//escape recursion
			return;
		}

	}
	else if (hour == clock)
	{

		//adjusts am/pm flag when crossing 12:00
		if (isPM == true)
		{
			isPM = false;
		}
		else
			isPM = true;
	}

	//increment hour for next iteration
	hour++;

	//if we crossed 12, reset to one.
	if (hour == notClock)
	{
		hour = 1;
	}

	//adds the current hour, which was not yet the correct time.
	total += MinHr;

	//RECURISIVE CALL
	dateLine(hour, futureHour, minute, futureMinute, isPM, futurePM, total);

	//ESCAPE RECURISON
	return;
}

