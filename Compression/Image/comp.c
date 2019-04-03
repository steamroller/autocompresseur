#include <stdio.h>
#include <err.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include "compressionimage.h"
#include "display.h"
#include "pixel_operations.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
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
    
    printf("old width= %d\n",image_surface->w);
    printf("old height= %d\n",image_surface->h);
    int size0 = image_surface->w*image_surface->h*4;
    printf("old size of the image= %d octets\n\n",size0);
    resized_surface=sizechange(image_surface);
    
    int nwidth= resized_surface->w;
    int nheight= resized_surface->h;

    printf("new width=%d\nnew height=%d\n",nwidth,nheight);

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
            docmatrixDCT2(ensemble->next,a);
            a++;
            ensemble=ensemble->next;
        }
    };
    char name[40];
    char namme[40];

    sprintf(name,"%s%i.DCT",argv[1],bea);
    sprintf(namme,"%s%i.tree",argv[1],bea);
    
    struct stat *stating=fichiercompress2(name,nwidth,nheight);

    printf("the compressed file have a size of %lld octets \n\n",
            (long long) stating->st_size);
    printf("the size has been divided with a ratio of  %f  \n", (double)size0/(long long)stating->st_size);
    
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
