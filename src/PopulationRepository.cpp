#include "PopulationRepository.hpp"

PopulationRepository::PopulationRepository() { 
}

PopulationRepository::~PopulationRepository() {
}

std::vector<Child>* PopulationRepository::getChildren() {
	return &children;
}

std::vector<Adult>* PopulationRepository::getAdults() {
	return &adults;
}

std::vector<Elder>* PopulationRepository::getElders() {
	return &elders;
}

void PopulationRepository::initialize() { // This is just a mock data for now.
	for (int i = 0; i < 5; i++) {
		Child child;
		children.push_back(child);
		Adult adult;
		adults.push_back(adult);
		Elder elder;
		elders.push_back(elder);
	}
}