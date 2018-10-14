#pragma once

#include <vector>

#include "Monster.h"

using namespace std;

class Boss : public Monster
{
public:
	Boss();
	Boss(string inName, int inHealth, int lowerDamage, int higherDamage, string inDescription, string inYouKilledBossMessage, string inBossKilledYouMessage);
	~Boss();

	string getDescription() { return description; }

	string randomHitMessage()
	{
		vector<string>::const_iterator it = hitMessages.begin();
		it += randomNumber(hitMessages.size());
		return (*it);
	}
	void addRandomHitMessage(string message) { hitMessages.push_back(message); }

	string bossKilledYouMessage() { return bossKilledYouMessages; }
	string youKilledBossMessage() { return youKilledBossMessages; }

private:
	string description;
	vector<string> hitMessages;

	string bossKilledYouMessages;
	string youKilledBossMessages;

	int randomNumber(int max)
	{
		return rand() % max;
	}
};
