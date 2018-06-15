

#include <stdlib.h>
#include <cstdlib>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>


using namespace std;


//give properties of our game windows application
// wg = width of game windows
// hg = height of game windows
// bg = bit of game windows
int wg = 320;
int hg = 240;
int bg = 32;

//declare initial condition
SDL_Surface* sprites = NULL;
SDL_Surface* background = NULL;
SDL_Surface* screen = NULL;
SDL_Surface* cannon = NULL;
SDL_Surface* rotate_cannon = NULL;

//construct event in here
SDL_Event event;

//loading files
SDL_Surface *load_image( std::string filename )
{
    //Get Free store for loadedImage
    SDL_Surface* loadedImage = NULL;

    //Get free store for optimizedImage
    SDL_Surface* optimizedImage = NULL;

    //Loading the image
    loadedImage = IMG_Load( filename.c_str() );

    //Check status of loadedImage
    if( loadedImage != NULL )
    {
        //Convert a surface to the display format
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Frees the resources used by a previously created SDL_Surface
        SDL_FreeSurface( loadedImage );

        //Then we go to mix the color
        if( optimizedImage != NULL )
        {
          //Map the color key
            Uint32 mixlorkey = SDL_MapRGB( optimizedImage->format, 255, 255, 255 );

          //Set it transparent
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, mixlorkey );
        }
    }

    //Return the optimized image
    return optimizedImage;
}

//rotate image
SDL_Surface* rotate(SDL_Surface* source, double angle, double zoom, int smooth)
{
    //give initial for rotate image
    SDL_Surface* rotatefile = NULL;

    //give initial for optimizing rotate image
    SDL_Surface* optimizedrotate = NULL;

    //get rotate here
    rotatefile = rotozoomSurface(source, angle, zoom, smooth);

    //get optimizing
    optimizedrotate = SDL_DisplayFormat(rotatefile);

    //free surface
    SDL_FreeSurface( rotatefile );

    return optimizedrotate;
}

//draw load files
void drawfiles(SDL_Surface* imageSurface,SDL_Surface* screenSurface,int srcX, int srcY,int dstX, int dstY,int width, int height)
{
    //defines a rectangular area of pixels for source
    SDL_Rect srcRect;
    srcRect.x = srcX;
    srcRect.y = srcY;
    srcRect.w = width;
    srcRect.h = height;

    //defines a rectangular area of pixels for destination
    SDL_Rect dstRect;
    dstRect.x = dstX;
    dstRect.y = dstY;
    dstRect.w = width;
    dstRect.h = height;

    SDL_BlitSurface(imageSurface, &srcRect, screenSurface, &dstRect);
}

//initial condition of all sdl
bool init()
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( wg, hg, bg, SDL_ANYFORMAT );

    //If there was an error in setting up the screen
    if ( !screen )
    {
        printf("Unable to set 320x240 video: %s\n", SDL_GetError());
        return false;
    }

    //If everything initialized fine
    return true;
}

//check load files
bool load_files()
{
    //Loading sprites
    sprites = load_image( "/home/corrado/sdl/sprites.png" );

    //If there was an error in loading sprites
    if (sprites == NULL)
    {
        printf("Unable to load sprites: %s\n", SDL_GetError());
        return false;
    }

    //Loading cannon
    cannon = load_image( "/home/corrado/sdl/cannon.png" );

    //If there was an error in loading cannon
    if (cannon == NULL)
    {
        printf("Unable to load cannon: %s\n", SDL_GetError());
        return false;
    }

    //If everything loaded fine
    return true;
}

//clean all memory
void clean_up()
{
    //Free the images
    SDL_FreeSurface( sprites );
    SDL_FreeSurface( background );
    SDL_FreeSurface( cannon );
    SDL_FreeSurface( rotate_cannon );

    //Quit SDL
    SDL_Quit();
}

int main ( int argc, char** argv )
{
    //run init
    if( init() == false )
    {
        return 1;
    }

    //Load the files with optimizing
    if( load_files() == false )
    {
        return 1;
    }

    // load an image of background but with no optimizing
    background = IMG_Load("/home/corrado/sdl/background.png");
    if (background == NULL)
    {
        printf("Unable to load background: %s\n", SDL_GetError());
        return 1;
    }

    double degree = 30;

    // program main loop
    bool done = false;
    bool keyboardstate[323] = {false};
    while (!done)
    {
        // message processing loop
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done = true;
            }
            if (event.type == SDL_KEYDOWN)
            {
                keyboardstate[event.key.keysym.sym] = true;
            }
            if (event.type == SDL_KEYUP)
            {
                keyboardstate[event.key.keysym.sym] = false;
            }
        }
        if (keyboardstate[SDLK_DOWN])
        {
            degree = degree - 1;
        }

        // end of message processing

        // DRAWING STARTS HERE
        //rotating image
        rotate_cannon = rotate(cannon, degree, 1, 0);


        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // centre the image on screen
        //for background
        drawfiles( background, screen, 0, 0, 0, 0, 320, 240 );

        //draw tank
        drawfiles( sprites, screen, 3,5,100,200,32,18);

        //draw bazooka
        drawfiles( sprites, screen, 176, 12,5,180,35,23);

        //draw
        drawfiles( rotate_cannon, screen, NULL, NULL, 50, 50, 40, 40);

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // free loaded bitmap
    clean_up();

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
