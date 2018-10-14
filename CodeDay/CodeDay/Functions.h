#pragma once

#define MAP_WIDTH 5
#define MAP_HEIGHT 5

#include <iostream>
#include "Room.h"

using namespace std;

int randomNumber(int min, int max);
int randomNumberInclusive(int min, int max);

char getDirection(bool up = true, bool left = true, bool down = true, bool right = true);

char getAction(bool attack = true, bool defend = true, bool potion = true, bool run = true);

void generateRooms(Room (&rooms)[MAP_WIDTH][MAP_HEIGHT], int floor);


// Room messages
const string hitMessages[6] = { "You swing your sword!","You stab forward!","You slash down!","The enemy is bleeding!","Your swing reached its mark!","Your mighty swing has damaged the enemy!" };
const string missMessages[6] = { "How did you miss!?","You've missed....","Are you getting tired? Your swings are getting worse!","If you swing like that again, death will find you soon....","The disappointment your father would feel if he saw that swing...","Your family suffers and you miss? Do you feel nothing?" };

const string postionMessages[3] = { "You drink the potion and feel your strength returning ","It tastes like cookies... ","Oh. Your vision stopped fading " };

const string succsesfulRunawayMessages[3] = { "It takes a real warrior to know when he cannot best his enemy","You've run away? Some would say cowardice","The disappointment your family must feel..."};
const string failedRunawayMessages[3] = { "You can't run! Face your enemy!","Your family sits in a cell and you run away?!", "The sheer cowardice..." };

const string roomInteratactionMessages[8] = { "You enter a room and find skeletons all over the floor...","The horrors in this room...God has abandoned this place","You find a torture chamber, whatever did this was not human.","Chains litter the floor, all unbroken","So many bodies...So many","You find an oddly shaped skull, you get the feeling it's not from a humans","As you enter the room, a chill is felt","The floor is slippery, but you're too afraid to look down to see why" };

const string desertMessages[8] = { "Sand...Endless Sand","You see a bone sticking out of the sand, you move on","What living thing could possibly thrive out here...","A rusty sword... Sadly, yours is still better.","You spot a tail in the distance, better steer clear","You see a group of strangers, you hide as they pass by","As you see another skeleton in the sand, you wonder how many lives this desert has claimed","Thirsty...so thirsty" };

const string loseMessages[4] = { "Victory is not yours this day...","The world fades from your vision, in your delirious mind you see your family weeping as you fall to the ground.","Guilt racks your body as you feel the sweet release of death. If only your mother had a better child...","As you fall to the ground, you think of your sister... how disappointed she must feel in you." };
const string winMessages[5] = { "The enemy lies at your feet, death is swift","You stare into the eyes of your enemy, watching as the light leaves its eyes, praying for a swift death when your time comes.","You have won the fight! This time.","As the enemy falls to his knees, you feel no remorse as you sever its head from its body","At what point did you stop feeling any emotion upon taking a life from the world?" };
const string monsterMessages[3] = {"You've run into a ", "Be Careful! It's a ", "Be Careful! It's a "};
