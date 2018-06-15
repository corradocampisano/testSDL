/*
 * TestCamera.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: corrado
 */

#include "TestCamera.h"

//#include <cstdlib>
#include <ctgmath>

#include <iostream>
#include <string>

#include <gl.h>
#include <glu.h>



bool paused=true;


/* Dimensions of our window. */
int width = 1200;
int height = 800;

/* perspective rotation */
static GLfloat rotate_hor = 0.0f;
static GLfloat rotate_ver = 30.0f;
static const GLfloat ROTATE_STEP = 5.0f;
/* perspective distance */
static GLfloat distance = -100.0f;
static const GLfloat DISTANCE_STEP = 5.0f;

int timespeed = 2;

/* simulation to be shown */
Simulation* sim;



TestCamera::TestCamera() {

	int i;
	std::cout << "Please enter an integer value for the bodies to run with: ";
	std::cout << "can use 2-4-5-6 bodies right now";
	std::cin >> i;

	// TODO Auto-generated constructor stub
	this->setup_sdl();
	this->setup_opengl();

	// can use 2-4-5-6 bodies right now
	sim = new Simulation(i);

	/*
	 * Now we want to begin our normal app process--
	 * an event loop with a lot of redrawing.
	 */
	while (1) {

		/* Process incoming events. */
		this->process_events();

		/* Draw the screen. */
		this->draw_screen();

		/* Draw the things. */
		this->draw_things();

		/* Swap the buffers. This this tells the driver to
		 * render the next frame from the contents of the
		 * back-buffer, and to set all rendering operations
		 * to occur on what was the front-buffer.
		 *
		 * Double buffering prevents nasty visual tearing
		 * from the application drawing on areas of the
		 * screen that are being updated at the same time.
		 */
		SDL_GL_SwapBuffers();


		/* calculate movements */
		for (int i=0; i<timespeed; i++)
			if (!paused) sim->move();
	}

	/*
	 * EXERCISE:
	 * Record timings using SDL_GetTicks() and
	 * and print out frames per second at program
	 * end.
	 */
}

TestCamera::~TestCamera() {
	this->quit(0);
}




void TestCamera::quit(int code) {

	/*
	 * Quit SDL so we can release the fullscreen
	 * mode and restore the previous video settings,
	 * etc.
	 */
	SDL_Quit();

	/* Exit program. */
	std::exit(code);
}

void TestCamera::setup_sdl(void) {

	/* Information about the current video settings. */
	const SDL_VideoInfo* info = NULL;
	/* Color depth in bits of our window. */
	int bpp = 0;
	/* Flags we will pass into SDL_SetVideoMode. */
	int flags = 0;

	/* First, initialize SDL's video subsystem. */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		/* Failed, exit. */
		fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
		quit(1);
	}

	/* Let's get some video information. */
	info = SDL_GetVideoInfo();

	if (!info) {
		/* This should probably never happen. */
		fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
		quit(1);
	}

	/*
	 * Set our width/height to 640/480 (you would
	 * of course let the user decide this in a normal
	 * app). We get the bpp we will request from
	 * the display. On X11, VidMode can't change
	 * resolution, so this is probably being overly
	 * safe. Under Win32, ChangeDisplaySettings
	 * can change the bpp.
	 */
	bpp = info->vfmt->BitsPerPixel;

	/*
	 * Now, we want to setup our requested
	 * window attributes for our OpenGL window.
	 * We want *at least* 5 bits of red, green
	 * and blue. We also want at least a 16-bit
	 * depth buffer.
	 *
	 * The last thing we do is request a double
	 * buffered window. '1' turns on double
	 * buffering, '0' turns it off.
	 *
	 * Note that we do not use SDL_DOUBLEBUF in
	 * the flags to SDL_SetVideoMode. That does
	 * not affect the GL attribute state, only
	 * the standard 2D blitting setup.
	 */
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	/*
	 * We want to request that SDL provide us
	 * with an OpenGL window, in a fullscreen
	 * video mode.
	 *
	 * EXERCISE:
	 * Make starting windowed an option, and
	 * handle the resize events properly with
	 * glViewport.
	 */
	flags = SDL_OPENGL; // | SDL_FULLSCREEN;

	/*
	 * Set the video mode
	 */
	if (SDL_SetVideoMode(width, height, bpp, flags) == 0) {
		/*
		 * This could happen for a variety of reasons,
		 * including DISPLAY not being set, the specified
		 * resolution not being available, etc.
		 */
		fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
		quit(1);
	}
}

void TestCamera::setup_opengl(void) {
	float ratio = (float) width / (float) height;

	/* Our shading model--Gouraud (smooth). */
	glShadeModel(GL_SMOOTH);

	/* Culling. */
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	/* Set the clear color. */
	glClearColor(0, 0, 0, 0);

	/* Setup our viewport. */
	glViewport(0, 0, width, height);

	/*
	 * Change to the projection matrix and set our viewing volume.
	 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*
	 * EXERCISE:
	 * Replace this with a call to glFrustum.
	 */
	// todo : see http://unspecified.wordpress.com/2012/06/21/calculating-the-gluperspective-matrix-and-other-opengl-matrix-maths/
	gluPerspective(60.0, ratio, 0.20, 1024.0);
	//glOrtho(120.0, 20.0, 120.0, 20.0, 120.0, 20.0);
}

