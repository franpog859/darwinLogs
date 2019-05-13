#include <fstream>
#include <regex>
#include <iostream>
#include <iomanip>
#include "IoService.hpp"
#include "Statistics.hpp"
#include "Exceptions.hpp"
#include "../lib/argh.h"
#include "../lib/json.hpp"
#include "../lib/csvfile.h"

Parameters IoService::parseArgs(int argc, char *argv[]) {
	Parameters params;
	auto cmdl = argh::parser(argc, argv);

	if (cmdl[{ "-h", "--help" }]) {
		throw HelpException();
	}
	if (!(cmdl({ "-e", "--epochs" }) >> params.epochs)) {
		throw InvalidEpochsParameterException();
	}
	if (!(cmdl({ "-ie", "--environment" }) >> params.inputEnvironmentFile)) {
		throw InvalidEnvironmentParameterException();
	}
	if (!(cmdl({ "-ip", "--population" }) >> params.inputPopulationFile)) {
		throw InvalidPopulationParameterException();
	}

	cmdl({ "-opp", "--outputPopulation" }, "outputPopulation.json") >> params.outputPopulationFile;
	cmdl({ "-oe", "--outputEnvironment" }, "outputEnvironment.json") >> params.outputEnvironmentFile; 
	cmdl({ "-l", "--logs" }, "logs.csv") >> params.outputLogsFile;
	cmdl({ "-op", "--outputPath" }) >> params.outputFilesPath;

	if (!validateParams(&params)) {
		throw InvalidValuesException();
	}

	return params;
}

bool IoService::validateParams(Parameters * params) {
	std::regex inputFileRegex("([a-zA-Z]+/)*[a-zA-Z]+\\.json");
	if (!std::regex_match(params->inputEnvironmentFile, inputFileRegex)) {
		return false;
	}
	if (!std::regex_match(params->inputPopulationFile, inputFileRegex)) {
		return false;
	}

	std::regex outputPathRegex("(../)*([a-zA-Z]+/)*");
	if (!std::regex_match(params->outputFilesPath, outputPathRegex)) {
		return false;
	}

	std::regex outputJSONFileRegex("([a-zA-Z]+\\.json)*");
	if (!std::regex_match(params->outputEnvironmentFile, outputJSONFileRegex)) {
		return false;
	}
	if (!std::regex_match(params->outputPopulationFile, outputJSONFileRegex)) {
		return false;
	}

	std::regex outputCSVFileRegex("([a-zA-Z]+\\.csv)*");
	if (!std::regex_match(params->outputLogsFile, outputCSVFileRegex)) {
		return false;
	}
	return true;
}

void IoService::printHelp() {
	std::cout << "DarwinLogs is a simple population evolution symulator." << std::endl;
	std::cout << "Use flags below to run it:" << std::endl;
	std::cout << "  -h     --help                  - to print this help page" << std::endl;
	std::cout << "  -e     --epochs                - to set number of epochs (required)" << std::endl;
	std::cout << "  -ie    --environment           - to set the path + name to input JSON environment file (required)" << std::endl;
	std::cout << "  -ip    --population            - to set the path + name to input JSON population file (required)" << std::endl;
	std::cout << "  -op    --outputPath            - to set the custom path for the output files" << std::endl;
	std::cout << "  -l     --logs                  - to set the custom name for the output CSV logs file" << std::endl; 
	std::cout << "  -opp   --outputPopulation      - to set the custom name for the output JSON population file" << std::endl; 
	std::cout << "  -oe    --outputEnvironment     - to set the custom name for the output JSON environment file" << std::endl; 
	std::cout << "Example usage: ./darwinLogs -e=12 -ie=data/env.json -ip=data/pop.json -op=data/output/\n";
}

Environment IoService::readEnvironment(Parameters *parameters) {
	try {
		std::cout << "Reading environment from " << parameters->inputEnvironmentFile << std::endl;
		std::ifstream inputFile(parameters->inputEnvironmentFile);
		nlohmann::json jsonEnvironment;
		inputFile >> jsonEnvironment;

		if (jsonEnvironment.empty()) {
			throw EmptyFileException();
		}

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
		std::cerr << "Error occured: " << e.what() << '\n';
		throw ReadEnvironmentException();
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
			throw NotArrayException();
		}
		if (jsonPopulation.empty()) {
			throw EmptyFileException();
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
		std::cerr << "Error occured: " << e.what() << '\n';
		throw ReadPopulationException();
	}
}

Child IoService::readChild(nlohmann::json::iterator person) { 	
	Statistics stats = readStatistics(person);
	bool isMale = person.value().at("isMale");
	Child child(stats, isMale);
	return child;
}

