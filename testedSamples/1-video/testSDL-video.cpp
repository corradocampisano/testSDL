//============================================================================
// Name        : testSDL-video.cpp
// Author      : corrado
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "SDL/SDL.h"   			/* All SDL App's need this */
#include "SDL/SDL_video.h"   	/* this is required for video */
#include <stdio.h>

int main(int argc, char *argv[]) {

	SDL_Surface *screen;

	/* Initialize the SDL library */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	/* Clean up on exit */
	atexit (SDL_Quit);

	/* Have a preference for 8-bit, but accept any depth */
	screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE | SDL_ANYFORMAT);
	if (screen == NULL) {
		fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n",
				SDL_GetError());
		exit(1);
	}
	printf("Set 640x480 at %d bits-per-pixel mode\n",
			screen->format->BitsPerPixel);
}
