#include <stdio.h>
#include <err.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include "decompression.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int decomp(char *path)
{
    SDL_Surface *screen;
    char *ff = calloc(1,1);
    asprintf(&ff,"%s.tree",path);
    struct DM_Im *c=decodage(ff,path);
    SDL_Surface *surface;
    surface=insertionDCTI(c);
    screen=display_image(surface);
    update_surface(screen,surface);
    wait_for_keypressed();
    return 1;
}
int main(int argc, char *argv[])
{
    if(argc!=2)
        errx(1,"not good nomber");
    decomp(argv[1]);
    return 1;
}
