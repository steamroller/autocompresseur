#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"lzw.h"

struct dictionary
{
	char *value;
	struct dictionary *next;
	int num;
};

int nbword(char *s)
{
	size_t p = strlen(s);
	size_t i = 0;
	int cpt =  0;
	while(i < p)
	{
		if(s[i]=='<')
			cpt += 1;
		i+=1;
	}
	return cpt;
}


char *convert(int q)
{
	char *t = calloc(1,sizeof(char));

	if(digit_count(q)==1)
	{
		int a = asprintf(&t,"%c%c%i",'0','0',q);
		if (a == -1)
			printf("error");
		return t;
	}
	if(digit_count(q)==2)
	{
		int a = asprintf(&t,"%c%i",'0',q);
		if (a == -1)
			printf("error");
			
		return t;
	}
	else
	{
		int a = asprintf(&t,"%i",q);
		if (a == -1)
			printf("error");
	}
		
	return t;
}


int digit_count(int nombre)
{
	if(nombre == 0)
		return 1;
	else
	{
		int res = 0;
		while(nombre > 0)
		{
			nombre = nombre/10;
			res += 1;
		}
		return res;
	}
}






void substring(char *s)
{
	size_t len = strlen(s);
	s[len-1] = 0;
}


//Function that tells if two strings are equals or not
int are_equal(char* s1, char* s2)
{
	return strcmp(s1,s2);
}

//Function returning the ascii's weight of a string
int weight(char *s)
{
	size_t i = strlen(s);
	int u = 0;
	for(size_t p = 0; p < i; p++)
	{
		u += (int)(s[p]);
	}
	return u;
}

int is_belonging(struct dictionary *dico, char *s)
{
	//printf("pas d'abandon\n");
	int w = weight(s);
	//struct dictionary *f = dico;
	int index = 0;
	while(dico->next != NULL)
	{
		if(dico->num == w && strcmp(dico->value,s)==0)
		{
			return index;
		}
		index += 1;
		dico = dico->next;
	}
	if(strcmp(dico->value,s)==0)
	{
		return index;
	}
	return -1;
}






//Function that initializes a dictionary only with the ascii table(128)
struct dictionary *build()
{
	struct dictionary *dico = calloc(1,sizeof(struct dictionary));
	struct dictionary *un = dico;;
	for(size_t i = 0; i<128; i++)
	{
		if(dico == NULL)
			printf("capi\n");
		char *str = malloc(2*sizeof(char));
		str[1] = 0;
		*str = (char)i;
		(dico->value) = (char*)str;
		dico -> num = (int)(weight(str));
		if(i<127)
		{
			dico->next = calloc(1,sizeof(struct dictionary));
			dico = dico->next;
		}
	}
	dico->next = NULL;
	return un;

}

//Fuction that add a new sequence in the dictionary
struct dictionary *add(char* to_add,struct dictionary *dico)
{

	struct dictionary *final = dico;
	//size_t l = strlen(to_add);
	//int w = weight(to_add);
	//printf("to_add's weight = %i\n",w);
	//printf("to_add = %s \n",(to_add));
	struct dictionary *new = malloc(1*sizeof(struct dictionary));
	/*char *str = malloc(2*sizeof(char));
	for(size_t y = 0;y < l; y++)
	{
		*str = *to_add;
		str += 1;
		to_add += 1;
	}
	str-= l;
	new->value = (char*)str;*/
	new->value = to_add;
	while(dico->next != NULL)
	{
		dico = dico->next;
	}
	dico->next = new;
	//new->num = (int)(weight(str));
	new->num = (int)(weight(to_add));
	new->next = NULL;
	return final;
}



//======================================================================================================================================================================
																																										
																																										
//																COMPRESSION																								
																																										
																																										
//======================================================================================================================================================================

struct arya
{
	int nbww;
	char *chaine;
};

