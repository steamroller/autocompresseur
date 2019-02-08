#ifndef COMPRESSIONIMAGE_H
#define COMPRESSIONIMAGE_H
#include <SDL/SDL.h>
#include "pixel_operations.h"
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include "display.h"
#include <math.h>

typedef struct node
{
    char *cryptedvalue;
    int realvalue;
    struct node *left;
    struct node *right;
} node;

typedef struct carre
{
    SDL_Rect* rect;
    SDL_Surface* surf;
    struct node *binaryarbre;
    int col;
    int line;
    struct carre* next;
} carre;

typedef struct matrix
{
    double value;
    struct matrix *next;
} matrix;

typedef struct ensemble
{
    struct matrix *Blue;
    struct matrix *Red;
    struct matrix *Green;
    int col;
    int ligne;
    struct ensemble *next;
} ensemble;

struct node *initnode();
struct carre *initcarre(int heigh, int width);
struct matrix *initmatrix(double a);
struct ensemble *initensemble(int col, int line);
void freecarre(struct carre *car);
void freematrix(struct matrix *mat);
void freeens(struct ensemble *ens);
void freenode(struct node *no);
SDL_Surface* sizechange(SDL_Surface* image_surface);
struct carre *bloc(SDL_Surface *image_surface, int col, int line);
void matricequantification(int coefficient,int matrixquantification[]);
double C(int pos);
void DCT(SDL_Surface *image,struct ensemble *ens,int mq[]);
void docmatrixDCT(struct ensemble *ens, int a);
void fichiercompress(char *name, int line, int col);
#endif 
