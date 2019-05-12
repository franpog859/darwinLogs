#ifndef IO_SERVICE_HPP
#define IO_SERVICE_HPP

#include "Parameters.hpp"
#include "Environment.hpp"
#include "PopulationRepository.hpp"
#include "Info.hpp"
#include "Plotter.hpp"
#include "../lib/json.hpp"

class IoService : public Plotter {
public:
	static Parameters parseArgs(int argc, char *argv[]);
	static void printHelp();
	static Environment readEnvironment(Parameters *parameters);
	static PopulationRepository readPopulation(Parameters *parameters);
	static void saveLogs(std::vector<Info> *info, Parameters *parameters);
	static void saveEnvironment(Environment *environment, Parameters *parameters);
	static void savePopulation(PopulationRepository *populationRepository, Parameters *parameters);
	using Plotter::saveGraphs;

private:
	static Child readChild(nlohmann::json::iterator person);
	static Adult readAdult(nlohmann::json::iterator person);
	static Elder readElder(nlohmann::json::iterator person);
};

#endif
