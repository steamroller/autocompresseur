#ifndef HAUTENF_H
#define HAUTENF_H
#include <gtk/gtk.h>


typedef struct
{
	GtkBuilder *builder;
	gpointer user_data;

} SGlobalData;





struct main_board
{
	struct user* next; 
	size_t size;
};

struct user
{
	char* name;
	char* password;
	size_t nb_file;
	struct file_board* file;
};

struct file_board
{
	char* pathname;
	struct file_board* next; 
};

struct main_board* main_board_init();
struct user* user_init();
struct file_board* file_board_init();

int  add_user( struct main_board *main_board, char* name, char* password);
int is_name_available(struct main_board* main_board, char* name);
int connexion(struct main_board* main_board, char* name, char* password);

#endif
