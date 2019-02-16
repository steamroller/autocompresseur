#include<stdlib.h>
#include<stdio.h>
#include"lzw.h"



struct dictionary
{
	char *value;
	struct dictionary *next;
	int num;

};


int main(int argc, char *argv[])
{

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
	tty=final(ret,argv[1],1);

	size_t v = 0;
	while(c!=NULL)
	{
		//printf("pipi\n");
		printf("Dic[%zu] = %s, numeric value : %i \n",v,c->value, c->num);
		c = c->next;
		v += 1;
	}
	int n = 0;
	printf("Initial sentence : %s\n",argv[1]);
	printf("Resultat apres compression : %s\n",(final(d,argv[1],n)));
	printf("%i * %i = %i bits\n",nbword(tty),7+(sod(d)/127),nbword(tty)*(7+(sod(d)/127)));
	printf("Resultat apres decompression : %s\n",decompress(tty,try,nbword));
	printf("%i * %i = %i bits\n",strlen(argv[1]),7,7*strlen(argv[1]));
	//printf("nbword = %i\n",nbword(tty));


	/*size_t v = 0;
	while(c!=NULL)
	{
		//printf("pipi\n");
		printf("Dic[%zu] = %s, numeric value : %i \n",v,c->value, c->num);
		c = c->next;
		v += 1;
	}*/
	//printf(recup(d,130));
}
