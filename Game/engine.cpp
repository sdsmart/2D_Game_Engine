// =====================================================
// #                   ENGINE CLASS                    #
// #               IMPLEMENTATION FILE                 #
// =====================================================

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include "engine.h"
#include "constants.h"

// *****************************************************
// Description:
//  - Default constructor for an Engine object
// *****************************************************
Engine::Engine()
{
	// ======================
	//  INITIALIZING DISPLAY
	// ======================
	display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);

	if (!display)
	{
		al_show_native_message_box(NULL,
			"Error",
			"Failed to initialize display!",
			"Program will now close.",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	// ====================
	//  INITIALIZING TIMER
	// ====================
	timer = al_create_timer(1.0 / FPS);

	if (!timer)
	{
		al_show_native_message_box(display,
			"Error",
			"Failed to initialize timer!",
			"Program will now close.",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	// ==========================
	//  INITIALIZING EVENT QUEUE
	// ==========================
	event_queue = al_create_event_queue();

	if (!event_queue)
	{
		al_show_native_message_box(NULL,
			"Error",
			"Failed to initialize event queue!",
			"Program will now close.",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	// ====================
	//  INITIALIZING FONTS
	// ====================
	font_small = al_load_font(FONT_PATH.c_str(), FONT_SIZE_SMALL, NULL);

	// =======================================
	//  INITIALIZING KEYBOARD INPUT VARIABLES
	// =======================================
	keys_pressed = new bool[ALLEGRO_KEY_MAX];

	for (int i = 0; i < ALLEGRO_KEY_MAX; ++i)
	{
		keys_pressed[i] = false;
	}

	// ==============================
	//  INITIALIZING DEBUG VARIABLES
	// ==============================
	debug_mode = false;
	debug_toggle_held = false;
}

// *****************************************************
// Description:
//  - The destructor for an Engine object
// *****************************************************
Engine::~Engine()
{
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_font(font_small);
}

// *****************************************************
// Description:
//  - Updates a single frame of the game
// Returns:
//  - void
// *****************************************************
void Engine::update()
{
	// ... Update game logic here ...

	// Toggling debug_mode if the toggle button is pressed.
	// However, if the toggle button is being held, then debug mode
	// should not be toggled because the toggle already happened
	// when the button was first pressed.
	// This avoids a flashing effect caused by toggling debug_mode
	// every single update cycle.
	if (keys_pressed[ALLEGRO_KEY_F1] && !debug_toggle_held)
	{
		debug_mode = !debug_mode;
		debug_toggle_held = true;
	}

	// Resetting the debug_toggle_held flag if the button is not
	// being pressed.
	else if (!keys_pressed[ALLEGRO_KEY_F1])
	{
		debug_toggle_held = false;
	}
}

// *****************************************************
// Description:
//  - Renders a single frame of the game
// Returns:
//  - void
// *****************************************************
void Engine::render()
{
	// ... Render game here ...

	// Rendering debug information if flag set to true.
	if (debug_mode)
	{
		al_draw_textf(font_small, al_map_rgb(255, 255, 255), 8, 5, NULL,
			"ELAPSED FRAMES:");
		al_draw_textf(font_small, al_map_rgb(255, 25, 25), 166, 5, ALLEGRO_ALIGN_LEFT,
			"%i", total_elapsed_frames);

		al_draw_textf(font_small, al_map_rgb(255, 255, 255), 8, 22, 0,
			"FPS:");
		al_draw_textf(font_small, al_map_rgb(255, 25, 25), 50, 22, ALLEGRO_ALIGN_LEFT,
			"%i", updates_per_second);
	}

	// Flipping display buffer.
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

// *****************************************************
// Description:
//  - Runs the game logic until the game is finished
// Returns:
//  - void
// *****************************************************
void Engine::run_game()
{
	// Setting up for game loop entry.
	bool render_is_ready = false;
	
	elapsed_game_time_update = al_current_time();

	al_start_timer(timer);

	// ===========
	//  GAME LOOP
	// ===========
	while (true)
	{
		al_wait_for_event(event_queue, &event);

		// Setting the keys_pressed flags corresponding
		// to keyboard events.
		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			keys_pressed[event.keyboard.keycode] = true;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			keys_pressed[event.keyboard.keycode] = false;
		}
		// Closing the game if the red X in the top of the
		// display is clicked.
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}
		// Updating the game if the timer ticks.
		else if (event.type == ALLEGRO_EVENT_TIMER)
		{
			update();

			// Updating debug information.
			++total_update_frames;
			++total_elapsed_frames;

			if ((al_current_time() - elapsed_game_time_update) >= 1)
			{
				elapsed_game_time_update = al_current_time();
				updates_per_second = total_update_frames;
				total_update_frames = 0;
			}

			render_is_ready = true;
		}

		// Rendering the game if no more events need to be
		// processed and the game is ready to be rendered again.
		if (render_is_ready && al_is_event_queue_empty(event_queue))
		{
			render();

			render_is_ready = false;
		}
	}
}
