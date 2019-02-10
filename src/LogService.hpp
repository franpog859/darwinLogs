#ifndef LOG_SERVICE_HPP
#define LOG_SERVICE_HPP

#include "Environment.hpp"
#include "PopulationService.hpp"

class LogService {
public:
	static void prepareStatisticsFor(Environment *environment, PopulationService *populationService);
	static void printPopulationInfo();
	static std::vector<Info> getLogs();

private:
	static std::vector<Info> populationInfo;
	static std::vector<Statistics> minimalSurvivalStats;
	static std::vector<Statistics> minimalReproductionStats;
};

#endif
