#include "World.h"

#include "WD.h"

World::World(void)
{
	width = 100;
	height = 100;
}


World::~World(void)
{
}

void World::load()
{
	width = 128; //Because the constructor does not seem to set the values propperly
	height = 128;

	//Loading the two spritesheets which contain world items
	int groundIMG = agk::LoadImage(GF::getPath("~Ground.png"));
	groundSS = agk::CreateSprite(groundIMG);
	agk::SetSpriteAnimation(groundSS, 128, 128, 64);

	int topIMG = agk::LoadImage(GF::getPath("~Top.png"));
	topSS = agk::CreateSprite(topIMG);
	agk::SetSpriteAnimation(topSS, 128, 128, 64);

	//Hiding the original sprites
	agk::SetSpriteVisible(groundSS, 0);
	agk::SetSpriteVisible(topSS, 0);

	//The media is loaded, creating separate sprites for each tile
	/*for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			tile[x][y].createSprites(groundSS, topSS, GF::tileSize/128);
			tile[x][y].setPosition(x*GF::tileSize, y * GF::tileSize);
			tile[x][y].updateFrame();
		}
	}*/
}

void World::updateFrames()
{
	//The media is loaded, creating separate sprites for each tile
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			tile[x][y].updateFrame();
		}
	}
}

void World::updateWalkability()
{
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			tile[x][y].updateWalkability();
		}
	}
}
int World::findPath(std::vector<Waypoint>* foundPath, int startX, int startY, int endX, int endY)
{
	s_oList tempOList; //"Template" for putting in the open list vector

	std::vector<s_oList> oList;

	std::vector<std::vector<s_Nodes>> nodes;

	//Creating filling the node vector
	for(int x = 0; x < width; x++)
	{
		//Creating a temporary node
		std::vector<s_Nodes> tempVector;
		for(int y = 0; y < height; y++)
		{
			s_Nodes tempNode;
			tempNode.open = 0;
			//nodes[x].push_back(tempNode);
			tempVector.push_back(tempNode);

			int a = 0;
		}

		nodes.push_back(tempVector);
	}

	if(startX < 0 || startX > width || endX < 0 || endX > width)//Something is wrong on the x-axis, abort the pathfinder
	{
		return 3;
	}

	if(startY < 0 || startY > height || endY < 0 || endY > height) //Something is wrong on the y axis, abort the pathfinder
	{
		return 3;
	}

	//Checking if the goal is reachable
	if(tile[endX][endY].getWalkability() == 0)
	{
		//The goal is not walkable, abort the pathfinding
		return 2;
	}

	//Everything seems to work, time to start looking for a path
	//First of all, we must add the start node to open list
	nodes[startX][startY].open = 1;
	nodes[startX][startY].x = startX;
	nodes[startX][startY].y = startY;
	nodes[startX][startY].parentX = startX;
	nodes[startX][startY].parentY = startY;
	nodes[startX][startY].gScore = tile[startX][startY].getWalkability();
	nodes[startX][startY].hScore = 0;
	nodes[startX][startY].fScore = 0;
	nodes[startX][startY].onPath = 0;

	oList.push_back(tempOList);
	oList.back().x = startX;
	oList.back().y = startY;

	int currentX = startX;
	int currentY = startY;

	int pathFound = 100;

	while(pathFound != 1) //The main pathfinding loop
	{
		//Creating a for XY loop which will go thru all the tiles;
		int xStart = (currentX - 1);
		int yStart = (currentY - 1);
		int xEnd = (currentX + 1);
		int yEnd = (currentY + 1);

		for(int x = xStart; x <= xEnd; x++)
		{
			for(int y = yStart; y <= yEnd; y++)
			{
				//For loop has been created
				//Checking if we should actually check this tile
				bool chkTile = true;

				if(x == currentX && y == currentY) //Checking if we are looking at the current tile
				{
					//Skip this tile
					chkTile = false;
				}

				int xInc = currentX - x;
				int yInc = currentY - y;
				//Checking if we are looking at a diagonal tile
				if(agk::Abs(xInc) == agk::Abs(yInc))
				{
					chkTile = false; //This was a diagonal tile, abort the pathfinding
				}

				//Making sure the tile is both walkable and not closes
				if(tile[x][y].getWalkability() == 0 || nodes[x][y].open == 2){
					chkTile = false; //The tile should not be checked, skip the chek
				}

				//Checking if the tile should be checked
				if(chkTile == true)
				{
					int hModifyer = 10; //Value of the default cost for walking one tile
					//Tile should be checked, keep going
					if(nodes[x][y].open == 1) //Is the node already open?
					{
						//Calculate new scores
						int NewGScore = tile[x][y].getWalkability(); //Because nothing is diagonal, we can just set the walk cost to the current tiles walkability

						//Adding the new score to the old ones
						int optionalGScore = nodes[currentX][currentY].gScore + NewGScore;
						int optionalHScore = ((agk::Abs(endX - x)) + agk::Abs(endY - y) * hModifyer);
						int optionalFScore = (optionalGScore + optionalHScore);

						//Checking if the new score is better than the old one
						if(optionalFScore < nodes[x][y].fScore)
						{
							//Updating the new scores
							nodes[x][y].gScore = optionalGScore;
							nodes[x][y].hScore = optionalHScore;
							nodes[x][y].fScore = optionalFScore;

							//updating the parent
							nodes[x][y].parentX = currentX;
							nodes[x][y].parentY = currentY;
						}
					}

					//If the tile is not on the open list
					if(nodes[x][y].open == 0)
					{
						nodes[x][y].open = 1; //Opening the node
						nodes[x][y].parentX = currentX;
						nodes[x][y].parentY = currentY; //Giving the node parents

						//Calculating the new scores
						int newGScore = tile[x][y].getWalkability();
						nodes[x][y].gScore = nodes[currentX][currentY].gScore + newGScore;
						nodes[x][y].hScore = ((agk::Abs(endX - x)) + agk::Abs(endY - y) * hModifyer);
						nodes[x][y].fScore = nodes[x][y].gScore + nodes[x][y].hScore;

						//Adding the node to the open list
						oList.push_back(tempOList);
						oList.back().x = x;
						oList.back().y = y;
						nodes[x][y].listSlot = &oList.back();
					}
				}
			}
		} //Out of the for loop

		//Adding the current node ot the closed list
		nodes[currentX][currentY].open = 2;

		int lowestF = 10000000;
		int lowestX = 0;
		int lowestY = 0;

		for(signed int i = 0; i < oList.size(); i++) //Determenign the lowest scores to know where to look next
		{
			int listX = oList[i].x;
			int listY = oList[i].y;
			if(nodes[listX][listY].open == 1)
			{
				if(nodes[listX][listY].fScore < lowestF) //Checking if the current node has the lowest score
				{
					lowestF = nodes[listX][listY].fScore;
					lowestX = listX;
					lowestY = listY;
				}
			}
		}

		//Preventing the pathfinder from freesing the program when no path can be found
		//When lowestF is not changed, it means that there are no open tiles left
		//The pathfinder must be aborted
		if(lowestF == 10000000)
		{
			return 4;
		}

		//Setting the current tile to the lowest tile
		currentX = lowestX;
		currentY = lowestY;

		//Checking if the path has been found
		if(nodes[endX][endY].open == 2)
		{
			pathFound = 1;
		}
	}

	//It looks like we found a path, let's save it
	
	//Clearing the old path to make room for a new one
	foundPath->clear();

	//Getting the first tile in the chain
	int cX = endX;
	int cY = endY;

	while(cX != startX || cY != startY)
	{
		Waypoint tempWaypoint; //Creating a tempoarary variable for putting in the vector
		tempWaypoint.x = cX;
		tempWaypoint.y = cY;

		foundPath->push_back(tempWaypoint);

		//Getting the next chain
		int nextX = nodes[cX][cY].parentX;
		int nextY = nodes[cX][cY].parentY;

		cX = nextX;
		cY = nextY;
	}

	return 1;
}

