#include "PopulationService.hpp"
#include "Random.hpp"

PopulationService::PopulationService() {
}

PopulationService::PopulationService(PopulationRepository *populationRepo) : populationRepo(populationRepo) {
}

PopulationService ::~PopulationService() {
	populationRepo = nullptr;
}

std::vector<Couple> PopulationService::pairCouples() { // TODO: Somehow minify this function. It is huge.
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
	int randomAdult = 0;
	do {
		randomAdult = (int)(Random::getRandomDouble() * (double)(adultsNumber));
	} while (wasPaired[randomAdult]);
	wasPaired[randomAdult] = true;
	return &populationRepo->getAdults()->at(randomAdult);
}

void PopulationService::add(std::vector<Child>* newborns) {
	std::vector<Child>* children = populationRepo->getChildren();

	for (unsigned int i = 0; i < newborns->size(); i++) {
		children->push_back(newborns->at(i));
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
		if (populationRepo->getAdults()->at(i).getIsMale())
			populationInfo.maleNumber++;
		else
			populationInfo.femaleNumber++;
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
	populationInfo.averageChildsStatistics /= populationRepo->getChildren()->size();
	for (int i = 0; i < populationRepo->getAdults()->size(); i++)
		populationInfo.averageAdultsStatistics += populationRepo->getAdults()->at(i).getStats();
	populationInfo.averageStatistics += populationInfo.averageAdultsStatistics;
	populationInfo.averageAdultsStatistics /= populationRepo->getAdults()->size();
	for (int i = 0; i < populationRepo->getElders()->size(); i++)
		populationInfo.averageEldersStatistics += populationRepo->getElders()->at(i).getStats();
	populationInfo.averageStatistics += populationInfo.averageEldersStatistics;
	populationInfo.averageEldersStatistics /= populationRepo->getElders()->size();
	populationInfo.averageStatistics /=
		populationRepo->getChildren()->size() +
		populationRepo->getAdults()->size() +
		populationRepo->getElders()->size();

	return populationInfo;
}
