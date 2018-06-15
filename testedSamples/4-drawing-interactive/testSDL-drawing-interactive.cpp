//============================================================================
// Name        : testSDL-keyboard.cpp
// Author      : corrado
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
// see: http://www.libsdl.org/release/SDL-1.2.15/docs/html/guideinputkeyboard.html
//============================================================================

#include "SDL.h"   			/* All SDL App's need this */
#include "SDL_video.h"   	/* this is required for video */
#include <stdio.h>
#include <stdlib.h>

/* Function Prototypes */

Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void draw(SDL_Surface *surface, int x, int y);

void PrintKeyInfo(SDL_KeyboardEvent *key);
void PrintModifiers(SDLMod mod);

/* main */
int main(int argc, char *argv[]) {

	SDL_Event event;
	int quit = 0;

	SDL_Surface *surface;

	int x, y;


	/* Initialise SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Could not initialise SDL: %s\n", SDL_GetError());
		exit(-1);
	}

	/* Set a video mode */
	if (!SDL_SetVideoMode(320, 200, 0, 0)) {
		fprintf(stderr, "Could not set video mode: %s\n", SDL_GetError());
		SDL_Quit();
		exit(-1);
	}

	surface = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE | SDL_ANYFORMAT);
	if (surface == NULL) {
		fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n",
				SDL_GetError());
		exit(1);
	}
	printf("Set 640x480 at %d bits-per-pixel mode\n",
			surface->format->BitsPerPixel);

	x = surface->w / 2;
	y = surface->h / 2;


	/* Enable Unicode translation */
	SDL_EnableUNICODE(1);

	/* Loop until an SDL_QUIT event is found */
	while (!quit) {

		/* Poll for events */
		while (SDL_PollEvent(&event)) {

			switch (event.type) {
			/* Keyboard event */
			/* Pass the event data onto PrintKeyInfo() */
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				PrintKeyInfo(&event.key);
				x++;y--;
				break;

				/* SDL_QUIT event (window close) */
			case SDL_QUIT:
				quit = 1;
				break;

			default:
				break;
			}

		}

		draw(surface, x, y);

	}

	/* Clean up */
	SDL_Quit();
	exit(0);
}


/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y) {
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;

	case 2:
		return *(Uint16 *) p;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;

	case 4:
		return *(Uint32 *) p;

	default:
		return 0; /* shouldn't happen, but avoids warnings */
	}
}


/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16 *) p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		} else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *) p = pixel;
		break;
	}
}



void draw(SDL_Surface *surface, int x, int y) {

	/* Code to set a yellow pixel at the center of the screen */

	//int x, y;
	Uint32 yellow;

	/* Map the color yellow to this display (R=0xff, G=0xFF, B=0x00)
	 Note:  If the display is palettized, you must set the palette first.
	 */
	yellow = SDL_MapRGB(surface->format, 0xff, 0xff, 0x00);

	//x = surface->w / 2;
	//y = surface->h / 2;

	/* Lock the screen for direct access to the pixels */
	if (SDL_MUSTLOCK (surface)) {
		if (SDL_LockSurface(surface) < 0) {
			fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
			return;
		}
	}

	putpixel(surface, x, y, yellow);

	if (SDL_MUSTLOCK (surface)) {
		SDL_UnlockSurface(surface);
	}
	/* Update just the part of the display that we've changed */
	SDL_UpdateRect(surface, x, y, 1, 1);

	return;

}

/* Print all information about a key event */
void PrintKeyInfo(SDL_KeyboardEvent *key) {
	/* Is it a release or a press? */
	if (key->type == SDL_KEYUP)
		printf("Release:- ");
	else
		printf("Press:- ");

	/* Print the hardware scancode first */
	printf("Scancode: 0x%02X", key->keysym.scancode);
	/* Print the name of the key */
	printf(", Name: %s", SDL_GetKeyName(key->keysym.sym));
	/* We want to print the unicode info, but we need to make */
	/* sure its a press event first (remember, release events */
	/* don't have unicode info                                */
	if (key->type == SDL_KEYDOWN) {
		/* If the Unicode value is less than 0x80 then the    */
		/* unicode value can be used to get a printable       */
		/* representation of the key, using (char)unicode.    */
		printf(", Unicode: ");
		if (key->keysym.unicode < 0x80 && key->keysym.unicode > 0) {
			printf("%c (0x%04X)", (char) key->keysym.unicode,
					key->keysym.unicode);
		} else {
			printf("? (0x%04X)", key->keysym.unicode);
		}
	}
	printf("\n");
	/* Print modifier info */
	PrintModifiers(key->keysym.mod);
}

/* Print modifier info */
void PrintModifiers(SDLMod mod) {
	printf("Modifers: ");

	/* If there are none then say so and return */
	if (mod == KMOD_NONE) {
		printf("None\n");
		return;
	}

	/* Check for the presence of each SDLMod value */
	/* This looks messy, but there really isn't    */
	/* a clearer way.                              */
	if (mod & KMOD_NUM)
		printf("NUMLOCK ");
	if (mod & KMOD_CAPS)
		printf("CAPSLOCK ");
	if (mod & KMOD_LCTRL)
		printf("LCTRL ");
	if (mod & KMOD_RCTRL)
		printf("RCTRL ");
	if (mod & KMOD_RSHIFT)
		printf("RSHIFT ");
	if (mod & KMOD_LSHIFT)
		printf("LSHIFT ");
	if (mod & KMOD_RALT)
		printf("RALT ");
	if (mod & KMOD_LALT)
		printf("LALT ");
	if (mod & KMOD_CTRL)
		printf("CTRL ");
	if (mod & KMOD_SHIFT)
		printf("SHIFT ");
	if (mod & KMOD_ALT)
		printf("ALT ");
	printf("\n");
}
