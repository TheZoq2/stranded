#include "GF.h"


//Defining static variables
char GF::sdPath[128] = "media/";
int GF::quality = 1;

float GF::oldTime = 0;
float GF::frameTime = 0;
float GF::speedMod = 0;
float GF::time = 0;

float GF::tileSize = 10;

GF::GF(void)
{
}


GF::~GF(void)
{
}

uString GF::getPath(char originalPath[128])
{
	uString result;
	
	if(GF::quality == 1)
	{
		result.SetStr(sdPath);
		result.Append(originalPath);
	}

	return result; //Returning the final path
}

void GF::updateTime()
{
	oldTime = time; //Saving the old time

	time = agk::Timer(); //Getting the timer

	frameTime = time - oldTime; //Calculating the frame time

	speedMod = 60*frameTime;
}