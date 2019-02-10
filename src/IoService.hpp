#ifndef IO_SERVICE_HPP
#define IO_SERVICE_HPP

#include "Parameters.hpp"
#include "Environment.hpp"
#include "PopulationRepository.hpp"
#include "Info.hpp"
#include "../lib/json.hpp"

class IoService {
public:
	static Parameters parseArgs(int argc, char *argv[]);
	static Environment readEnvironment(Parameters *parameters);
	static PopulationRepository readPopulation(Parameters *parameters);
	static void saveLogs(std::vector<Info> info, Parameters * parameters);

private:
	static void printHelp();
	static Child readChild(nlohmann::json::iterator person);
	static Adult readAdult(nlohmann::json::iterator person);
	static Elder readElder(nlohmann::json::iterator person);
};

#endif
