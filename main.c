#include <stdio.h>
#include <err.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include "compressionimage.h"
#include "display.h"
#include "pixel_operations.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc!=3)
        errx(1,"not good amount of argument :the good amount is 2 with first argument is the path and second is the quality");
    
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;
    SDL_Surface* resized_surface;

    init_sdl();

    image_surface = load_image(argv[1]);
    screen_surface = display_image(image_surface);
    
    //int width= image_surface->w;
    //int height= image_surface->h;

    resized_surface=sizechange(image_surface);
    
    int nwidth= resized_surface->w;
    int nheight= resized_surface->h;
   
    update_surface(screen_surface,resized_surface);
    

    nwidth=nwidth/8;
    nheight=nheight/8;

    struct carre *carre=initcarre(8,8);
    struct ensemble *ensemble=initensemble(-1,-1);
    struct carre *begincarre=carre;
    struct ensemble *beginensemble=ensemble;
    int mq[64];
    int a=0;
    char *p;
    long coocoo=strtol(argv[2], &p,10);
    int bea=coocoo;
    matricequantification(bea,mq);

    for(int c=0;c<nwidth;c++)
    {
        carre->col++;

        for(int l=0;l<nheight;l++)
        {
            ensemble->next=initensemble(c,l);
            carre->next=bloc(resized_surface,8*c,8*l);
            carre->next->line++;
            carre=carre->next;
            DCT(carre,ensemble->next,mq);
            docmatrixDCT(ensemble->next,a);
            a++;
            ensemble=ensemble->next;
        }
    };
    char name[40];
    char namme[40];

    sprintf(name,"%s%i.DCT",argv[1],bea);
    sprintf(namme,"%s%i.tree",argv[1],bea);

    fichiercompress(name,nwidth,nheight);

    treecompress(namme,nwidth,nheight);

    for(int j=0;j<a;j++)
    {
            int status,status2;

            char filename[20];
            char ff[20];

            int n=10000000+j;

            sprintf(filename, "%d.DCT",n);
            sprintf(ff,"%d.tree",n);

            status= remove(filename);
            if(status!=0)
                puts(filename);

            status2= remove(ff);
            if(status2!=0)
                puts(ff);
    }

    freeens(beginensemble);
    freecarre(begincarre);
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(resized_surface);
    SDL_FreeSurface(screen_surface);

    return 0;
}
