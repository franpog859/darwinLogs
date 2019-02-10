#ifndef INFO_HPP
#define INFO_HPP

#include "Statistics.hpp"
#include "../lib/json.hpp"

struct Info { // TODO: Create full class from this struct for better abstraction.
	int childrenNumber = 0;
	int adultsNumber = 0;
	int eldersNumber = 0;
	Statistics averageStatistics; // TODO: Get it from PopulationService and add it to toJson() method.

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