#include "Environment.hpp"
#include "Random.hpp"

Environment::Environment() {
}

Environment::Environment(Statistics minimalSurvivalStats, Statistics minimalReproductionStats)
	: minimalSurvivalStats(minimalSurvivalStats), minimalReproductionStats(minimalReproductionStats) {
}

Environment::~Environment() {
}

void Environment::initialize() { // This is just a mock for now. //TODO: Delete it.
	minimalSurvivalStats.intelligence = 40;
	minimalSurvivalStats.dexterity = 40;
	minimalSurvivalStats.strength = 40;
	minimalReproductionStats.intelligence = 60;
	minimalReproductionStats.dexterity = 60;
	minimalReproductionStats.strength = 60;
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
	return &minimalReproductionStats;
}
Statistics* Environment::getMinimalReproductionStats() {
	return &minimalSurvivalStats;
}

nlohmann::json Environment::toJson() {
	nlohmann::json jsonEnvironment{
		{"srv_dexterity", minimalSurvivalStats.dexterity},
		{"srv_intelligence", minimalReproductionStats.intelligence},
		{"srv_strength", minimalSurvivalStats.strength},
		{"rep_dexterity", minimalReproductionStats.dexterity},
		{"rep_intelligence", minimalReproductionStats.intelligence},
		{"rep_strength", minimalReproductionStats.strength}
	};
	return jsonEnvironment;
}