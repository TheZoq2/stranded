#include "Player.h"


Player::Player(void)
{
	path = new std::vector<Waypoint>;
}


Player::~Player(void)
{
}

void Player::begin()
{
	path = new std::vector<Waypoint>;
}

void Player::load()
{
	joystick = 1;
	agk::AddVirtualJoystick(joystick, 150, 600, 200);

	int image = agk::LoadImage("media/Human.png");
	SID = agk::CreateSprite(image);
	agk::SetSpriteScale(SID, float(.04), float(.04));
}

void Player::Spawn()
{
	//Getting a random tile to observe
	int tempX = agk::Random(1, 127);
	int tempY = agk::Random(1, 127);
	while(world->getTileGround(tempX, tempY) != 2) //Checking if the tile is sand
	{
		tempX = agk::Random(1, 127);
		tempY = agk::Random(1, 127);
	}

	//A tile was found, set it as spawn
	spawnX = tempX;
	spawnY = tempY;

	tileX = spawnX;
	tileY = spawnY;

	x = tileX * GF::tileSize + (GF::tileSize/2); //+ half tilesize because we want the player to be in the middle of a tile
	y = tileY * GF::tileSize + (GF::tileSize/2);
}

void Player::update() //Main update loop for the player
{
	x = x + agk::GetVirtualJoystickX(joystick) * GF::speedMod;
	y = y + agk::GetVirtualJoystickY(joystick) * GF::speedMod; 
	//Calling the world update
	world->drawNear(tileX, tileY, 15, 10);

	if(agk::GetRawKeyState(87))
	{
		y = y - 1 * GF::speedMod;
	}
	if(agk::GetRawKeyState(83))
	{
		y = y + 1 * GF::speedMod;
	}
	if(agk::GetRawKeyState(65))
	{
		x = x - 1 * GF::speedMod;
	}
	if(agk::GetRawKeyState(68))
	{
		x = x + 1 * GF::speedMod;
	}


	/////////////////////////////////////////////////////////////////////////////
	//Updating the player tile position
	tileX = int(x / GF::tileSize);
	tileY = int(y / GF::tileSize);

	agk::SetSpritePositionByOffset(SID, x, y);
	agk::SetSpriteAngle(SID, angle);
	//*************************************************************************//
	//Navigation
	if(I::w_pressed) //If the user has clicked  a tile
	{

		//starting the pathfinder
		int pathReturn = world->findPath(path, tileX, tileY, I::pTX, I::pTY);

		//If the pathfinder returns 1, the pathfinding succeeded
		if(pathReturn == 1)
		{
			hasPath = true; //The player has a path
			cWaypoint = path->size() - 1; //Setting the next tile in the waypoint chain
		}

		/*for(unsigned int i = 0; i < path->size(); i++)
		{
			std::vector<Waypoint> tempPath;
			
			tempPath = *path; //temporary path vector to actually be able to access the path vector

			world->highlight(tempPath[i].x, tempPath[i].y);
		}*/
	}

	if(hasPath == true) //The player has a path, follow it
	{
		//Setting a tempoarary speed
		speed = float(.05);

		std::vector<Waypoint> tempPath;
			
		tempPath = *path; //temporary path vector to actually be able to access the path vector
		
		//Simplifying the variables
		float tX = tempPath[cWaypoint].x * GF::tileSize + (GF::tileSize / 2); //Half of the tilesize because we want the center of the tile
		float tY = tempPath[cWaypoint].y * GF::tileSize + (GF::tileSize / 2);

		//Calculating the angle betwee the current player position and the target
		float distX = tX - x;
		float distY = tY - y;

		angle = (agk::ATanFull(distX, distY)) - 90; //90 because 90 degrees because 360 degrees mathematicaly is straight right

		int cTileSpeed = world->getWalkSpeed(tileX, tileY); //The walkingspeed of the current tile

		float xInc = agk::Cos(angle) * cTileSpeed * speed * GF::speedMod;
		float yInc = agk::Sin(angle) * cTileSpeed * speed * GF::speedMod;

		x = x + xInc; //Adding the new values to the old position
		y = y + yInc;

		//Checking if the waypoint has been reached
		if(agk::Round(tX) == agk::Round(x) && agk::Round(tY) == agk::Round(y))
		{
			//The waypoint has been reached, move on to the next one
			cWaypoint--;

			//Checking if there are more waypoints
			if(cWaypoint < 0)
			{
				hasPath = false;
			}
		}
	}
}

float Player::getX()
{
	return x;
}

float Player::getY()
{
	return y;
}