Statistics IoService::readStatistics(nlohmann::json::iterator person) {
	Statistics stats; // TODO: Keep in mind that it should not be single function because adavanced stats could be different for every age!
	person.value().at("dexterity").get_to(stats.dexterity);
	person.value().at("intelligence").get_to(stats.intelligence);
	person.value().at("strength").get_to(stats.strength);
	return stats;
}

Adult IoService::readAdult(nlohmann::json::iterator person) { 	
	Statistics stats = readStatistics(person);
	bool isMale = person.value().at("isMale");
	Adult adult(stats, isMale);
	return adult;
}

Elder IoService::readElder(nlohmann::json::iterator person) { 	
	Statistics stats = readStatistics(person);
	bool isMale = person.value().at("isMale");
	Elder elder(stats, isMale);
	return elder;
}

void IoService::saveLogs(std::vector<Info> *info, Parameters *parameters) {
	try {
		std::string outputFileName = parameters->outputFilesPath + parameters->outputLogsFile;
		std::cout << "Saving logs to " << outputFileName << std::endl;
		csvfile outputFile(outputFileName);
		outputFile << "epoch" << "children_number" << "adults_number" << "elders_number" << "males_number" <<
			"females_number" << "adult_males_number" << "adult_females_number" << "deaths_number" << 
			"newborns_number" << "straight_couples_number" << "homo_couples_number" <<
			"average_child_dexterity" << "average_child_intelligence" << "average_child_strength" <<
			"average_adult_dexterity" << "average_adult_intelligence" << "average_adult_strength" <<
			"average_elder_dexterity" << "average_elder_intelligence" << "average_elder_strength" <<
			"average_dexterity" << "average_intelligence" << "average_strength" <<
			"minimal_survival_dexterity" << "minimal_survival_intelligence" << "minimal_survival_strength" <<
			"minimal_reproduction_dexterity" << "minimal_reproduction_intelligence" << "minimal_reproduction_strength" << endrow;
		for (int i = 0; i < info->size(); i++) {
			Info singleInfo = info->at(i);
			outputFile << i << singleInfo.childrenNumber << singleInfo.adultsNumber << singleInfo.eldersNumber <<
				singleInfo.maleNumber << singleInfo.femaleNumber << singleInfo.maleAdultNumber <<
				singleInfo.femaleAdultNumber << singleInfo.deathsNumber << singleInfo.newbornsNumber <<
				singleInfo.straightCouplesNumber << singleInfo.homoCouplesNumber <<
				singleInfo.averageChildsStatistics.dexterity << singleInfo.averageChildsStatistics.intelligence << singleInfo.averageChildsStatistics.strength <<
				singleInfo.averageAdultsStatistics.dexterity << singleInfo.averageAdultsStatistics.intelligence << singleInfo.averageAdultsStatistics.strength <<
				singleInfo.averageEldersStatistics.dexterity << singleInfo.averageEldersStatistics.intelligence << singleInfo.averageEldersStatistics.strength <<
				singleInfo.averageStatistics.dexterity << singleInfo.averageStatistics.intelligence << singleInfo.averageStatistics.strength <<
				singleInfo.minimalSurvivalStatistics.dexterity << singleInfo.minimalSurvivalStatistics.intelligence << singleInfo.minimalSurvivalStatistics.strength <<
				singleInfo.minimalReproductionStatistics.dexterity << singleInfo.minimalReproductionStatistics.intelligence << singleInfo.minimalReproductionStatistics.strength << endrow;
		}
		std::cout << "Logs saved successfully!" << std::endl;
	} 
	catch (std::exception &e) {
		std::cerr << "Error occured: " << e.what() << std::endl;
		throw SaveLogsException();
	}
}

void IoService::saveEnvironment(Environment *environment, Parameters *parameters) {
	try {
		std::string outputFileName = parameters->outputFilesPath + parameters->outputEnvironmentFile;
		std::cout << "Saving environment to " << outputFileName << std::endl;
		nlohmann::json jsonEnvironment = environment->toJson();
		std::ofstream outputFile(outputFileName);
		outputFile << std::setw(4) << jsonEnvironment << std::endl;
		outputFile.close();
		std::cout << "Environment saved successfully!" << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Error occured: " << e.what() << std::endl;
		throw SaveEnvironmentException();
	}
}

void IoService::savePopulation(PopulationRepository *populationRepository, Parameters *parameters) {
	try {
		std::string outputFileName = parameters->outputFilesPath + parameters->outputPopulationFile;
		std::cout << "Saving population to " << outputFileName << std::endl;
		nlohmann::json jsonPopulation = populationRepository->toJson();
		std::ofstream outputFile(outputFileName);
		outputFile << std::setw(4) << jsonPopulation << std::endl;
		outputFile.close();
		std::cout << "Population saved successfully!" << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Error occured: " << e.what() << std::endl;
		throw SavePopulationException();
	}
}

