#include "Child.hpp"

Child::Child() {
}

Child::~Child() {
}

Adult Child::growOlder() {
	Adult adolescent(stats, isMale);
	return adolescent;
}