/*#include <iostream>
#include <windows.h>

HANDLE hConsole;

int main()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << "Bright red text\n";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	std::cout << "Dull red text\n";

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "Bright blue text\n";

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	std::cout << "Dull blue text\n";

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Bright green text\n";

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	std::cout << "Dull green text\n";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Bright white text\n";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	std::cout << "Back to normal text\n";

	// you can loop k higher to see more color choices
	for(int k = 0; k < 255; k++)
	{
		// pick the colorattribute k you want
		SetConsoleTextAttribute(hConsole, k);
		std::cout << k << " I want to be nice today!" << std::endl;
	}

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	system("pause");
	return 0;
}*/