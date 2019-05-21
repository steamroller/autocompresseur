#define _GNU_SOURCE

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include "encryption.h"
#include "decoding.h"

//Allows to get what the user writes on the terminal back.
int reado(char *chain, int len)
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

// Transform an int into a char
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
int is_prime_number1(int n)
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
int PGCD1(int a, int b)
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
long expo_modul1(long a, long b, long n)
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

// Initialize the sentinel of an emtpy list
void list_init1(struct list1 *List)
{
	List->data = 0;
	List->next = NULL;
}
// Insert an element at the end of the list
void list_push_endo1(struct list1 *List, char* elm)
{
	struct list1 *new = malloc(sizeof(struct list1));
	new->data = elm;
	new->next = NULL;
	
	
	struct list1 *temp = List;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new;
	
}

// Transform a list of element into a char*
char* list_to_char1(struct list1 *l, int size)
{
	char* s = calloc(size, sizeof(char));
	l = l->next;
	int i;
	for (i = 0; l != NULL; l = l->next, i++)
	{
		int z = asprintf(&s, "%s%s%c", s, l->data, ',');
		
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
	if (is_prime_number1(p) == 0 || is_prime_number1(q) == 0)
	{
		errx(1, "Number not prime");
	}
	while (PGCD1(phiden, e) != 1)
	{
		e++;
	}

	return e;
}

// Allows to convert each bloc into the base 50
char conv50(int n)
{
	char c;
	if (n == 0)
	{
		c = (char)'0';		
	}
	if (n == 1)
	{
		c = (char)'1';		
	}
	if (n == 2)
	{
		c = (char)'2';		
	}
	if (n == 3)
	{
		c = (char)'3';		
	}
	if (n == 4)
	{
		c = (char)'4';		
	}
	if (n == 5)
	{
		c = (char)'5';		
	}
	if (n == 6)
	{
		c = (char)'6';		
	}
	if (n == 7)
	{
		c = (char)'7';		
	}
	if (n == 8)
	{
		c = (char)'8';		
	}
	if (n == 9)
	{
		c = (char)'9';		
	}
	if (n == 10)
	{
		c = (char)'a';		
	}
	if (n == 11)
	{
		c = (char)'b';		
	}
	if (n == 12)
	{
		c = (char)'c';		
	}
	if (n == 13)
	{
		c = (char)'d';		
	}
	if (n == 14)
	{
		c = (char)'e';		
	}
	if (n == 15)
	{
		c = (char)'f';		
	}
	if (n == 16)
	{
		c = (char)'g';
	}
	if (n == 17)
	{
		c = (char)'h';
	}
	if (n == 18)
	{
		c = (char)'i';
	}
	if (n == 19)
	{
		c = (char)'j';
	}
	if (n == 20)
	{
		c = (char)'k';
	}
	if (n == 21)
	{
		c = (char)'l';
	}
	if (n == 22)
	{
		c = (char)'m';
	}
	if (n == 23)
	{
		c = (char)'n';
	}
	if (n == 24)
	{
		c = (char)'o';
	}
	if (n == 25)
	{
		c = (char)'p';
	}
	if (n == 26)
	{
		c = (char)'q';
	}
	if (n == 27)
	{
		c = (char)'r';
	}
	if (n == 28)
	{
		c = (char)'s';
	}
	if (n == 29)
	{
		c = (char)'t';
	}
	if (n == 30)
	{
		c = (char)'u';
	}
	if (n == 31)
	{
		c = (char)'v';
	}
	if (n == 32)
	{
		c = (char)'w';
	}
	if (n == 33)
	{
		c = (char)'x';
	}
	if (n == 34)
	{
		c = (char)'y';
	}
	if (n == 35)
	{
		c = (char)'z';
	}
	if (n == 36)
	{
		c = (char)'A';
	}
	if (n == 37)
	{
		c = (char)'B';
	}
	if (n == 38)
	{
		c = (char)'C';
	}
	if (n == 39)
	{
		c = (char)'D';
	}
	if (n == 40)
	{
		c = (char)'E';
	}
	if (n == 41)
	{
		c = (char)'F';
	}
	if (n == 42)
	{
		c = (char)'G';
	}
	if (n == 43)
	{
		c = (char)'H';
	}
	if (n == 44)
	{
		c = (char)'I';
	}
	if (n == 45)
	{
		c = (char)'J';
	}
	if (n == 46)
	{
		c = (char)'K';
	}
	if (n == 47)
	{
		c = (char)'L';
	}
	if (n == 48)
	{
		c = (char)'M';
	}
	if (n == 49)
	{
		c = (char)'N';
	}
	if (n == 50)
	{
		c = (char)'O';
	}
	return c;
}

char *to_base_50(int n)
{
	char *s = calloc(10, sizeof(char));
	int q = n;
	int r = n;
	while (q != 0)
	{
		q = n/50;
		r = n%50;
		char c = conv50(r);
		//~ printf("c = %c\n", c);
		asprintf(&s, "%c%s", c, s);
		//~ printf("s = %s\n", s);
		n = q;
	}
	return s;
}

char* encryption(char string[])
{
	int p = 191;
	int q = 229;
	int n = p*q;
	int e = public_key(p, q);


// Begin of the encryption
	struct list1 *L = malloc(sizeof(struct list1));
	list_init1(L);
	int ascii;
	int encr_let;
	int length = strlen(string);
	int i = 0;
	while(i < length)
	{
		ascii = (int)string[i];
		encr_let = expo_modul1(ascii, e, n);
		char *tmp = to_base_50(encr_let);
		list_push_endo1(L, tmp);
		i++;
	}
	char* code = list_to_char1(L, length);
	printf("\nYour encoded message is : \n%s", code);
	printf("\n");
 
	return code;
}

//~ int main()
//~ {
	//~ char msg[100];
	//~ printf("\nEnter the message you want to encrypte:\n");
    //~ reado(msg, 100);
    
    //~ encryption(msg);
    //~ return 0;
//~ }

