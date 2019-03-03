#pragma once

#include <stdio.h>

#include "agk.h"

class GF
{
public:
	GF(void);
	~GF(void);

	static char sdPath[128];
	static int quality;

	static uString getPath(char originalPath[128]); //Returns the path to a file with medium quality

	static float tileSize; //The size of each tile in the world

	static void updateTime();
	static float time;
	static float oldTime;
	static float frameTime;
	static float speedMod;
};

