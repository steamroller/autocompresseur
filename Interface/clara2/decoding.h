#ifndef DECODING_H
#define DECODING_H

//Check if a number is a prime number
int is_prime_number(int n);

//Find the Highest Common Factor of a number
int PGCD(int a, int b);

//Count the number of digit in an integer
unsigned char digit_count(int n);

// Calculate pow(a,b)mod[n]
long expo_modul(long a, long b, long n);

//Create the private key
int private_key(int p, int q);

//Convert the char c in its base 50
int conv10(char c);

//Calculate a power b
int power(int a, int b);

//Converts the string s into the base 50
long base_10(char *s);

//Allows to decode the string enter in parameter
char* decoding(char str[]);

struct list
{
	struct list *next;
	char data;
};

// Initialize the sentinel of an emtpy list
void list_init(struct list *List);

// Insert an element at the end of the list
void list_push_end(struct list *list, char elm);

void list_free(struct list *l);

void list_push_endo(struct list *list, int elm);

//Allows to convert a list of char into a char*
char* list_to_char(struct list *l, int size);

#endif
