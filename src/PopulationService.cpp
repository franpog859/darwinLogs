#include "PopulationService.hpp"
#include "Random.hpp"

PopulationService::PopulationService() {
}

PopulationService::PopulationService(PopulationRepository *populationRepo) : populationRepo(populationRepo) {
}

PopulationService ::~PopulationService() {
	populationRepo = nullptr;
}

std::vector<Couple> PopulationService::pairCouples() { 
	const int adultsNumber = populationRepo->getAdults()->size();
	std::vector<Couple> couples;
	if (adultsNumber < 2) {
		return couples;
	}
	bool * wasPaired = new bool[adultsNumber];
	for (int i = 0; i < adultsNumber; i++) {
		wasPaired[i] = false;
	}
	int pairedAdultsNumber = 0;
	do {
		Couple newlyweds = createCouple(wasPaired);
		couples.push_back(newlyweds);
		pairedAdultsNumber += 2;
	} while (pairedAdultsNumber < adultsNumber - 1);

	delete [] wasPaired;
	return couples;
}

Couple PopulationService::createCouple(bool * wasPaired) {
	Adult * first = getRandomNotPairedAdult(wasPaired);
	Adult * second = getRandomNotPairedAdult(wasPaired);
	Couple newlyweds(first, second);
	first = nullptr;
	second = nullptr;
	return newlyweds;
}

Adult * PopulationService::getRandomNotPairedAdult(bool * wasPaired) {
	int adultsNumber = populationRepo->getAdults()->size();
	int singleNumber = 0;
	for (int i = 0; i < adultsNumber; i++) {
		if (!wasPaired[i]) {
			singleNumber++;
		}
	}
	int randomSingle = (int)(Random::getRandomDouble() * (double)(singleNumber));
	int singleAdult = 0;
	for (int i = 0; i < adultsNumber; i++) {
		if (randomSingle == 0) {
			singleAdult = i;
			break;
		}
		if (!wasPaired[i]) {
			randomSingle--;
		}
	}
	wasPaired[singleAdult] = true;
	return &populationRepo->getAdults()->at(singleAdult);
}

void PopulationService::add(std::vector<Child>* newborns) {
	std::vector<Child>* children = populationRepo->getChildren();

	for (std::vector<Child>::iterator newborn = newborns->begin(); newborn < newborns->end(); newborn++) {
		children->push_back(*newborn);
	}
}

std::vector<Person> PopulationService::killUnadaptedTo(Environment * environment) {
	std::vector<Person> deadPeople;
	for (int i = 0; i < populationRepo->getChildren()->size(); i++) {
		if (!populationRepo->getChildren()->at(i).canSurvive(environment)) {
			deadPeople.push_back(populationRepo->getChildren()->at(i));
			populationRepo->getChildren()->erase(populationRepo->getChildren()->begin() + i);
			i--;
		}
	}
	for (int i = 0; i < populationRepo->getAdults()->size(); i++) {
		if (!populationRepo->getAdults()->at(i).canSurvive(environment)) {
			deadPeople.push_back(populationRepo->getAdults()->at(i));
			populationRepo->getAdults()->erase(populationRepo->getAdults()->begin() + i);
			i--;
		}
	}
	for (int i = 0; i < populationRepo->getElders()->size(); i++) {
		if (!populationRepo->getElders()->at(i).canSurvive(environment)) {
			deadPeople.push_back(populationRepo->getElders()->at(i));
			populationRepo->getElders()->erase(populationRepo->getElders()->begin() + i);
			i--;
		}
	}
	return deadPeople;
}

void PopulationService::growOlder() {
	for (int i = 0; i < populationRepo->getElders()->size(); i++) {
		populationRepo->getElders()->at(i).growOlder();
	}
	while (populationRepo->getAdults()->size() > 0) {
		Elder middleAgedMan = populationRepo->getAdults()->at(0).growOlder();
		populationRepo->getElders()->push_back(middleAgedMan);
		populationRepo->getAdults()->erase(populationRepo->getAdults()->begin());
	} 
	while (populationRepo->getChildren()->size() > 0) {
		Adult adolescent = populationRepo->getChildren()->at(0).growOlder();
		populationRepo->getAdults()->push_back(adolescent);
		populationRepo->getChildren()->erase(populationRepo->getChildren()->begin());
	}
}

Info PopulationService::getGeneralPopulationInfo() {
	Info populationInfo;

	populationInfo.childrenNumber = populationRepo->getChildren()->size();
	populationInfo.adultsNumber = populationRepo->getAdults()->size();
	populationInfo.eldersNumber = populationRepo->getElders()->size();
	
	for (int i = 0; i < populationRepo->getChildren()->size(); i++) {
		if (populationRepo->getChildren()->at(i).getIsMale())
			populationInfo.maleNumber++;
		else
			populationInfo.femaleNumber++;
	}
	for (int i = 0; i < populationRepo->getAdults()->size(); i++) {
		if (populationRepo->getAdults()->at(i).getIsMale()) {
			populationInfo.maleNumber++;
			populationInfo.maleAdultNumber++;
		}
		else {
			populationInfo.femaleNumber++;
			populationInfo.femaleAdultNumber++;
		}
	}
	for (int i = 0; i < populationRepo->getElders()->size(); i++) {
		if (populationRepo->getElders()->at(i).getIsMale())
			populationInfo.maleNumber++;
		else
			populationInfo.femaleNumber++;
	}

	for (int i = 0; i < populationRepo->getChildren()->size(); i++)
		populationInfo.averageChildsStatistics += populationRepo->getChildren()->at(i).getStats();
	populationInfo.averageStatistics += populationInfo.averageChildsStatistics;
	if (populationRepo->getChildren()->size() > 0) 
		populationInfo.averageChildsStatistics /= populationRepo->getChildren()->size();
	for (int i = 0; i < populationRepo->getAdults()->size(); i++)
		populationInfo.averageAdultsStatistics += populationRepo->getAdults()->at(i).getStats();
	populationInfo.averageStatistics += populationInfo.averageAdultsStatistics;
	if (populationRepo->getAdults()->size() > 0) 
		populationInfo.averageAdultsStatistics /= populationRepo->getAdults()->size();
	for (int i = 0; i < populationRepo->getElders()->size(); i++)
		populationInfo.averageEldersStatistics += populationRepo->getElders()->at(i).getStats();
	populationInfo.averageStatistics += populationInfo.averageEldersStatistics;
	if (populationRepo->getElders()->size() > 0) 
		populationInfo.averageEldersStatistics /= populationRepo->getElders()->size();
	if (populationRepo->getChildren()->size() +
		populationRepo->getAdults()->size() +
		populationRepo->getElders()->size() > 0) 
	populationInfo.averageStatistics /=
		populationRepo->getChildren()->size() +
		populationRepo->getAdults()->size() +
		populationRepo->getElders()->size();

	return populationInfo;
}
