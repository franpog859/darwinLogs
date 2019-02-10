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
	for (int i = 0; i < couples->size(); i++) {
		std::vector<Child> children = couples->at(i).begetChildren(environment);
		for (int j = 0; j < children.size(); j++) {
			embryos.push_back(children.at(j));
		}
	}
	return embryos;
}

std::vector<Child> Midwife::mutateEmbryos(std::vector<Child> * embryos) {
	std::vector<Child> newborns;
	for (int i = 0; i < embryos->size(); i++) {
		Statistics stats = embryos->at(i).getStats();
		bool sexOfTheChild = embryos->at(i).getIsMale();
		stats = mutateGenes(&stats);
		Child newborn(stats, sexOfTheChild);
		newborns.push_back(newborn);
	}
	return newborns;
}

Statistics Midwife::mutateGenes(Statistics * stats) {
	Statistics statistics = {
		stats->intelligence + (int)(Random::getRandomDouble() * (double)(MAX_MUTATION_CHANGE)-(double)(MAX_MUTATION_CHANGE) / 2), // TODO: It can be somewhere in Random class. Function like getRandomIntResultant(const int).
		stats->dexterity + (int)(Random::getRandomDouble() * (double)(MAX_MUTATION_CHANGE)-(double)(MAX_MUTATION_CHANGE) / 2),
		stats->strength + (int)(Random::getRandomDouble() * (double)(MAX_MUTATION_CHANGE)-(double)(MAX_MUTATION_CHANGE) / 2)
	};
	return statistics;
}
