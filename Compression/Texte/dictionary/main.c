#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<err.h>
#include"lzw.h"
#include"bitwise.h"
//#include<conio.h>

long size(char *adrr)
{
	FILE *f;
	long size;
	f = fopen(adrr,"rb");
	if(f)
	{
		fseek(f,0,SEEK_END);
		size = ftell(f);
		fclose(f);
		return size;
	}
	return -1;
}

struct double_tab
{
	u_int8_t *keep;
	u_int8_t *res;
};

struct tabint
{
	u_int8_t *tab;
	int nb;
};

void printab(int *tab)
{
	printf("chips\n");
	printf("%i\n",*tab);
	//int taille = sizeof(tab)/sizeof(int);
	//int i = 0;
	while(*tab != -1)
	{
		printf("kcbeoi\n");
		printf("%i\n",*tab);
		tab += 1;
	}
}


int sod(struct dictionary *dico);

//int *tab = calloc(1000,sizeof(int));


struct dictionary
{
	char *value;
	struct dictionary *next;
	int num;

};

int poww(int i)
{
	int acc = 1;
	for(int y = 0; y < i; y++)
	{
		acc *= 2;
	}
	return acc;

}
int nec(int nb)
{
	int i = 8;
	while(poww(i)<nb)
	{
		i += 1;
	}
	return i;

}


