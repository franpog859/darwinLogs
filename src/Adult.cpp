#include "Adult.hpp"

Adult::Adult() {
}

Adult::~Adult() {
}

Elder Adult::growOlder() {
	Elder middleAgedMan(stats, isMale);
	return middleAgedMan;
}