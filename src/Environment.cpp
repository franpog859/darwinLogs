#include "Environment.hpp"
#include "Random.hpp"

Environment::Environment() {
}

Environment::Environment(Statistics minimalSurvivalStats, Statistics minimalReproductionStats)
	: minimalSurvivalStats(minimalSurvivalStats), minimalReproductionStats(minimalReproductionStats) {
}

Environment::~Environment() {
}

void Environment::change() {
	minimalSurvivalStats.intelligence = changeSingleStats(minimalSurvivalStats.intelligence);
	minimalSurvivalStats.dexterity = changeSingleStats(minimalSurvivalStats.dexterity);
	minimalSurvivalStats.strength = changeSingleStats(minimalSurvivalStats.strength);
	minimalReproductionStats.intelligence = changeSingleStats(minimalReproductionStats.intelligence);
	minimalReproductionStats.dexterity = changeSingleStats(minimalReproductionStats.dexterity);
	minimalReproductionStats.strength = changeSingleStats(minimalReproductionStats.strength);
}

int Environment::changeSingleStats(int stats) {
	int randomChange = (int)(Random::getRandomDouble() * (double)(MAX_STATS_CHANGE)-(double)(MAX_STATS_CHANGE / 2));
	int changedStats = stats + randomChange;
	return changedStats;
}

Statistics* Environment::getMinimalSurvivalStats() {
	return &minimalSurvivalStats;
}
Statistics* Environment::getMinimalReproductionStats() {
	return &minimalReproductionStats;
}

nlohmann::json Environment::toJson() {
	nlohmann::json jsonEnvironment{
		{"srv_dexterity", minimalSurvivalStats.dexterity},
		{"srv_intelligence", minimalSurvivalStats.intelligence},
		{"srv_strength", minimalSurvivalStats.strength},
		{"rep_dexterity", minimalReproductionStats.dexterity},
		{"rep_intelligence", minimalReproductionStats.intelligence},
		{"rep_strength", minimalReproductionStats.strength}
	};
	return jsonEnvironment;
}