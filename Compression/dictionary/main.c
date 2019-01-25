#include<stdlib.h>
#include<stdio.h>
#include"lzw.h"



struct dictionary
{
	char *value;
	struct dictionary *next;
	int num;

};



void print_array(int *array, size_t length)
{
	for(size_t i = 0; i < length; i++)
		printf("%i ", array[i]);
	printf("\n");
}

size_t length(char*s)
{
	size_t i = 0;
	while(*s!=0)
	{
		i += 1;
		s += 1;
	}
	return i;
}

int main()
{
	/*char *u = malloc(1*sizeof(char));
	*u = 'f';
	u += 1;
	*u = 'f';
	u-=1;

	//printf("%s\n",u);*/

	char tt[8] = "antoine";
	char ttt[4] = "45";

	
	struct dictionary *tab = build();

	struct dictionary *b = add(ttt,tab);

	struct dictionary *ret = add(tt,b);
	struct dictionary *f = ret;
	size_t i = 0;
	while(ret!=NULL)
	{
		//printf("pipi\n");
		printf("Dic[%zu] = %s, numeric value : %i \n",i,ret->value, ret->num);
		ret = ret->next;
		i += 1;



	}
	while(f != NULL)
	{
		struct dictionary *temp = f;
		f = f->next;
		free(temp->value); 
		free(temp);
	}
	free(tab);

	char un[23] = "je ne suis pas méchant";
	char deux[23] = "je ne suis pas méchant";

	//printf("the len is %zu \n", leng(tt));
	//printf(" are equal : %i \n",are_equal(un,deux));
	//printf("the weight of tt is : %i \n",weight(tt));

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



	/*char *phrase = "Bonjour";
	size_t l = length(phrase);
	int *array = invalues(phrase,l);
	print_array(array,l);*/
}
