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

// Initialize the sentinel of an emtpy list
void list_init(struct list *List)
{
	List->data = 0;
	List->next = NULL;
}

// Insert an element at the end of the list
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

//Allows to convert a list of char into a char*
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

//Create the private key
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

//Convert the char c in its base 50
int conv10(char c)
{
	int r;
	if(c == '0')
	{
		r = 0;
	}
	if(c == '1')
	{
		r = 1;
	}
	if(c == '2')
	{
		r = 2;
	}
	if(c == '3')
	{
		r = 3;
	}
	if(c == '4')
	{
		r = 4;
	}
	if(c == '5')
	{
		r = 5;
	}
	if(c == '6')
	{
		r = 6;
	}
	if(c == '7')
	{
		r = 7;
	}
	if(c == '8')
	{
		r = 8;
	}
	if(c == '9')
	{
		r = 9;
	}
	if(c == 'a')
	{
		r = 10;
	}
	if(c == 'b')
	{
		r = 11;
	}
	if(c == 'c')
	{
		r = 12;
	}
	if(c == 'd')
	{
		r = 13;
	}
	if(c == 'e')
	{
		r = 14;
	}
	if(c == 'f')
	{
		r = 15;
	}
	if(c == 'g')
	{
		r = 16;
	}
	if(c == 'h')
	{
		r = 17;
	}
	if(c == 'i')
	{
		r = 18;
	}
	if(c == 'j')
	{
		r = 19;
	}
	if(c == 'k')
	{
		r = 20;
	}
	if(c == 'l')
	{
		r = 21;
	}
	if(c == 'm')
	{
		r = 22;
	}
	if(c == 'n')
	{
		r = 23;
	}
	if(c == 'o')
	{
		r = 24;
	}
	if(c == 'p')
	{
		r = 25;
	}
	if(c == 'q')
	{
		r = 26;
	}
	if(c == 'r')
	{
		r = 27;
	}
	if(c == 's')
	{
		r = 28;
	}
	if(c == 't')
	{
		r = 29;
	}
	if(c == 'u')
	{
		r = 30;
	}
	if(c == 'v')
	{
		r = 31;
	}
	if(c == 'w')
	{
		r = 32;
	}
	if(c == 'x')
	{
		r = 33;
	}
	if(c == 'y')
	{
		r = 34;
	}
	if(c == 'z')
	{
		r = 35;
	}
	if(c == 'A')
	{
		r = 36;
	}
	if(c == 'B')
	{
		r = 37;
	}
	if(c == 'C')
	{
		r = 38;
	}
	if(c == 'D')
	{
		r = 39;
	}
	if(c == 'E')
	{
		r = 40;
	}
	if(c == 'F')
	{
		r = 41;
	}
	if(c == 'G')
	{
		r = 42;
	}
	if(c == 'H')
	{
		r = 43;
	}
	if(c == 'I')
	{
		r = 44;
	}
	if(c == 'J')
	{
		r = 45;
	}
	if(c == 'K')
	{
		r = 46;
	}
	if(c == 'L')
	{
		r = 47;
	}
	if(c == 'M')
	{
		r = 48;
	}
	if(c == 'N')
	{
		r = 49;
	}
	if(c == 'O')
	{
		r = 50;
	}
	return r;
}

//Calculate a power b
int power(int a, int b)
{
	if (b == 0)
	{
		return 1;
	}
	else
	{
		return a*power(a, b-1);
	}
}

//Converts the string s into the base 50
long base_10(char *s)
{
	int len = strlen(s);
	long sum = 0;
	int r = 0;
	int j = 0;
	for(int i = len - 1; i >= 0; i--)
	{
		r = conv10(s[i]);
		sum += r * power(50,j);
		j++;
	}
	return sum;
}


char* decoding(char str[])
{	
	int p = 191;
	int q = 229;
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
			//~ printf("\nencr_let[%d] = %c\n", j, str[i]);
			i++;
			j++;
		}
		//~ printf("sortie de boucle\n");
		//~ printf("encr_let = %s\n", encr_let);
		
		long bloc = base_10(encr_let);
		//~ printf("bloc = %ld\n", bloc);
		long ascii = expo_modul(bloc, d, n);
		char decod = (char)ascii;
		list_push_end(L, decod);
		i++;
	}
	char* code = list_to_char(L, i);
	printf("Your decoded message is : \n");
	printf("%s", code);
	printf("\n");
	return code;
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
	
	decoding(msg);
	
    return 0;
}
