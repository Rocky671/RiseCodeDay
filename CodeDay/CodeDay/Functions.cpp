#include "Functions.h"

int randomNumber(int min, int max)
{
	return (rand() % max) + min;
}

int randomNumberInclusive(int min, int max)
{
	int random = rand();
	// TODO: fix this so that it doesn't generate numbers outside the range
	return (random % (max + 1 - min)) + min;
}

char getDirection(bool up, bool left, bool down, bool right)
{
	char direction;

	cout << "Which direction will you go?";
	cout << endl << endl;

	if (up)
	{
		cout << "\t" << "W) Up" << endl;
	}

	if (left)
	{
		cout << "\t" << "A) Left" << endl;
	}

	if (down)
	{
		cout << "\t" << "S) Down" << endl;
	}

	if (right)
	{
		cout << "\t" << "D) Right" << endl;
	}

	cout << endl;

	do
	{
		cout << "> ";
		cin >> direction;
		cin.ignore(256, '\n');

		direction = tolower(direction);
		if (!(up && direction == 'w') && !(left && direction == 'a') && !(down && direction == 's') && !(right && direction == 'd'))
		{
			cout << "Please enter a valid value" << endl;
		}
	} while (!(up && direction == 'w') && !(left && direction == 'a') && !(down && direction == 's') && !(right && direction == 'd'));

	return direction;
}

char getAction(bool attack, bool defend, bool potion, bool run)
{
	char action;

	cout << "What would you like to do?";
	cout << endl << endl;

	if (attack)
	{
		cout << "\t" << "A) Attack" << endl;
	}

	if (defend)
	{
		cout << "\t" << "D) Defend" << endl;
	}

	if (potion)
	{
		cout << "\t" << "P) Potion" << endl;
	}

	if (run)
	{
		cout << "\t" << "R) Run" << endl;
	}

	cout << endl;

	do
	{
		cout << "> ";
		cin >> action;
		cin.ignore(256, '\n');

		action = tolower(action);
		if (!(attack && action == 'a') && !(defend && action == 'd') && !(potion && action == 'p') && !(run && action == 'r'))
		{
			cout << "Please enter a valid value" << endl;
		}
	} while (!(attack && action == 'a') && !(defend && action == 'd') && !(potion && action == 'p') && !(run && action == 'r'));

	return action;
}

