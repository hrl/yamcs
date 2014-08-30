#ifndef	__FUNCTIONS_H
#define __FUNCTIONS_H 1
#include <gtk/gtk.h>
#include "structs.h"

/* Builder Function */
/* Helper function */
void error_out(char *error);
void build_UI();
void insert_into_container(Container **head, void *data);
int category_edit(Container **self, void *data);
int clothes_edit(Container **self, void *data);
int order_edit(Container **self, void *data);

int category_create(Category **head ,char code, char name[], int clothes_count, Clothes *clothes);
int clothes_create(Clothes **head, char name[], char type, float price, int order_count, float mark, Category *category, Order *order);
int order_create(Order **head, char date[], char name[], int mark, Clothes *clothes);

int data_delete(Container **self, int type);
/* End Helper function */

/* Basic I/O */
short save_file();
void open_file(char *filename);
short load_file();
void close_file(); /* clean data then you can change file */
char *file_choose(int type);

void file_new();
void file_open();
void file_save();
void file_save_as();
void file_quit();
/* End Basic I/O */

/* Maintenance */
void maintenance_add_category();
void maintenance_add_clothes();
void maintenance_add_order();
/* End Maintenance */

/* Query */
/* End Query */

/* Statistics */
/* End Statistics */

/* Other Function */
void other_about();
/* End Other Function */

#endif /* functions.h */