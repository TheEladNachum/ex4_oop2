#include <iostream>
#include "Controller.h"

int main()
{
	try
	{
		Controller start;
		start.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Fatal Error: " << e.what() << std::endl;
	}
	return 0;
}
