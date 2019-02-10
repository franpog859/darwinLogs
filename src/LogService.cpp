#include <iostream>
#include "LogService.hpp"
#include "Info.hpp"

std::vector<Info> LogService::populationInfo;
std::vector<Statistics> LogService::minimalSurvivalStats;
std::vector<Statistics> LogService::minimalReproductionStats;

void LogService::prepareStatisticsFor(Environment *environment, PopulationService *populationService) {
	Statistics singleMinimalReproductionStats = {
		environment->getMinimalReproductionStats()->dexterity,
		environment->getMinimalReproductionStats()->strength,
		environment->getMinimalReproductionStats()->intelligence,
	};
	minimalReproductionStats.push_back(singleMinimalReproductionStats);

	Statistics singleMinimalSurvivalStats = {
		environment->getMinimalSurvivalStats()->dexterity,
		environment->getMinimalSurvivalStats()->strength,
		environment->getMinimalSurvivalStats()->intelligence,
	};
	minimalSurvivalStats.push_back(singleMinimalSurvivalStats);

	populationInfo.push_back(populationService->getPopulationInfo());
}

void LogService::printPopulationInfo() {
	std::cout << "Population info:" << std::endl;

	Info info = populationInfo.back();
	std::cout << "	Number of children: " << info.childrenNumber << std::endl;
	std::cout << "	Number of adults: " << info.adultsNumber << std::endl;
	std::cout << "	Number of elders: " << info.eldersNumber << std::endl;

	Statistics lastReproductionStats = minimalReproductionStats.back();
	std::cout << "	Minimal dexterity to reproduce: " << lastReproductionStats.dexterity << std::endl;
	std::cout << "	Minimal intelligence to reproduce: " << lastReproductionStats.intelligence << std::endl;
	std::cout << "	Minimal strength to reproduce: " << lastReproductionStats.strength << std::endl;

	Statistics lastSurvivalStats = minimalSurvivalStats.back();
	std::cout << "	Minimal dexterity to survive: " << lastSurvivalStats.dexterity << std::endl;
	std::cout << "	Minimal intelligence to survive: " << lastSurvivalStats.intelligence << std::endl;
	std::cout << "	Minimal strength to survive: " << lastSurvivalStats.strength << std::endl;
}

std::vector<Info> LogService::getLogs() {
	return populationInfo;
}
