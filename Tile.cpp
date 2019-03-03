#include "Tile.h"


Tile::Tile(void)
{
	ground = 0;
	top = 0;
	state = 0;
}


Tile::~Tile(void)
{
}

void Tile::createSprites(int groundID, int topID, float scale)
{
	gSID = agk::CloneSprite(groundID);
	tSID = agk::CloneSprite(topID);

	//Setting the frame of the sprite
	agk::SetSpriteFrame(gSID, 1);

	//Setting the scale of the sprites
	gSID = agk::CloneSprite(groundID);
	agk::SetSpriteScale(tSID, scale, scale);

	agk::SetSpriteDepth(gSID, 15);
	
	//Changing the visibility of the sprites
	agk::SetSpriteVisible(gSID, 1);
	agk::SetSpriteVisible(tSID, 0);
}

void Tile::setPosition(float x, float y)
{
	agk::SetSpritePosition(gSID, x, y);
	agk::SetSpritePosition(tSID, x, y);
}

void Tile::updateFrame()
{
	agk::SetSpriteFrame(gSID, ground + 1); //+1 because frames don't start at 0
	
	if(top != 0)
	{
		agk::SetSpriteFrame(tSID, WD::t[top].state[state].frame);
		agk::SetSpriteVisible(tSID, 1);
	}

	updateWalkability();
}

void Tile::highlight()
{
	agk::SetSpriteColor(gSID, 255, 0, 0, 255);
}

void Tile::draw( int groundID, int topID, float scale, float x, float y)
{
	if(agk::GetSpriteExists(gSID) == 0) //If the ground does not exist
	{
		//Creating the sprite
		gSID = agk::CloneSprite(groundID);
		
		agk::SetSpriteScale(gSID, float(scale + .001), float(scale + .001)); // + 2 because 128 is not 128
		agk::SetSpritePosition(gSID, x, y);

		agk::SetSpriteVisible(gSID, 1);

		agk::SetSpriteDepth(gSID, 15);
	}

	if(agk::GetSpriteExists(tSID) == 0) //If the top does not exist
	{
		//Creating the sprite
		tSID = agk::CloneSprite(topID);
		
		agk::SetSpriteScale(tSID, scale, scale); 
		agk::SetSpritePosition(tSID, x, y);
	}
	agk::SetSpriteAngle(tSID, angle);

	//alright, sprites exists. Let's update the frames
	updateFrame();
}

void Tile::updateWalkability()
{
	//Getting the walkability for the top and ground
	int groundW = WD::g[ground].walkSpeed;
	int topW = 100;
	
	if(top != 0) //Making sure an array is not accessed
	{
		topW = WD::t[top].state[state].walkSpeed;
	}

	//Calculating the minimum walkability of the tile
	if(groundW < topW)
	{
		Tile::walkSpeed = groundW; //The ground had the lowest walkability, set it as the tile walkability
	}else
	{
		Tile::walkSpeed = topW; //The top has the lowest walkability, set it as the tile walkability
	}

	//Calculating the walkSpeed
	//Getting the percentage of the defalut speed that the speed is
	if(walkSpeed != 0)
	{
		float walkFact = GF::tileSize / walkSpeed;

		walkability = GF::tileSize * walkFact;
	}else
	{
		walkability = 0;
	}
}

void Tile::setGround(int ground)
{
	this->ground = ground;
}
void Tile::setTop(int top)
{
	this->top = top;

	if(WD::t[top].rotated == true) //Checking if the top should be rotated
	{
		angle = float(agk::Random(0, 360));
	}else
	{
		angle = 0;
	}
}

int Tile::getGround()
{
	return ground;
}
int Tile::getTop()
{
	return top;
}
int Tile::getWalkability()
{
	
	return walkability;
}
int Tile::getWalkSpeed()
{
	return walkSpeed;
}