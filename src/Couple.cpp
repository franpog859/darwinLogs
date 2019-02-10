#include "Couple.hpp"
#include "Random.hpp"

Couple::Couple() {
}

Couple::Couple(Adult * first, Adult * second) : first(first), second(second) {
}

Couple::~Couple() {
	first = nullptr;
	second = nullptr;
}

std::vector<Child> Couple::begetChildren(Environment * environment) {
	std::vector<Child> children;
	if (!isStraight() ||
		!first->canReproduce(environment) ||
		!second->canReproduce(environment)) {
			return children;
	}
	for (int i = 0; i < MAX_NUMBER_OF_CHILDREN; i++) {
		Statistics childStats = getChildStatistics();
		bool sexOfTheChild = isChildMale(); // ChildSex does not sound well.
		Child newborn(childStats, sexOfTheChild);
		children.push_back(newborn);
	}
	return children;
}

bool Couple::isStraight() {
	return (
		(first->getIsMale() && !second->getIsMale()) ||
		(!first->getIsMale() && second->getIsMale())
	);
}

Statistics Couple::getChildStatistics() {
	return { 
		(first->getStats().intelligence + second->getStats().intelligence) / 2, // TODO: Handle it in the Statistics methods.  
		(first->getStats().dexterity + second->getStats().dexterity) / 2,
		(first->getStats().strength + second->getStats().strength) / 2
	};
}

bool Couple::isChildMale() {
	return Random::getRandomBool();
}