#include<stdlib.h>
#include<stdio.h>
#include"huffman.h"
#include<string.h>

int main(int argc, char *argv[])
{
	printf("Taille originale du fichier : %li\n",strlen(argv[1]));
	whole_comp(argv[1], argv[2]);
}
