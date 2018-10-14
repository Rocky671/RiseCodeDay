#pragma once

#include <string>
#include "Player.h"
#include "Boss.h"

using namespace std;

class Room
{
public:
	Room()
	{
		// Set default values
		item = NEITHER;
		swordName = "";
		lowerDamage = 0;
		upperDamage = 0;
		moreHealth = 0;
		monster = false;
		boss = false;
		customMessage = "";
		empty = false;
	}
	Room(bool isEmpty)
	{
		empty = true;
	}
	~Room() {}

	void setRoomItem(string someItem, string someSwordName = "", int swordLowerDamage = 0, int swordUpperDamage = 0)
	{ 
		if (someItem == "potion")
		{
			item = POTION;

			return;
		}
		else if (someItem == "sword")
		{
			item = SWORD;

			swordName = someSwordName;
			lowerDamage = swordLowerDamage;
			upperDamage = swordUpperDamage;
		}
		else 
		{
			item = NEITHER;
		}
	}
	void removeRoomItem()
	{
		item = NEITHER;
		swordName = "";
		lowerDamage = 0;
		upperDamage = 0;
	}

	void setMonster(Monster newMonster) { roomMonster = newMonster; monster = true; }
	bool hasMonster() { return monster; }

	// We can't do this because it returns a copy of the monster so it won't modify the monster in the room
	// Monster getMonster() { return roomMonster; }
	Monster * getMonster() { return & roomMonster; }
	Boss * getBoss() { return & roomBoss; }

	// we might need to make the boss public
	void setBoss(Boss newBoss) { roomBoss = newBoss; boss = true; }
	bool hasBoss() { return boss; }

	bool hasSword() { return item == SWORD; }
	// we need to return sword damage as well
	string sword() { return swordName; }
	int swordLowerDamageLimit() { return lowerDamage; }
	int swordUpperDamageLimit() { return upperDamage; }

	bool hasPotion() { return item == POTION; }

	void setHealthIncrease(int healthIncrease) { moreHealth = healthIncrease; }
	bool hasHealthIncrease() { return moreHealth != 0; }
	int getHealthIncrease() { return moreHealth; }

	bool hasCustomMessage() { return customMessage.length() > 0; }
	void setCustomRoomMassage(string message) { customMessage = message; }
	string customRoomMessage() { return customMessage; }
	// easy peasy cover girl

	void increaseHealth(Player & hero) { hero.setMaxHealth(hero.getMaxHealth() + moreHealth); hero.setHealth(hero.getHealth() + moreHealth); }

	void setEmpty() { empty = true; }
	bool isEmpty() { return empty; }

private:
	enum roomItem { SWORD, POTION, NEITHER } item;
	string swordName;
	int lowerDamage;
	int upperDamage;

	int moreHealth;

	bool monster;
	Monster roomMonster;

	bool boss;
	Boss roomBoss;

	string customMessage;

	bool empty;

public:
	struct directions { bool up = true; bool down = true; bool left = true; bool right = true; } availableDirections;
};