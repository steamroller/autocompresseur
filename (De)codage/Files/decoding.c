#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "decoding.h"

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

void list_push_end(struct list *List, char elm)
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
		int z = asprintf(&s, "%s%c", s, l->data);
		if (z == -1)
		{
			errx(1, "Impossible to convert");
		}
	}
	return s;
}

int private_key(int p, int q)
{
//creation of the public key thanks to the two number entered by the user
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

	//creation of the private key thanks to the two number entered by the user 
	int d = 0;
	while (d * e % phiden != 1)
	{
		d++;
	}
	return d;
}

char* decoding(char str[])
{
	int p = 0;
	int q = 0;
	printf("\nEnter the first PRIME number you choose during the ");
	printf("encoding part in order to create your private key :\n");
    scanf("%d", &p);
    if(is_prime_number(p) == 0) 
	{ 
		errx(1, "\nWRONG INPUT\n"); 
	}
	
    printf("Choose the second PRIME number you choose during the ");
	printf("the encoding part in order to create your private key :\n");
    scanf("%d", &q);
    if(is_prime_number(q) == 0||p == q) 
	{ 
		errx(1, "\nWRONG INPUT\n");
	} 
	int n = p*q;
	int d = private_key(p, q);
	
	// Begin of the decoding
	struct list *L = malloc(sizeof(struct list));
	list_init(L);
	long len_str = strlen(str);
	char encr_let[len_str];	
			
	//decode each block
	int i = 0;
	while(i < len_str) 
	{
		memset(encr_let, 0, len_str);
		int j = 0;
		while(str[i] != ',')
		{
			encr_let[j] = str[i];
			i++;
			j++;
		}
		long bloc = atol(encr_let);
		long ascii = expo_modul(bloc, d, n);
		char decod = (char)ascii;
		list_push_end(L, decod);
		i++;
	}
	return list_to_char(L, i);
}

int main()
{
	char msg[100];
    printf("\nEnter the message you want to decode:\n");
    if (fflush(stdin) != 0)
    {
		errx(EXIT_FAILURE, "Impossible because %d", errno);
	}
	scanf("%s", msg);
	
	char* code = decoding(msg);
	printf("Your decoded message is : \n");
	printf("%s", code);
	printf("\n");
	
    return 0;
}
