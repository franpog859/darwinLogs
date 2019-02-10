#ifndef WORLD_HPP
#define WORLD_HPP

#include "Environment.hpp"
#include "PopulationService.hpp"
#include "Parameters.hpp"

class World {
public:
	World(Environment * environment, Parameters * parameters, PopulationService * populationService);
	~World();

	void start();

private:
	Environment * environment;
	Parameters * parameters;
	PopulationService * populationService;
};

#endif 
