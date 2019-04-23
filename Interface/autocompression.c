#define _GNU_SOURCE

#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <gtk/gtk.h>
#include <SDL/SDL.h>
#include "antoine/huffman.h"
#include "antoine/huffman.c"
#include "clara/encryption.h"
#include "clara/encoding.c"
#include "clara/decoding.h"
#include "clara/decoding.c"

//void whole_comp(char *input, char *filename);


struct components
{
  
  char *str;
  
};

GtkBuilder* builder;

/* BUTTON*/

GtkWidget* new_user;
GtkWidget* new_file_button;
GtkWidget* open_file_button;
GtkWidget* setting_button;
GtkWidget* save_button;
GtkWidget* close_edit_button;
GtkWidget* oui_button;
GtkWidget* valid_button;

GtkWidget* switch_rsa;
GtkWidget* switch_huffman;
GtkWidget* switch_dictionnary;

/*CONNECT*/

GtkLabel* textlabel;


GtkEntry* name_entry;
GtkEntry * password_entry;
GtkLabel * connexion_message;
GtkEntry* filename_entry;
GtkEntry* filename_open_entry;



const gchar * name;
const gchar * password;
const gchar * filename;
const gchar * filename_open;

/*list file */
GtkTreeModel* store;
GtkWidget * file_list; 
GtkTreeIter  list_iter;
GtkWidget *list_window;
GtkWidget *view;

/* WINDOW */

GtkWidget * main_window;
GtkWidget * menu_window;
GtkWidget * settings_window;
GtkWidget * edit_window;
GtkWidget * filename_window;
GtkWidget * filename_open_window;

GtkTextBuffer * text_buffer;	
GtkWidget * text_zone;


void model_data_new(GtkTreeModel* store,const gchar* fichier)  
{  
    GtkTreeIter iter;  
    gtk_list_store_append(GTK_LIST_STORE(store), &iter);  
    gtk_list_store_set(GTK_LIST_STORE(store), &iter,0,fichier,-1);  
}


void get_available_files()
{
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("available_files", "r");
    
    while ((read = getline(&line, &len, fp)) != -1) {
        //const gchar* tt = "...";
        model_data_new(store, line);
       // printf("%s", line);
    }

    fclose(fp);
    
}


void on_edit_window_destroy()
{
	gtk_main_quit();
	//printf("chocobn\n");
}

void on_menu_window_destroy()
{
	gtk_main_quit();
	//printf("chocobn\n");
}

void on_main_window_destroy()
{
	gtk_main_quit();
	//printf("chocobn\n");
}



char* strncpy(char *dest, const char *src,size_t n){
    size_t i;

    for (i = 0 ; i<n && src[i] != '\0' ; i++)
        dest[i] = src[i];
    for ( ; i < n ; i++)
        dest[i] = '\0';

    return dest;
}

//--- COMPAR ENTRY DATA AND FILE DATA
int compar(	char* rdname,const gchar* s2,size_t len_rd,size_t len_enter)
{
	char *cmp=rdname;
	
	size_t c=0;
	if(len_rd != len_enter)
		return 1;
	while(c<len_rd && c<len_enter)
	{
		if(cmp[c]!=s2[c])
		{
			return 1;
		}
		
		c++;
	}
	
	return 0;
}

//---- CREATE AN ACCOUNT (FILES)
void on_new_user_button_clicked()
{
	name= gtk_entry_get_text(GTK_ENTRY(name_entry));
	password= gtk_entry_get_text(GTK_ENTRY(password_entry));
	
	size_t len_login=strlen(name);
	size_t len_password=strlen(password);
	char nam[len_login];

	char  pass[len_password];
	strncpy(nam,name,len_login);
	strncpy(pass,password,len_password);
	if(access("userdatal",R_OK)!=-1)
		gtk_label_set_text(GTK_LABEL(connexion_message),"There is already an account on this computer ! ");
	else
	{
	//	printf("------------------New account------------------\n");
	//	printf("Login: %s \nPassword: %s \n\n", name, password);

		int fdl=open("userdatal",O_TRUNC|O_CREAT|O_RDWR,00700);
		int fdm=open("userdatam",O_TRUNC|O_CREAT|O_RDWR,00700);
		write(fdl,nam,len_login);
		write(fdm,pass,len_password);
		gtk_label_set_text(GTK_LABEL(connexion_message),"Account created !");
	}

}

