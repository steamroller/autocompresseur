#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include "encryption.h"

int my_read(char *chain, int len)
{
	char *entrypos = NULL;
	if (fgets(chain, len, stdin) != NULL)
	{
		entrypos = strchr(chain, '\n');
		if (entrypos != NULL)
		{
			*entrypos = '\0';
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

char* my_itoa(int nb)
{
	int a = nb;
	char* final = calloc(2, sizeof(char));
	while(a != 0)
	{
		int last = a%10;
		asprintf(&final, "%c%s", (char)last + 48, final);
		a = a/10;
	}
	return final;
}

//Check if a number is a prime number

int is_prime_number(int n)
{
	for (int i = 2; i < n; i++)
	{
		if (n%i == 0)
		{
			return 0;
		}
	}
	return 1;
}

//Find the Highest Common Factor of a number

int PGCD(int a, int b)
{
	int r;
	while(b != 0)
	{
		r = a%b;
		a = b;
		b = r;
	}
	return a;
}


// Calculate pow(a,b)mod[n]
long expo_modul(long a, long b, long n)
{
	long r;
	for (r = 1; b > 0; b = b/2)
	{
		if (b%2 != 0)
		{
			r = (r * a) % n;
		}
		a = (a * a) % n;
	}
	return r;
}


void list_init(struct list *List)
{
	List->data = 0;
	List->next = NULL;
}

void list_push_end(struct list *List, int elm)
{
	struct list *new = malloc(sizeof(struct list));
	new->data = elm;
	new->next = NULL;
	
	struct list *temp = List;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new;
	
}

char* list_to_char(struct list *l, int size)
{
	char* s = calloc(size, sizeof(char));
	l = l->next;
	int i;
	for (i = 0; l != NULL; l = l->next, i++)
	{
		int z = asprintf(&s, "%s%s%c", s, my_itoa(l->data), ',');
		if (z == -1)
		{
			errx(1, "Impossible to convert");
		}
	}
	return s;
}

int public_key(int p, int q)
{
	//creation of the public key
	int e = 2;
	int phiden = (p-1)*(q-1);
	if (is_prime_number(p) == 0 || is_prime_number(q) == 0)
	{
		errx(1, "Number not prime");
	}
	while (PGCD(phiden, e) != 1)
	{
		e++;
	}

	return e;
}

char* encryption(char string[])
{
	printf("\nHere is a list of prime number : \n101,103,107,109,113,127,");
	printf("131,139,149,151,157,163,167,173,179,181,191,193,197,199,211,");
	printf("223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,");
	printf("307,311,313,317,331,337,347,349,353,359,367,373,379,383,389\n");
	
	int p = 0;
	int q = 0;
	printf("\nChoose the first PRIME number to create your private key :\n");
    scanf("%d", &p);
    if(is_prime_number(p) == 0) 
	{ 
		errx(1, "\nWRONG INPUT\n"); 
	}
	
    printf("Choose the second PRIME number to create your private key :\n");
    scanf("%d", &q);
    if(is_prime_number(q) == 0||p == q) 
	{ 
		errx(1, "\nWRONG INPUT\n");
	}

	int n = p*q;
	int e = public_key(p, q);


// Begin of the encryption
	struct list *L = malloc(sizeof(struct list));
	list_init(L);
	int ascii;
	int encr_let;
	int length = strlen(string);
	int i = 0;
	while(i < length)
	{
		ascii = (int)string[i];
		encr_let = expo_modul(ascii, e, n);
		list_push_end(L, encr_let);
		i++;
	}
	char* code = list_to_char(L, length);
	printf("\nYour encoded message is : \n%s", code);
	printf("\n");
 
	return code;
}

//~ int main()
//~ {
	//~ char msg[100];
	//~ printf("\nEnter the message you want to encrypte:\n");
    //~ my_read(msg, 100);
    
    //~ encryption(msg);
    //~ return 0;
//~ }

