#include <fstream>
#include <iostream>
#include <iomanip>
#include "IoService.hpp"
#include "Statistics.hpp"
#include "../lib/argh.h"
#include "../lib/json.hpp"

Parameters IoService::parseArgs(int argc, char *argv[]) {
	Parameters params;
	auto cmdl = argh::parser(argc, argv);

	if (cmdl[{ "-h", "--help" }]) {
		printHelp();
		return params;
	}
	if (!(cmdl({ "-e", "--epochs" }) >> params.epochs)) {
		std::cerr << "You should provide valid epochs number!" << '\n';
		printHelp();
		params.isHelp = true;
		return params;
	}
	if (!(cmdl({ "-ie", "--environment" }) >> params.inputEnvironmentFile)) {
		std::cerr << "You should provide valid input file for the environment!" << '\n';
		printHelp();
		params.isHelp = true;
		return params;
	}
	if (!(cmdl({ "-ip", "--population" }) >> params.inputPopulationFile)) {
		std::cerr << "You should provide valid input file for the population!" << '\n';
		printHelp();
		params.isHelp = true;
		return params;
	}

	cmdl({ "-op", "--outputPath" }) >> params.outputFilesPath;
	//cmdl({ "-oe", "--outputEnvironment" }) >> params.outputLogsFile;
	//cmdl({ "-op", "--outputPopulation" }) >> params.outputLogsFile;
	cmdl({ "-l", "--logs" }, "logs.json") >> params.outputLogsFile; // TODO: Delete it after refactor.

	params.isHelp = false;
	return params;
}

Environment IoService::readEnvironment(Parameters *parameters) {
	try {
		std::cout << "Reading environment from " << parameters->inputEnvironmentFile << std::endl;
		std::ifstream inputFile(parameters->inputEnvironmentFile);
		nlohmann::json jsonEnvironment;
		inputFile >> jsonEnvironment;

		Statistics minimalSurvivalStats;
		jsonEnvironment.at("srv_dexterity").get_to(minimalSurvivalStats.dexterity);
		jsonEnvironment.at("srv_intelligence").get_to(minimalSurvivalStats.intelligence);
		jsonEnvironment.at("srv_strength").get_to(minimalSurvivalStats.strength);

		Statistics minimalReproductionStats;
		jsonEnvironment.at("rep_dexterity").get_to(minimalReproductionStats.dexterity);
		jsonEnvironment.at("rep_intelligence").get_to(minimalReproductionStats.intelligence);
		jsonEnvironment.at("rep_strength").get_to(minimalReproductionStats.strength);

		Environment environment(minimalSurvivalStats, minimalReproductionStats);
		std::cout << "Environment read successfully!" << std::endl;
		return environment;
	}
	catch (std::exception &e) {
		std::cerr << "You should provide valid input file for the environment!" << '\n';
		std::cerr << "Error occured: " << e.what() << '\n';
		Environment environment;
		environment.initialize(); //TODO: Handle wrong input file with by closing program.
		std::cout << "Environment initialized with test data." << std::endl;
		return environment;
	}
}

PopulationRepository IoService::readPopulation(Parameters *parameters) {
	try {
		std::cout << "Reading population from " << parameters->inputPopulationFile << std::endl;
		std::ifstream inputFile(parameters->inputPopulationFile);
		nlohmann::json jsonPopulation;
		inputFile >> jsonPopulation;
		inputFile.close();

		if (!jsonPopulation.is_array()) {
			throw "Population file does not contain an array.";
		}
		if (jsonPopulation.empty()) {
			throw "Population file is empty.";
		}

		PopulationRepository populationRepository; // TODO: Make smaller function for that. It is huge right now.
		for (nlohmann::json::iterator it = jsonPopulation.begin(); it != jsonPopulation.end(); ++it) {
			auto person = it.value();
			if (person.at("personType") == "Adult") {
				Adult adult = readAdult(it);
				populationRepository.getAdults()->push_back(adult);
			}
			if (person.at("personType") == "Child") {
				Child child = readChild(it);
				populationRepository.getChildren()->push_back(child);
			}
			if (person.at("personType") == "Elder") {
				Elder elder = readElder(it);
				populationRepository.getElders()->push_back(elder);
			}
		}
		std::cout << "Population read successfully!" << std::endl;
		return populationRepository;
	}
	catch (std::exception &e) {
		std::cerr << "You should provide valid input file for the population!" << '\n';
		std::cerr << "Error occured: " << e.what() << '\n';
		PopulationRepository populationRepository;
		populationRepository.initialize(); //TODO: Handle wrong input file with by closing program.
		std::cout << "Population repository initialized with test data." << std::endl;
		return populationRepository;
	}
}

