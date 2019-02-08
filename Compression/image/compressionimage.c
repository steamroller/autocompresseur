#include <SDL/SDL.h>
#include "pixel_operations.h"
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include "display.h"
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
typedef struct node
{
    char *cryptedvalue;
    int  realvalue;
    struct node *left;
    struct node *right;
} node ;



typedef struct carre
{
    SDL_Rect* rect;
    SDL_Surface* surf;
    struct node *binaryarbre;
    int line;
    int col;
    struct carre *next;
} carre;
typedef struct matrix
{
    double value;
    struct matrix* next;
} matrix;

typedef struct ensemble
{
    struct matrix *Blue;
    struct matrix *Red;
    struct matrix *Green;
    int col;
    int ligne;
    struct ensemble* next;
} ensemble;

//////generate_struct

struct node *initnode()
{
    struct node *no=malloc(sizeof(struct node));
    if(no==0)
        errx(1,"error generating node");
    no->cryptedvalue="";
    no->realvalue=0;
    no->left=NULL;
    no->right=NULL;
    return no;
}


struct carre *initcarre(int heigh, int width)
{
    struct carre *carre=malloc(sizeof(struct carre));
    if(carre==0)
        errx(1,"malloc carré error");
    SDL_Surface* surf=SDL_CreateRGBSurface(0,width,heigh,32,0,0,0,0);
    SDL_Rect *Rect=malloc(sizeof(struct SDL_Rect));
    Rect->x=0;
    Rect->y=0;
    Rect->w=width;
    Rect->h=heigh;
    carre->rect=Rect;
    carre->surf=surf;
    carre->col=0;
    carre->line=0;
    carre->next=NULL;
    return carre;
}
struct matrix *initmatrix(double a)
{
    struct matrix *matrix=malloc(sizeof(struct matrix));
    if(matrix==0)
        errx(1,"malloc matrix error");
    matrix->value=a;
    matrix->next=NULL;
    return matrix;
}
struct ensemble *initensemble(int col, int line)
{
    struct ensemble *ens=malloc(sizeof(struct ensemble));
    if(ens==0)
        errx(1,"malloc ensemble error");
    ens->Blue=initmatrix(0);
    ens->Red=initmatrix(0);
    ens->Green=initmatrix(0);
    ens->col=col;
    ens->ligne=line;
    ens->next=NULL;
    return ens;
}
//////free_struct
void freecarre(struct carre *car)
{
    if(car->next)
        freecarre(car->next);
    free(car->rect);
    free(car->surf);
    free(car);
}

void freematrix(struct matrix *mat)
{
    struct matrix *ne=mat;
    while(mat->next)
    {
        mat=mat->next;
        free(ne);
        ne=mat;
    }
    free(ne);
}

void freeens(struct ensemble *ens)
{
    if(ens->next)
        freeens(ens->next);
    freematrix(ens->Blue);
    freematrix(ens->Green);
    freematrix(ens->Red);
    free(ens);
}
void freenode(struct node *no)
{
    if(no->left==NULL && no->right==NULL)
    {
        free(no->cryptedvalue);
        free(no);
    }
    if(no->left==NULL)
        freenode(no->right);
    else
        freenode(no->left);
}

    
/////change_shape_image
SDL_Surface* sizechange(SDL_Surface* image_surface)
{
    int width= image_surface->w;
    int height= image_surface->h;
    int i=0;
    int j=0;
    while(width%8!=0)
    {
        width+=1;
        i++;
    }
    while(height%8!=0)
    {
        j++;
        height++;
    }
    SDL_Surface* newsurface;
    newsurface=SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_Rect image= { 0, 0, image_surface->w, image_surface->h};
    SDL_BlitSurface( image_surface, &image, newsurface, &image);
    SDL_Rect image1 ={ image_surface->w, 0, j, image_surface->h};
    SDL_Rect image2 ={0, image_surface->h, width, i};
    SDL_FillRect(newsurface, &image1,
            SDL_MapRGB(image_surface->format,255,255,255));
    SDL_FillRect(newsurface, &image2,
            SDL_MapRGB(image_surface->format, 255,255,255));
    return newsurface;
}

//////take 8,8 block in the matrix
struct carre *bloc(SDL_Surface *image_surface, int col, int line)
{
    struct carre *matrix = initcarre(8,8);
    SDL_Rect rect={ col,line,8,8};
    SDL_BlitSurface( image_surface,&rect, matrix->surf, matrix->rect );
    Uint8 r,g,b;
    Uint32 pixel= get_pixel(matrix->surf,0,2);
    SDL_GetRGB(pixel,matrix->surf->format, &r,&g,&b);
    return matrix;
}


///// generate a matrix
void matricequantification(int coefficent,int matrixquantification[])
{
    for(int lines=0;lines<8;lines++)
    {
        for(int col=0;col<8;col++)
            matrixquantification[8*lines+col]=1+coefficent*(col+lines);
    }
}

double C(int pos)
{
    if(pos ==0)
        return 1/sqrt(2);
    return 1;
}

