#define _GNU_SOURCE
#include <stdlib.h>
#include<stdio.h>
#include<string.h>


struct double_tab
{
	u_int8_t *keep;
	u_int8_t *res;
};

struct tabint
{
	u_int8_t *tab;
	int nb;
};

u_int8_t mod1(u_int8_t arg)
{
	u_int8_t tot = 0;
	tot += (arg & 16)>>2;
	tot += (arg & 8)>>2;
	tot += (arg & 4)>>2;
	return tot;
}

//============================================================================
//=================================pour ecriture et lecture sur 9bits=========
//============================================================================

struct tabint *neufbits(int *tab,int nbw)
{
	int index = 0;
	u_int8_t *ret = calloc(1,(nbw * sizeof(u_int8_t))/4 + 1);
	u_int8_t *bis = ret;
	int m = 0;
	while(m<nbw)//pour tous les nombres
	{
		while(m<nbw && index < 8)//on occupe tous les bits
		{
			u_int8_t reste = (*tab & (1<<8))>>8;//= 1 ou 0
			//printf("r = %i\n",reste);
			int masque = reste << (7-index);
			//printf("masque = %i\n",masque);
			*ret = *ret | masque;
			tab += 1;
			index += 1;
			m+=1;
		}
		//printf("ret = %i\n",*ret);
		index = 0;
		ret += 1;
	}
	struct tabint *f = calloc(1,sizeof(struct tabint));
	f->tab = bis;
	f->nb = nbw;
	return f;
}

//FONCTION PRINCIPALE
struct double_tab *build_neuf(int *tab,int nbw)
{
	u_int8_t *k = calloc(1,nbw*sizeof(u_int8_t));
	u_int8_t *kk = k;
	int *tabtab =tab;
	u_int8_t *r = calloc(1,(nbw/8 + 1*(nbw%8 != 0))*sizeof(u_int8_t));
	for(int i = 0; i < nbw;i++)
	{
		*k = *tab & 255;
		k += 1;
		tab += 1;
	}
	struct tabint *tmp = neufbits(tabtab,nbw);
	r = tmp->tab;

	struct double_tab *final = calloc(1,sizeof(struct double_tab));
	final->keep = kk;
	final->res = r;

	FILE *f1;
	f1 = fopen("test.bin","wb");
	for(int i = 0; i < nbw;i++)
	{
		fwrite(&(*kk),1,1,f1);
		kk += 1;
	}
	fclose(f1);

	FILE *f2;
	f2 = fopen("testb.bin","wb");
	for(int i = 0; i < nbw/8 + 1*(nbw%8 != 0);i++)
	{
		fwrite(&(*r),1,1,f2);
		r += 1;
	}
	fclose(f2);




	return final;


}

char *recup9(char *datapath,char *datapath2)
{
	int *somme = calloc(1,10000*sizeof(int));
	int *somme2 = somme;
	int *sommef = somme;
	FILE *f =fopen(datapath,"rb");
	int nbit = 0;
	u_int8_t p = 0;
	while(fread(&p,1,1,f)==1)
	{
		//printf("close = %i\n",p);
		*somme = p;
		somme += 1;
		nbit += 1;
	}
	fclose(f);


	FILE *fp =fopen(datapath2,"rb");
	u_int8_t d = 0;
	while(fread(&d,1,1,f)==1)
	{
		//printf("good = %i\n",d);
		for(int i = 0 ; i < 8 ; i++)
		{
			//printf("mask = %i\n",(d & (1<<(7-i)))<<i);
			*somme2 += (d & (1<<(7-i)))<<(i+1);
			somme2 += 1;
		}
	}
	*somme2 = -1;
	fclose(fp);
	char *fou = calloc(1,sizeof(char));
	int o = 0;
	while(o < nbit)//*sommef != -1)
	{
		int a = 0; 
		//printf("sommef = %i\n",*sommef);
		if(*sommef > 99)
			a = asprintf(&fou,"%s<%i>",fou,*sommef);
		//printf("fff = %i\n",*sommef);
		else if(*sommef > 9)
			a = asprintf(&fou,"%s<%c%i>",fou,'0',*sommef);
		else
			a = asprintf(&fou,"%s<%c%c%i>",fou,'0','0',*sommef);
		
		if(a == -1)
			printf("error with asprintf\n");

		sommef += 1;
		o+=1;
	}
	return fou;
}



