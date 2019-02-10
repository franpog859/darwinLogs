#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <string>

struct Parameters {
	bool isHelp = true;
	int epochs = 0;
	std::string inputEnvironmentFile = "";
	std::string inputPopulationFile = "";
	std::string outputEnvironmentFile = "";
	std::string outputPopulationFile = "";
	std::string outputLogsFile = "";
};

#endif
