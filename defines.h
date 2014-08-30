#ifndef	__DEFINES_H
#define __DEFINES_H 1

#define UI_FILE "UI.xml"

const char *version = "0.1";
const char *program_name = "Yet Another Manager of a simple Clothing Shop";
const char *author[] = {"Ruilin Huang", NULL};

FILE *file = NULL;
short updated; /*  */
GtkWidget *window = NULL;
GtkTreeView *treeview = NULL;

Category *category_head;  /* Main head of the linked list */

Container *category_list_head = NULL;
Container *clothes_list_head = NULL;
Container *order_list_head = NULL;

enum {
	FILE_CHOOSE_OPEN,
	FILE_CHOOSE_SAVE,
	FILE_CHOOSE_SAVE_AS,
};

enum {
	TYPE_CATEGORY,
	TYPE_CLOTHES,
	TYPE_ORDER,
};

#endif /* defines.h */