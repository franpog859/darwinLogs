#include <iostream>
#include <iterator>
#include "Logger.hpp"
#include "Exceptions.hpp"
#include "Info.hpp"

Info Logger::infoBuilder;
std::vector<Info> Logger::info;

void Logger::addGeneralInfo(Environment *environment, PopulationService *populationService) {
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
void Logger::addCouplesInfo(std::vector<Couple> *couples) {
	for (std::vector<Couple>::iterator couple = couples->begin(); couple < couples->end(); couple++) {
		if (couple->isStraight())
			infoBuilder.straightCouplesNumber++;
		else
			infoBuilder.homoCouplesNumber++;
	}
}

void Logger::addNewbornsInfo(std::vector<Child> *newborns) {
	infoBuilder.newbornsNumber = newborns->size();
}

void Logger::addDeathsInfo(std::vector<Person> *deadPeople) {
	infoBuilder.deathsNumber = deadPeople->size();
}

void Logger::printLogs() {
	if (info.size() == 0) {
		throw EmptyInfoException();
	}
	
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "Population info:" << std::endl;

	Info i = info.back();
	std::cout << "	Minimal dexterity to reproduce: " << i.minimalReproductionStatistics.dexterity << std::endl;
	std::cout << "	Minimal intelligence to reproduce: " << i.minimalReproductionStatistics.intelligence << std::endl;
	std::cout << "	Minimal strength to reproduce: " << i.minimalReproductionStatistics.strength << std::endl;

	std::cout << "	Minimal dexterity to survive: " << i.minimalSurvivalStatistics.dexterity << std::endl;
	std::cout << "	Minimal intelligence to survive: " << i.minimalSurvivalStatistics.intelligence << std::endl;
	std::cout << "	Minimal strength to survive: " << i.minimalSurvivalStatistics.strength << std::endl;
	
	std::cout << "	Number of children: " << i.childrenNumber << std::endl;
	std::cout << "	Number of adults: " << i.adultsNumber << std::endl;
	std::cout << "	Number of elders: " << i.eldersNumber << std::endl;

	std::cout << "	Males number: " << i.maleNumber << std::endl;
	std::cout << "	Females number: " << i.femaleNumber << std::endl;

	std::cout << "	Newborns number: " << i.newbornsNumber << std::endl;
	std::cout << "	Deaths number: " << i.deathsNumber << std::endl;

	std::cout << "	Straight couples number: " << i.straightCouplesNumber << std::endl;
	std::cout << "	Homo couples number: " << i.homoCouplesNumber << std::endl;

	std::cout << "	Average child dexterity: " << i.averageChildsStatistics.dexterity << std::endl;
	std::cout << "	Average child intelligence: " << i.averageChildsStatistics.intelligence << std::endl;
	std::cout << "	Average child strength: " << i.averageChildsStatistics.strength << std::endl;

	std::cout << "	Average adult dexterity: " << i.averageAdultsStatistics.dexterity << std::endl;
	std::cout << "	Average adult intelligence: " << i.averageAdultsStatistics.intelligence << std::endl;
	std::cout << "	Average adult strength: " << i.averageAdultsStatistics.strength << std::endl;

	std::cout << "	Average elder dexterity: " << i.averageEldersStatistics.dexterity << std::endl;
	std::cout << "	Average elder intelligence: " << i.averageEldersStatistics.intelligence << std::endl;
	std::cout << "	Average elder strength: " << i.averageEldersStatistics.strength << std::endl;

	std::cout << "	Average dexterity: " << i.averageStatistics.dexterity << std::endl;
	std::cout << "	Average intelligence: " << i.averageStatistics.intelligence << std::endl;
	std::cout << "	Average strength: " << i.averageStatistics.strength << std::endl;

	std::cout << "------------------------------------------------" << std::endl;
}

std::vector<Info> Logger::getLogs() {
	return info;
}

void Logger::saveBuiltInfo() {
	info.push_back(infoBuilder);
	Info newInfoBuilder;
	infoBuilder = newInfoBuilder;
}