Child IoService::readChild(nlohmann::json::iterator person) { 	
	Statistics stats; // TODO: Make new function for that. Keep in mind that it should not be single function because adavanced stats could be different for every age!
	person.value().at("dexterity").get_to(stats.dexterity);
	person.value().at("intelligence").get_to(stats.intelligence);
	person.value().at("strength").get_to(stats.strength);
	bool isMale = person.value().at("isMale");
	Child child(stats, isMale);
	return child;
}

Adult IoService::readAdult(nlohmann::json::iterator person) { 	
	Statistics stats;
	person.value().at("dexterity").get_to(stats.dexterity);
	person.value().at("intelligence").get_to(stats.intelligence);
	person.value().at("strength").get_to(stats.strength);
	bool isMale = person.value().at("isMale");
	Adult adult(stats, isMale);
	return adult;
}

Elder IoService::readElder(nlohmann::json::iterator person) { 	
	Statistics stats;
	person.value().at("dexterity").get_to(stats.dexterity);
	person.value().at("intelligence").get_to(stats.intelligence);
	person.value().at("strength").get_to(stats.strength);
	bool isMale = person.value().at("isMale");
	Elder elder(stats, isMale);
	return elder;
}

void IoService::printHelp() {
	std::cout << "DarvinLogs is a simple population evolution symulator." << std::endl;
	std::cout << "Use flags below to run it:" << std::endl;
	std::cout << "	-h	--help          - to print this help page" << std::endl;
	std::cout << "	-e	--epochs        - to set number of epochs (required)" << std::endl;
	std::cout << "	-ie	--environment   - to set the path to input JSON environment file (required)" << std::endl;
	std::cout << "	-ip	--population    - to set the path to input JSON population file (required)" << std::endl;
	std::cout << "	-op	--outputPath    - to set the path for the output environment, population and logs files" << std::endl;
	std::cout << "	-l	--logs          - to set the custom path for output JSON logs file" << std::endl; // TODO: Delete it after refactor.
	std::cout << "Example usage: ./darwinLogs -e=12 -ie=data/env.json -ip=data/pop.json -op=data/output/\n";
}

void IoService::saveLogs(std::vector<Info> info, Parameters * parameters) {
	try {
		std::cout << "Saving logs to " << parameters->outputLogsFile << std::endl;
		std::vector<nlohmann::json> jsonVector;
		for (int i = 0; i < info.size(); i++) {
			jsonVector.push_back(info[i].toJson());
		}
		nlohmann::json jsonLogs(jsonVector);
		std::ofstream outputFile(parameters->outputLogsFile);
		outputFile << std::setw(4) << jsonLogs << std::endl;
		outputFile.close();
		std::cout << "Logs saved successfully!" << std::endl;
	} 
	catch (std::exception &e) {
		std::cerr << "Failed to save logs!" << std::endl;
		std::cerr << "Error occured: " << e.what() << std::endl;
	}
}

void IoService::saveEnvironment(Environment *environment, Parameters *parameters) {
	try {
		std::string outputFileName = parameters->outputFilesPath + "outputEnvironment.json";
		std::cout << "Saving environment to " << outputFileName << std::endl;
		nlohmann::json jsonEnvironment = environment->toJson();
		std::ofstream outputFile(outputFileName);
		outputFile << std::setw(4) << jsonEnvironment << std::endl;
		outputFile.close();
		std::cout << "Environment saved successfully!" << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Failed to save environment!" << std::endl;
		std::cerr << "Error occured: " << e.what() << std::endl;
	}
}

void IoService::savePopulation(PopulationRepository *populationRepository, Parameters *parameters) {
	try {
		std::string outputFileName = parameters->outputFilesPath + "outputPopulation.json";
		std::cout << "Saving population to " << outputFileName << std::endl;
		nlohmann::json jsonPopulation = populationRepository->toJson();
		std::ofstream outputFile(outputFileName);
		outputFile << std::setw(4) << jsonPopulation << std::endl;
		outputFile.close();
		std::cout << "Population saved successfully!" << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Failed to save population!" << std::endl;
		std::cerr << "Error occured: " << e.what() << std::endl;
	}
}

