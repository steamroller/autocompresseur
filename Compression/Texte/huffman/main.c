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
    char *encode = encodedata(test,argv[1]);
    //printf("message encode %s:\n",encode);

	printf("encode_data = %s\n",encodedata(test,argv[1]));
	//printf("entier = %li\n",strlen((tobinarybis("01011010010000001010010011000110111"))->string));
	struct mousquetaire *chapeau = compression(argv[1]);
	/*char *testt = calloc(1,sizeof(char));
	asprintf(&testt,"(%s , %i)  (%s , %i)\n",chapeau->cabane->string,chapeau->cabane->booleen,chapeau->fut->string,chapeau->fut->booleen);
	FILE *f = fopen("file.txt","w");
	fprintf(f,"testt = %s",testt);
	fclose(f);*/

	printf("Resultat compressé : Le texte -> (%s , %i) L'arbre -> (%s , %i)\n\n",chapeau->cabane->string,chapeau->cabane->booleen,chapeau->fut->string,chapeau->fut->booleen);

  printf("========= D E C O M P R E S S I O N ==========\n");
	//printf(" test de decodedata : %s\n",decodedata(test,"00"));
	struct bintree *te = calloc(1,sizeof(struct bintree));
	//te = decode_tree("01011000110101110010101101111"); //representation binaire de l'arbre obtenu en compressant "croco"
	printTree(te);
	te = decode_tree(bin); //representation binaire de l'arbre obtenu en compressant "croco"
	printTree(te);

  char *string = decodedata(test,encode);
  printf("decode : %s\n",string);
	//struct gobelin *g = calloc(1,sizeof(struct gobelin));
	//g = tobinarybis("10101010");
//	printf("choco = %s, %i\n",g->string,g->booleen);

	//printf("res = %s\n",frombinary(g->string,g->booleen));
  char *final = decompress(chapeau->cabane->string,chapeau->cabane->booleen,chapeau->fut->string,chapeau->fut->booleen);
printf("decompress : %s\n",final);
float tx = (float)(strlen(chapeau->cabane->string)/7 + strlen(chapeau->fut->string)/7) / (float)strlen(argv[1]);
printf("tx = %f \n",tx);
printf("Taux de compression : %.2f / %.2f = %.2f%%\n",(float)(strlen(chapeau->cabane->string)/7 + strlen(chapeau->fut->string)/7),(float)strlen(argv[1]),(float)100-(tx*100));

/*FILE *f;
f = fopen("res.tree","w");
fprintf(f,"%i%s",chapeau->fut->booleen,chapeau->fut->string);
fclose(f);
FILE *f2;
f2 = fopen("res.data","w");
fprintf(f2,"%i%s",chapeau->cabane->booleen,chapeau->cabane->string);
fclose(f2);*/
//whole_comp(argv[1],"testo");
whole_decomp("testo");

//fread(dodo,sizeof(struct mousquetaire),1,f);
//printf("coucou\n");
//int ret;
//char *s = calloc(56,sizeof(char));
//ret = fgetc(f);
//printf("decalage = %i\n",ret-48);
//fscanf(f,"%s",s);
//printf("waited = %s\n",s);
//printf("ftell = %lu\n",(ftell(f)));
//fclose(f2);




}


