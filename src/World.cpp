#include <iostream>
#include "World.hpp"
#include "LogService.hpp"
#include "Couple.hpp"
#include "../lib/ProgressBar.hpp"

World::World(Environment * environment, Parameters * parameters, PopulationService * populationService)
	: environment(environment), parameters(parameters), populationService(populationService) {
}

World::~World() {
	environment = nullptr;
	parameters = nullptr;
	populationService = nullptr;
}

void World::start() {
	std::cout << "World has started. It can take a while." << std::endl;
	const int PROGRESS_BAR_WIDTH = 50; //TODO: Keep progress bar and other console communication in some static class.
	ProgressBar progressBar(parameters->epochs, PROGRESS_BAR_WIDTH);
	Midwife midwife;
	for (int i = 0; i < parameters->epochs; i++) {
		std::vector<Couple> couples = populationService->pairCouples();
		LogService::addCouplesInfo(&couples);

		std::vector<Child> newborns = midwife.begetChildren(environment, &couples);
		LogService::addNewbornsInfo(&newborns);

		populationService->add(&newborns);
		std::vector<Person> deadPeople = populationService->killUnadaptedTo(environment);
		LogService::addDeathsInfo(&deadPeople);
		LogService::addGeneralInfo(environment, populationService);

		populationService->growOlder();
		environment->change();

		LogService::saveBuiltInfo();
		++progressBar;
		progressBar.display();
	}
	progressBar.done();
	LogService::printLogs();
}