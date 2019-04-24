#ifndef INFO_HPP
#define INFO_HPP

#include "Statistics.hpp"
#include "../lib/json.hpp"

struct Info { // TODO: Create full class from this struct for better abstraction.
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

	nlohmann::json toJson() {
		nlohmann::json jsonInfo{
			{"childrenNumber", childrenNumber},
			{"adultsNumber", adultsNumber},
			{"eldersNumber", eldersNumber}
		};
		return jsonInfo;
	}
};

#endif