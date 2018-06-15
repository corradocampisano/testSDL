/*
 * TestCamera.h
 *
 *  Created on: Apr 10, 2014
 *  Author: corrado
 */

#ifndef TestCamera_H_
#define TestCamera_H_


#include <SDL.h>
#include <SDL_keysym.h>

#include "Simulation.h"



class TestCamera {
public:
	TestCamera();
	virtual ~TestCamera();

private:
	void quit( int code );
	void handle_key_down( SDL_keysym* keysym );
	void process_events( void );
	void draw_screen( void );
	void draw_things( void );
	void setup_sdl( void );
	void setup_opengl( void );
};

#endif /* TestCamera_H_ */