int main(int argc, char *argv[])
{
	if(argc != 2)
		errx(1,"2 arguments excpected");

	//char p[9]="chocolat";
	//printf("%i est le poids de chocolat \n",weight(p));
	//substring(p);
	//printf("%s\n",p);
	/*char *u = malloc(1*sizeof(char));
	*u = 'f';
	u += 1;
	*u = 'f';
	u-=1;
	
	//printf("%s\n",u);*/

	//char tt[8] = "an";
	//char ttt[4] = "45";
	//int y = 233;
	//char *s = (char*)y;
	//printf("s = %s \n",s);

	//ICI
	//printf("5 en char donne : %c\n",(char)514);
	struct dictionary *ret = build();
	struct dictionary *c = ret;
	struct dictionary *e = ret;
	struct dictionary *d = build();
	//struct dictionary *d = ret;
	//struct dictionary *c = ret;////LAAA


	//struct dictionary *m = add("ab",ret);
	//struct dictionary *c = add("ba",m);
	/*struct dictionary *b = add(ttt,tab);
	struct dictionary *c = add("chou",b);
	struct dictionary *d = add("cho",c);
	struct dictionary *e = add("anto",d);
	struct dictionary *u = add("antoinette",e);
	struct dictionary *ret = add(tt,u);
	struct dictionary *f = ret;
	struct dictionary *g = ret;*/


	/*size_t i = 0;
	while(b!=NULL)
	{
		//printf("pipi\n");
		printf("Dic[%zu] = %s, numeric value : %i \n",i,b->value, b->num);
		b = b->next;
		i += 1;



	}*/
	/*while(f != NULL)
	{
		struct dictionary *temp = f;
		f = f->next;
		free(temp->value);
		free(temp);
	}
	free(tab);*/

	//char un[22] = "je ne suis pas méchant";
	//char deux[22] = "je ne suis pas méchant";
	//char ptn[15] = "45";
	//printf("an appartient : %i \n",is_belonging(c,"an"));
	//printf("the len is %zu \n", leng(tt));
	//printf(" are equal : %i \n",are_equal(un,deux));
	//printf("the weight of tt is : %i \n",weight(tt));


	//printf("max de 454584589 = %i \n" , max_word(c,"chou de choupichou deux"));
	//printf("Un chasseur sachant chasser doit savoir chasser sans son chien\n");
	//printf("Resultat apres compression : %s\n",(final(d,argv[1])));
	//printf("ab appartient : %i \n",is_belonging(c,"ab"));
	//printf("%zu\n", leng("chou de choupichou deux chou de choupichou deux chou de choupichou deux chou de choupichou deux chou de choupichou deux chou de choupichou deux chou de choupichou deux chou de choupichou deux chou de choupichou deux chou de choupichou deux\n"));
	//printf("antoine appartient ? : %i \n",is_belonging(b,"antoine"));
	//printf("max de 456 = %i \n" , max_word(b,"456"));
	//struct dictionary *test = c;
	//size_t v = 0;
	/*while(c!=NULL)
	{
		//printf("pipi\n");
		printf("Dic[%zu] = %s, numeric value : %i \n",v,c->value, c->num);
		c = c->next;
		v += 1;
	}*/

	//printf("%i\n",strcmp("antoine","an"));
	//printf("en pos 129, il y a : %s\n",recup(test, 129));
	//printf("sizeofdico = %i\n",sod(test));
	//printf("en pos 147, il y a %s%s \n",recup(c,147),"ha\n");
	//printf("eho");
	
	
	//printf("%zu \n",leng(u));
	/*char* str = malloc(3*sizeof(char));
	*str = 'f';
	str+=1;
	*str = 'u';
	str+=1;
	*str = 'k';
	str -=2 ;
	printf("%s \n",(char*)str);*/

	/*for(size_t i = 0;i < 128; i++)
	{
		char *str = malloc(1*sizeof(char));
		*str = (char)i;
		printf("%s \n",str);

	}*/
	//*n = NULL;
	//n =(int *)calloc(1,100*sizeof(int));

	//printf("wtf");
	//printf("<119><104><111><032><097><114><101><032><121><111><117>\n");
	//char t[1250] ="<101><104><111><128><111>\n";
	
	char *try = calloc(1,200*sizeof(char));
	//printf("crochet = %s\n",first(t));
	//printf("decomp = %s\n",decompress(t,try));
	/*char *phrase = "Bonjour";
	size_t l = length(phrase);
	int *array = invalues(phrase,l);
	print_array(array,l);*/
	char *tty = calloc(1,888*sizeof(char));
	int *tab2 = calloc(1000,sizeof(int));
	int *balec = malloc(2*sizeof(int));
	tty=final(ret,argv[1],tab2,balec);
	//printf("balec = %i\n",*balec);
	//printf("tty : %s\n",tty);
	printf("\n");
	size_t v = 0;
	while(c!=NULL)
	{
		//printf("pipi\n");
		printf("Dic[%zu] = %s\n",v,c->value);// numeric value : %i \n",v,c->value, c->num);
		c = c->next;
		v += 1;
	}
	//int n = 0;
	//int *tab = calloc(1,1000*sizeof(int));
	int *n = calloc(1,1000*sizeof(int));
	printf("\nPhrase initiale : %s\n\n",argv[1]);
	printf("Nombre de caracteres : %li\n",strlen(argv[1]));

	printf("Resultat apres compression : %s -----> ",tty);//(final(d,argv[1],n,balec)));
	int saude = sod(d);
	//printf("saud = %i\n",saude);
	int saud = sod(e);
	int pr = *balec*nec(saud);
	//printf("pr = %i\n",pr);
	//printab(n);
	printf("%i * %i = %i bits\n\n",*balec,nec(saud),pr);
	/*printf("ce tab : %i\n",*n);
	n += 1;
	printf("ce tab : %i\n",*n);*/
	//printab(n);
	
	int which = -1;
	char *rep;
	if(saud < 256)
	{
		struct double_tab *prisoner = build_huit(tab2,*balec);
		(void)prisoner;
		which = 8;
		//printf("on est sur 8 bits\n");
		rep = recup8("test.bin","testb.bin");
	}
	else if(saud < 512)
	{
		struct double_tab *prisoner = build_neuf(tab2,*balec);
		(void)prisoner;
		which = 9;
		//printf("on est sur 9 bits\n");
		rep = recup9("test.bin","testb.bin");
	}
	else if(saud < 1023)
	{
		struct double_tab *prisoner = build_dix(tab2,*balec);
		(void)prisoner;
		which = 10;
		//printf("on est sur 10 bits\n");
		rep = recup10("test.bin","testb.bin");
	}
	else if(saud < 2048)
	{
		struct double_tab *prisoner = build_onze(tab2,*balec);
		(void)prisoner;
		which = 11;
		//printf("on est sur 11 bits\n");
		rep = recup11("test.bin","testb.bin");
	}
	else 
	{
		struct double_tab *prisoner = build_douze(tab2,*balec);
		(void)prisoner;
		which = 12;
		printf("on est sur 12 bits\n");
		rep = recup12("test.bin","testb.bin");
	}
	printf("on travail sur %i bits\n",which);

	long somme = size("test.bin")+size("testb.bin");
	printf("LA TAILLE DU FICHIER TEST EST DE : %li\n",size("test.bin"));
	printf("LA TAILLE DU FICHIER TESTB EST DE : %li\n",size("testb.bin"));
	printf("La somme totale de l'enregistrement est de : %li octets\n",size("test.bin")+size("testb.bin"));

	//char *rep = recup9("test.bin","testb.bin");




	
	printf("Resultat apres decompression : %s -----> ",decompress(rep,try));
	int apr = strlen(argv[1]);
	printf("%li * %i = %i octets\n\n",strlen(argv[1]),8,apr);
	//printf("nbword = %i\n",nbword(tty));
	printf("Taux de compression : %.2f%%\n\n",100 - (double)somme/(double)apr*100);

	


	/*size_t v = 0;
	while(c!=NULL)
	{
		//printf("pipi\n");
		printf("Dic[%zu] = %s, numeric value : %i \n",v,c->value, c->num);
		c = c->next;
		v += 1;
	}*/
	//printf(recup(d,130));
	(void)saude;
	(void)n;
}
