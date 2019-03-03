#include "I.h"

int I::pTX;
int I::pTY;
float I::px;
float I::py;

int I::w_pressed;

I::I(void)
{
}


I::~I(void)
{
}

void I::update()
{
	I::px = agk::ScreenToWorldX(agk::GetPointerX());
	I::py = agk::ScreenToWorldY(agk::GetPointerY());

	//Calculating the tile
	I::pTX = int(px / GF::tileSize);
	I::pTY = int(py / GF::tileSize);

	I::w_pressed = agk::GetPointerPressed();
}