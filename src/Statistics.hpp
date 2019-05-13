#ifndef STATISTICS_HPP
#define STATISTICS_HPP

struct Statistics { 
	int intelligence = 0;
	int dexterity = 0;
	int strength = 0;

	Statistics &operator +=(const Statistics stats) {
		this->dexterity += stats.dexterity;
		this->intelligence += stats.intelligence;
		this->strength += stats.strength;
		return *this;
	}

	Statistics &operator /=(const int div) {
		this->dexterity /= div;
		this->intelligence /= div;
		this->strength /= div;
		return *this;
	}

	Statistics operator +(const Statistics addend) {
		Statistics statistics;
		statistics += *this;
		statistics += addend;
		return statistics;
	}
};

#endif 