//---- CONNEXION USING THE COMPAR FUNCTION
void on_connexion_button_clicked()
{
	name= gtk_entry_get_text(GTK_ENTRY(name_entry));
	password= gtk_entry_get_text(GTK_ENTRY(password_entry));
	size_t len_enter_name=strlen(name);
	size_t len_enter_password=strlen(password);
	

	int fdl=open("userdatal",O_RDWR,00700);
	int fdm=open("userdatam",O_RDWR,00700);
	if(fdm ==-1 || fdl==-1)
		gtk_label_set_text(GTK_LABEL(connexion_message),"You should create an account");
	else
	{
	//	printf("------------------Connexion------------------\n");
	//	printf("Name entry : %s \nPassword entry: %s \n", name, password);


		char rdname[len_enter_name];
		rdname[len_enter_name-1]='\n';
		char rdpassword[len_enter_password];
		rdname[len_enter_password-1]='\n';
		size_t len_rd_name=read(fdl,rdname,20);
		size_t len_rd_password=read(fdm,rdpassword,20);
	
		int cmn=compar(rdname,name,len_rd_name,len_enter_name);
		
		int cmp=compar(rdpassword,password,len_rd_password,len_enter_password);
	//	printf("\n\n\n");
		if(cmp==0 && cmn==0)
		{
		//	printf("        Connected  !            \n");
			gtk_label_set_text(GTK_LABEL(connexion_message),"Connected !");
			gtk_widget_show(menu_window);
			gtk_widget_hide(main_window);
	
		}
		else
		{
		//	printf("Wrong login or password, try again.\n");
			gtk_label_set_text(GTK_LABEL(connexion_message),"Wrong login or password, try again.");
			
		}
	
	}
}


void on_new_file_button_clicked()
{
	gtk_widget_show(edit_window);
	gtk_widget_hide(menu_window);

}

char *conca(const char *s1, const char *s2) //Concatenate char
{
     char *s3 = NULL;
     s3 = (char *)malloc((strlen(s1)+strlen(s2))+1);
     strcpy(s3,s1);
     strcat(s3,s2);
     return s3;
}


void cp_file(char *filename)   // copy file choosed in the folder tmp/
{
	char *cp_arg1 = conca("cp ", filename);
	char *arg1_arg2 = conca(cp_arg1, "  tmp/test_file.txt");

	system(arg1_arg2);
}


int dechiffrement_needed(char *s)
{
	int len = strlen(s);
	int i = 0;
	int b = 1;
	while(i < len/2 && b == 1)
	{
		if(!((int)s[i] >= 48 && (int)s[i] <= 57) && s[i] != ',')
			b = 0;
		i+=1;
	}
	return b;
}

void on_valid_button_clicked()
{
	gtk_widget_hide(list_window);
	filename_open = gtk_entry_get_text(GTK_ENTRY(filename_open_entry));
	printf("Ouverture du fichier : %s \n\n--------------------------------------\n\n", filename_open);
	
	char *decomp;
	printf("choco\n");
	char *fln = g_strdup(filename_open);
	printf("fln = %s\n",fln);
	
	decomp = whole_decomp(fln);
	
	printf("pbivb = %s\n",decomp);
	const gchar *result = calloc(strlen(decomp),sizeof(char));
	//strcpy(decomp,result);
	
		
	if( dechiffrement_needed(decomp))
	{
		result = decoding(decomp);
		printf("res = %s\n",result);
		text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_zone));
		GtkTextIter end;
		gtk_text_buffer_get_end_iter(text_buffer,&end);
		gtk_text_buffer_insert(text_buffer,&end,result,-1);
	}
	else
	{
		result =decomp;
		printf("res = %s\n",result);
		text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_zone));
		GtkTextIter end;
		gtk_text_buffer_get_end_iter(text_buffer,&end);
		gtk_text_buffer_insert(text_buffer,&end,result,-1);
	}
	
	
	
	
	/*cp_file(filename_open);
		
    
    printf("Ouverture du fichier : %s \n\n--------------------------------------\n\n", filename);
	FILE* temp = NULL;
    char result[1000] = "";
   	temp = fopen("tmp/test_file.txt", "r");	
	text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_zone));
    if (temp != NULL)
    {
		while ( fgets(result, 1000, temp))
		{
			GtkTextIter end;
			gtk_text_buffer_get_end_iter(text_buffer,&end);
			gtk_text_buffer_insert(text_buffer,&end,result,-1);
		}
    	fclose(temp);
    }
		elm->str = result;
		gtk_text_buffer_set_text(text_buffer, elm->str, strlen(elm->str));*/

	gtk_widget_show(edit_window);
	gtk_widget_hide(filename_open_window);
	gtk_widget_hide(file_list);
	//gtk_widget_hide(menu_window);
	//}
}

void on_open_file_button_clicked()
{

	gtk_widget_show(filename_open_window);
	gtk_widget_hide(menu_window);
	gtk_widget_show_all ( file_list );
	/*GtkWidget *toplevel=gtk_widget_get_toplevel(GTK_WIDGET(open_file_button));
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	dialog = gtk_file_chooser_dialog_new ("Open File",GTK_WINDOW(toplevel)     
,action,
        "open",GTK_RESPONSE_ACCEPT,"Cancel",GTK_RESPONSE_CANCEL, NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        char * filename_open = gtk_file_chooser_get_filename (chooser);
		
		struct components *elm = malloc(sizeof(struct components));
		elm->str =malloc(sizeof(char)*1200);*/
		
}