void World::generate(int type)
{
	width = 128;
	height = 128;

	if(type == 0) //Standard grass island
	{
		tile[width / 2][height / 2].setGround(1); //Setting the spawn of an island

		generateBase1(1, 2, 30000); //Generating a base with grass and sand

		generateTop(WD::tree, 1, 35); //Some Trees on the grass
		generateTop(WD::tree, 2, 15); //Some disperced trees on the sand

		generateTop(WD::rock, 1, 5); //Rocks on grass
		generateTop(WD::rock, 2, 5); //Rocks on sand

		generateTop(WD::appleTree, 1, 10); //Appletrees on grass

		generateTop(WD::blueBush, 1, 10); //Blueberries on grass
	}
	if(type == 1) //Multiple small islands
	{
		tile[agk::Random(20, 108)][agk::Random(20, 108)].setGround(1);
		tile[agk::Random(20, 108)][agk::Random(20, 108)].setGround(1);
		tile[agk::Random(20, 108)][agk::Random(20, 108)].setGround(1);
		tile[agk::Random(20, 108)][agk::Random(20, 108)].setGround(1);

		generateBase1(1, 2, 20000); //Generating a base with grass and sand

		generateTop(WD::tree, 1, 35); //Some Trees on the grass
		generateTop(WD::tree, 2, 15); //Some disperced trees on the sand

		generateTop(WD::rock, 1, 5); //Rocks on grass
		generateTop(WD::rock, 2, 5); //Rocks on sand

		generateTop(WD::appleTree, 1, 15); //Appletrees on grass

		generateTop(WD::blueBush, 1, 10); //Blueberries on grass
	}
}

