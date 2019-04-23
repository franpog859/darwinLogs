#include "Child.hpp"

Child::Child() {
}

Child::~Child() {
}

Adult Child::growOlder() {
	Adult adolescent(stats, isMale);
	return adolescent;
}

nlohmann::json Child::toJson() {
	nlohmann::json jsonInfo{
		{"personType", "Child"},
		{"intelligence", stats.intelligence},
		{"dexterity", stats.dexterity},
		{"strength", stats.intelligence},
		{"isMale", isMale}
	};
	return jsonInfo;
}