void on_setting_button_clicked()
{
	gtk_widget_show(settings_window);
	gtk_widget_hide(menu_window);
	

}


void on_close_edit_button_clicked()
{
	gtk_widget_show(menu_window);
	gtk_widget_hide(edit_window);
	//const gchar *result = calloc(1000,sizeof(char));
	text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_zone));
	GtkTextIter end;
	GtkTextIter start;
	gtk_text_buffer_get_start_iter(text_buffer,&start);
	gtk_text_buffer_get_end_iter(text_buffer,&end);
	gtk_text_buffer_delete (text_buffer,&start,&end);
}



void on_oui_button_clicked()
{
	filename = gtk_entry_get_text(GTK_ENTRY(filename_entry));
	
	printf("filename : %s \n\n--------------------------------------\n\n",filename);
	
	char pathFile[50];
	sprintf(pathFile, "filenames/%s", filename);
	int fd = open(pathFile, O_RDWR | O_APPEND | O_CREAT); 
	if(fd==-1)
		printf("open file failed");
	
	model_data_new(store, filename); 
	text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_zone));
	GtkTextIter start;
	GtkTextIter end;
	gtk_text_buffer_get_start_iter(text_buffer,&start);
	gtk_text_buffer_get_end_iter(text_buffer,&end);
	char* lines = gtk_text_buffer_get_text(text_buffer,&start,&end,FALSE);

	
	char *toencode = calloc(strlen(lines),sizeof(char));
	
	toencode= lines;
	
	
	char *copy = g_strdup(filename);
	
	if (gtk_switch_get_active(GTK_SWITCH(switch_rsa)) && (gtk_switch_get_active(GTK_SWITCH(switch_huffman))))
	{
		//chiffrement
		char *tocompress= calloc(strlen(lines)*4,sizeof(char));
		tocompress = encryption(toencode);
		whole_comp(tocompress,copy);

	}
	else if(!(gtk_switch_get_active(GTK_SWITCH(switch_rsa))) && gtk_switch_get_active(GTK_SWITCH(switch_huffman)))
	{
		
		whole_comp(toencode,copy);
	}
	
	printf(" text :\n %s \n\n--------------------------------------\n\n",lines);
	
	gtk_widget_hide(filename_window);
}

void on_save_button_clicked()
{

	gtk_widget_show(filename_window);
	
	
	
/*
	 ENVOYER LINES AU FCT DE CHIFFR ET COMPR 
	FILE* fichier = fopen("tmp/test_file.txt","w");
	fputs(lines,fichier);
	fputs("\n",fichier);
	fclose(fichier);
	GtkWidget *toplevel=gtk_widget_get_toplevel(GTK_WIDGET(save_button));
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	dialog = gtk_file_chooser_dialog_new ("Save File",GTK_WINDOW(toplevel)     
,action,
        "save",GTK_RESPONSE_ACCEPT,"Cancel",GTK_RESPONSE_CANCEL, NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
	gtk_file_chooser_set_current_name(chooser,"Untitled document");
        filename = gtk_file_chooser_get_filename (chooser);
        
        printf("Sauvegarde du fichier : %s \n\n--------------------------------------\n\n", filename);
		 SEND FILENAME TO ANTOINE FOR COMPRESS AND SAVE IT 
	}
	
	gtk_widget_destroy(dialog);*/


}

void on_apply_button_clicked()
{
	
	gtk_widget_show(menu_window);
	gtk_widget_hide(settings_window);
	
	printf("Les paramètres sont : \n\n");
	if(gtk_switch_get_active(GTK_SWITCH(switch_rsa)))
	{
		printf("Chiffrement RSA\n\n");
	}
	if(gtk_switch_get_active(GTK_SWITCH(switch_huffman)))
	{
		printf("Compression HUFFMAN\n\n");
		
	}
	if(gtk_switch_get_active(GTK_SWITCH(switch_dictionnary)))
	{
		printf("Compression DICTIONNAIRE\n\n");
	}
	printf("--------------------------------------\n\n");
}


void on_switch_rsa_state_set()
{
	if(gtk_switch_get_active(GTK_SWITCH(switch_rsa)))
	{
		//printf("rsa on ! \n");
		gtk_switch_set_active(GTK_SWITCH(switch_dictionnary),FALSE);
		gtk_switch_set_active(GTK_SWITCH(switch_huffman),TRUE);
	}
/*	else
	{
		
	}*/

}

