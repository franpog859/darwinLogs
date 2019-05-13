#include <iterator>
#include "Midwife.hpp"
#include "Random.hpp"

Midwife ::Midwife () {
}

Midwife ::~Midwife () {
}

std::vector<Child> Midwife::begetChildren(Environment * environment, std::vector<Couple> * couples) {
	std::vector<Child> embryos = giveBirths(environment, couples);
	std::vector<Child> newborns = mutateEmbryos(&embryos);
	return newborns;
}

std::vector<Child> Midwife::giveBirths(Environment * environment, std::vector<Couple> * couples) {
	std::vector<Child> embryos;
	for (std::vector<Couple>::iterator couple = couples->begin(); couple < couples->end(); couple++) {
		std::vector<Child> children = couple->begetChildren(environment);
		for (std::vector<Child>::iterator child = children.begin(); child < children.end(); child++) {
			embryos.push_back(*child);
		}
	}
	return embryos;
}

std::vector<Child> Midwife::mutateEmbryos(std::vector<Child> * embryos) {
	std::vector<Child> newborns;
	for (std::vector<Child>::iterator embryo = embryos->begin(); embryo < embryos->end(); embryo++) {
		Statistics stats = embryo->getStats();
		bool sexOfTheChild = embryo->getIsMale();
		stats = mutateGenes(&stats);
		Child newborn(stats, sexOfTheChild);
		newborns.push_back(newborn);
	}
	return newborns;
}

Statistics Midwife::mutateGenes(Statistics * stats) {
	Statistics mutation = {
		(int)(Random::getRandomDouble() * (double)(MAX_MUTATION_CHANGE)-(double)(MAX_MUTATION_CHANGE) / 2), 
		(int)(Random::getRandomDouble() * (double)(MAX_MUTATION_CHANGE)-(double)(MAX_MUTATION_CHANGE) / 2),
		(int)(Random::getRandomDouble() * (double)(MAX_MUTATION_CHANGE)-(double)(MAX_MUTATION_CHANGE) / 2)
	};
	return *stats + mutation;
}
