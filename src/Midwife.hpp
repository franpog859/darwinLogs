#ifndef MIDWIFE_HPP
#define MIDWIFE_HPP

#include <vector>
#include "Environment.hpp"
#include "Child.hpp"
#include "Couple.hpp"
#include "Statistics.hpp"

const int MAX_MUTATION_CHANGE = 10;

class Midwife {
public:
	Midwife ();
	~Midwife ();

	std::vector<Child> begetChildren(Environment * environment, std::vector<Couple> * couples);

private:
	std::vector<Child> giveBirths(Environment * environment, std::vector<Couple> * couples);
	std::vector<Child> mutateEmbryos(std::vector<Child> * embryos);
	Statistics mutateGenes(Statistics * stats);
};

#endif 