//============================================================================
//================================Pour ecriture et lecture sur 10bits=========
//============================================================================

struct tabint *dixbits(int *tab,int nbw)
{
	int index = 0;
	u_int8_t *ret = calloc(1,(nbw * sizeof(u_int8_t))/2 + 1);
	u_int8_t *bis = ret;
	int m = 0;
	while(m<nbw)//pour tous les nombres
	{
		while(m<nbw && index < 8)//on occupe tous les bits
		{
			u_int8_t reste = 0b0000;
			if(*tab > 767)//si les deux bits supplementaires sont à 1
			{
				reste = 0b0011;
			}
			else if(*tab >= 512)//si le bit le plus fort est a 1 et le 9 à 0
			{
				reste = 0b0010;
			}
			else if(*tab >= 256)//si le plus fort est a 0 mais le 9 à 1
			{
				reste = 0b0001;
			}
			else//si les deux sont à 0
			{
				reste = 0b0000;
			}

			//u_int8_t reste = (*tab & (1<<8))>>8;//= 1 ou 0
			//printf("tab = %i, r = %i\n",*tab,reste);
			int masque = reste << (6-index);
			//printf("masque = %i\n",masque);
			*ret = *ret | masque;
			tab += 1;
			index += 2;
			m+=1;
		}
		//printf("ret = %i\n",*ret);
		index = 0;
		ret += 1;
	}
	struct tabint *f = calloc(1,sizeof(struct tabint));
	f->tab = bis;
	f->nb = nbw;
	return f;
}


//FONCTION PRINCIPALE
struct double_tab *build_dix(int *tab,int nbw)
{
	u_int8_t *k = calloc(1,nbw*sizeof(u_int8_t));
	u_int8_t *kk = k;
	int *tabtab =tab;
	u_int8_t *r = calloc(1,(nbw/4 + 1*(nbw%8 != 0))*sizeof(u_int8_t));
	for(int i = 0; i < nbw;i++)
	{
		*k = *tab & 255;
		k += 1;
		tab += 1;
	}
	struct tabint *tmp = dixbits(tabtab,nbw);
	r = tmp->tab;

	struct double_tab *final = calloc(1,sizeof(struct double_tab));
	final->keep = kk;
	final->res = r;

	FILE *f1;
	f1 = fopen("test.bin","wb");
	for(int i = 0; i < nbw;i++)
	{
		fwrite(&(*kk),1,1,f1);
		kk += 1;
	}
	fclose(f1);

	FILE *f2;
	f2 = fopen("testb.bin","wb");
	for(int i = 0; i < nbw/4 + 1*(nbw%8 != 0);i++)
	{
		fwrite(&(*r),1,1,f2);
		r += 1;
	}
	fclose(f2);




	return final;


}

