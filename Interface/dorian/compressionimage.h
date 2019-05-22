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
    int r;
    int g;
    int b;
    struct node *left;
    struct node *right;
    struct node *previous;
} node;

typedef struct carre
{
    SDL_Rect* rect;
    SDL_Surface* surf;
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
    struct node *btree;
    struct ensemble *next;
} ensemble;

struct node *initnode(struct node* prev, int r,int g, int b);
struct carre *initcarre(int heigh, int width);
struct matrix *initmatrix(double a);
struct ensemble *initensemble(int col, int line);
void freecarre(struct carre *car);
void freematrix(struct matrix *mat);
void freeens(struct ensemble *ens);
void freenode(struct node *no);
SDL_Surface* sizechange(SDL_Surface* image_surface);
struct carre *bloc(SDL_Surface* surf, int col, int line);
void matricequantification(int coefficient,int matrixquantification[]);
double C(int pos);
void DCT(struct carre* car,struct ensemble *ens,int mq[]);
void docmatrixDCT(struct ensemble *ens, int a);
void docmatrixDCT2(struct ensemble *ens, int a);
void treecompress(char *name, int line, int col);
struct stat *fichiercompress2(char *name, int line, int col);
struct stat *fichiercompress(char *name, int line, int col);
#endif 
