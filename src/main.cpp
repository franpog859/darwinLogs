#include <iostream>
#include "PopulationRepository.hpp"
#include "PopulationService.hpp"
#include "World.hpp"
#include "Parameters.hpp"
#include "Random.hpp"
#include "IoService.hpp"
#include "Logger.hpp"
#include "Exceptions.hpp"

int main(int argc, char *argv[]) {
	try {
		Parameters params = IoService::parseArgs(argc, argv);
		Random::initialize();

		Environment environment = IoService::readEnvironment(&params);
		PopulationRepository populationRepo = IoService::readPopulation(&params);
		PopulationService populationSvc(&populationRepo);

		World world(&environment, &params, &populationSvc);
		world.start();

		IoService::saveEnvironment(&environment, &params);
		IoService::savePopulation(&populationRepo, &params);
		std::vector<Info> logs = Logger::getLogs();
		IoService::saveLogs(&logs, &params); 
		IoService::saveGraphs(&logs, &params);
	}
	catch(HelpException &e) {
		std::cerr << e.what() << std::endl;
		IoService::printHelp();
	}
	catch(ReadException &e) {
		std::cerr << e.what() << std::endl;
	}
	catch(std::exception &e) {
		std::cerr << "Error occurred: " << e.what() << std::endl;
	}

	return 0;
}
