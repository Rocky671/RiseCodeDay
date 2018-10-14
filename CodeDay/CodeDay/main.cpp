/*
	This is our text-based game for CodeDay
*/

#include <iostream>
#include <string>
#include <ctime>

#include "Functions.h"
#include "Monster.h"
#include "Player.h"
#include "Room.h"

using namespace std;

int main()
{
	char direction;
	Player player;

	Room map[MAP_WIDTH][MAP_HEIGHT];
	struct { int x; int y; } currentRoom;
	int currentFloor = 0; // goes to 1 and 2 and since 2 is the last floor that finishes the game
	// Starting room coordinates
	currentRoom.x = 2, currentRoom.y = 4;

	generateRooms(map, currentFloor);

	// DON'T MOVE THIS FUNCTION
	srand(time(0));

	cout << "__          ___ _ _  __     __           _____  _          " << "\n"
		<< "\\ \\        / (_) | | \\ \\   / /          |  __ \\(_)         " << "\n"
		<< " \\ \\  /\\  / / _| | |  \\ \\_/ /__  _   _  | |__) |_ ___  ___ " << "\n"
		<< "  \\ \\/  \\/ / | | | |   \\   / _ \\| | | | |  _  /| / __|/ _ \\ " << "\n"
		<< "   \\  /\\  /  | | | |    | | (_) | |_| | | | \\ \\| \\__ \\  __/" << "\n"
		<< "    \\/  \\/   |_|_|_|    |_|\\___/ \\__,_| |_|  \\_\\_|___/\\___|" << endl;
	cout << "Enter your name: ";
	{
		string temp;
		getline(cin, temp);
		player.setName(temp);
	}

	//begin story
	cout << "They came during the cover of night. It's all your fault really, being the renowned warrior you are. Your fame attracted the attention of the once great king, an aging bastard who still clings to the former glory of his youth. King Arcien, upon hearing of your exploits, sent a messenger to give you a glorious quest. And yet you…You with all of your arrogance, thought you could deny the King without repercussions. And look now, at the consequences of your actions. Your childhood home, burning. Your family, taken. And all you have left in your hands is a letter, sending you to the deadliest area of the desert to find a library that might not exist, for a book that gives its reader godly power. Laughable. What will you do? What. Will. You. Do." << endl << endl;
	system("pause");
	cout << endl << "After weeks of wandering around the depths of the kingdom, begging, pleading, Praying for a guide to the unknown library, a stranger gives you a map. You wonder if you should trust it, you've been given maps before, only to be ambushed by those with less than honorable intentions. What else can you do? Follow it." << endl << endl;
	system("pause");
	cout << endl << "You travel far, dressed in a cloak with a hood, owning nothing else but the bag on your back and the rusty short sword by your side. Finally, you enter the desert of Karo. A large, desolate, unforgiving, land, dangerous to those even who know of it's trails." << endl << endl;
	system("pause");
	cout << endl << "Your move, " << player.getName() << ". Will you rise up and save your family on time? Or will you be among the thousands of decaying bodies littering the sand floors?" << endl << endl;
	system("pause");

	cout << endl << "You wake with sand all around you" << endl << endl;
	for (int i = 0; i < 3; i++)
	{
		getDirection();
		//text will be used from desert interation array
		int messageNumber = randomNumber(0, 7);
		cout << endl << desertMessages[messageNumber] << endl << endl;

	}
	getDirection();
	cout << "You see a structure ahead of you...It's the library!" << endl;
	cout << "You enter the library." << endl;

	do
	{
		do
		{
			char direction = getDirection(map[currentRoom.x][currentRoom.y].availableDirections.up, map[currentRoom.x][currentRoom.y].availableDirections.left, map[currentRoom.x][currentRoom.y].availableDirections.down, map[currentRoom.x][currentRoom.y].availableDirections.right);
			switch (direction)
			{
			case 'w':
				currentRoom.y--;
				break;
			case 'a':
				currentRoom.x--;
				break;
			case 's':
				currentRoom.y++;
				break;
			case 'd':
				currentRoom.x++;
				break;
			}

			// Say something about the room
			if (map[currentRoom.x][currentRoom.y].hasCustomMessage())
			{
				cout << map[currentRoom.x][currentRoom.y].customRoomMessage() << endl;
			}

			// If there's a boss, don't do the next things
			if (map[currentRoom.x][currentRoom.y].hasBoss())
			{
				break;
			}

			// TODO: when you enter a room, take the stuff out of it so you don't get it twice
			// Check if the room has something and then do it
			if (map[currentRoom.x][currentRoom.y].hasPotion())
			{
				cout << endl << "You got a potion!" << endl << endl;
				player.givePotion();
				// Remove the potion from the room
				map[currentRoom.x][currentRoom.y].setRoomItem("neither");
			}
			if (map[currentRoom.x][currentRoom.y].hasSword())
			{
				// Check if this sword is better and then give it to the player
				if (map[currentRoom.x][currentRoom.y].swordLowerDamageLimit() > player.swordLowerDamageLimit())
				{
					cout << endl << "You got a new, better sword! It is the " << map[currentRoom.x][currentRoom.y].sword() << " and it has a lower damage limit of " << map[currentRoom.x][currentRoom.y].swordLowerDamageLimit() << " and an upper damage limit of " << map[currentRoom.x][currentRoom.y].swordUpperDamageLimit() << endl << endl;
					player.pickUpSword(map[currentRoom.x][currentRoom.y].sword(), map[currentRoom.x][currentRoom.y].swordLowerDamageLimit(), map[currentRoom.x][currentRoom.y].swordUpperDamageLimit());
				}
				else
				{
					cout << endl << "You found a new sword, but it's worse than your current one; therefore, you did not pick it up." << endl << endl;
				}
				map[currentRoom.x][currentRoom.y].setRoomItem("neither");
			}
			if (map[currentRoom.x][currentRoom.y].hasHealthIncrease())
			{
				player.setMaxHealth(player.getMaxHealth() + map[currentRoom.x][currentRoom.y].getHealthIncrease());
				player.setHealth(player.getHealth() + map[currentRoom.x][currentRoom.y].getHealthIncrease());
				cout << "You've increased your maximum health by " << map[currentRoom.x][currentRoom.y].getHealthIncrease() << " HP!" << endl;
				// Remove increase from room
				map[currentRoom.x][currentRoom.y].setHealthIncrease(0);
			}
			// If it's a monster, do combart
			// we're breaking some things
			if (map[currentRoom.x][currentRoom.y].hasMonster())
			{
				Monster * theMonster = map[currentRoom.x][currentRoom.y].getMonster();
				bool stopFighting = false;

				if (theMonster->getHealth() > 0)
				{
					cout << monsterMessages[randomNumber(0, 3)] << theMonster->getName() << "!" << endl << endl;
				}

				while (theMonster->getHealth() > 0 && !stopFighting)
				{

					// Let the player have a turn
					char action = getAction();
					bool defending = false;

					cout << endl;

					switch (action)
					{
					case 'a':
					{
						// Atack
						int damage = randomNumberInclusive(player.swordLowerDamageLimit(), player.swordUpperDamageLimit());

						// Do damage to the monster
						// TODO: if damage is 0, say the user missed
						// whatever
						theMonster->getAttacked(damage);
						cout << hitMessages[randomNumber(0, 5)] << " You hit " << theMonster->getName() << " and did " << damage << " damage!";

						if (theMonster->isDead())
						{
							// Do something else
							cout << endl << winMessages[randomNumber(0, 5)];
							stopFighting = true;
						}
						break;
					}
					case 'd':
					{
						// Defend
						defending = true;
						break;
					}
					case 'p':
					{
						// Use a potion
						// There is no failsafe against using a potion if you already have full health
						// It's a feature
						if (player.usePotion())
						{
							cout << postionMessages[randomNumber(0, 2)] << player.getHealth() << " health";
						}
						else
						{
							cout << "You do not have potions to use";
						}
						break;
					}
					case 'r':
					{
						// Run
						int chanceToRun = randomNumber(0, 100);
						// 35% chance
						if (chanceToRun < 45)
						{
							stopFighting = true;
							cout << succsesfulRunawayMessages[randomNumber(0, 2)];
						}
						else
						{
							// TODO: put in successful/unsuccessful messages
							cout << failedRunawayMessages[randomNumber(0, 2)];
						}
						break;
					}
					}

					cout << endl << endl;

					if (stopFighting)
					{
						// The monster won't get an attack
						break;
					}

					if (defending)
					{
						// Reset defending so you are no longer defending
						defending = false;
						cout << "You defended successfully!" << endl;
						continue;
					}
					// Let the monster have a turn
					int monsterDamage = randomNumberInclusive(theMonster->getLowerDamageLimit(), theMonster->getUpperDamageLimit());
					player.getAttacked(monsterDamage);
					cout << theMonster->getName() << " attacked you for " << monsterDamage << " damage. You now have " << player.getHealth() << " HP remaining";

					if (player.isDead())
					{
						// oops! the player died
						cout << endl << loseMessages[randomNumber(0, 3)] << endl << endl;
						system("pause");
						return 0;
					}
					cout << endl << endl;
				}
				// This down here is what happens when the monster is dead or is already dead and the user is just now entering the tile or the user just ran away.
			}
		} while (!map[currentRoom.x][currentRoom.y].hasBoss());

		{
			char enterBossRoom;

			do
			{
				cout << "There is a boss in here. Would you like to enter? (Y/N) ";
				cin >> enterBossRoom;
				cin.ignore(256, '\n');
				enterBossRoom = tolower(enterBossRoom);
			} while (enterBossRoom != 'y' && enterBossRoom != 'n');

			if (enterBossRoom == 'n')
			{
				cout << "Ok! See you soon!" << endl;
				continue;
			}
		}

		// There is a boss here!
		Boss * theBoss = map[currentRoom.x][currentRoom.y].getBoss();
		
		cout << theBoss->getName() << endl << theBoss->getDescription() << endl;

		// TODO: check to make sure the user actually wants to fight at first or if he keeps fighting
		while (theBoss->getHealth() > 0)
		{
			// Let the player have a turn
			bool stopFighting = false;
			char action = getAction(true, false, true, false);

			cout << endl;

			switch (action)
			{
				case 'a':
				{
					// Atack
					int damage = randomNumberInclusive(player.swordLowerDamageLimit(), player.swordUpperDamageLimit());

					// Do damage to the monster
					// TODO: if damage is 0, say the user missed
					// whatever
					theBoss->getAttacked(damage);

					cout << hitMessages[randomNumber(0, 5)] << " You hit " << theBoss->getName() << " and did " << damage << " damage!";

					if (theBoss->isDead())
					{
						// Do something else
						
						cout << endl << theBoss->youKilledBossMessage();
						stopFighting = true;
					}
					break;
				}
				case 'p':
				{
					// Use a potion
					// There is no failsafe against using a potion if you already have full health
					// It's a feature
					if (player.usePotion())
					{
						cout << postionMessages[randomNumber(0, 2)] << player.getHealth() << " health";
					}
					else
					{
						cout << "You do not have potions to use";
					}
					break;
				}
			}

			cout << endl << endl;

			if (stopFighting)
			{
				// The monster won't get an attack
				break;
			}

			// Let the boss have a turn
			int monsterDamage = randomNumberInclusive(theBoss->getLowerDamageLimit(), theBoss->getUpperDamageLimit());
			player.getAttacked(monsterDamage);
			cout << theBoss->randomHitMessage();
			cout << theBoss->getName() << " attacked you for " << monsterDamage << " damage. You now have " << player.getHealth() << " HP remaining";

			if (player.isDead())
			{
				// oops! the player died
				cout << endl << theBoss->bossKilledYouMessage() << endl << endl;
				system("pause");
				return 0;
			}
			cout << endl << endl;
		}
		// This is where the boss dies
		// Give the player more health
		player.setMaxHealth(player.getMaxHealth() + 7);
		player.setHealth(player.getHealth() + 7);
		// Go down a floor
		currentFloor++;
		cout << "You went down a floor" << endl;
		generateRooms(map, currentFloor);
		// Set the player's location to the starting location
		currentRoom.x = 2, currentRoom.y = 4;
	} while (currentFloor < 3);

	// Ending
	cout << "The book...It...It exists! Relief spreads through your body as you take the book into your hands. Fantasies dance in your eyes, your vision blurs as you imagine yourself with the power of Gods. Why should you bend your knee to any who are beneath you? Why should you obey any commands other than your own? And then your memories come flooding back to you. The cold winters you spent with your family in front of the fireplace, the wonderful meals your mother would make you after a long day, the pride you saw in your father as he saw you grow. No amount of power is worth the risk of losing all that matters to you. If you lost all that you cared for, this life would be meaningless." << endl << endl;
	system("pause");
	cout << endl << "With this thought in your mind and the book in your arms, you leave the Library, which is already sinking and being reclaimed by the desert sands.You smile as you see the sun for the first time in what seemed like an eternity.Suddenly, a thought pops into your head.How much time has passed ? You've been gone for such a long time...Would the King think you had failed? That you had run away? Horror and dread rack your thoughts as you realize what the ruthless King would do if he thought you had betrayed him. In a panic, you start running." << endl << endl;
	system("pause");
	cout << endl << "You come across a nomad of the desert and coerce him into giving you his horse.You set a course directly for the castle, riding as hard as you dared without risking the health of the beast beneath you.After a few days of riding, you finally reach the village outside of the walls." << endl << endl;



	char castleVillagers;

	do
	{
		cout << "Would you like to go to the castle, or talk to the villagers? (C/V) ";
		cin >> castleVillagers;
		cin.ignore(256, '\n');
		castleVillagers = tolower(castleVillagers);
	} while (castleVillagers != 'c' && castleVillagers != 'v');

	if (castleVillagers == 'c')
	{
		// Castle ending
		cout << "No longer able to wait, you head straight for the castle. With a smile on your face, you stroll happily inside, eagerly awaiting the moment you see your family again. You enter the great hall and kneel before the king, presenting the book with your outstretched arms when suddenly, you feel pain in your back. You press the hand to the small of your back to feel a liquid pouring and you slowly realize... it's your blood. You look up at the king as his advisor removes the book from your hands and brings it to him. With a smug look on his face, the king thanks you for service and informs you that your family had been put to death weeks after you had begun your journey. As your vision fades to black, you see the King reading the book, slowly starting to glow. The last thing you see is the castle walls crashing around you as the King ascends to Godhood.";
	}
	else
	{
		// Villagers ending
		cout << "As you approach the villagers, you are met only with downcast eyes. Their gazes drift from yours as you try to catch the look of anyone. They wear shame as a mask, as if they have all done you some sort of harm. Slowly, you realize what has taken place. Slowly, you feel the dread creep up your spine until all at once, your world comes crashing down upon your head. You fall to your knees as you scream at the skies, cursing the day of your infamy. The villagers stare at you in sympathy, having all witnessed the brutal public deaths of your family. You reach into your bag and pull out the book, no longer caring for the world, for yours had just burned away. You read the first line and you feel your humanity seeping away. One paragraph in and you begin to feel your skin burning with power. You turn the page and begin to wonder the purpose of life itself. As you finish the book, only one emotion is left in your body, anger. The villagers run in terror as your aura incinerates anyone close to you, the world trembles beneath your feet as you step forward. The heavens themselves have begun weeping, for the reign of " << player.getName() << " has begun.";
	}

	cout << endl << endl;

	system("pause");

	return 0;
}