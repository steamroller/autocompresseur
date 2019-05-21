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
    char ff[20];
    sprintf(ff, "%d.tree",path);
    struct DM_Im *c=decodage(path,ff);
    SDL_Surface *surface;
    surface=insertionDCTI(c);
    screen=display_image(surface);
    update_surface(screen,surface);
    wait_for_keypressed();
    return 1;
}
