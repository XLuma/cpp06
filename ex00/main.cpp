//
// Created by Louis-gabriel Laplante on 2022-06-21.
//

#include <string>
#include <iostream>
#include "Convert.h"

int main(int argc, char **argv)
{
	Convert conversion;
	if (argc != 2)
	{
		std::cout << "No viable argument provided ! Usage: ./convert [arg]" << std::endl;
		return 0;
	}
	try {
		conversion.detect_type(argv[1]);
		conversion.convert_data();
		conversion.print_data();
	}
	catch (std::exception &e) {
		std::cout << "Conversion aborted. Cannot go bigger than a long !" << std::endl;
	}
	return 0;
}