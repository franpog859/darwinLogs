#include "Person.hpp"

Person::Person() {
}

Person::Person(Statistics statistics, bool isMale) : stats(statistics), isMale(isMale) {
}

Person ::~Person() {
}

bool Person::canReproduce(Environment* env) {
	if (stats.intelligence < env->getMinimalReproductionStats()->intelligence)
		return false;
	if (stats.dexterity < env->getMinimalReproductionStats()->dexterity)
		return false;
	if (stats.strength < env->getMinimalReproductionStats()->strength)
		return false;
	return true;
}

bool Person::canSurvive(Environment* env) {
	if (stats.intelligence < env->getMinimalSurvivalStats()->intelligence)
		return false;
	if (stats.dexterity < env->getMinimalSurvivalStats()->dexterity)
		return false;
	if (stats.strength < env->getMinimalSurvivalStats()->strength)
		return false;
	return true;
}

bool Person::getIsMale() {
	return isMale;
}

Statistics Person::getStats() {
	return stats;
}

nlohmann::json Person::toJson() {
	nlohmann::json jsonInfo{
		{"personType", "none"},
		{"intelligence", stats.intelligence},
		{"dexterity", stats.dexterity},
		{"strength", stats.intelligence},
		{"isMale", isMale}
	};
	return jsonInfo;
}
