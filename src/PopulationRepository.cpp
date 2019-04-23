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

nlohmann::json PopulationRepository::toJson() {
	std::vector<nlohmann::json> jsonVector;
	for (int i = 0; i < children.size(); i++) {
		jsonVector.push_back(children[i].toJson());
	}
	for (int i = 0; i < adults.size(); i++) {
		jsonVector.push_back(adults[i].toJson());
	}
	for (int i = 0; i < elders.size(); i++) {
		jsonVector.push_back(elders[i].toJson());
	}
	nlohmann::json jsonPopulation(jsonVector);
	return jsonPopulation;
}