#pragma once
#include "agk.h"

#include "WD.h"
#include "GF.h"

class Tile
{
public:
	Tile(void);
	~Tile(void);

	void createSprites(int groundID, int topID, float scale); //This function clones the sprites and sets them up for as tiles
	void setPosition(float x, float y);

	void setTop(int top);
	void setGround(int ground);
	void updateFrame();

	void draw(int groundID, int topID, float scale, float x, float y); //Draws the current tile, if no sprite exists, creates one
	
	void highlight();

	void updateWalkability();

	int getGround();
	int getTop();
	int getWalkability();
	int getWalkSpeed();
private:
	int ground;
	int top;

	int gSID;
	int tSID;

	int state;

	float angle;

	int walkability;
	int walkSpeed;
};

