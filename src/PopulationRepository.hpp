#ifndef POPULATION_REPOSITORY_HPP
#define POPULATION_REPOSITORY_HPP

#include <vector>
#include "Child.hpp"
#include "Adult.hpp"
#include "Elder.hpp"
#include "../lib/json.hpp"

class PopulationRepository {
public:
	PopulationRepository ();
	~PopulationRepository ();

	std::vector<Child>* getChildren();
	std::vector<Adult>* getAdults();
	std::vector<Elder>* getElders();

	void initialize();
	nlohmann::json toJson();

private:
	std::vector<Child> children;
	std::vector<Adult> adults;
	std::vector<Elder> elders;
};

#endif
