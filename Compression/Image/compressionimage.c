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
    int r;
    int g;
    int b;
    struct node *left;
    struct node *right;
    struct node *previous;
} node ;



typedef struct carre
{
    SDL_Rect* rect;
    SDL_Surface* surf;
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
    struct node *btree;
    int col;
    int ligne;
    struct ensemble* next;
} ensemble;

//////generate_struct

struct node *initnode(struct node* pre,int red,int green,int blue)
{
    struct node *no=malloc(sizeof(struct node));
    if(no==0)
        errx(1,"error generating node");
    no->cryptedvalue=malloc(sizeof(char)*64);;
    no->r=red;
    no->g=green;
    no->b=blue;
    no->left=NULL;
    no->right=NULL;
    no->previous=pre;
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
    ens->btree=initnode(NULL,0,0,0);
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
void freenode(struct node *no)
{
    if(no->left==NULL && no->left==NULL)
    {
        free(no);
    }
    if(no->left!=NULL)
        freenode(no->left);
    if(no->right!=NULL)
        freenode(no->right);
}
void freeens(struct ensemble *ens)
{
    if(ens->next)
        freeens(ens->next);
    freematrix(ens->Blue);
    freematrix(ens->Green);
    freenode(ens->btree);
    freematrix(ens->Red);
    free(ens);
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

void DCT(struct carre *carr,struct ensemble *ens,int mq[])
{
    SDL_Surface *image = carr->surf;
    struct matrix* blue=ens->Blue;
    struct matrix* red=ens->Red;
    struct matrix* green=ens->Green;
    int x=0;
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
            Rres=(double)((1/sqrt(16))*C(j)*C(i)*Rres)/(double)mq[8*i+j];
            Gres=(double)((1/sqrt(16))*C(j)*C(i)*Gres)/(double)mq[8*i+j];
            Bres=(double)((1/sqrt(16))*C(j)*C(i)*Bres)/(double)mq[8*i+j];
            nmB->value=Bres;
            nmG->value=Gres;
            nmR->value=Rres;
            blue=blue->next;
            green=green->next;
            red=red->next;
            x++;
        }
    }
}
long decimalToBinary(int decimalnum)
{
    long binarynum = 0;
    int rem, temp = 1;

    while (decimalnum!=0)
    {
        rem = decimalnum%2;
        decimalnum = decimalnum / 2;
        binarynum = binarynum + rem*temp;
        temp = temp * 10;
    }
    return binarynum;
}

void docmatrixDCT(struct ensemble *ens,int a)
{
    FILE *f;
    FILE *o;
    a=10000000+a;
    char filename[20];
    char ff[20];
    sprintf(filename, "%d.DCT", a);
    sprintf(ff,"%d.tree",a);
    f=fopen(filename, "w");
    o=fopen(ff, "w");
    int x=0;
    struct matrix *r=ens->Red;
    struct matrix *b=ens->Blue;
    struct matrix *g=ens->Green;
    fputs("|",f);
    struct node* prev=ens->btree;
    int n=0;
    int nomber=0;
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
        /*printf("before=%s\n",before);
        printf("cryptedvalue=%s\n",prev->cryptedvalue);*/
        if((int)b->value!= 0 || (int)g->value!=0 || (int)r->value!=0)
        {
            char value[30];
            char Huffman[64*3+30];
            char after[30];
            long goodenough=decimalToBinary(nomber);
            sprintf(after,"%ld",goodenough);
            nomber++;
            struct node* noon=initnode(prev,
                        (int)r->value,(int)g->value,(int)b->value);
            noon->cryptedvalue=after;
            if(n==0)
            {
                n++;
                prev->left=noon;
            }
            else
            {
                n=0;
                prev->right=noon;

                if(prev->previous!=NULL && prev==prev->previous->left)
                {
                    prev=prev->previous->right;
                }
                else
                {
                    prev=prev->left;
                }
            }
            sprintf(Huffman,"%s={%d;%d;%d}\n",noon->cryptedvalue,noon->b,noon->r,noon->g);
            sprintf(value,"%s",noon->cryptedvalue);
            fputs(value,f);
            fputs(Huffman,o);
        }
        /* size_t a=0;
        while((value++)!=" ")
            a++;
        for(int i=0;i+a<30;i++)
            fputs(" ",f);*/
        x++;
    }
    fputs("|\n",f);
    fclose(f);
    fclose(o);
}
void treecompress(char* name,int line,int nbdecol)
{
    int fd=open(name, O_CREAT|O_RDWR,00700);
    char rline[30];
    for(int s=0;s<line;s++)
    {
        for(int i=0;i<nbdecol;i++)
        {
            size_t len=30;
            FILE* g;
            int nmb=10000000+s*nbdecol+i;
            char ff[30];
            memset(ff,0,sizeof(ff));
            sprintf(ff,"%d.tree",nmb);
            g=fopen(ff,"r");
            while(len!=0)
            {
                memset(rline,0,sizeof(rline));
                if(fgets(rline, 30, g)==NULL)
                    break;
                len=strlen(rline);
                if(write(fd,rline,len)==-1)
                    errx(1,"didn't write all the line");
            }
            if(write(fd,"\n",1)==-1)
                errx(1,"error writing");
            fclose(g);
        }
    }
    close(fd);
}