void on_switch_huffman_state_set()
{
	if(gtk_switch_get_active(GTK_SWITCH(switch_huffman)))
	{
		//printf("huffman on ! \n");
		gtk_switch_set_active(GTK_SWITCH(switch_dictionnary),FALSE);
	}
	//else
	//	printf("huffman off ! \n");

}

void on_switch_dictionnary_state_set()
{
	if(gtk_switch_get_active(GTK_SWITCH(switch_dictionnary)))
	{
		gtk_switch_set_active(GTK_SWITCH(switch_rsa),FALSE);
		gtk_switch_set_active(GTK_SWITCH(switch_huffman),FALSE);
		//printf("dictionnary on ! \n");
	}
	//else
		//printf("dictionnary off ! \n");

}

  
GtkTreeModel* create_model() {  
    GtkListStore  *store;  
    store = gtk_list_store_new (1,G_TYPE_STRING);  
    return GTK_TREE_MODEL(store);  
}  
  
void arrange_tree_view(GtkWidget* view) {  
    GtkCellRenderer* renderer;  
  
    // colonne 1: nom  
    renderer = gtk_cell_renderer_text_new ();  
    gtk_tree_view_insert_column_with_attributes(  
        GTK_TREE_VIEW(view), -1, "fichiers disponibles", renderer, "text",0, NULL);  
  
}  


int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv);
	
	builder=gtk_builder_new();

	//------ GET ELEMENT FROM GLADE FILE
	gtk_builder_add_from_file(builder,"gui.glade",NULL);
	
	
	
	/* START LIST WINDOW */
	list_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	file_list=gtk_window_new(GTK_WINDOW_TOPLEVEL);  
    
    GtkWidget* view;  
    view = gtk_tree_view_new();  
    gtk_container_add( GTK_CONTAINER(file_list), view);  
    arrange_tree_view(view); 
    store = create_model();  
    gtk_tree_view_set_model ( GTK_TREE_VIEW(view),  store);  
   
   	system("ls filenames/ >> available_files");
	get_available_files();
	printf("file added \n");
	system(" rm available_files");
    g_object_unref( store );  
  	
    /* END LIST WINDOW*/
    
	main_window=GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
	menu_window=GTK_WIDGET(gtk_builder_get_object(builder,"menu_window"));
	settings_window=GTK_WIDGET(gtk_builder_get_object(builder,"settings_window"));
	edit_window=GTK_WIDGET(gtk_builder_get_object(builder,"edit_window"));
	text_zone=GTK_WIDGET(gtk_builder_get_object(builder,"text_zone"));
	filename_window=GTK_WIDGET(gtk_builder_get_object(builder,"filename_window"));
	filename_open_window=GTK_WIDGET(gtk_builder_get_object(builder,"filename_open_window"));

    switch_rsa=GTK_WIDGET(gtk_builder_get_object(builder,"switch_rsa"));
 	switch_huffman=GTK_WIDGET(gtk_builder_get_object(builder,"switch_huffman"));
	switch_dictionnary=GTK_WIDGET(gtk_builder_get_object(builder,"switch_dictionnary"));
	
	gtk_switch_set_active(GTK_SWITCH(switch_dictionnary),FALSE);
	gtk_switch_set_active(GTK_SWITCH(switch_huffman),TRUE);


	new_user=GTK_WIDGET(gtk_builder_get_object(builder,"new_user_button"));
	new_file_button=GTK_WIDGET(gtk_builder_get_object(builder,"new_file_button"));
	open_file_button=GTK_WIDGET(gtk_builder_get_object(builder,"open_file_button"));
	setting_button=GTK_WIDGET(gtk_builder_get_object(builder,"setting_button"));
	save_button=GTK_WIDGET(gtk_builder_get_object(builder,"new_user_button"));
	close_edit_button=GTK_WIDGET(gtk_builder_get_object(builder,"close_edit_button"));
	oui_button=GTK_WIDGET(gtk_builder_get_object(builder,"oui_button"));
	valid_button=GTK_WIDGET(gtk_builder_get_object(builder,"valid_button"));

	connexion_message= GTK_LABEL(gtk_builder_get_object(builder,"connexion_message"));
	name_entry=GTK_ENTRY(gtk_builder_get_object(builder,"login_entry"));
	password_entry=GTK_ENTRY(gtk_builder_get_object(builder,"password_entry"));
	filename_entry=GTK_ENTRY(gtk_builder_get_object(builder,"filename_entry"));
	filename_open_entry=GTK_ENTRY(gtk_builder_get_object(builder,"filename_open_entry"));
	
	//------ CONNECT BUTTON
	gtk_builder_connect_signals(builder,NULL);
	g_object_unref(builder);
	gtk_widget_show(main_window);
	gtk_main();
	return  0;


}
