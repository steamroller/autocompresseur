#include<stdlib.h>
#include<stdio.h>

struct dictionary
{
	char *value;
	struct dictionary *next;
	int num;
};

//Function that return the length of a string
size_t leng(char *s)
{
	size_t i = 0;
	while (*s != 0)
	{
		i+=1;
		s+=1;
	}
	return i;
}


//Function that tells if two strings are equals or not
int are_equal(char* s1, char* s2)
{
	size_t i = leng(s1);
	size_t y = leng(s2);
	if(i != y)
		return 0;
	else
	{
		size_t u = 0;
		while(u < i && *s1 == *s2)
		{
			s1 += 1;
			s2 += 1;
			u += 1;
		}
		return *s1 == *s2;
	}
}

//Function returning the ascii's weight of a string
int weight(char *s)
{
	size_t i = leng(s);
	size_t u = 0;
	int accu = 0;
	while(u < i)
	{
		//printf("%c \n" ,*s);
		accu += (*s);
		s += 1;
		u += 1;
	}
	return accu;
}



//Function that initializes a dictionary only with the ascii table(128)
struct dictionary *build()
{
	struct dictionary *dico = calloc(1,sizeof(struct dictionary));
	struct dictionary *un = dico;;
	for(size_t i = 0; i<128; i++)
	{
		if(dico == NULL)
			printf("capi\n");
		char *str = malloc(1*sizeof(char));
		*str = (char)i;
		(dico->value) = (char*)str;
		dico -> num = (int)(weight(str));
		if(i<127)
		{
			dico->next = calloc(1,sizeof(struct dictionary));
			dico = dico->next;
		}
	}
	dico->next = NULL;
	return un;

}

//Fuction that add a new sequence in the dictionary
struct dictionary *add(char* to_add,struct dictionary *dico)
{

	struct dictionary *final = dico;
	size_t l = leng(to_add);
	int w = weight(to_add);
	printf("to_add = %s \n",(to_add));
	struct dictionary *new = malloc(1*sizeof(struct dictionary));
	char *str = malloc(2*sizeof(char));
	for(size_t y = 0;y < l; y++)
	{
		*str = *to_add;
		str += 1;
		to_add += 1;
	}
	str-= l;
	new->value = (char*)str;

	printf("chipo\n");

	while(dico->next != NULL && w > dico->num)
	{
		dico = dico->next;
	}
	printf("dddd\n");
	struct dictionary *temp = malloc(1*sizeof(struct dictionary));
	if(dico->next == NULL)
	{
		temp = NULL;
		printf("please \n");
	}
	else
	{
		temp = dico->next;
	}
	printf("chuibo\n");
	if (temp == NULL)
		dico->next = new;
	else
		dico->next = new;
	printf("et la \n");
	new->next = temp;
	new->num = (int)(weight(str));
	return final;
}


