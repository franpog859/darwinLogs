#ifndef CHILD_HPP
#define CHILD_HPP

#include "Person.hpp"
#include "Adult.hpp"

class Child : public Person {
public:
	Child();
	using Person::Person; // Change it to actual constructor with some parameters. It should be different for every type of person.
	~Child();

	Adult growOlder();
	nlohmann::json toJson();
};

#endif