char *recup10(char *datapath,char *datapath2)
{
	int *somme = calloc(1,10000*sizeof(int));
	int *somme2 = somme;
	int *sommef = somme;
	FILE *f =fopen(datapath,"rb");
	int nbit = 0;
	u_int8_t p = 0;
	while(fread(&p,1,1,f)==1)
	{
		//printf("close = %i\n",p);
		*somme = p;
		somme += 1;
		nbit += 1;
	}
	fclose(f);


	FILE *fp =fopen(datapath2,"rb");
	u_int8_t d = 0;
	while(fread(&d,1,1,f)==1)
	{
		//printf("good = %i\n",d);
		for(int i = 0 ; i < 4 ; i++)
		{
			//printf("mask = %i\n",(d & (1<<(7-i)))<<i);
			u_int8_t v = 0b0011;
			*somme2 += (d & (v<<(6-i*2)))<<(i*2+2);
			somme2 += 1;
		}
	}
	*somme2 = -1;
	fclose(fp);
	char *fou = calloc(1,sizeof(char));
	int o = 0;
	int a = 0;
	while(o < nbit)//*sommef != -1)
	{
		
		//printf("sommef = %i\n",*sommef);
		if(*sommef > 99)
			a = asprintf(&fou,"%s<%i>",fou,*sommef);
		//printf("fff = %i\n",*sommef);
		else if(*sommef > 9)
			a = asprintf(&fou,"%s<%c%i>",fou,'0',*sommef);
		else
			a = asprintf(&fou,"%s<%c%c%i>",fou,'0','0',*sommef);

		if(a == -1)
			printf("error with asprintf\n");
			
		sommef += 1;
		o+=1;
	}
	return fou;
}


//============================================================================
//=================================pour ecriture et lecture sur 11bits=========
//============================================================================

struct tabint *onzebits(int *tab,int nbw)
{
	int index = 0;
	u_int8_t *ret = calloc(1,(nbw * sizeof(u_int8_t))/2 + 1);
	u_int8_t *bis = ret;
	int m = 0;
	int it = 1;
	while(m<nbw)//pour tous les nombres
	{
		while(m<nbw && index < 8)//on occupe tous les bits
		{
			u_int8_t reste = *tab>>8;
			//printf("tab = %i\n",*tab);
			//printf("r = %i\n",reste);
			if(m%8 == 0)
			{
				*ret = *ret | (reste<<5);
				//printf("retf = %i\n",*ret);
			}
			else if(m%8 == 1)
			{
				*ret = *ret | (reste<<2);
			}
			else if(m%8 == 2)
			{
				u_int8_t gauche = reste>>1;
				u_int8_t droite = reste % 2;
				*ret = *ret | gauche;
				//printf("ret = %i\n",*ret);
				ret += 1;
				it += 1;
				*ret = *ret | (droite<<7);
			}
			else if(m%8 == 3)
			{
				*ret = *ret | (reste<<4);
			}
			else if(m%8 == 4)
			{
				*ret = *ret | (reste<<1);
			}
			else if(m%8 == 5)
			{
				u_int8_t gauche = reste & 4;
				u_int8_t droite = reste & 3;
				*ret = *ret | (gauche);
				//printf("ret = %i\n",*ret);
				ret += 1;
				it += 1;
				*ret = *ret | (droite<<6);
			}
			else if(m%8 == 6)
			{
				*ret = *ret | (reste<<3);
			}
			else if(m%8 == 7)
			{
				*ret = *ret | (reste);
				//printf("retf = %i\n",*ret);
				ret += 1;
				if(m+1<nbw)
					it+=1;
			}
			m+=1;
			tab += 1;
			//printf("ret = %i\n",*ret);

		}
		//printf("ret = %i\n",*ret);
	}
	struct tabint *f = calloc(1,sizeof(struct tabint));
	f->tab = bis;
	//printf("nbitnec = %i\n",it);
	f->nb = it;
	return f;
}

//FONCTION PRINCIPALE
struct double_tab *build_onze(int *tab,int nbw)
{
	u_int8_t *k = calloc(1,nbw*sizeof(u_int8_t));
	u_int8_t *kk = k;
	int *tabtab =tab;
	u_int8_t *r = calloc(1,(nbw/2 + 1*(nbw%8 != 0))*sizeof(u_int8_t));
	for(int i = 0; i < nbw;i++)
	{
		*k = *tab & 255;
		k += 1;
		tab += 1;
	}
	struct tabint *tmp = onzebits(tabtab,nbw);
	r = tmp->tab;
	int it = tmp->nb;

	struct double_tab *final = calloc(1,sizeof(struct double_tab));
	final->keep = kk;
	final->res = r;

