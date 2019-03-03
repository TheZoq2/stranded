#include "WD.h"

WD::Top WD::t[100];
WD::Ground WD::g[100];

int WD::water = 0;
int WD::grass = 1;
int WD::sand = 2;
int WD::sWater = 3;
int WD::shallow = 4;

int WD::tree = 1;
int WD::rock = 2;
int WD::appleTree = 3;
int WD::blueBush = 4;

WD::WD(void)
{
}


WD::~WD(void)
{
}

void WD::setupData()
{
	WD::State temp; //temporary variable for .push back

///////////////////////////////////////////////////////////////
	//Trees
	t[WD::tree].tall = true;
	t[WD::tree].rotated = true;

	//State 0 - Full grown
	temp.autoGrow = false;
	temp.maxGrow = 0;
	temp.minGrow = 0;
	temp.g_newState = 0;

	temp.frame = 10;

	temp.harvestable = true;
	temp.h_time = 1;
	temp.h_tool = 0;

	temp.lootable = true;
	temp.l_newState = 1;
	temp.l_time = float(.5);
	temp.l_tool = 0;

	temp.walkSpeed = 0;

	t[WD::tree].state.push_back(temp); //Ading the data

	temp.autoGrow = true;
	temp.maxGrow = 5*60;
	temp.minGrow = 30;
	temp.g_newState = 1;

	temp.frame = 11;
	temp.harvestable = true;
	temp.h_time = .75;
	temp.h_tool = 0;
	
	temp.lootable = false;

	temp.walkSpeed = 0;

	t[WD::tree].state.push_back(temp);
//////////////////////////////////////////////////////////////
	//Rocks
	t[WD::rock].tall = false;
	t[WD::rock].rotated = true;

	
	temp.autoGrow = false;
	temp.frame = 9;
	temp.harvestable = false;
	temp.lootable = false;

	temp.walkSpeed = 0;

	t[WD::rock].state.push_back(temp);
//////////////////////////////////////////////////////////////
	//appletree
	t[WD::appleTree].tall = true;
	t[WD::appleTree].rotated = true;

	temp.autoGrow = false;
	temp.frame = 1;

	temp.harvestable = true;
	temp.h_time = .75;
	temp.h_tool = 0;

	temp.lootable = true;
	temp.l_newState = 2;
	temp.l_time = .5;
	temp.l_tool = 0;

	temp.walkSpeed = 0;

	t[WD::appleTree].state.push_back(temp);

///////////////////////////////////////////////////////////////
	//Blueberry bush
	t[WD::blueBush].tall = true;
	t[WD::blueBush].rotated = true;
	
	temp.frame = 3;
	temp.autoGrow = false;
	temp.harvestable = false;
	
	temp.lootable = true;
	temp.l_newState = 1;
	temp.l_time = .5;
	temp.l_tool = 0;
	
	temp.walkSpeed = 8;

	t[WD::blueBush].state.push_back(temp);

///////////////////////////////////////////////////////////////////////////////////////////////
//											Ground
///////////////////////////////////////////////////////////////////////////////////////////////
	g[water].walkSpeed = 2;
	g[grass].walkSpeed = 10;
	g[sand].walkSpeed = 10;
	g[sWater].walkSpeed = 3;
	g[shallow].walkSpeed = 6;
}