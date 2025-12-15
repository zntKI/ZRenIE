#include <iostream>

#include "Utils.hpp"

std::ostream& operator<<(std::ostream& os, ConsoleTextColor color)
{
	if (color == ConsoleTextColor::Red) {
		os << "\033[1;31m";
	}
	else {
		os << "\033[0m";
	}
	return os;
}

void Utils::logMessage(const std::string& message)
{
	std::cout << ConsoleTextColor::Default << message << std::endl;
}

void Utils::logError(const std::string& errorMessage)
{
	std::cerr << ConsoleTextColor::Red << errorMessage << ConsoleTextColor::Default << std::endl;
}