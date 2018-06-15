
# testSDL 1.0



## a simple "superclassical gravitation" simulator

of course gravit is better, but/hence this is quite easier to understand...

the noticeable thing is "how stable 2^n-body problems could be", despite all the "perturbations" due to errors: 

1. we're working with 64 bit "double" numbers, not "real" numbers
2. time is not continuous, it's just a counter for the "main loop"

still, 2-body stays there for days, 2^2 too, which is quite unexpected.



# OS requirements

proven to work on linux (debian 8 and 9), uses libSDL 1.2: 

	apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-gfx1.2-dev

libraries should get installed into 

	/usr/include/SDL



# IDEs

developed with eclipse-C++, several versions used (currently oxygen).

GIT repo also contains .project and .cproject files, so to help track dependencies.



# about

uses simple linearization of the (idealized) n-body problem differential equations:

1. all "particles" are "dirac's deltas in spacetime", so all "weight" 1

2. at start, initial positions and speeds are specified, for all n "particles"
    *  at the moment a consol prompt only asks for how many particles
    * initial conditions are statically coded, tried to use XML files for that 

3. at each "loop" in the simulation, the following happens:
    * all particles are drawn on the SDL 3D output
    * all n*(n-1) distances are calculated into a "zero signature, symmetrical distances matrix"
    * all n "next speeds" and all n "next positions" are calculated
    * user inputs are taken so to control 3D camera (just rotate and zoom for now)
    * next loop goes in unless "exit" was requested



# todos

SDL 3D output (especially projections) are "working unknowns": I adapted a working 3D sample,
but got no real understanding of it, so that should really be improved.

initial conditions should be specified either via an external data file, see the attempt done with XML/xcerses,
but the actual goal would be for the simulation to help users with 2^n-body problems, which are the real subject of study.

probably the best option would be to learn how to do that 2^n with LUA and use gravit (see below), but that won't likely help adding a "cosmological constant", to take into account also "the stuff out there", beyond the 2^n+m which you may want to study "locally" (i.e. placing them into a finite region of inifinite space: with gravit, all stuff tends to "collapse" into - and then "bang" out - some "central place", which, of course, "has no meaning to exist").  



# also see

gravit (debian package) has optimized (better than linearization, also using localized distances matrix reduction) simulation, which makes it a lot more "fluid" and performing. 

It's also "initializable" with LUA scripts, so 2^n+m could be (easily) be done, but I'm not sure if it can provide a setup for "the masses out there" (sort of "cosmological constant", which "pulls outwards", since "you're not alone").

