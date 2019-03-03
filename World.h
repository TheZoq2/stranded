#pragma once

#include "agk.h"
#include <vector>
#include <iostream>

#include "Tile.h"
#include "GF.h"
#include "Waypoint.h"

class World
{
public:
	World(void);
	~World(void);

	void generate(int type);
	void load();

	void generateBase1(int mainGround, int beachGround, int maxGrass);
	void generateTop(int item, int ground, int chance); //Item is the item to be generated, ground is the ground needed for the generation and chanse is the procentual chanse of a tree spawning.

	void updateFrames();

	void updateWalkability();

	int findPath(std::vector<Waypoint>* foundPath, int startX, int startY, int endX, int endY); //Returns diffirent integers based on the success of the pathfinding

	void highlight(int x, int y);

	int getTileGround(int x, int y);
	int getWalkSpeed(int x, int y);

	void drawNear(int xo, int yo, int distX, int distY);
private:
	//Creating an array containing the tiles
	Tile tile[128][128];
	int width;  //These two variables are set in the load function, they will be used for refernece but dont change the size of the array
	int height;

	int type;

	int groundSS;
	int topSS;

	int walkability;

	//Creating lists for the pathfinder
	struct s_oList
	{
		int x;
		int y;
	};

	//Node list
	struct s_Nodes
	{
		int open;
		int x;
		int y;
		int parentX;
		int parentY;
		int gScore;
		int fScore;
		int hScore;
		int onPath;

		s_oList* listSlot;
	};
};

