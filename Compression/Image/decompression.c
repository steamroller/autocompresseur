#include <err.h>                                                                
#include <stdlib.h>                                                             
#include <stdio.h>                                                                      
#include <math.h>                                                               
#include <unistd.h>                                                             
#include <sys/types.h>                                                          
#include <sys/stat.h>                                                           
#include <fcntl.h>                                                              
#include <string.h> 
#include "display.h"
#include <SDL/SDL.h>
#include "pixel_operations.h"

typedef struct bloc
{
    int r;
    int g;
    int b;
    int col;
    int lin;
    struct bloc *next;
} bloc;

typedef struct DM_Im
{
    int col;
    int line;
    int colonnes;
    int lines;
    struct bloc *bloc;
    struct DM_Im *next;
} DM_Im;

   
struct bloc *initbloc(int col,int line)
{
    struct bloc *bc=malloc(sizeof(struct bloc));
    if(bc==0)
        errx(1,"error generating bloc");
    bc->r=0;
    bc->g=0;
    bc->b=0;
    bc->col=col;
    bc->lin=line;
    bc->next=NULL;
    return bc;
}

struct DM_Im *initDM_Im(int coll,int lin, int a, int b)
{
    struct DM_Im* dm=malloc(sizeof(struct DM_Im));
    if(dm==0)
        errx(1,"error generating DM_Im");
    dm->colonnes=coll;
    dm->lines=lin;
    dm->bloc=initbloc(0,0);
    dm->next=NULL;
    dm->line=a;
    dm->col=b;
    return dm;
}

void freebloc(struct bloc *b)
{
    if(b->next)
        freebloc(b->next);
    free(b);
}

void freeDM_Im(struct DM_Im *D)
{
    if(D->next)
        freeDM_Im(D->next);
    freebloc(D->bloc);
    free(D);
}

int nombredec(int nb)
{
    int a=1;
    int d=nb;
    while(d/2>0)
    {
        d=d/2;
        a++;
    }
    return a;
}

struct DM_Im *decodage(char *pathtree,char *pathdct)
{
    FILE* tree;
    FILE* Dct;
    tree=fopen(pathtree,"r");
    Dct=fopen(pathdct,"r");
    char collin[30];
    memset(collin,0,sizeof(collin));
    if(fgets(collin,30,Dct)==NULL)
        errx(1,"couldn't access to data");
    int line=0;
    int col=0;
    int value=0;
    size_t len=strlen(collin);
    for(size_t i=0;i<len && collin[i]!='\n';)
    {
        char *q=malloc(sizeof(char));
        q=strncpy(q,(char*)collin+i,1);
        value=10*value+atoi(q);
        i++;
        if(collin[i]=='.')
        {
            line=value;
            value=0;
        }
    }
    col=value;
    printf("line=%d && col= %d \n",line,col);
    int v=0;
    int x=0;
    struct DM_Im *dm=initDM_Im(x,v,line,col);
    struct DM_Im *p=dm;
    for(int i=0;i<col*line;i++)
    {
        struct bloc* g=p->bloc;
        int a=0;
        int b=0;
        int m=1;
        int end=0;
        char f[30];
        char e[30];
        for(size_t j=0;j<64;j++)
        {
            struct bloc *abc=initbloc(a,b);
            g->next=abc;
            if(end==1)
            {
                //printf("0,");
                abc->r=0;
                abc->g=0;
                abc->b=0;
            }
            else
            {
                //c=nombredec(m);
                //printf("c=%d\n",c);
                m++;
                memset(f,0,sizeof(f));
                memset(e,0,sizeof(e));
                //do
                //{
                //    if(fgets(f,c+1,Dct)==NULL)
                //        errx(1,"couldn't access to data");
                //}while(f[0]=='\n');
                //size_t len=strlen(f);
                //printf("len(f)=%ld\n",len);
                //if(f[len-1]=='\n')
                //    d=1;
                //printf("f=%s\n",f);
                value=0;
                if(fgets(e,30,tree)==NULL)
                    errx(1,"Couldn't access to datas");
                if(e[0]=='\n')
                {
                    end=1;
                    continue;
                }

                size_t n=0;
                int negatif=0;
                while(e[n]!='\0')
                {
                    //printf("%s\n",&e[n]);
                    while(e[n]!='.')
                    {
                        if(e[n]=='\n')
                            break;
                        if(e[n]=='-')
                        {
                            negatif=1;
                            n++;
                        }
                        else
                        {
                            char *w=malloc(sizeof(char));
                            w=strncpy(w,(char*)e+n,1);
                            if(negatif!=1)
                            {
                                negatif=0;
                                value=10*value+atoi(w);
                            }
                            else
                                value=(-1)*atoi(w);
                            n++;
                            free(w);
                            //printf("%d\n",value);
                        }
                    }
                    value=value*(1+20*(a+b));
                    if(abc->r==0)
                    {
                        abc->r=value;
                        value=0;
                    }
                    if(abc->g==0)
                    {
                        abc->g=value;
                        value=0;
                    }
                    abc->b=value;
                    n++;
                }
            }
            if(x==0 && v==0)
                printf("d(%d,%d),b(%d,%d)=(%d,%d,%d)\n",
                    v,x,a,b,abc->r,abc->g,abc->b);
            a++;
            if(a==8)
            {
                a=0;
                b++;
            }
            g=g->next;
        }
        v++;
        if(v==col)
        {
            v=0;
            x++;
        }
        struct DM_Im *def=initDM_Im(v,x,line,col);
        p->next=def;
        p=p->next;
    }
    return dm;
}

double C(int pos)
{
    if(pos ==0)
        return 1/sqrt(2);
    return 1;
}

SDL_Surface *insertionDCTI(struct DM_Im *dm)
{
    struct DM_Im*d=dm;
    int line=d->line;
    int col=d->col;
    SDL_Surface* newsurface;
    newsurface= SDL_CreateRGBSurface(0,8*line,8*col,32,0,0,0,0);
    for(int x=0;x<line;x++)
    {
        for(int y=0;y<col;y++)
        {
            struct bloc* b=d->bloc;
            for(size_t l=0;l<8;l++)
            {
                for(size_t c=0;c<8;c++)
                {
                    struct bloc *m=b;
                    unsigned int r=0;
                    unsigned int g=0;
                    unsigned int b=0;
                    for(size_t li=0;li<8;li++)
                    {
                        for(size_t co=0;co<8;co++)
                        {
                            r+=C(l)*C(c)*m->r*
                                (double)cos((double)(2*l+1)*li*M_PI/16)*
                                (double)cos((double)(2*c+1)*li*M_PI/16);
                            g+=C(l)*C(c)*m->g*
                                (double)cos((double)(2*l+1)*li*M_PI/16)*
                                (double)cos((double)(2*c+1)*li*M_PI/16);
                            b+=(double)C(l)*(double)C(c)*m->b*
                                (double)cos((double)(2*li+1)*li*M_PI/16)*
                                (double)cos((double)(2*co+1)*li*M_PI/16);
                            m=m->next;
                        }
                    }
                    Uint8 r1=r/4;
                    Uint8 g1=g/4;
                    Uint8 b1=b/4;
                    printf("pixel(%ld;%ld)=r1=%d,g1=%d,b1=%d\n",8*x+l,8*y+c,r1,g1,b1);
                    Uint32 pixel=SDL_MapRGBA(newsurface->format,r1,g1,b1,255);
                    put_pixel(newsurface,8*x+l,8*y+c,pixel);
                }
            }
            d=d->next;
        }
    }
    free(dm);
    return newsurface;
}