struct arya *max_word(struct dictionary *dico, char*s,char *str,int nbw,int *tab)
{
	if(*s == 0)
	{
		nbw = nbw;
		tab-=nbw;
		//return str;
		struct arya *r = calloc(1,sizeof(struct arya));
		r->nbww = nbw;
		r->chaine = str;
		return r;

	}
	if(strlen(s) == 1)
	{
		*tab = is_belonging(dico,s);
		//printf("*tab = %i\n",*tab);
		int a = asprintf(&str,"%s<%d>",str,is_belonging(dico,s));
		if (a == -1)
			printf("error");
		nbw = nbw;
		//*(tab+1) = -1;
		tab -= nbw;
		//printf("*f = %i\n",*tab);
		//printf("nbw = %i\n",nbw);
		struct arya *r = calloc(1,sizeof(struct arya));
		r->nbww = nbw;
		r->chaine = str;
		return r;
	}
	else
	{
		struct dictionary *f = dico;
		int size = 1;
		char *toreturn = calloc(1,1000*sizeof(char));
		*toreturn = *s;
		toreturn += 1;
		s += 1;
		char *temp = toreturn-size;
		while(*s != 0 && is_belonging(dico,temp)!= -1)
		{
			*toreturn = *s;
			s+=1;
			toreturn += 1;
			size += 1;
			temp = toreturn - size;
		}

		//printf("par ici : %s\n",temp);
		int a;
		if((a = is_belonging(dico,temp))!=-1)
		{
			//printf("pas de chance = %i\n",a);
			*tab = a;
			//printf("*tab = %i\n",*tab);
			int b = asprintf(&str,"%s<%s>",str,convert(a));
			if (b == -1)
				printf("error");
			dico = f;
			nbw = nbw;
			//*(tab+1) = -1;
			tab -= nbw;
			//printf("*f = %i\n",*tab);
			//printf("nbw = %i\n",nbw);

			//return str;
			struct arya *r = calloc(1,sizeof(struct arya));
			r->nbww = nbw;
			r->chaine = str;
			return r;

		}
		

		
		//substring(temp);
		//printf("we add = %s\n",temp);
		//char *chiffre = (substring(temp,1));
		char *chiffre = temp;
		char last = chiffre[strlen(chiffre)-1];
		substring(chiffre);
		char *chiffree = calloc(1,1000*sizeof(char));
		//printf(" = %s\n",chiffre);
		for(size_t i = 0; i<strlen(chiffre);i++)
		{
			chiffree[i]=chiffre[i];
		}
		temp[strlen(chiffre)]= last;
		temp[strlen(chiffre)] = 0;
		//printf("we add = %s\n",temp);
		//printf("we write = %s\n",chiffree);
		int vg  = is_belonging(dico, chiffree);
		//printf("vg = %i\n",vg);
		dico = f;
		dico = add(temp,dico);
		dico = f;
		s -= 1;
		*tab = vg;
		printf("*tab = %i\n",*tab);
		tab += 1;
		int c = asprintf(&str,"%s<%s>",str,convert(vg));
		if (c == -1)
			printf("error");
		return max_word(dico,s,str,nbw+1,tab);
	}
}

/*char *max_word(struct dictionary *dico,char *s,int i, char *str)
{
	if(s[i] == 0)
	{
		return str;
	}
	else
	{
		size_t u = 2;//nb caracteres
		char *tmp = calloc(1,u*sizeof(char));
		tmp[0]=s[i];
		while(s->next != NULL && is_blonging(dico,tmp)!=-1)
		{
			i+=1;
			tmp = realloc(tmp,(u+1)*sizeof(char));
			tmp[i]=s[i];
		}
	}
}*/


char *final(struct dictionary *dico, char *s,int *tab,int *nbw)
{
	//printf("taille = %i\n",sod(dico));
	char *v = calloc(1,8000*sizeof(char));
	int a = 1;
	struct arya *ret = max_word(dico,s,v,a,tab);
	//printf("a = %i\n",ret->nbww);
	*nbw = ret->nbww;
	return ret->chaine;
}

//======================================================================================================================================================================
																																										
																																										
//																DECOMPRESSION																							
																																										
																																										
//======================================================================================================================================================================


char *recup(struct dictionary *dic, int index)
{
	//printf("index = %i\n",index);
	if(index >= sod(dic))
		printf("tentative de recuperer un valeur superieur à la taille du dico");
	int s = 0;
	//printf("graille\n");
	struct dictionary *f = dic;
	//printf("steak\n");
	while(s != index)
	{
		//printf("fanta");
		dic = dic->next;
		s += 1;
	}
	//printf("germain le mais humain\n");
	//size_t t = strlen(dic->value);
	//printf("t = %li\n",t);
	char *ret = calloc(1,10*sizeof(char));
	//printf("la\n");
	//printf("val = %s\n",dic->value);
	int a = asprintf(&ret,"%s%s",ret,dic->value);
	//printf("back\n");
	if (a == -1)
		printf("error");
	//printf(" si ca s'affiche j'y vais\n");
	dic = f;
	//printf("pcq la c bon \n");
	return ret;
}

int sod(struct dictionary *dico)
{
	int retour = 0;
	while(dico != NULL)
	{
		retour += 1;
		dico = dico->next;
	}
	return retour;
}



char *first(char *s)
{
	//printf("sos");
	size_t taille = strlen(s);
	int i = 0;
	if(*s == '>'&& taille > 1)
		s+= 1;
	if(*s == '<')
		s += 1;
	//printf("ddd");
	char *ret = calloc(1,4*sizeof(char));
	while(s[i]!='>')
	{
		//printf("first = %c \n",*s);
		ret[i] = s[i];
		i += 1;
	}
	return ret;
	
}

