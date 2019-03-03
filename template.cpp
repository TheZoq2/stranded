// Includes
#include "template.h"

// Namespace
using namespace AGK;

app App;

void app::Begin(void)
{
	agk::SetVirtualResolution (agk::GetDeviceWidth(), agk::GetDeviceHeight());
	agk::SetClearColor( 0, 0, 0 ); // light blue
	agk::SetSyncRate(0,0);
	agk::SetScissor(0,0,0,0);

	//Changing print size
	agk::SetPrintSize(18);

	debug = true;
	programState = 0;

	//Setting default values for the world
	WD::setupData();

	//Calling custom constructors because c++ is acting weird
	player.begin();
}

void app::Loop (void)
{
	//Updating the input
	I::update();

	if(programState == 0) // The user is in the main menu
	{
		//No menu
		programState = 2;
	}else if(programState == 1) //Main game
	{
		agk::SetViewZoomMode(1);
		agk::SetViewZoom(11);
		//agk::SetViewOffset(128 * GF::tileSize / 2 - (agk::GetDeviceWidth()/2), 128 * GF::tileSize / 2 -(agk::GetDeviceHeight() / 2)); //Offsetting the world for now
		agk::SetViewOffset(player.getX() - (agk::GetDeviceWidth()/2), player.getY() - (agk::GetDeviceHeight()/2)); //Offsetting the world for now

		player.update();
	}else if(programState == 2) //Will generate a new world
	{
		world.generate(1);

		//Loading the new world
		programState = 3;

		agk::Print("World has been generated");
	}else if(programState == 3)
	{
		//Loading the spritesheets
		world.load();

		programState = 1; //Going to the game

		//Pointing the player to the world object
		player.world = &world;
		player.Spawn();

		player.load();
	}

	GF::updateTime();

	if(debug == true){ //Debug info should be displayed
		agk::PrintC("FPS: ");agk::Print( agk::ScreenFPS() );

		agk::PrintC("SpeedMod: ");agk::Print(GF::speedMod);

		agk::PrintC("PointerTileX: ");agk::PrintC(I::pTX);agk::PrintC("  PointerTileY: ");agk::Print(I::pTY);
	}

	agk::Sync();
}


void app::End (void)
{

}
