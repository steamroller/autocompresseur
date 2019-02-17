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

//Count the number of digit in an integer
unsigned char digit_count(int n)
{
	unsigned char c=0;
	if (n==0)
	{
		c=1;
	}
	while (n>0)
	{
		n=n/10;
		c=c+1;
	}
	return c;
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

void print_list(struct list *l)
{
	l = l->next;
	for(int i = 0; l != NULL; l = l->next, i++)
	{
		printf("%c", l->data);
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

void decoding(char str[], int p, int q)
{
	//creation of the public key thanks to the two number entered by the user
	int n = p*q;
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
	printf("Your decoded message is: ");
	print_list(L);
	printf("\n");
	list_free(L);
}

int main()
{
	int p = 0;
	int q = 0;
	char msg[100];
	
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
    
    printf("Enter the message you want to decode:\n");
    if (fflush(stdin) != 0)
    {
		errx(EXIT_FAILURE, "Impossible because %d", errno);
	}
	scanf("%s", msg);
	
    decoding(msg, p, q);
    return 0;
}
