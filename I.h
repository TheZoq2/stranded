#pragma once

#include "agk.h"

#include "GF.h"

class I
{
public:
	I(void);
	~I(void);

	static int pTX;
	static int pTY; //The tile the mosue is currently hovering over
	
	static float px; //The x cordinate of the pointer
	static float py;

	static int w_pressed; //If the world has been clicked

	static void update();
};

