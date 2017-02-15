// =====================================================
// #                   ENGINE CLASS                    #
// #                SPECIFICATION FILE                 #
// # ------------------------------------------------- #
// # This class handles the framework of the game.     #
// # Updating and rendering the game each frame,       #
// # managing the various states of the game, and      #
// # cleaning everything up afterwards.                #
// =====================================================

#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Engine
{
	private:
		// ALLEGRO VARIABLES
		ALLEGRO_DISPLAY* display;
		ALLEGRO_TIMER* timer;
		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_EVENT event;
		ALLEGRO_FONT* font_small;

		// KEYBOARD INPUT VARIABLES
		bool* keys_pressed;

		// DEBUG VARIABLES
		bool debug_mode;
		bool debug_toggle_held;
		float elapsed_game_time_update;
		int total_update_frames;
		int updates_per_second;
		int total_elapsed_frames;

		// PRIVATE MEMBER FUNCTIONS
		void update();
		void render();

	public:
		// CONSTRUCTOR(S) / DESTRUCTOR
		Engine();
		~Engine();

		// PUBLIC MEMBER FUNCTIONS
		void run_game();
};