void TestCamera::handle_key_down(SDL_keysym* keysym) {

	/*
	 * We're only interested if 'Esc' has
	 * been presssed.
	 *
	 * EXERCISE:
	 * Handle the arrow keys and have that change the
	 * viewing position/angle.
	 */
	switch (keysym->sym) {
	case SDLK_ESCAPE:
		quit(0);
		break;
	case SDLK_LEFT:
		rotate_hor += ROTATE_STEP;
		break;
	case SDLK_RIGHT:
		rotate_hor -= ROTATE_STEP;
		break;
	case SDLK_UP:
		rotate_ver += ROTATE_STEP;
		break;
	case SDLK_DOWN:
		rotate_ver -= ROTATE_STEP;
		break;
	case SDLK_MINUS:
		distance -= DISTANCE_STEP;
		break;
	case SDLK_PLUS:
		distance += DISTANCE_STEP;
		break;
	case SDLK_SPACE:
		paused=!paused;
		break;
	default:
		break;
	}

}

void TestCamera::process_events(void) {
	/* Our SDL event place holder. */
	SDL_Event event;

	/* Grab all the events off the queue. */
	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_KEYDOWN:
			/* Handle key presses. */
			handle_key_down(&event.key.keysym);
			break;
		case SDL_QUIT:
			/* Handle quit requests (like Ctrl-c). */
			quit(0);
			break;
		}

	}

}

void TestCamera::draw_screen() {

	/* Clear the color and depth buffers. */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* We don't want to modify the projection matrix. */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* Move down the z-axis. */
	glTranslatef(0.0, 0.0, distance);

	/* Rotate. */
	glRotatef(rotate_hor, 0.0, 1.0, 0.0);
	glRotatef(rotate_ver, 1.0, 0.0, 0.0);


	static GLubyte lightGray[] = { 100, 100, 100, 100 };
	static GLubyte darkGray[] = { 40, 40, 40, 120 };

	// this showed "call of overloaded ‘abs(GLfloat&)’ is ambiguous" since debian9 (not on debian8)
	//double zoom = abs(distance);
	// see: https://stackoverflow.com/questions/1374037/ambiguous-overload-call-to-absdouble
	// solved by using fabs() and including "#include <ctgmath>" and instead of "#include <cstdlib>"?
	double zoom = fabs(distance);


	glBegin(GL_LINES);

	// negative axeses
	glColor4ubv(darkGray);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-zoom*1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -zoom*1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -zoom*1.0f);

	// positive axeses
	glColor4ubv(lightGray);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(zoom*1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, zoom*1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, zoom*1.0f);

	glEnd();

}

void TestCamera::draw_things() {

	static GLubyte red[] = { 255, 0, 0, 255 };
	static GLubyte green[] = { 0, 255, 0, 255 };
	static GLubyte blue[] = { 0, 0, 255, 255 };

	std::vector<Being> beings = sim->getBeings();
	Being *baricentre = sim->getBaricentre();

	glPointSize(8.0);
	glBegin(GL_POINTS);
	glColor4ubv(green);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor4ubv(blue);
	glVertex3f(baricentre->getPosX(), baricentre->getPosY(), baricentre->getPosZ());
	glEnd();
	glPointSize(1.0);

	for (unsigned i = 0; i < beings.size(); i++) {
		Being being = beings.at(i);

		double zoom = fabs(distance);

		// draw acceleration
		glBegin(GL_LINES);
		glColor4ubv(green);
		glVertex3f(
				(GLfloat) being.getPosX(),
				(GLfloat) being.getPosY(),
				(GLfloat) being.getPosZ());
		glVertex3f(
				(GLfloat) being.getPosX() + (zoom*5)*being.getAccX(),
				(GLfloat) being.getPosY() + (zoom*5)*being.getAccY(),
				(GLfloat) being.getPosZ() + (zoom*5)*being.getAccZ() );
		glEnd();


		// draw velocity
		glBegin(GL_LINES);
		glColor4ubv(blue);
		glVertex3f(
				(GLfloat) being.getPosX(),
				(GLfloat) being.getPosY(),
				(GLfloat) being.getPosZ());
		glVertex3f(
				(GLfloat) being.getPosX() + (zoom/2)*being.getVelX(),
				(GLfloat) being.getPosY() + (zoom/2)*being.getVelY(),
				(GLfloat) being.getPosZ() + (zoom/2)*being.getVelZ() );
		glEnd();


		// draw position
		glPointSize(8.0);
		glBegin(GL_POINTS);
		glColor4ubv(red);
		glVertex3f((GLfloat) being.getPosX(), (GLfloat) being.getPosY(), (GLfloat) being.getPosZ());
		glEnd();
		glPointSize(1.0);
	}



}