struct stat *fichiercompress(char* name,int line,int nbdecol)
{
    struct stat *b=malloc(sizeof(struct stat));
    int fd=open(name, O_CREAT|O_RDWR,00700);
    size_t len=0;
    char Bigline[nbdecol*30*line];
    char Bigline1[nbdecol*30*line];
    char Bigline2[nbdecol*30*line];
    char Bigline3[nbdecol*30*line];
    char Bigline4[nbdecol*30*line];
    char Bigline5[nbdecol*30*line];
    char Bigline6[nbdecol*30*line];
    char Bigline7[nbdecol*30*line];
    for(int s=0;s<line;s++)
    {
        ssize_t r,r1,r2,r3,r4,r5,r6,r7;
        r=0;
        r1=0;
        r2=0;
        r3=0;
        r4=0;
        r5=0;
        r6=0;
        r7=0;
        memset(Bigline,0,sizeof(Bigline));
        memset(Bigline1,0,sizeof(Bigline1));
        memset(Bigline2,0,sizeof(Bigline2));
        memset(Bigline3,0,sizeof(Bigline3));
        memset(Bigline4,0,sizeof(Bigline4));
        memset(Bigline5,0,sizeof(Bigline5));
        memset(Bigline6,0,sizeof(Bigline6));
        memset(Bigline7,0,sizeof(Bigline7));
        for(int i=0;i<nbdecol;i++)
        {
            FILE* f;
            int numberf=10000000+s*nbdecol+i;
            char filename[20];
            memset(filename,0,20*sizeof(char));
            sprintf(filename, "%d.DCT", numberf);
            f=fopen(filename, "r");
            char abc[200];
            if(fgets(abc,200,f)==NULL) 
                errx(1,"error reading the first line");
            len=strlen(abc);
            r+=len-1;
            strncat(Bigline,abc,len-1);
            if(fgets(abc,200,f)==NULL)
                errx(1,"error reading the 2nd line");
            len=strlen(abc);
            r1+=len-1;
            strncat(Bigline1,abc,len-1);
            if(fgets(abc,200,f)==NULL)
                errx(1,"error reading the 3rd line");
            len=strlen(abc);
            r2+=len-1;
            strncat(Bigline2,abc,len-1);
            if(fgets(abc,200,f)==NULL)
                errx(1,"error reading the 4th line");
            len=strlen(abc);
            r3+=len-1;
            strncat(Bigline3,abc,len-1);
            if(fgets(abc,200,f)==NULL)
                errx(1,"error reading the 5th line");
            len=strlen(abc);
            r4+=len-1;
            strncat(Bigline4,abc,len-1);
            if(fgets(abc,200,f)==NULL)
                errx(1,"error reading the 6th line");
            len=strlen(abc);
            r5+=len-1;
            strncat(Bigline5,abc,len-1);
            if(fgets(abc,200,f)==NULL)
                errx(1,"error reading the 7th line");
            len=strlen(abc);
            r6+=len-1;
            strncat(Bigline6,abc,len-1);
            if(fgets(abc,200,f)==NULL)
                errx(1,"error reading the 8th line");
            len=strlen(abc);
            r7+=len-1;
            strncat(Bigline7,abc,len-1);
            fclose(f);
       }
       if(write(fd,Bigline,r)==-1)
           errx(1,"error writing");
       if(write(fd,"\n",1)==-1)
           errx(1,"error writing");
       if(write(fd,Bigline1,r1)==-1)
           errx(1,"error writing");
       if(write(fd,"\n",1)==-1)
           errx(1,"error writing");
       if(write(fd,Bigline2,r2)==-1)
           errx(1,"error writing");
       if(write(fd,"\n",1)==-1)
           errx(1,"error writing");
       if(write(fd,Bigline3,r3)==-1)
           errx(1,"error writing");
       if(write(fd,"\n",1)==-1)
           errx(1,"error writing");
       if(write(fd,Bigline4,r4)==-1)
           errx(1,"error writing");
       if(write(fd,"\n",1)==-1)
           errx(1,"error writing");
       if(write(fd,Bigline5,r5)==-1)
           errx(1,"error writing");
       if(write(fd,"\n",1)==-1)
           errx(1,"error writing");
       if(write(fd,Bigline6,r6)==-1)
           errx(1,"error writing");
       if(write(fd,"\n",1)==-1)
           errx(1,"error writing");
       if(write(fd,Bigline7,r7)==-1)
           errx(1,"error writing");
       if(write(fd,"\n\n",2)==-1)
           errx(1,"error writing");
    }
    if(fstat(fd,b)==-1)
        errx(1,"couldn't get back the value of stat");
    close(fd);
    return b;
}

