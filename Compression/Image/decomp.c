#include <stdio.h>
#include <err.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include "decompression.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    SDL_Surface *screen;
    if(argc!=3 &&  argc!=5)
        errx(1,"not good amount of argument :the good amount is 2 or 4");
    struct DM_Im *c=decodage(argv[1],argv[2]);
    SDL_Surface *surface;
    surface=insertionDCTI(c);
    screen=display_image(surface);
    update_surface(screen,surface);
    wait_for_keypressed();
    return 1;
}
