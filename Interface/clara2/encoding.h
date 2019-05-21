#ifndef ENCRYPTION_H
#define ENCRYPTION_H

//Allows to get what the user writes on the terminal back.
int reado(char *chain, int len);

// Transform an int into a char
char* my_itoa(int nb, int size);

//Check if a number is a prime number
int is_prime_number(int n);

//Find the Highest Common Factor of a number
int PGCD(int a, int b);

// Calculate pow(a,b)mod[n]
long expo_modul(long a, long b, long n);

// Encrypte a text
char* encryption(char string[]);

// Allows to create the public key
int public_key(int p, int q);


struct list1
{
	struct list1 *next;
	int data;
};

// Allows to convert each bloc into the base 50
char* to_base_50(int n);

// Initialize the sentinel of an emtpy list
void list_init1(struct list1 *List);

// Insert an element at the end of the list
void list_push_endo1(struct list1 *list, int elm);


// Transform a list of element into a char*
//~ char* list_to_char(struct list *l, int size);

// Allows to print a list on the therminal
void print_list(struct list1 *l);

#endif
