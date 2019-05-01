#include "Environment.hpp"
#include "Random.hpp"

Environment::Environment() {
}

Environment::Environment(Statistics minimalSurvivalStats, Statistics minimalReproductionStats)
	: minimalSurvivalStats(minimalSurvivalStats), minimalReproductionStats(minimalReproductionStats) {
}

Environment::~Environment() {
}

void Environment::initialize() { // This is just a mock for now. 
	minimalSurvivalStats.intelligence = 40;
	minimalSurvivalStats.dexterity = 40;
	minimalSurvivalStats.strength = 40;
	minimalReproductionStats.intelligence = 60;
	minimalReproductionStats.dexterity = 60;
	minimalReproductionStats.strength = 60;
}

void Environment::change() {
	do {
		minimalSurvivalStats.intelligence = changeSingleStats(minimalSurvivalStats.intelligence);
		minimalSurvivalStats.dexterity = changeSingleStats(minimalSurvivalStats.dexterity);
		minimalSurvivalStats.strength = changeSingleStats(minimalSurvivalStats.strength);
		minimalReproductionStats.intelligence = changeSingleStats(minimalReproductionStats.intelligence);
		minimalReproductionStats.dexterity = changeSingleStats(minimalReproductionStats.dexterity);
		minimalReproductionStats.strength = changeSingleStats(minimalReproductionStats.strength);
	} while (false); //TODO: Delete it. Whole loop.
}

int Environment::changeSingleStats(int stats) {
	int randomChange = (int)(Random::getRandomDouble() * (double)(MAX_STATS_CHANGE)-(double)(MAX_STATS_CHANGE / 2));
	int changedStats = stats + randomChange;
	return changedStats;
}

bool Environment::isSurvivalHigherThanReproduction() { // Consider that it do not have to be this way. If not it could be interesting to make children.
	if (minimalSurvivalStats.intelligence > minimalReproductionStats.intelligence)
		return true;
	if (minimalSurvivalStats.dexterity > minimalReproductionStats.dexterity)
		return true;
	if (minimalSurvivalStats.strength > minimalReproductionStats.strength)
		return true;
	return false;
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