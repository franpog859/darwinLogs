#ifndef ADULT_HPP
#define ADULT_HPP

#include "Person.hpp"
#include "Elder.hpp"

class Adult : public Person {
public:
	Adult();
	using Person::Person; // Change it to actual constructor with some parameters. It should be different for every type of person.
	~Adult();

	Elder growOlder();
	nlohmann::json toJson();
};

#endif