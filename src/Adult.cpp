#include "Adult.hpp"

Adult::Adult() {
}

Adult::~Adult() {
}

Elder Adult::growOlder() {
	Elder middleAgedMan(stats, isMale);
	return middleAgedMan;
}

nlohmann::json Adult::toJson() {
	nlohmann::json jsonInfo{
		{"personType", "Adult"},
		{"intelligence", stats.intelligence},
		{"dexterity", stats.dexterity},
		{"strength", stats.intelligence},
		{"isMale", isMale}
	};
	return jsonInfo;
}