#ifndef ELDER_HPP
#define ELDER_HPP

#include "Person.hpp"

class Elder : public Person {
public:
	Elder();
	using Person::Person; // Change it to actual constructor with some parameters. It should be different for every type of person.
	~Elder();

	void growOlder();
	nlohmann::json toJson();
};

#endif