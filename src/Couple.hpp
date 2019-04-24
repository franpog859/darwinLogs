#ifndef COUPLE_HPP
#define COUPLE_HPP

#include <vector>
#include "Adult.hpp"
#include "Child.hpp"
#include "Environment.hpp"
#include "Statistics.hpp"

const int MAX_NUMBER_OF_CHILDREN = 5;

class Couple {
public:
	Couple();
	Couple(Adult * first, Adult * second);
	~Couple();

	std::vector<Child> begetChildren(Environment * environment);
	bool isStraight();

private:
	Adult * first = nullptr;
	Adult * second = nullptr;

	Statistics getChildStatistics();
	bool isChildMale();
};

#endif