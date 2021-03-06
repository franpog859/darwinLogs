#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <string>

struct Parameters {
	int epochs = 0;

	std::string inputEnvironmentFile = "";
	std::string inputPopulationFile = "";

	std::string outputEnvironmentFile = "";
	std::string outputPopulationFile = "";
	std::string outputLogsFile = ""; 
	std::string outputFilesPath = "";
};

#endif
