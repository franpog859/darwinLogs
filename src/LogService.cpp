#include <iostream>
#include "LogService.hpp"
#include "Info.hpp"

Info LogService::infoBuilder;
std::vector<Info> LogService::info;
std::vector<Info> LogService::populationInfo;
std::vector<Statistics> LogService::minimalSurvivalStats;
std::vector<Statistics> LogService::minimalReproductionStats;

void LogService::addGeneralInfo(Environment *environment, PopulationService *populationService) {
	infoBuilder.minimalReproductionStatistics = *environment->getMinimalReproductionStats();
	infoBuilder.minimalSurvivalStatistics = *environment->getMinimalSurvivalStats();

	Info generalPopulationInfo = populationService->getGeneralPopulationInfo();
	infoBuilder.childrenNumber = generalPopulationInfo.childrenNumber;
	infoBuilder.adultsNumber = generalPopulationInfo.adultsNumber;
	infoBuilder.eldersNumber = generalPopulationInfo.eldersNumber;
	infoBuilder.maleNumber = generalPopulationInfo.maleNumber;
	infoBuilder.femaleNumber = generalPopulationInfo.femaleNumber;
	infoBuilder.averageChildsStatistics = generalPopulationInfo.averageChildsStatistics;
	infoBuilder.averageAdultsStatistics = generalPopulationInfo.averageAdultsStatistics;
	infoBuilder.averageEldersStatistics = generalPopulationInfo.averageEldersStatistics;
	infoBuilder.averageStatistics = generalPopulationInfo.averageStatistics;
}

void LogService::printLogs() {
	std::cout << "Population info:" << std::endl;

	Info i = info.back();
	std::cout << "	Number of children: " << i.childrenNumber << std::endl;
	std::cout << "	Number of adults: " << i.adultsNumber << std::endl;
	std::cout << "	Number of elders: " << i.eldersNumber << std::endl;

	std::cout << "	Minimal dexterity to reproduce: " << i.minimalReproductionStatistics.dexterity << std::endl;
	std::cout << "	Minimal intelligence to reproduce: " << i.minimalReproductionStatistics.intelligence << std::endl;
	std::cout << "	Minimal strength to reproduce: " << i.minimalReproductionStatistics.strength << std::endl;

	std::cout << "	Minimal dexterity to survive: " << i.minimalSurvivalStatistics.dexterity << std::endl;
	std::cout << "	Minimal intelligence to survive: " << i.minimalSurvivalStatistics.intelligence << std::endl;
	std::cout << "	Minimal strength to survive: " << i.minimalSurvivalStatistics.strength << std::endl;
}

std::vector<Info> LogService::getLogs() {
	return info;
}

void LogService::saveBuiltInfo() {
	info.push_back(infoBuilder);
	Info newInfoBuilder;
	infoBuilder = newInfoBuilder;
}