	FILE *f1;
	f1 = fopen("test.bin","wb");
	for(int i = 0; i < nbw;i++)
	{
		fwrite(&(*kk),1,1,f1);
		kk += 1;
	}
	fclose(f1);

	FILE *f2;
	f2 = fopen("testb.bin","wb");
	for(int i = 0; i < it;i++)
	{
		//printf("writtenr = %i\n",*r);
		fwrite(&(*r),1,1,f2);
		r += 1;
	}
	fclose(f2);




	return final;


}

char *recup11(char *datapath,char *datapath2)
{
	int *somme = calloc(1,10000*sizeof(int));
	int *somme2 = somme;
	int *sommef = somme;
	int m = 0;
	FILE *f =fopen(datapath,"rb");
	int nbit = 0;
	u_int8_t p = 0;
	while(fread(&p,1,1,f)==1)
	{
		//printf("sur 8bits = %i\n",p);
		*somme = p;
		somme += 1;
		nbit += 1;
	}
	fclose(f);


	FILE *fp =fopen(datapath2,"rb");
	u_int8_t d = 0;
	int a = 1;
	int joker = 0;
	int jokerbis = 0;
	while(fread(&d,1,1,f)==1)
	{
		//printf("lus = %i\n",d);
		while(a)
		{
			if(m%8 == 0)
			{
				//printf("somme init= %i\n",*somme2);
				//printf("d = %i\n",d);
				*somme2 += ((d>>5)<<8);
				//printf("dodo = %i\n",*somme2);
				somme2 += 1;
				m+=1;
			}
			else if(m%8 == 1)
			{
				//printf("congru a 1\n");
				*somme2 += (mod1(d)<<8);
				somme2 += 1;
				m+=1;
			
			}
			else if(m%8 == 2)
			{
				if(joker == 0)
				{
					//printf("congru a 2,1\n");
					int b = 0b0011;
					*somme2 += ((d & b)<<9);
					a = 0;
					joker = 1;
				}
				else
				{
					//printf("congru a 2,2\n");
					*somme2 += ((d & 128)<<1);
					joker = 0;
					somme2 += 1;
					m+=1;
				}
			}
			else if(m%8 == 3)
			{
				//printf("congru a 3\n");
				int mask = 0b01110000;
				*somme2 += ((d&mask)<<4);
				somme2 += 1;
				m+=1;
			}
			else if(m%8 == 4)
			{
				//printf("congru a 4\n");
				int mask = 0b00001110;
				*somme2 += ((d&mask)<<7);
				somme2 += 1;
				m+=1;
			}
			else if(m%8 == 5)
			{
				if(jokerbis == 0)
				{
					//printf("congru a 5,1\n");
					*somme2 += ((d & 1)<<10);
					a = 0;
					jokerbis = 1;
				}
				else
				{
					//printf("congru a 5,2\n");
					int n = 0b11000000;
					*somme2 += ((d & n)<<2);
					jokerbis = 0;
					somme2 += 1;
					m+=1;
				}
			}
			else if(m%8 == 6)
			{
				//printf("congru a 6\n");
				int mask = 0b00111000;
				*somme2+= ((d&mask)<<5);
				somme2 += 1;
				m+=1;
			}
			else if(m%8 == 7)
			{
				//printf("congru a 7\n");
				int mask = 0b00000111;
				*somme2+= ((d&mask)<<8);
				somme2 += 1;
				a=0;
				m+=1;
			}
		}
		a=1;
	}
	*somme2 = -1;
	fclose(fp);
	char *fou = calloc(1,sizeof(char));
	int o = 0;
	int lostintheflood = 0;
	while(o < nbit)//*sommef != -1)
	{
		//printf("sommef = %i\n",*sommef);
		if(*sommef > 99)
			lostintheflood = asprintf(&fou,"%s<%i>",fou,*sommef);
		//printf("fff = %i\n",*sommef);
		else if(*sommef > 9)
			lostintheflood = asprintf(&fou,"%s<%c%i>",fou,'0',*sommef);
		else
			lostintheflood = asprintf(&fou,"%s<%c%c%i>",fou,'0','0',*sommef);


		if(lostintheflood == -1)
			printf("error with asprintf\n");
			
		sommef += 1;
		o+=1;
	}
	return fou;
}



