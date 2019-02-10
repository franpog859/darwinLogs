#include "Random.hpp"

std::default_random_engine Random::engine;

std::uniform_real_distribution<double> Random::distribution;

void Random::initialize() {
	auto time = std::chrono::system_clock::now();
	auto interval = time.time_since_epoch();
	engine.seed(interval.count());
}

double Random::getRandomDouble() {
	return distribution(engine);
}

bool Random::getRandomBool() {
	return getRandomDouble() < 0.5;
}