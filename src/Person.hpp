#ifndef PERSON_HPP
#define PERSON_HPP

#include "Statistics.hpp"
#include "Environment.hpp"

class Person {
public:
	Person ();
	Person(Statistics statistics, bool isMale);
	~Person ();

	bool canReproduce(Environment*);
	bool canSurvive(Environment*);
	bool getIsMale();
	Statistics getStats();

protected:	
	Statistics stats;
	bool isMale = true;
};

#endif