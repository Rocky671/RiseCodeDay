#include "Boss.h"

Boss::Boss() : Monster()
{

}

Boss::Boss(string inName, int inHealth, int lowerDamage, int higherDamage, string inDescription, string inYouKilledBossMessage, string inBossKilledYouMessage) : Monster(inName, inHealth, lowerDamage, higherDamage)
{
	description = inDescription;
	youKilledBossMessages = inYouKilledBossMessage;
	bossKilledYouMessages = inBossKilledYouMessage;
}

Boss::~Boss() {}