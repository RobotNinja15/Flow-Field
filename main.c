/* The perlin.c file was gotten from nowl on github: https://gist.github.com/nowl/828013
It provided me with the necessary noise fucntions: noise2(), noise2d() and perlin() */

/* Thanks to Mattias Gustavsson for the wonderful dos-like library/framework */

/////////////////////////////////////////////////////////////////////////////
// PROGRAM START
////////////////////////////////////////////////////////////////////////////


/*A VERY SIMPLE FLOW FIELD PROGRAM */
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include "dos.h"
#include "perlin.c"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

#define NB 1000               // change this to increase or decrease the number of particles
#define NOISE_SCALE 0.005f     // increase or decrease the noise scale, 0.05 seems like a sweet spot for me
#define NOISE_ANGLE 23.0f  //6.283f //probably in radians not sure lmao, but you have increase and increase this for different results
float noiseSpeed = 2.5f;    //this can also be changed to achieve different results. Why didn't I make it a MACRO? well, C wouldn't let me :(

////////////////////////////
//Particle struct
///////////////////////////
typedef struct {
    int x;
    int y;
    int vx;
    int vy;
} particle_t;

//the particle array to store: postion/co-ords, and velocity(vx and vy) for each particle object
particle_t particles[NB];

///////////////////////////////
//MAIN
//////////////////////////////
int main(int argc, char* args[]){

    setvideomode(videomode_320x200);
    //setpal(0, 36, 36, 56);  //Blue background.

    setdoublebuffer(1);
    uint8_t* framebuffer = screenbuffer(); //initialize framebuffer

    srand (time(NULL)); //initialize seed for rand()


    //this loads random values into the x and y for each particle in the array
    for(int i = 0; i < NB; i++){
        particles[i].x = rand() % SCREEN_WIDTH;
        particles[i].y = rand() % SCREEN_HEIGHT;
    }

    //GAME LOOP! - I have been calling all while() loops game loops for 2 years now :(
    while(!shuttingdown()){
        waitvbl();
        //clearscreen();                 //gives us the nice pixel trails when it's disabled, if you want to enable it you can do it

        //this spawns the particles with the postion values
        for (int i = 0; i < NB; ++i){

            // this is the core right here, the main course, crème de la crème, the good shit.
            // well it's responsible for the lovely noise movements of the particles
            // I had to get perlin.c file from someone's repo on github (it has been corrected to account for negative values)
            // you can replace the noise2(), with noise2d or perlin()
            float n  = NOISE_ANGLE*noise2(NOISE_SCALE*particles[i].x, NOISE_SCALE*particles[i].y);

            //gets the lovely values from noispeed*cos/sin(angle) into the velocity variables of each particle(vx,vy)
            particles[i].vx = noiseSpeed * cos(n);
            particles[i].vy = noiseSpeed * sin(n);

            // adds the velocity values to the position(x,y) of each particle to give them some movement
            particles[i].x += particles[i].vx;
            particles[i].y += particles[i].vy;

            //circle(particles[i].x,particles[i].y, 2);// Using circles is very messy, you loose a lot of detail

            // this wraps the particles around the screen, doesn't look great to me
            /*
            if(particles[i].x < 0) particles[i].x = SCREEN_WIDTH -1;
            if(particles[i].x >= SCREEN_WIDTH) particles[i].x = 0;
            if(particles[i].y < 0) particles[i].y = SCREEN_HEIGHT -1;
            if(particles[i].y >= SCREEN_HEIGHT) particles[i].y = 0;
            */


            //be careful while using the framebuffer, since you are directly interacting with memory you have to watch out for out of bounds issues
            //sadly, this is C so you have to be careful or it will kill itself(crash) :(
            if (particles[i].x >= 0 && particles[i].x < SCREEN_WIDTH && particles[i].y >= 0 && particles[i].y < SCREEN_HEIGHT){

                //2D values(x,y) coverted to 1D(Linear) positions: x,y = (Width*y)+x;
                //and 0x19 is the color value for each particle, I could make it colorfull by giving it random color values.
                framebuffer[(SCREEN_WIDTH * particles[i].y) + particles[i].x] = 0x19;
            }

        }

        //swaps buffers, very self explanatory
        framebuffer = swapbuffers();

        //Exits the Program
        if (keystate(KEY_ESCAPE))
            break;
    }

    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// END OF LINE
/////////////////////////////////////////////////////////////////////////////////////////////