void generateRooms(Room (&rooms)[MAP_WIDTH][MAP_HEIGHT], int floor)
{
	//"You enter a hallway", "You find some stairs and head deeper into the library"
	int health = 10 + 5 * floor;

	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			// Generate a default room for every room except rooms that don't exist
			rooms[i][j] = Room();

			// If the room is an edge, set the movable directions so they can't exit the grid
			// now how do i do that
			if (i == 0)
			{
				rooms[i][j].availableDirections.left = false;
			}
			if (i == MAP_WIDTH - 1)
			{
				rooms[i][j].availableDirections.right = false;
			}
			if (j == 0)
			{
				rooms[i][j].availableDirections.up = false;
			}
			if (j == MAP_HEIGHT - 1)
			{
				rooms[i][j].availableDirections.down = false;
			}
		}
	}

	if (floor == 0)
	{
		// Floor 0
		// Monsters
		Monster monster1Floor1("Dogface", health, 1, 3);
		Monster monster2Floor1("Sparky", health, 1, 1);
		Monster monster3Floor1("Vampire", health, 0, 2);
		Monster monster4Floor1("Wolf", health, 0, 1);

		Boss bossFloor1("WereDemon", health + 15, 4, 6,"Once a human, it has now been twice cursed, straying further and further from God's light. There is nothing left of it to save, nothing to salvage. Its humanity is nonexistent, strike without mercy! But be careful, he is much more powerful than anything you've faced so far...", "You have given this creature a well deserved deat...Who knows how many more it would have slain.", "With its left claw around your waist and it's right claw around your neck, the Weredemon descends upon your exposed face...");
		bossFloor1.addRandomHitMessage("The Weredemon rakes his claws across your chest!");
		bossFloor1.addRandomHitMessage("The Weredemon sinks his jaws into your arm!");
		bossFloor1.addRandomHitMessage("The Weredemon's claws graze your arm!");

		// These are empty spaces
		rooms[0][1].setEmpty();
		rooms[1][3].setEmpty();
		rooms[4][2].setEmpty();
		//room messages
		rooms[0][0].setCustomRoomMassage("");
		rooms[0][2].setCustomRoomMassage("You hear a crackle in the air.");
		rooms[0][3].setCustomRoomMassage("There's something on the floor...");
		rooms[0][4].setCustomRoomMassage("There's something slippery on the floor...You don't look down.");
		rooms[1][0].setCustomRoomMassage("What is this strange looking creature...");
		rooms[1][1].setCustomRoomMassage("Hmm...That looks useful.");
		rooms[1][2].setCustomRoomMassage("...It smells awful in here.");
		rooms[1][4].setCustomRoomMassage("Skeletons litter the floor.");
		rooms[2][0].setCustomRoomMassage("There's an awful stench in the air, You almost gag as you proceed through the room.");
		rooms[2][1].setCustomRoomMassage("Oh! Another person! Why does he have fangs...");
		rooms[2][2].setCustomRoomMassage("Armor! This will come in handy.");
		rooms[2][3].setCustomRoomMassage("You hear snarling as you enter the room.");
		rooms[2][4].setCustomRoomMassage("It's so dark in here....");
		rooms[3][0].setCustomRoomMassage("You see something move in the corner of the room, you ignore it.");
		rooms[3][1].setCustomRoomMassage("You step into the room and hear a crack, you don't look down.");
		rooms[3][2].setCustomRoomMassage("There's an awful lot of bodies in here...");
		rooms[3][3].setCustomRoomMassage("You begin to wonder if you'll ever see the sun again.");
		rooms[3][4].setCustomRoomMassage("There's a glint on the floor.");
		rooms[4][0].setCustomRoomMassage("Hmm... It seems we've hit a corner.");
		rooms[4][1].setCustomRoomMassage("Whoa...It's a sword!");
		rooms[4][3].setCustomRoomMassage("There's nothing in this room.");
		rooms[4][4].setCustomRoomMassage("It seems we've hit a corner.");
		

		// Setting stuff per room
		rooms[0][0].setBoss(bossFloor1); // This one is a boss
		rooms[1][0].setMonster(monster1Floor1);
		rooms[1][1].setRoomItem("potion");
		rooms[0][2].setMonster(monster2Floor1);
		rooms[4][1].setRoomItem("sword", "Viper", 3, 7);
		rooms[2][1].setMonster(monster3Floor1);
		rooms[2][2].setHealthIncrease(5); // gets 5 more max health
		rooms[0][3].setRoomItem("potion");
		rooms[2][3].setMonster(monster4Floor1);
		rooms[3][4].setRoomItem("potion");
		rooms[2][0].setRoomItem("potion");
	}

	if (floor == 1)
	{
		// Floor 1
		
		Monster monster1Floor2("Slayer", health, 1, 2);
		Monster monster2Floor2("Zombat", health, 2, 3);
		Monster monster3Floor2("WereDragon", health, 2, 5);
		Monster monster4Floor2("Basilisk", health, 2, 4);
		
		Boss bossFloor2("Mimic", health + 12, 6, 10,"...This can't be right. Your father is standing before you... why is he here? How is he here? He calls out to you, smiling as he asks you to embrace him. He can't be here...He just can't! You scream at your own father even as he grins back at you when you finally convince yourself that there's no way he can be here. With anger written all over your face, you charge.", "You stare at the corpse on your blade, changing from your father to your mother to your sister. Tears fill your eyes as you wonder if you've actually slain your family by your own hands, until finally the grotesque reality of the mimic appears and takes its last breath.", "As your Father comes charging at you, you can't bring yourself to lift your arms. Your Mother raises her sword to strike you, and yet your body won't obey to block. Finally, the last vision you see is your sisters sword coming straight for your eyes.");
		bossFloor2.addRandomHitMessage("The mimic has changed shape and landed a hit in the form of your sister!");
		bossFloor2.addRandomHitMessage("Your Father swings his sword at you!");
		bossFloor2.addRandomHitMessage("Your mother stabs you with her dagger!");
		bossFloor2.addRandomHitMessage("Your sister has slapped you!");

		// These are empty spaces
		rooms[0][0].setEmpty();
		rooms[1][2].setEmpty();
		rooms[1][4].setEmpty();
		rooms[3][2].setEmpty();
		rooms[4][4].setEmpty();

		//room messages
		rooms[0][1].setCustomRoomMassage("Is... Is that a dragon?");
		rooms[0][2].setCustomRoomMassage("Another sword!");
		rooms[0][3].setCustomRoomMassage("You hear something moving around in the darkness, you don't look.");
		rooms[0][4].setCustomRoomMassage("");

		rooms[1][0].setCustomRoomMassage("There's something on the floor.");
		rooms[1][1].setCustomRoomMassage("The horrors in this room, God has abandoned this place.");
		rooms[1][3].setCustomRoomMassage("With every step you stray further and further from the sun.");

		rooms[2][0].setCustomRoomMassage("now That's a weird looking creature...");
		rooms[2][1].setCustomRoomMassage("This room smells awful.");
		rooms[2][2].setCustomRoomMassage("This guy's carrying an awfully large sword.");
		rooms[2][3].setCustomRoomMassage("This room has an extraordinary amount of books.");
		rooms[2][4].setCustomRoomMassage("This is a well lit room.");

		rooms[3][0].setCustomRoomMassage("Another piece of armor!");
		rooms[3][1].setCustomRoomMassage("Just how much time has passed?");
		rooms[3][3].setCustomRoomMassage("There's something on the ground.");
		rooms[3][4].setCustomRoomMassage("There's not much to see in this room.");

		rooms[4][0].setCustomRoomMassage("There's something shiny in here.");
		rooms[4][1].setCustomRoomMassage("The walls are covered in slime, You don't stay long.");
		rooms[4][3].setCustomRoomMassage("There's armor on the floor, but it's way too broken to use.");


		//setting stuff per room
		rooms[0][4].setBoss(bossFloor2); // This one is a boss

		rooms[2][2].setMonster(monster1Floor2);
		rooms[4][2].setMonster(monster2Floor2);
		rooms[0][1].setMonster(monster3Floor2);
		rooms[2][0].setMonster(monster4Floor2);

		rooms[3][3].setRoomItem("potion");
		rooms[1][0].setRoomItem("potion");
		rooms[4][0].setRoomItem("potion");
		rooms[0][3].setRoomItem("potion");

		rooms[0][2].setRoomItem("sword", "Ginvel", 6, 12);
		rooms[3][0].setHealthIncrease(5); // gets 5 more max health
	}
	
	if (floor == 2)
	{
		// Floor 2
		
		Monster monster1Floor3("Zombie", health, 3, 6);
		Monster monster2Floor3("Griffin", health, 3, 5);
		Monster monster3Floor3("PurpleEye", health, 5, 7);
		Monster monster4Floor3("MummyWolf", health, 4, 8);
		
		Boss bossFloor3("Uncrowned King", health + 12, 8, 15, "Power emanates from his very being, sorrow and despair overpowers your every emotion. Every terrible memory flows into your mind. Your first heartbreak, your first wound, the first scrape on your knee. Every horrible feeling, every destructive emotion you've ever felt, every time you've ever been hurt overwhelms you. You feel your soul begging to be released from your body, all you want is to fall on your knees and die, until you see him step forward. You grit your teeth and bare the pain, readying yourself to fight for your very soul.", "You stare into the Uncrowned Kings eyes as life abandons his body. A whisper leaves his mouth, He has thanked you for bringing an end to his unholy reign.", "The Uncrowned King stares into your eyes as he plunges his sword into your chest. Your vision fades as you see sadness written on his face, almost as if he wished you would have won the fight.");
		bossFloor3.addRandomHitMessage("The King has delivered a devastating blow!");
		bossFloor3.addRandomHitMessage("The King blasts the ground beneath your feet with magic!");
		bossFloor3.addRandomHitMessage("The King calmly walks towards you and sends you flying!");


		// These are empty spaces
		rooms[1][0].setEmpty();
		rooms[0][2].setEmpty();
		rooms[1][4].setEmpty();
		rooms[3][0].setEmpty();
		rooms[4][4].setEmpty();

		//room messages
		//room messages
		rooms[0][0].setCustomRoomMassage("Whoa, This sword looks powerful!");
		rooms[0][1].setCustomRoomMassage("You hear a groaning as you enter the room.");
		rooms[0][3].setCustomRoomMassage("You hear the flapping of wings as you enter.");
		rooms[0][4].setCustomRoomMassage("This... Now THIS is a sword!!");

		rooms[1][1].setCustomRoomMassage("There's not much to see in here.");
		rooms[1][2].setCustomRoomMassage("There's something on the ground.");
		rooms[1][3].setCustomRoomMassage("It looks like a torture chamber.");

		rooms[2][0].setCustomRoomMassage("");
		rooms[2][1].setCustomRoomMassage("Chains hang from the ceiling.");
		rooms[2][2].setCustomRoomMassage("You see purple eyes glowing in the darkness.");
		rooms[2][3].setCustomRoomMassage("This room has an extraordinary amount of books.");
		rooms[2][4].setCustomRoomMassage("You hear a roaring in the distance.");

		rooms[3][1].setCustomRoomMassage("There are body parts everywhere, whatever did this wasn't human.");
		rooms[3][2].setCustomRoomMassage("Slave chains litter the floor, all broken.");
		rooms[3][3].setCustomRoomMassage("You trip as you enter the room, You get up and never wonder why.");
		rooms[3][4].setCustomRoomMassage("Oh! This will be useful.");

		rooms[4][0].setCustomRoomMassage("Another piece of armor!");
		rooms[4][1].setCustomRoomMassage("So many bodies... So many.");
		rooms[4][2].setCustomRoomMassage("This will definitely be useful.");
		rooms[4][3].setCustomRoomMassage("Is...Is that a wolf wrapped in bandages?");

		//setting stuff per room
		rooms[2][0].setBoss(bossFloor3); // This one is a boss

		rooms[0][1].setMonster(monster1Floor3);
		rooms[0][3].setMonster(monster2Floor3);
		rooms[2][2].setMonster(monster3Floor3);
		rooms[4][3].setMonster(monster4Floor3);

		rooms[1][2].setRoomItem("potion");
		rooms[3][4].setRoomItem("potion");
		rooms[4][2].setRoomItem("potion");
		rooms[2][1].setRoomItem("potion");

		rooms[0][0].setRoomItem("sword", "Suno", 12, 18);
		rooms[0][4].setRoomItem("sword", "King Slayer", 16, 20);
		rooms[4][0].setHealthIncrease(5); // gets 5 more max health
	}

	//Monster monster4Floor4("Drowner", 10, 1, 1);

	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (!rooms[i][j].isEmpty())
			{
				// The room is not empty so skip it
				continue;
			}

			// Set the adjacent rooms things so you can't come here
			if (i != 0)
			{
				// If the room to the left exists, set it so you can't go right
				rooms[i - 1][j].availableDirections.right = false;
			}
			if (i != MAP_WIDTH - 1)
			{
				// If the room to the right exists, set it so you can't go left
				rooms[i + 1][j].availableDirections.left = false;
			}
			if (j != 0)
			{
				// if the room below exists, set it so you can't go up
				rooms[i][j - 1].availableDirections.down = false;
			}
			if (j != MAP_HEIGHT - 1)
			{
				rooms[i][j + 1].availableDirections.up = false;
			}
		}
	}
}
