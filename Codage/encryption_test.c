#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "encryption.h"

int read(char *chain, int len)
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

void print_list(struct list *l)
{
	l = l->next;
	for(int i = 0; l != NULL; l = l->next, i++)
	{
		printf("%d", l->data);
		printf(",");
	}
}

void list_free(struct list *l)
{
	if (l->next)
		list_free(l->next);
	// Attention il ne faudra pas free la sentinelle
	l->next = NULL;
	free(l);
}

void encryption(char string[], int p, int q)
{
//creation of the public key thanks to the two number entered by the user and 
// code a sentence
	int n = 0;
	int e = 0;
	int phiden = 0;
	if (is_prime_number(p) == 0 || is_prime_number(q) == 0)
	{
		errx(1, "Number not prime");
	}
	else
	{
		n = p*q;
		phiden = (p-1)*(q-1);
		
		e = 2;
		while (PGCD(phiden, e) != 1)
		{
			e++;
		}
	}
	printf("\nPublic key: (%d,%d)\n\n", e, n);

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
		printf("string = %c\nascii = %d\ne = %d\nn = %d\n", string[i], ascii, e, n);
		if (ascii > n)
		{
			errx(1, "Numbers are too small, start again");
		}
		printf("lettre cryptée = %d\n\n", encr_let);
		list_push_end(L, encr_let);
		i++;
	}
	printf("Your encoded message is: ");
	print_list(L);
	printf("\n");
	list_free(L);
}

int main()
{
	char msg[100];
	printf("Enter the message you want to encrypte:\n");
    read(msg, 100);
    
	int p = 0;
	int q = 0;
	
    printf("\nChoose the first PRIME number to create your public key :\n");
    scanf("%d", &p);
    if(is_prime_number(p) == 0) 
	{ 
		errx(1, "\nWRONG INPUT\n"); 
	}
	
    printf("Choose the second PRIME number to create your public key :\n");
    scanf("%d", &q);
    if(is_prime_number(q) == 0||p == q) 
	{ 
		errx(1, "\nWRONG INPUT\n");
	} 
    
    if (fflush(stdin) != 0)
    {
		errx(EXIT_FAILURE, "Impossible because %d", errno);
	}
	
    encryption(msg, p, q);
 
    return 0;
}