//===========================================================================
//===============================Ecriture et lecture sur 12 bits=============
//===========================================================================
struct tabint *douzebits(int *tab,int nbw)
{
	int index = 0;
	u_int8_t *ret = calloc(1,(nbw * sizeof(u_int8_t))/2 + 1);
	u_int8_t *bis = ret;
	int m = 0;
	while(m<nbw)//pour tous les nombres
	{
		while(m<nbw && index < 8)//on occupe tous les bits
		{
			u_int8_t reste = (*tab>>8);//= 1 ou 0
			//printf("squelette = %i\n",reste);
			int masque = reste << (4-index);
			//printf("masque = %i\n",masque);
			*ret = *ret | masque;
			tab += 1;
			index += 4;
			m+=1;
		}
		//printf("ret = %i\n",*ret);
		index = 0;
		ret += 1;
	}
	struct tabint *f = calloc(1,sizeof(struct tabint));
	f->tab = bis;
	f->nb = nbw;
	return f;
}

//FONCTION PRINCIPALE
struct double_tab *build_douze(int *tab,int nbw)
{
	u_int8_t *k = calloc(1,nbw*sizeof(u_int8_t));
	u_int8_t *kk = k;
	int *tabtab =tab;
	u_int8_t *r = calloc(1,(nbw/8 + 1*(nbw%8 != 0))*sizeof(u_int8_t));
	for(int i = 0; i < nbw;i++)
	{
		*k = *tab & 255;
		k += 1;
		tab += 1;
	}
	struct tabint *tmp = douzebits(tabtab,nbw);
	r = tmp->tab;

	struct double_tab *final = calloc(1,sizeof(struct double_tab));
	final->keep = kk;
	final->res = r;

	FILE *f1;
	f1 = fopen("test.bin","wb");
	for(int i = 0; i < nbw;i++)
	{
		fwrite(&(*kk),1,1,f1);
		kk += 1;
	}
	fclose(f1);

	FILE *f2;
	f2 = fopen("testb.bin","wb");
	for(int i = 0; i < nbw/2 + 1*(nbw%8 != 0);i++)
	{
		fwrite(&(*r),1,1,f2);
		r += 1;
	}
	fclose(f2);




	return final;


}

char *recup12(char *datapath,char *datapath2)
{
	int *somme = calloc(1,10000*sizeof(int));
	int *somme2 = somme;
	int *sommef = somme;
	FILE *f =fopen(datapath,"rb");
	int nbit = 0;
	u_int8_t p = 0;
	while(fread(&p,1,1,f)==1)
	{
		//printf("avantdernier= %i\n",p);
		*somme = p;
		somme += 1;
		nbit += 1;
	}
	fclose(f);


	FILE *fp =fopen(datapath2,"rb");
	u_int8_t d = 0;
	while(fread(&d,1,1,f)==1)
	{
		//printf("good = %i\n",d);
		for(int i = 0 ; i < 8 ; i++)
		{
			//printf("mask = %i\n",(d & (1<<(7-i)))<<i);
			if(i == 0)
			{
				*somme2 += ((d & 240)<<4);
			}
			else
			{
				*somme2 += ((d&15)<<8);
			}
			i+=4;
			somme2 += 1;
		}
	}
	*somme2 = -1;
	fclose(fp);
	char *fou = calloc(1,sizeof(char));
	int o = 0;
	int a = 0;
	while(o < nbit)//*sommef != -1)
	{
		//printf("sommef = %i\n",*sommef);
		if(*sommef > 99)
			a= asprintf(&fou,"%s<%i>",fou,*sommef);
		//printf("fff = %i\n",*sommef);
		else if(*sommef > 9)
			a = asprintf(&fou,"%s<%c%i>",fou,'0',*sommef);
		else
			a = asprintf(&fou,"%s<%c%c%i>",fou,'0','0',*sommef);
			
		if(a == -1)
			printf("error with asprintf\n");

		sommef += 1;
		o+=1;
	}
	return fou;
}

