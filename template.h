#ifndef _H_SMACKIT_
#define _H_SMACKIT_

// Link to GDK libraries
#include "AGK.h"

//App includes
#include "GF.h"
#include "World.h"
#include "Player.h"
#include "WD.h"
#include "I.h"

#define DEVICE_WIDTH 1600
#define DEVICE_HEIGHT 900
#define DEVICE_POS_X 32
#define DEVICE_POS_Y 32
#define FULLSCREEN false

// Global values for the app
class app
{
	public:

		// constructor
		app() { memset ( this, 0, sizeof(app)); }

		// main app functions - mike to experiment with a derived class for this..
		void Begin( void );
		void Loop( void );
		void End( void );

	protected:
		World world;
	private:
		bool debug; //True if the debug info should be displayed
		int programState;

		Player player;
};

extern app App;

#endif

// Allow us to use the LoadImage function name
#ifdef LoadImage
 #undef LoadImage
#endif