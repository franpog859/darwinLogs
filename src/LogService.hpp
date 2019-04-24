#ifndef LOG_SERVICE_HPP
#define LOG_SERVICE_HPP

#include "Environment.hpp"
#include "PopulationService.hpp"

class LogService {
public:
	static void printLogs();
	static std::vector<Info>* getLogs();
	static void saveBuiltInfo();

	static void addGeneralInfo(Environment *environment, PopulationService *populationService);
	static void addCouplesInfo(std::vector<Couple> *couples);
	static void addNewbornsInfo(std::vector<Child> *newborns);
	static void addDeathsInfo(std::vector<Person> *deadPeople);

private:
	static Info infoBuilder;

	static std::vector<Info> info;
};

#endif
