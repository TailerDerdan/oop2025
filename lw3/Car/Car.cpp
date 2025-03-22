#include "GUIOfCar.h"
#include <iostream>

int main()
{
	GUIOfCar gui(std::cin, std::cout);
	gui.DialogWithUser();
	return EXIT_SUCCESS;
}
