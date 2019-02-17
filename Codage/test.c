#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
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
 
int main(int argc, char *argv[])
{
    char nom[10];
 
    printf("Quel est votre nom ? ");
    read(nom, 10);
    printf("Ah ! Vous vous appelez donc %s !\n\n", nom);
 
    return 0;
}
