#pragma once

#include <iostream>
#include <string>
#include "Monster.h"
#include "Functions.h"

using namespace std;

class Player
{
public:
	Player() {
		swordName = "Short Sword";
		health = 20;
		maxHealth = 20;
		potions = 0;
		lowerDamageLimit = 1;
		upperDamageLimit = 5;
	}
	~Player() {}

	string getName() { return name; }
	void setName(string inName) { name = inName; }

	int getHealth() { return health; }
	int getMaxHealth() { return maxHealth; }
	void setHealth(int inHealth) { health = inHealth; }
	void setMaxHealth(int inHealth) { maxHealth = inHealth; }

	void inventory()
	{
		cout << "You have " << potions << " potions and you have the " << swordName << " sword";
	}

	void getAttacked(int damage) {
		for (int i = 0; i < damage && health > 0; i++, health--);
	}
	bool isDead() { return health <= 0; }

	void pickUpSword(string name, int lowerDamage, int higherDamage) { swordName = name; lowerDamageLimit = lowerDamage; upperDamageLimit = higherDamage; }

	void givePotion() { potions++; }
	bool usePotion() {
		if (potions > 0) {
			// take away a potion
			potions--;

			// potions heal for 5 up to max health
			for (int i = 0; i < 10 && health < maxHealth; i++, health++);

			// return true because you were able to use a potion
			return true;
		}

		// not able to use a potion
		return false;
	}

	int swordLowerDamageLimit() { return lowerDamageLimit; }
	int swordUpperDamageLimit() { return upperDamageLimit; }

private:
	string name;

	int health;
	int maxHealth;
	int potions;

	string swordName;
	int lowerDamageLimit;
	int upperDamageLimit;

	// we have a pet cricket
};

