#ifndef POPULATION_SERVICE_HPP
#define POPULATION_SERVICE_HPP

#include <vector>
#include "PopulationRepository.hpp"
#include "Info.hpp"
#include "Couple.hpp"
#include "Midwife.hpp"

class PopulationService {
public:
	PopulationService ();
	PopulationService(PopulationRepository*);
	~PopulationService ();

	std::vector<Couple> pairCouples();
	void add(std::vector<Child>*);
	void killUnadaptedTo(Environment*);
	void growOlder();
	Info getPopulationInfo();

private:
	PopulationRepository * populationRepo = nullptr;

	Couple createCouple(bool * wasPaired);
	Adult * getRandomNotPairedAdult(bool * wasPaired);
};

#endif 

