#ifndef STATISTICS_HPP
#define STATISTICS_HPP

struct Statistics { //TODO: Add operators +Statistics and +int to the struct.
	int intelligence = 0;
	int dexterity = 0;
	int strength = 0;

	Statistics operator +=(const Statistics stats) {
		return {
			intelligence + stats.intelligence,
			dexterity + stats.dexterity,
			strength + stats.strength
		};
	}

	Statistics operator /=(const int div) {
		return {
			intelligence / div,
			dexterity / div,
			strength  / div
		};
	}
};

#endif 
