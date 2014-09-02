#ifndef	__FUNCTIONS_H
#define __FUNCTIONS_H 1
#include <gtk/gtk.h>
#include "structs.h"

/* Builder Function */
/* Helper function */
void error_out(char *error);
void clean_var();
void call_last_func();
void build_UI();

GtkWidget **create_message_dialog(GtkWindow *fwindow, char *messages, GtkMessageType type, GtkWidget **dialog_response);
GtkWidget **create_edit_dialog(GtkWindow *fwindow, int rws, char argi[][30], GtkWidget **dialog_response);

int category_create(Category **head ,char code, char name[], int clothes_count, Clothes *clothes);
int clothes_create(Clothes **head, char name[], char type, float price, int order_count, float mark, Category *category, Order *order);
int order_create(Order **head, char date[], char name[], int mark, Clothes *clothes);

int data_delete();
int category_delete(void *self);
int clothes_delete(void *self);
int order_delete(void *self);

Category **category_search(char code);
Clothes **clothes_search(char name[30]);

void data_out();

void clean_column();
char *string(char code);

/* End Helper function */

/* Basic I/O */
int save_file();
void open_file(char *filename);
int load_file();
void close_file(); /* clean data then you can change file */
char *file_choose(int type);

void file_new();
void file_open();
void file_save();
void file_save_as();
void file_quit();
/* End Basic I/O */

/* Maintenance */
int maintenance_category_dialog(void *self);

void maintenance_add_category();
void maintenance_add_clothes();
void maintenance_add_order();

void maintenance_edit();
void maintenance_delete();
/* End Maintenance */

/* Query */
void query_category_all(void *pass, int call_type);
/* End Query */

/* Statistics */
/* End Statistics */

/* Other Function */
void other_about();
/* End Other Function */

#endif /* functions.h */