#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <gtk/gtk.h>
#include <SDL/SDL.h>


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

/*CONNECT*/

gchar *filename= "";
GtkLabel* textlabel;

GtkEntry* name_entry;
GtkEntry * password_entry;
GtkLabel * connexion_message;


const gchar * name;
const gchar * password;

/* WINDOW */

GtkWidget * main_window;
GtkWidget * menu_window;
GtkWidget * settings_window;
GtkWidget * edit_window;

GtkTextBuffer * text_buffer;	
GtkWidget * text_zone;

int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv);


	builder=gtk_builder_new();

	//------ GET ELEMENT FROM GLADE FILE
	gtk_builder_add_from_file(builder,"autocompresseur_gui.glade",NULL);
	
	main_window=GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
	menu_window=GTK_WIDGET(gtk_builder_get_object(builder,"menu_window"));
	settings_window=GTK_WIDGET(gtk_builder_get_object(builder,"settings_window"));
	edit_window=GTK_WIDGET(gtk_builder_get_object(builder,"edit_window"));
	text_zone=GTK_WIDGET(gtk_builder_get_object(builder,"text_zone"));


	new_user=GTK_WIDGET(gtk_builder_get_object(builder,"new_user_button"));
	new_file_button=GTK_WIDGET(gtk_builder_get_object(builder,"new_file_button"));
	open_file_button=GTK_WIDGET(gtk_builder_get_object(builder,"open_file_button"));
	setting_button=GTK_WIDGET(gtk_builder_get_object(builder,"setting_button"));
	save_button=GTK_WIDGET(gtk_builder_get_object(builder,"new_user_button"));
	close_edit_button=GTK_WIDGET(gtk_builder_get_object(builder,"close_edit_button"));

	connexion_message= GTK_LABEL(gtk_builder_get_object(builder,"connexion_message"));
	name_entry=GTK_ENTRY(gtk_builder_get_object(builder,"login_entry"));
	password_entry=GTK_ENTRY(gtk_builder_get_object(builder,"password_entry"));

	//------ CONNECT BUTTON
	gtk_builder_connect_signals(builder,NULL);
	g_object_unref(builder);
	gtk_widget_show(main_window);
	gtk_main();
	return  0;


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
		printf("------------------New account------------------\n");
		printf("Login: %s \nPassword: %s \n\n", name, password);

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
		printf("------------------Connexion------------------\n");
		printf("Name entry : %s \nPassword entry: %s \n", name, password);


		char rdname[len_enter_name];
		rdname[len_enter_name-1]='\n';
		char rdpassword[len_enter_password];
		rdname[len_enter_password-1]='\n';
		size_t len_rd_name=read(fdl,rdname,20);
		size_t len_rd_password=read(fdm,rdpassword,20);
	
		int cmn=compar(rdname,name,len_rd_name,len_enter_name);
		
		int cmp=compar(rdpassword,password,len_rd_password,len_enter_password);
		printf("\n\n\n");
		if(cmp==0 && cmn==0)
		{
			printf("        Connected  !            \n");
			gtk_label_set_text(GTK_LABEL(connexion_message),"Connected !");
			gtk_widget_show(menu_window);
			gtk_widget_hide(main_window);
	
		}
		else
		{
			printf("Wrong login or password, try again.\n");
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


void cp_file(char *filename)   // copy file choosed in the folder images/
{
	char *cp_arg1 = conca("cp ", filename);
	char *arg1_arg2 = conca(cp_arg1, "  tmp/test_file.txt");

	system(arg1_arg2);
}

void on_open_file_button_clicked()
{

	GtkWidget *toplevel=gtk_widget_get_toplevel(GTK_WIDGET(open_file_button));
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	dialog = gtk_file_chooser_dialog_new ("Open File",GTK_WINDOW(toplevel)     
,action,
        "open",GTK_RESPONSE_ACCEPT,"Cancel",GTK_RESPONSE_CANCEL, NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
		
		struct components *elm = malloc(sizeof(struct components));
		elm->str =malloc(sizeof(char)*1200);
		
		cp_file(filename);

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

	/*	elm->str = result;

		gtk_text_buffer_set_text(text_buffer, elm->str, strlen(elm->str));*/

		gtk_widget_show(edit_window);
		gtk_widget_hide(menu_window);
	}
	else
		g_print("You pressed the cancel \n");

	gtk_widget_destroy(dialog);
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
}


void on_save_button_clicked()
{
/*	text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_zone));
	GtkTextIter start;
	GtkTextIter end;
	gtk_text_buffer_get_start_iter(text_buffer,&start);
	gtk_text_buffer_get_end_iter(text_buffer,&end);
	gchar* lines = gtk_text_buffer_get_text(text_buffer,&start,&end,FALSE);

	 ENVOYER LINES AU FCT DE CHIFFR ET COMPR 

	FILE* fichier = fopen("tmp/test_file.txt","w");
	fputs(lines,fichier);
	fputs("\n",fichier);
	fclose(fichier);*/

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

		/* SEND FILENAME TO ANTOINE FOR COMPRESS AND SAVE IT */
	}
	
	gtk_widget_destroy(dialog);


}

void on_apply_button_clicked()
{
	gtk_widget_show(menu_window);
	gtk_widget_hide(settings_window);
}