void World::generateBase1(int mainGround, int mainBeach, int maxGrass)
{
	width = 128;
	height = 128;
	int grassAmount = 0;
	while(grassAmount < maxGrass) //Generating a lot of grass around the center of the island
	{
		for(int x = 1; x < width - 1; x++) //-1 and 1 because we don't want to go out of bounds with the array
		{
			for(int y = 1; y < height - 1; y++)
			{
				for(int xMod = -1; xMod <= 1; xMod++)//Searching the tiles around the current tile
				{
					for(int yMod = -1; yMod <= 1; yMod++)
					{
						if(tile[x + xMod][y + yMod].getGround() == mainGround)
						{
							//Checking if grass should actually be generated
							if(agk::Random(0, 10) == 1)
							{
								tile[x][y].setGround(1);
								grassAmount++;
							}
						}
					}
				}
			}
		}
	}

	/*********************************************************************************/
	//					Grass has been generated, let's get some sand
	/*********************************************************************************/
	for(int x = 1; x < width - 1; x++)
	{
		for(int y = 1; y < height - 1; y++)
		{
			//Small loop to look at the adjacent tiles
			for(int xMod = -1; xMod <= 1; xMod++)//Searching the tiles around the current tile
			{
				for(int yMod = -1; yMod <= 1; yMod++)
				{
					if(tile[x][y].getGround() == mainGround) //If the tile is the main type of ground
					{
						if(tile[x + xMod][y + yMod].getGround() == 0) //If a nearby tile is water
						{
							tile[x][y].setGround(mainBeach);
						}
					}
				}
			}
		}
	}

	//Some sand has been placed, making a less uniform border
	for(int x = 2; x < width - 2; x++)
	{
		for(int y = 2; y < height - 2; y++)
		{
			//Small loop to look at the adjacent tiles
			for(int xMod = -2; xMod <= 2; xMod++)//Searching the tiles around the current tile
			{
				for(int yMod = -2; yMod <= 2; yMod++)
				{
					if(tile[x + xMod][y + yMod].getGround() == 0) //If the water is close
					{
						if(tile[x][y].getGround() == mainGround && agk::Random(1, 3) == 1) //The tile is grass and a sand tile would fit
						{
							tile[x][y].setGround(mainBeach); //Making the tile sand
						}
					}
				}
			}
		}
	}
}

void World::generateTop(int top, int ground, int chanse)
{
	for(int x = 1; x < width - 1; x++) //-1 and 1 because we don't want to go out of bounds with the array
	{
		for(int y = 1; y < height - 1; y++)
		{
			if(tile[x][y].getGround() == ground) //The item can be placed here
			{
				if(tile[x][y].getTop() == 0) //The tile does not have an item
				{
					//Random generator
					if(agk::Random(0, 100) < unsigned(chanse))
					{
						//setting the new item
						tile[x][y].setTop(top);
					}
				}
			}
		}
	}
}

void World::drawNear(int xo, int yo, int distX, int distY)
{
	//Looping thru all the tiles that need updating
	for(int x = xo - distX; x < xo + distX; x++)
	{
		for(int y = yo - distY; y < yo + distY; y++)
		{
			//Making sure nothing is outside the map
			if(x > 0 && x < width && y > 0 && y < height) 
			{
				//Drawing the tile
				tile[x][y].draw(groundSS, topSS, GF::tileSize/128, x*GF::tileSize, y*GF::tileSize);
			}
		}
	}
}

void World::highlight(int x, int y)
{
	tile[x][y].highlight();
}

int World::getTileGround(int x, int y)
{
	return tile[x][y].getGround();
}
int World::getWalkSpeed(int x, int y)
{
	return tile[x][y].getWalkSpeed();
}