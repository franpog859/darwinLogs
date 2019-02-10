#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <chrono>

class Random {
public:
	static void initialize();
	static double getRandomDouble();
	static bool getRandomBool();

private:
	static std::default_random_engine engine;
	static std::uniform_real_distribution<double> distribution;
};

#endif 
