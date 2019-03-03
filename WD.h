#pragma once

#include <vector>

class WD
{
public:
	WD(void);
	~WD(void);

	static void setupData();

	struct State
	{
		int frame; //The frame of the state
		
		bool autoGrow; //True if the item changes state automaticaly
		float minGrow; //Min time it will take for the object to grow
		float maxGrow; //Max time it will take for the object to grow
		int g_newState; //The state which the item grows to

		bool lootable; //True if the player can loot the item
		int l_tool; //The tool required to loot the item
		int l_newState; //The state which the item will go to if looted;
		float l_time; //The time it takes to loot the object

		bool harvestable;
		int h_tool; //The tool required to harvest the item
		float h_time;

		int walkability;
		int walkSpeed;
	};

	struct Top
	{
		bool tall; //True if the sprite should be above the player
		
		std::vector<State> state;

		bool rotated; //True if the item can have a random angle
	};

	struct Ground
	{
		int walkability;
		int walkSpeed;
	};

	static Top t[100];

	static Ground g[100];

	static int tree;
	static int rock;
	static int appleTree;
	static int blueBush;

	static int water;
	static int grass;
	static int sand;
	static int sWater;
	static int shallow;
};

/*
	The state system works as the following.
	All tops have state 0, this is the state which the object will spawn at.
	The state can be increased or decreased.
	If the state goes below the amount of states avalible, the item is destroyed

	The state can increase or decrease naturaly or by interaction by the player.
*/