//============================================================================
//=================================pour ecriture et lecture sur 8bits=========
//============================================================================

//FONCTION PRINCIPALE
struct double_tab *build_huit(int *tab,int nbw)
{
	u_int8_t *k = calloc(1,nbw*sizeof(u_int8_t));
	u_int8_t *kk = k;
	int *tabtab =tab;
	u_int8_t *r = calloc(1,(nbw/8 + 1*(nbw%8 != 0))*sizeof(u_int8_t));
	for(int i = 0; i < nbw;i++)
	{
		*k = *tab & 255;
		k += 1;
		tab += 1;
	}
	struct tabint *tmp = neufbits(tabtab,nbw);
	r = tmp->tab;

	struct double_tab *final = calloc(1,sizeof(struct double_tab));
	final->keep = kk;
	final->res = r;

	FILE *f1;
	f1 = fopen("test.bin","wb");
	for(int i = 0; i < nbw;i++)
	{
		fwrite(&(*kk),1,1,f1);
		kk += 1;
	}
	fclose(f1);

	FILE *f2;
	f2 = fopen("testb.bin","wb");
	fclose(f2);




	return final;


}

char *recup8(char *datapath,char *datapath2)
{
	(void)datapath2;
	int *somme = calloc(1,10000*sizeof(int));
	int *somme2 = somme;
	int *sommef = somme;
	FILE *f =fopen(datapath,"rb");
	int nbit = 0;
	u_int8_t p = 0;
	while(fread(&p,1,1,f)==1)
	{
		//printf("close = %i\n",p);
		*somme = p;
		somme += 1;
		nbit += 1;
	}
	fclose(f);


	char *fou = calloc(1,sizeof(char));
	int o = 0;
	int a = 0;
	while(o < nbit)//*sommef != -1)
	{
		//printf("sommef = %i\n",*sommef);
		if(*sommef > 99)
			a = asprintf(&fou,"%s<%i>",fou,*sommef);
		//printf("fff = %i\n",*sommef);
		else if(*sommef > 9)
			a = asprintf(&fou,"%s<%c%i>",fou,'0',*sommef);
		else
			a = asprintf(&fou,"%s<%c%c%i>",fou,'0','0',*sommef);

		if(a == -1)
			printf("error with asprintf");
		sommef += 1;
		o+=1;
	}
	(void)somme2;
	return fou;
}





/*int main(int argc,char *argv[])
{
	//int a = 500;
	int masque = 255;
	int reste = (a & (1<<8))>>8;
	printf("a = %i et reste = %i\n",a & masque,reste);

	int rec = (reste << 8) + (a & masque) ;
	printf("so = %i\n",rec);
	//int arg = atoi(argv[1]);
	//printf("res = %i\n",arg & 255);
	int tab[17]={4090,956,350,350,129,256,12,15,1020,899,350,350,129,256,12,15,1003};*/
	/*struct tabint *test = neufbits(tab,16);
	for(int u = 0;u<2;u++)
	{
		printf("reste = %i\n",*test->tab);
		test->tab += 1;
	}*/
////////
	/*struct double_tab *main = build_douze(tab,17);
	for(int u = 0; u < 17 ;u++)
	{
		printf("keep n-%i = %i\n",u,*(main->keep));
		main->keep+=1;
	}
	for(int p = 0; p < 2;p++)
	{
		printf("reste n-%i = %i\n",p,*(main->res));
		main->res += 1;

	}
	char *print = calloc(1,sizeof(char));
	int u = asprintf(&print,"%s%s",print,recup12("test.bin","testb.bin"));
	printf("%s\n",print);
	///////

	printf("test de lerde  = %i\n",mod1(111));
	//recup("test.bin","testb.bin");
	//dixbits(tab,15);

}*/
