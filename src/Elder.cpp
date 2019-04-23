#include "Elder.hpp"

Elder::Elder() {
}

Elder::~Elder() {
}

void Elder::growOlder() {
	stats = {
		stats.intelligence * 2 / 3,
		stats.dexterity * 2 / 3,
		stats.strength * 2 / 3
	};
}

nlohmann::json Elder::toJson() {
	nlohmann::json jsonInfo{
		{"personType", "Elder"},
		{"intelligence", stats.intelligence},
		{"dexterity", stats.dexterity},
		{"strength", stats.intelligence},
		{"isMale", isMale}
	};
	return jsonInfo;
}