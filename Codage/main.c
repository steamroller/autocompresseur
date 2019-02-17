#include "decoding_v2.c"

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
