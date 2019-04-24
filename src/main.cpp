#include "PopulationRepository.hpp"
#include "PopulationService.hpp"
#include "World.hpp"
#include "Parameters.hpp"
#include "Random.hpp"
#include "IoService.hpp"
#include "LogService.hpp"

//#define _CRTDBG_MAP_ALLOC // Comment this if you are not debugging it on Windows.
//#include <stdlib.h> // Comment this if you are not debugging it on Windows.
//#include <crtdbg.h> // Comment this if you are not debugging it on Windows.

int main(int argc, char *argv[]) {
//	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); // Comment this if you are not debugging it on Windows.

	Parameters params = IoService::parseArgs(argc, argv);
	if (!params.isHelp) {
		Random::initialize();

		Environment environment = IoService::readEnvironment(&params);
		PopulationRepository populationRepo = IoService::readPopulation(&params);
		PopulationService populationSvc(&populationRepo);

		World world(&environment, &params, &populationSvc);
		world.start();

		IoService::saveEnvironment(&environment, &params);
		IoService::savePopulation(&populationRepo, &params);
		std::vector<Info> logs = LogService::getLogs();
		IoService::saveLogs(&logs, &params); //TODO: This should save logs to CSV file.
		//IoService::generateGraphs(LogService::getLogs(), &params);
	}
	return 0;
}
