// ================================
// #  Title: <INSERT TITLE HERE>  #
// #  Author: Stephen Smart       # 
// #  Version: 1.0                #
// ================================

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include "engine.h"

// *****************************************************
// Description:
//  - It all starts here
// Returns:
// - int: -1 if an error occurrs, 0 otherwise
// *****************************************************
int main()
{
	// ======================
	//  INITIALIZING ALLEGRO
	// ======================
	if (!al_init())
	{
		al_show_native_message_box(NULL,
			"Error",
			"Allegro failed to initialize!",
			"Program will now close.",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	// =====================
	//  INITIALIZING ADDONS
	// =====================
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();

	// ==============
	//  RUNNING GAME
	// ==============
	Engine* engine = new Engine();
	engine->run_game();

	// ==============
	//  EXITING GAME
	// ==============
	delete engine;
	return 0;
}