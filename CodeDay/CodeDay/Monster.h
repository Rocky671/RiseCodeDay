#pragma once

#include <string>

using namespace std;

class Monster
{
public:
	Monster() {}
	Monster(string inName, int inHealth, int lowerDamage, int higherDamage) { name = inName; health = inHealth; lowerDamageLimit = lowerDamage; upperDamageLimit = higherDamage; }
	~Monster() {}

	void getAttacked(int & damage) { 
		health -= damage;
	}

	string getName() { return name; }

	bool isDead() { return health <= 0; }

	int getHealth() { return health; }
	int getLowerDamageLimit() { return lowerDamageLimit; }
	int getUpperDamageLimit() { return upperDamageLimit; }

	// easy breezy cover girl
protected:
	int health;
	int lowerDamageLimit;
	int upperDamageLimit;

	string name;
};

