#include <stdio.h>
#include <err.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include "compressionimage.h"
#include "display.h"
#include "pixel_operations.h"


int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;
    SDL_Surface* resized_surface;

    init_sdl();

    image_surface = load_image("imagetest.jpg");
    screen_surface = display_image(image_surface);

    wait_for_keypressed();
    
    int width= image_surface->w;
    int height= image_surface->h;

    printf(" size before= %i * %i \n", width, height);

    resized_surface=sizechange(image_surface);
    
    int nwidth= resized_surface->w;
    int nheight= resized_surface->h;
    printf(" size after = %i * %i \n", nwidth, nheight);
    update_surface(screen_surface,resized_surface);
    wait_for_keypressed();
    nwidth=nwidth/8;
    nheight=nheight/8;
    struct carre *carre=initcarre(8,8);
    struct ensemble *ensemble=initensemble(-1,-1);
    struct carre *begincarre=carre;
    struct ensemble *beginensemble=ensemble;
    int mq[64];
    int a=0;
    matricequantification(2,mq);
    for(int c=0;c<nwidth;c++)
    {
        carre->col++;
        for(int l=0;l<nheight;l++)
        {
            ensemble->next=initensemble(c,l);
            carre->next=bloc(resized_surface,8*c,8*l);
            carre->next->line++;
            carre=carre->next;
            DCT(carre->surf,ensemble->next,mq);
            docmatrixDCT(ensemble->next,a);
            a++;
            ensemble=ensemble->next;
        }
    }
    char name[30]="imagetest.DCT";
    fichiercompress(name,nwidth,nheight);
    for(int j=0;j<a;j++)
    {
            int status;
            char filename[20];
            int n=10000000+j;
            sprintf(filename, "%d.DCT",n);
            status= remove(filename);
            if(status!=0)
                puts(filename);
    } 
    printf("c'est la fin\n");
    freeens(beginensemble);
    freecarre(begincarre);
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(resized_surface);
    SDL_FreeSurface(screen_surface);
    return 0;
}
