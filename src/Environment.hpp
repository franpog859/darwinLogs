#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "Statistics.hpp"

const int MAX_STATS_CHANGE = 6;

class Environment {
public:
	Environment();
	Environment(Statistics minimalSurvivalStats, Statistics minimalReproductionStats);
	~Environment();

	void initialize(); 
	void change();
	Statistics* getMinimalSurvivalStats();
	Statistics* getMinimalReproductionStats();

private:
	Statistics minimalSurvivalStats;
	Statistics minimalReproductionStats;

	int changeSingleStats(int stats);
	bool isSurvivalHigherThanReproduction();
};

#endif 