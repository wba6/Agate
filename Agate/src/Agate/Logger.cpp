#include "Logger.h"
#include <iostream>

namespace Agate
{
	void Logger::printMSG(std::string msg)
	{
        std::cout << "Message: " << msg << std::endl;
	}

	void Logger::printWarn(std::string msg)
	{
        std::cout << "Warning: " << msg << std::endl;
	}

	void Logger::printCrit(std::string msg)
	{
        std::cout << "Critical: " << msg << std::endl;
	}
}
