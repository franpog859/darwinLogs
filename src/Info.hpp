#ifndef INFO_HPP
#define INFO_HPP

#include "Statistics.hpp"
#include "../lib/json.hpp"

struct Info { 
	int childrenNumber = 0;
	int adultsNumber = 0;
	int eldersNumber = 0;

	int maleNumber = 0;
	int femaleNumber = 0;

	int deathsNumber = 0;
	int newbornsNumber = 0;

	int straightCouplesNumber = 0;
	int homoCouplesNumber = 0;

	Statistics averageChildsStatistics; 
	Statistics averageAdultsStatistics; 
	Statistics averageEldersStatistics; 
	Statistics averageStatistics; 

	Statistics minimalSurvivalStatistics;
	Statistics minimalReproductionStatistics;
};

#endif