#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include"huffman.h"
#include<string.h>
#include<math.h>
#include<err.h>

struct bintree
{
	//int value;
	char letter;
	struct bintree *left;
	struct bintree *right;

};

struct mousquetaire
{
	struct gobelin *cabane;
	struct gobelin *fut;

};

struct bizzare//STRUCTURE DES LISTES DE TUPLES : [(int occ, bintree *arbre)...]
{
	int occ;
	struct bintree *arbre;
	struct bizzare *next;
};

struct listuple
{
	int freq;
	char letter;
	struct listuple *next;
	int len;
};

struct tree_list
{
	struct tree_list *next;
	struct bintree *this;
};

struct gobelin
{
	int booleen;
	char *string;
};

void print_tree(struct bintree *tree)
{
    if (tree != NULL)
    {
        printf("(%c,), ",tree->letter);
        print_tree(tree->left);
        print_tree(tree->right);
    }
}


int main(int argc,char *argv[])
{
	if(argc != 2)
		errx(1,"Two arguments are expected");
	//char sent[500] = "pipi";
	struct listuple *liste = calloc(1,sizeof(struct listuple));
	//liste = init(liste);
	printf("\nPhrase initiale : %s\n\n",argv[1]);
	printf("Liste des fréquences : ");
	liste = build_freq_list(argv[1]);
	//pop(liste);
	struct listuple *d = liste;
	printf("[");
	liste = liste->next;
	while(liste->next != NULL)
	{
		printf("(%c , %i) , ",liste->letter,liste->freq);
		liste=liste->next;
	}
	printf("(%c , %i)",liste->letter,liste->freq);
	printf("]\n");
	//printf("frq de d = %i\n",(d->next)->freq);
	//printf("This list has a len of : %i\n",len_listuple(d));
	struct bintree *test = calloc(1,sizeof(struct bintree));
	test = build_tree(d);
	printTree(test);
	printf("\n");
	char *bin = encodetree(test);
	printf("Arbre de Huffman associé =  %s\n\n",bin);
	//char *a = calloc(1,sizeof(char));
	//int coucou = findbinary(test,'a');
	//printf("%s\n",a);

	//printf("%s\n",encodedata(test,argv[1]));
	//printf("entier = %li\n",strlen((tobinarybis("01011010010000001010010011000110111"))->string));
	struct mousquetaire *chapeau = compression(argv[1]);
	/*char *testt = calloc(1,sizeof(char));
	asprintf(&testt,"(%s , %i)  (%s , %i)\n",chapeau->cabane->string,chapeau->cabane->booleen,chapeau->fut->string,chapeau->fut->booleen);
	FILE *f = fopen("file.txt","w");
	fprintf(f,"testt = %s",testt);
	fclose(f);*/

	printf("Resultat compressé : Le texte -> (%s , %i) L'arbre -> (%s , %i)\n\n",chapeau->cabane->string,chapeau->cabane->booleen,chapeau->fut->string,chapeau->fut->booleen);
	printf(" test de decodedata : %s\n",decodedata(test,"00"));




}


