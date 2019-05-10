#include<stdio.h>
#include<stdlib.h>
#include<string.h>






char *to_ascii(char *nul)
{
	char *res = calloc(1,strlen(nul)*sizeof(char));
	char *bis = res;
	int taille = strlen(nul);
	for(int i = 0 ; i < taille ; i++)
	{
		if (nul[i] == -30)
		{
			*res = (char)39;
			i+=2;
			res += 1;
		}
		else
		{
			*res = nul[i];
			res += 1;
		}
	}
	return bis;
}




/*int main()
{
	char test[45656] = "Queen Mary She’s my friend Yes, I believe I’ll go see her again Nobody has to guess That Baby can’t be blessed Till she sees finally that she’s like all the rest With her fog, her amphetamine and her pearls She takes just like a woman, yes She makes love just like a woman, yes, she does And she aches just like a woman But she breaks just like a little girl";
	printf("res = %s\n",to_ascii(test));
}*/
