//============================================================================
// Name        : testSDL-drawing.cpp
// Author      : corrado
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "SDL/SDL.h"   			/* All SDL App's need this */
#include "SDL/SDL_video.h"   	/* this is required for video */
#include <stdio.h>
#include <stdlib.h>



/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}



/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
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
        *(Uint32 *)p = pixel;
        break;
    }
}




void draw(SDL_Surface *surface) {

	/* Code to set a yellow pixel at the center of the screen */

	int x, y;
	Uint32 yellow;

	/* Map the color yellow to this display (R=0xff, G=0xFF, B=0x00)
	 Note:  If the display is palettized, you must set the palette first.
	 */
	yellow = SDL_MapRGB(surface->format, 0xff, 0xff, 0x00);

	x = surface->w / 2;
	y = surface->h / 2;

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





int main(int argc, char *argv[]) {

	SDL_Surface *surface;

	/* Initialize the SDL library */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	/* Clean up on exit */
	atexit (SDL_Quit);

	/* Have a preference for 8-bit, but accept any depth */
	surface = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE | SDL_ANYFORMAT);
	if (surface == NULL) {
		fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n",
				SDL_GetError());
		exit(1);
	}
	printf("Set 640x480 at %d bits-per-pixel mode\n",
			surface->format->BitsPerPixel);


	draw(surface);

	//sleep(2000);
}