void DCT(SDL_Surface *image,struct ensemble *ens,int mq[])
{
    struct matrix* blue=ens->Blue;
    struct matrix* red=ens->Red;
    struct matrix* green=ens->Green;
    for(int i=0; i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            struct matrix* nmB=initmatrix(0);
            blue->next=nmB;
            struct matrix* nmR=initmatrix(0);
            red->next=nmR;
            struct matrix* nmG=initmatrix(0);
            green->next=nmG;
            double Rres=0;
            double Gres=0;
            double Bres=0;
            Uint8 r,g,b;
            for(int lin=0;lin<8;lin++)
            {
                for(int col=0; col<8; col++)
                {
                    Uint32 pixel= get_pixel(image,lin,col);
                    SDL_GetRGB(pixel,image->format,&r,&g,&b);
                    Rres+=(double)cos((double)((2*lin+1)*i*M_PI)/16)*
                        cos((double)((2*col+1)*j*M_PI)/16)*r;
                    Gres+=(double)cos((double)((2*lin+1)*i*M_PI)/16)*
                        cos((double)((2*col+1)*j*M_PI)/16)*g;
                    Bres+=(double)cos((double)((2*lin+1)*i*M_PI)/16)*
                        cos((double)((2*col+1)*j*M_PI)/16)*b;
                }
            }
            Rres=(1/sqrt(16))*C(j)*C(i)*Rres/mq[i*8+j];
            Gres=(1/sqrt(16))*C(j)*C(i)*Gres/mq[i*8+j];
            Bres=(1/sqrt(16))*C(j)*C(i)*Bres/mq[i*8+j];
            nmB->value=Bres;
            nmG->value=Gres;
            nmR->value=Rres;
            blue=blue->next;
            green=green->next;
            red=red->next;
        }
    }
}

void docmatrixDCT(struct ensemble *ens,int a)
{
    FILE *f;
    a=10000000+a;
    char filename[20];
    sprintf(filename, "%d.DCT", a);
    f=fopen(filename, "w");
    int x=0;
    struct matrix *r=ens->Red;
    struct matrix *b=ens->Blue;
    struct matrix *g=ens->Green;
    fputs("|",f);
    while(x<64)
    {
        if(x%8==0 && x!=0)
        {
            fputs("|",f);
            fputs("\n",f);
        }
        r=r->next;
        b=b->next;
        g=g->next;
        char value[30];
        if((int)b->value!= 0 || (int)g->value!=0 || (int)r->value!=0)
        {
            sprintf(value,"{%d;%d;%d}",(int) b->value,(int)r->value,(int)g->value);
            fputs(value,f);
        }
        /* size_t a=0;
        while((value++)!=" ")
            a++;
        for(int i=0;i+a<30;i++)
            fputs(" ",f);*/
        x++;
    }
    
    fclose(f);
}

void fichiercompress(char* name,int line,int nbdecol)
{
    int fd=open(name, O_CREAT|O_RDWR,00700);
    for(int s=0;s<line;s++)
    {
        ssize_t r=0;
        ssize_t r1=0;
        ssize_t r2=0;
        ssize_t r3=0;
        ssize_t r4=0;
        ssize_t r5=0;
        ssize_t r6=0;
        ssize_t r7=0;
        size_t len=0;
        char Bigline[8*200*line];
        char Bigline1[8*200*line];
        char Bigline2[8*200*line];
        char Bigline3[8*200*line];
        char Bigline4[8*200*line];
        char Bigline5[8*200*line];
        char Bigline6[8*200*line];
        char Bigline7[8*200*line];
        for(int i=0;i<nbdecol;i++)
        {
            FILE* f;
            int numberf=10000000+s*nbdecol+i;
            char filename[20];
            sprintf(filename, "%d.DCT", numberf);
            f=fopen(filename, "r");
            char abc[200];
            fgets(abc,200,f);
            len=strlen(abc);
            r+=len-1;
            strncat(Bigline,abc,len-1);
            fgets(abc,200,f);
            len=strlen(abc);
            r1+=len-1;
            strncat(Bigline1,abc,len-1);
            fgets(abc,200,f);
            len=strlen(abc);
            r2+=len-1;
            strncat(Bigline2,abc,len-1);
            fgets(abc,200,f);
            len=strlen(abc);
            r3+=len-1;
            strncat(Bigline3,abc,len-1);
            fgets(abc,200,f);
            len=strlen(abc);
            r4+=len-1;
            strncat(Bigline4,abc,len-1);
            fgets(abc,200,f);
            len=strlen(abc);
            r5+=len-1;
            strncat(Bigline5,abc,len-1);
            fgets(abc,200,f);
            len=strlen(abc);
            r6+=len-1;
            strncat(Bigline6,abc,len-1);
            fgets(abc,200,f);
            len=strlen(abc);
            r7+=len-1;
            strncat(Bigline7,abc,len-1);
            fclose(f);
       }
       write(fd,Bigline,r);
       write(fd,"\n",1);
       write(fd,Bigline1,r1);
       write(fd,"\n",1);
       write(fd,Bigline2,r2);
       write(fd,"\n",1);
       write(fd,Bigline3,r3);
       write(fd,"\n",1);
       write(fd,Bigline4,r4);
       write(fd,"\n",1);
       write(fd,Bigline5,r5);
       write(fd,"\n",1);
       write(fd,Bigline6,r6);
       write(fd,"\n",1);
       write(fd,Bigline7,r7);
       write(fd,"\n",1);
    }
    close(fd);
}




    
    

