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

void PopulationService::killUnadaptedTo(Environment * environment) {
	for (int i = 0; i < populationRepo->getChildren()->size(); i++) {
		if (!populationRepo->getChildren()->at(i).canSurvive(environment)) {
			populationRepo->getChildren()->erase(populationRepo->getChildren()->begin() + i);
			i--;
		}
	}
	for (int i = 0; i < populationRepo->getAdults()->size(); i++) {
		if (!populationRepo->getAdults()->at(i).canSurvive(environment)) {
			populationRepo->getAdults()->erase(populationRepo->getAdults()->begin() + i);
			i--;
		}
	}
	for (int i = 0; i < populationRepo->getElders()->size(); i++) {
		if (!populationRepo->getElders()->at(i).canSurvive(environment)) {
			populationRepo->getElders()->erase(populationRepo->getElders()->begin() + i);
			i--;
		}
	}
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

Info PopulationService::getPopulationInfo() {
	Info populationInfo;
	populationInfo.childrenNumber = populationRepo->getChildren()->size();
	populationInfo.adultsNumber = populationRepo->getAdults()->size();
	populationInfo.eldersNumber = populationRepo->getElders()->size();
	// TODO: Somehow get average statistics.
	
	return populationInfo;
}