char *decompress(char *init,char *dest)
{
	struct dictionary *dico = calloc(1,sizeof(struct dictionary));
	dico = build();
	size_t i = 0;
	size_t tot = strlen(init);
	int index = 0;
	while(i < tot-1)
	{
		//bw += 1;
		int b = 0;
		if(init[i] == '<')
			i += 1;
		size_t s = 0;
		char *temp = calloc(1,10*sizeof(char));

		while(init[i] != '>')
		{
			temp[s] = init[i];
			i += 1;
			s += 1;
		}
		//printf("tmp %i = %s\n",index,temp);
		index += 1;
		int actu = atoi(temp);
		//if(tp < sod(dico))
		if(1)
		{
			//printf("potatoes\n");
			int a = asprintf(&dest,"%s%s",dest,recup(dico,actu));
			if (a == -1)
				printf("error");
			//printf("so?\n");
			char *temporary;
			//printf("init = %s\n",init);
			int next ;
			if (i<tot-4)
				next = atoi(first(init + i + 1));
			else
				next = 5;//CRAEFUL
			//printf("I = %i\n",i);
			//printf("as suposed, tpn = %i\n",next);
			//printf(" i = %i\n",i);
			//printf("actu = %i et next = %i sachant que le dico a %i cases\n",actu,next,sod(dico));

			if(i<tot-1 && next >= sod(dico))
			{
				//printf("c ca hein \n");
				char *casse = calloc(1,6*sizeof(char));
				a = asprintf(&casse,"%s%c",recup(dico,actu),recup(dico,actu)[0]);
				if (a == -1)
					printf("error");
				add(casse,dico);
				b = 1;
				//printf("b = 1\n");
			}


			if(b == 0 && i< tot -1)
			{
				int a = asprintf(&temporary,"%s%c",recup(dico,actu),recup(dico,next)[0]);
				if (a == -1)
					printf("error");
			}
			//printf("added = %s\n",temporary);
			//printf("here\n");
			if(i< tot -1 && b == 0 && is_belonging(dico,temporary)==-1)
			{
				//printf("addedd = %s\n",temporary);
				add(temporary,dico);
			}
			//i += digit_count(tpn);
			//printf("i = %i\n",i);
			//free(temp);
			i += 2;
			//printf(" ii = %i\n",i);
			//printf("result = %s\n",dest);
			//printf("bw = %i\n",bw);
		}

		
		//printf("bw = %i\n",bw);
		

	}
	//printf("bw = %i\n",bw);
	return dest;



}

char *inch(int *tab,char *dest)
{
	//printf("probably memory if not here\n");
	int *bis = NULL;
	bis = tab;
	int *tri = tab;
	/*for(int o = 0 ; o < 10 ;o++)
	{
		printf("crocodule = %i\n",*tab);
		tab += 1;
	}*/
	//printf("inchishere\n");
	//struct dictionary *dico = build();
	int brico = 0;
	while(*tri != -1)
	{
		//printf("u = %i\n",*tri);
		tri += 1;
		brico += 1;
	}
	tri -= brico;
	struct dictionary *dico = build();
	struct dictionary *last = dico;

	//printf("ehe\n");
	int si = 128;
	char *prev = calloc(1,15*sizeof(char));
	//printf("ehaeho\n");
	char *too = calloc(1,15*sizeof(char));
	/*if(prev == NULL || too == NULL)
		printf("dead\n");*/
	//printf("eho\n");
	int test = 0;
	//while(*bis != -1)
	while(test < brico)
	{
		test += 1;
		/*for(int u = 0 ; u < 10 ;u++)
		{
			printf("u = %i\n",*tri);
			tri += 1;
		}
		tri -= 10;*/
		//printf("dest = %s\n",dest);
		//printf("bis = %i\n",*bis);
		//printf("bis+1 = %i\n",*(bis+1));
		if(*bis < si)
		{
			//printf("va dej\n");
			int res = asprintf(&dest,"%s%s",dest, recup(dico, *bis));
			//printf("dest = %s\n",dest);
			//printf("masi wtfff\n");
			if(res == -1)
				printf("preob\n");
			too = "";
			int y = asprintf(&too, "%s%s%c",too,prev,(recup(dico,*bis))[0]);
			if(y == -1)
				printf("preob\n");
		//	printf("porte\n");
			if(is_belonging(dico,too)==-1)
			{
				//printf("choco\n");
				add(too,dico);
				//printf("too = %s\n",too);
				si += 1;
			}
			//printf("pronblaime\n");
			prev = recup(dico,*bis);
			//printf("chealsez\n");
		}
		else
		{
			//printf("even that\n");
			too = "";
			int j = asprintf(&dest,"%s%s%c",dest,prev,prev[0]);
			int k = asprintf(&too,"%s%s%c",too,prev,prev[0]);
			if(k == -1 || j == -1)
				printf("probb with asprintf\n");
			add(too,dico);
			prev =too;
			si += 1;
		}
		bis = bis + 1;
	}
	/*int x = 0;
	for(int m = 0 ; m < 169 ; m++)
	{
		printf("dico[%i] = %s\n",m,last->value);
		last = last->next;
	}*/
	(void)last;

	return dest;
}
