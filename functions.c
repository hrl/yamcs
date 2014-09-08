#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <gtk/gtk.h>

#include "structs.h"
#include "defines.h"
#include "functions.h"

/* Helper function */
void error_out(char *error){
  g_print("%s\n", error);
}

void clean_var(){
  data_delete();
  category_head = NULL;
  /*
  category_list_head = NULL;
  clothes_list_head = NULL;
  order_list_head = NULL;
  */
}

void call_last_func(){
  if(last_func){
    (*last_func)(NULL, CALL_TYPE_REDO);
  }
}

void build_UI(){
  GtkBuilder *builder = NULL;
  GError *error = NULL;
  builder = gtk_builder_new();
  if(!gtk_builder_add_from_file(builder, UI_FILE, &error)){
    g_warning("%s", error->message);
    g_free(error);
    exit(1);
  }

  /* Get objects */
  /* Main window */
  window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));
  treeview = GTK_TREE_VIEW(gtk_builder_get_object(builder, "treeview"));
  /* -File menu */
  GtkWidget *menuitem_file_new = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_file_new"));
  GtkWidget *menuitem_file_open = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_file_open"));
  GtkWidget *menuitem_file_save = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_file_save"));
  //GtkWidget *menuitem_file_save_as = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_file_save_as"));
  GtkWidget *menuitem_file_quit = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_file_quit"));
  /* -Query menu */
  /* --Query category menu */
  GtkWidget *menuitem_query_category_all = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_category_all"));
  GtkWidget *menuitem_query_category_code = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_category_code"));
  /* --Query clothes menu */
  GtkWidget *menuitem_query_clothes_all = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_clothes_all"));
  GtkWidget *menuitem_query_clothes_name = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_clothes_name"));
  GtkWidget *menuitem_query_clothes_code_price = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_clothes_code_price"));
  /* --Query order menu */
  GtkWidget *menuitem_query_order_all = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_order_all"));
  GtkWidget *menuitem_query_order_customer_date = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_order_customer_date"));
  GtkWidget *menuitem_query_order_name_mark = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_order_name_mark"));
  /* -Maintenance menu */
  /* --Maintenance add menu */
  GtkWidget *menuitem_maintenance_add_category = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_maintenance_add_category"));
  GtkWidget *menuitem_maintenance_add_clothes = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_maintenance_add_clothes"));
  GtkWidget *menuitem_maintenance_add_order = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_maintenance_add_order"));
  /* --Maintenance edit */
  GtkWidget *menuitem_maintenance_edit = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_maintenance_edit"));
  /* --Maintenance delete */
  GtkWidget *menuitem_maintenance_delete = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_maintenance_delete"));
  /* -Statistics menu */
  GtkWidget *menuitem_statistics_category = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_statistics_category"));
  GtkWidget *menuitem_statistics_year = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_statistics_year"));
  GtkWidget *menuitem_statistics_customer = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_statistics_customer"));
  GtkWidget *menuitem_statistics_quarter = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_statistics_quarter"));
  GtkWidget *menuitem_statistics_all = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_statistics_all"));
  /* -Other menu */
  GtkWidget *menuitem_other_about = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_other_about"));
  /* End Get objects */

  /* Connect signals */
  /* Main window */
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(file_quit), NULL);
  /* -File menu */
  g_signal_connect(G_OBJECT(menuitem_file_new), "activate", G_CALLBACK(file_new), NULL);
  g_signal_connect(G_OBJECT(menuitem_file_open), "activate", G_CALLBACK(file_open), NULL);
  g_signal_connect(G_OBJECT(menuitem_file_save), "activate", G_CALLBACK(file_save), NULL);
  //g_signal_connect(G_OBJECT(menuitem_file_save_as), "activate", G_CALLBACK(file_save_as), NULL);
  g_signal_connect(G_OBJECT(menuitem_file_quit), "activate", G_CALLBACK(file_quit), NULL);
  /* -Query menu */
  /* --Query category menu */
  g_signal_connect(G_OBJECT(menuitem_query_category_all), "activate", G_CALLBACK(query_category_all), NULL);
  g_signal_connect(G_OBJECT(menuitem_query_category_code), "activate", G_CALLBACK(query_category_code), NULL);
  /* --Query clothes menu */
  g_signal_connect(G_OBJECT(menuitem_query_clothes_all), "activate", G_CALLBACK(query_clothes_all), NULL);
  g_signal_connect(G_OBJECT(menuitem_query_clothes_name), "activate", G_CALLBACK(query_clothes_name), NULL);
  g_signal_connect(G_OBJECT(menuitem_query_clothes_code_price), "activate", G_CALLBACK(query_clothes_code_price), NULL);
  /* --Query order menu */
  g_signal_connect(G_OBJECT(menuitem_query_order_all), "activate", G_CALLBACK(query_order_all), NULL);
  g_signal_connect(G_OBJECT(menuitem_query_order_customer_date), "activate", G_CALLBACK(query_order_customer_date), NULL);
  g_signal_connect(G_OBJECT(menuitem_query_order_name_mark), "activate", G_CALLBACK(query_order_name_mark), NULL);

  /* -Maintenance menu */
  /* --Maintenance add menu */
  g_signal_connect(G_OBJECT(menuitem_maintenance_add_category), "activate", G_CALLBACK(maintenance_add_category), NULL);
  g_signal_connect(G_OBJECT(menuitem_maintenance_add_clothes), "activate", G_CALLBACK(maintenance_add_clothes), NULL);
  g_signal_connect(G_OBJECT(menuitem_maintenance_add_order), "activate", G_CALLBACK(maintenance_add_order), NULL);
  /* --Maintenance edit */
  g_signal_connect(G_OBJECT(menuitem_maintenance_edit), "activate", G_CALLBACK(maintenance_edit), NULL);
  /* --Maintenance delete */
  g_signal_connect(G_OBJECT(menuitem_maintenance_delete), "activate", G_CALLBACK(maintenance_delete), NULL);
  /* -Statistics menu */
  g_signal_connect(G_OBJECT(menuitem_statistics_category), "activate", G_CALLBACK(statistics_category), NULL);
  g_signal_connect(G_OBJECT(menuitem_statistics_year), "activate", G_CALLBACK(statistics_year), NULL);
  g_signal_connect(G_OBJECT(menuitem_statistics_customer), "activate", G_CALLBACK(statistics_customer), NULL);
  g_signal_connect(G_OBJECT(menuitem_statistics_quarter), "activate", G_CALLBACK(statistics_quarter), NULL);
  g_signal_connect(G_OBJECT(menuitem_statistics_all), "activate", G_CALLBACK(statistics_all), NULL);
  /* -Other menu */
  g_signal_connect(G_OBJECT(menuitem_other_about), "activate", G_CALLBACK(other_about), NULL);
  /* End Connect signals */

  /* Destroy builder */
  g_object_unref(G_OBJECT(builder));

  /* Show window */
  gtk_widget_show_all(GTK_WIDGET(window));
}

GtkWidget **create_message_dialog(GtkWindow *fwindow, char *messages, GtkMessageType type, GtkWidget **dialog_response){

  GtkButtonsType buttons;

  switch(type){
    case GTK_MESSAGE_ERROR: buttons = GTK_BUTTONS_OK; break;
    case GTK_MESSAGE_WARNING: buttons = GTK_BUTTONS_OK; break;
    case GTK_MESSAGE_QUESTION: buttons = GTK_BUTTONS_YES_NO; break;
  }

  GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;

  dialog_response[0] = GTK_WIDGET(gtk_message_dialog_new(
    fwindow,
    flags,
    type,
    buttons,
    messages));

  return dialog_response;
}

GtkWidget **create_edit_dialog(GtkWindow *fwindow, int rws, char argi[][100], GtkWidget **dialog_response){

  GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;

  dialog_response[0] = GTK_WIDGET(gtk_dialog_new_with_buttons(
    argi[0],
    window,
    flags,
    "确定", GTK_RESPONSE_ACCEPT,
    "取消", GTK_RESPONSE_REJECT,
    NULL));

  dialog_response[1] = gtk_grid_new();
  gtk_grid_insert_column(GTK_GRID(dialog_response[1]), 0);
  gtk_grid_insert_column(GTK_GRID(dialog_response[1]), 1);

  int i;
  for(i=0; i<rws; i++){
    gtk_grid_insert_row(GTK_GRID(dialog_response[1]), i);
  }

  gtk_grid_set_row_spacing(GTK_GRID(dialog_response[1]), 5);
  gtk_grid_set_column_spacing(GTK_GRID(dialog_response[1]), 5);

  for(i=1; i<=rws; i++){
    dialog_response[2*i] = gtk_label_new(argi[i]);
    dialog_response[2*i+1] = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(dialog_response[2*i+1]), argi[i+rws]);
    gtk_grid_attach(GTK_GRID(dialog_response[1]), dialog_response[2*i], 0, i, 1, 1);
    gtk_grid_attach(GTK_GRID(dialog_response[1]), dialog_response[2*i+1], 1, i, 1, 1);
  }

  gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog_response[0]))), dialog_response[1]);

  return dialog_response;
}

int category_create(Category **head ,char code, char name[], int clothes_count, Clothes *clothes){
  Category *tmp = NULL;
  tmp = (Category *)malloc(sizeof(Category));
  tmp->code = code;
  strcpy(tmp->name, name);
  tmp->clothes_count = clothes_count;
  tmp->clothes = clothes;
  tmp->__delete = &category_delete;


  tmp->next = *head;
  /* !Container
  if(*head){
    insert_into_container(&category_list_head, &(tmp->next));
  } else {
    insert_into_container(&category_list_head, head);
  }
  */
  *head = tmp;

  return 1;
}

int clothes_create(Clothes **head, char name[], char type, float price, int order_count, float mark, Category *category, Order *order){
  Clothes *tmp = NULL;
  tmp = (Clothes *)malloc(sizeof(Clothes));
  strcpy(tmp->name, name);
  tmp->type = type;
  tmp->price = price;
  tmp->order_count = order_count;
  tmp->mark = mark;
  tmp->category = category;
  tmp->order = order;
  tmp->__delete = &clothes_delete;

  tmp->next = *head;
  /* !Container
  if(*head){
    insert_into_container(&clothes_list_head, (void *)&(tmp->next));
  } else {
    insert_into_container(&clothes_list_head, (void *)head);
  }
  */
  *head = tmp;

  /* edit the category stats */
  (category->clothes_count)++;

  return 1;
}

int order_create(Order **head, char date[], char name[], int mark, Clothes *clothes){
  Order *tmp = NULL;
  tmp = (Order *)malloc(sizeof(Order));
  strcpy(tmp->date, date);
  strcpy(tmp->name, name);
  tmp->mark = mark;
  tmp->clothes = clothes;
  tmp->__delete = &order_delete;

  tmp->next = *head;
  /* !Container
  if(*head){
    insert_into_container(&order_list_head, (void *)&(tmp->next));
  } else {
    insert_into_container(&order_list_head, (void *)head);
  }
  */
  *head = tmp;

  /* edit the clothes stats */
  tmp->clothes->mark = (tmp->clothes->mark * tmp->clothes->order_count + mark) / (tmp->clothes->order_count + 1.0);
  (tmp->clothes->order_count)++;

  return 1;
}

int customer_create(Customer **head, char name[], int order_count, float money_count, float mark){
  Customer *tmp = NULL;
  tmp = (Customer *)malloc(sizeof(Customer));
  strcpy(tmp->name, name);
  tmp->order_count = order_count;
  tmp->money_count = money_count;
  tmp->mark = mark;

  tmp->next = *head;
  *head = tmp;

  return 1;
}

/* !Container
void insert_into_container(Container **head, void *data){
  Container *temp = NULL;
  temp = (Container *)malloc(sizeof(Container));
  temp->data = data;
  if(*head){
    temp->next = *head;
  } else {
    temp->next = NULL;
  }
  *head = temp;
}
*/

/* !Container
int data_delete(Container **self, int type){
*/
int data_delete(){
  /* delete target data */
  // self: target struct pointer

  Category **category_itor = &(category_head);
  while(*category_itor){
    category_delete(category_itor);
  }

  return 1;
  /* delete container */
  /* !Container
  Container *needfree = *self;
  *self = needfree->next;
  free(needfree);
  needfree = NULL;
  return 1;
  */
}

int category_delete(void *self){
  error_out("category_delete called.");
  /* init */
  Category **target = (Category **)self;
  Category *needfreeca = *target;

  /* delete clothes */
  Clothes **clothes_itor = &(needfreeca->clothes);
  while(*clothes_itor){
    clothes_delete(clothes_itor);
  }

  /* delete self */
  *target = needfreeca->next;
  free(needfreeca);
  needfreeca = NULL;

  return 1;
}

int clothes_delete(void *self){
  /* init */
  Clothes **target = (Clothes **)self;
  Clothes *needfreecl = *target;

  /* delete clothes */
  Order **order_itor = &(needfreecl->order);
  while(*order_itor){
    order_delete(order_itor);
  }

  /* delete self */
  ((*target)->category->clothes_count)--;
  *target = needfreecl->next;
  free(needfreecl);
  needfreecl = NULL;

  return 1;
}

int order_delete(void *self){
  /* init */
  Order **target = (Order **)self;
  Order *needfreeor = *target;

  /* delete self */
  ((*target)->clothes->order_count)--;
  *target = needfreeor->next;
  free(needfreeor);
  needfreeor = NULL;

  return 1;
}

int customer_delete(void *self){
  Customer **target = (Customer **)self;
  Customer *needfreecu = *target;

  *target = needfreecu->next;
  free(needfreecu);
  needfreecu = NULL;

  return 1;
}

Category **category_search(char code){
  Category **category_itor = &category_head;
  while(*category_itor){
    if((*category_itor)->code == code){
      return category_itor;
    }
    category_itor = &((*category_itor)->next);
  }

  return NULL;
}

Clothes **clothes_search(char name[30]){
  Category **category_itor = &category_head;
  while(*category_itor){
    Clothes **clothes_itor = &((*category_itor)->clothes);
    while(*clothes_itor){
      if(!strcmp((*clothes_itor)->name, name)){
        return clothes_itor;
      }
      clothes_itor = &((*clothes_itor)->next);
    }
    category_itor = &((*category_itor)->next);
  }
  
  return NULL;
}

Customer **customer_search(Customer **head, char name[20]){
  while(*head){
    if(!strcmp((*head)->name, name)){
      return head;
    }
    head = &((*head)->next);
  }
  return NULL;
}

void data_out(){
  Category *category_itor = category_head;
  while(category_itor){
    g_print("--------------------------\n");
    g_print("Category:\n code: %c\n name: %s\n clothes_count: %d \n", category_itor->code, category_itor->name, category_itor->clothes_count);

    Clothes *clothes_itor = category_itor->clothes;
    while(clothes_itor){
      g_print("--------------------------\n");
      g_print("Clothes:\n category_name: %s\n name: %s\n type: %c\n price: %f\n mark: %f\n order_count: %d\n",
              clothes_itor->category->name, clothes_itor->name, clothes_itor->type, clothes_itor->price, clothes_itor->mark, clothes_itor->order_count);

      Order *order_itor = clothes_itor->order;
      while(order_itor){
        g_print("--------------------------\n");
        g_print("Order:\n date: %s\n name: %s\n mark: %d\n",
                order_itor->date, order_itor->name, order_itor->mark);
        order_itor = order_itor->next;
      }
      clothes_itor = clothes_itor->next;
    }
    category_itor = category_itor->next;
  }
  g_print("--------------------------\n");
}

void create_list_store(GtkListStore **liststore, int type){
  if(type == CATEGORY_ALL){
    *liststore = gtk_list_store_new(
      CATEGORY_ALL_COLUMNS,
      G_TYPE_POINTER,
      G_TYPE_INT,
      G_TYPE_STRING, //CATEGORY_ALL_CODE
      G_TYPE_STRING, //CATEGORY_ALL_NAME
      G_TYPE_INT     //CATEGORY_ALL_CLOTHES_COUNT
    );
  } else if (type == CLOTHES_ALL){
    *liststore = gtk_list_store_new(
      CLOTHES_ALL_COLUMNS,
      G_TYPE_POINTER,
      G_TYPE_INT,
      G_TYPE_STRING, //CLOTHES_ALL_CODE
      G_TYPE_STRING, //CLOTHES_ALL_NAME
      G_TYPE_STRING, //CLOTHES_ALL_CTYPE
      G_TYPE_FLOAT,  //CLOTHES_ALL_PRICE
      G_TYPE_FLOAT,  //CLOTHES_ALL_MARK
      G_TYPE_INT     //CLOTHES_ALL_ORDER_COUNT
    );
  } else if (type == ORDER_ALL){
    *liststore = gtk_list_store_new(
      ORDER_ALL_COLUMNS,
      G_TYPE_POINTER,
      G_TYPE_INT,
      G_TYPE_STRING, //ORDER_ALL_CNAME
      G_TYPE_STRING, //ORDER_ALL_DATE
      G_TYPE_STRING, //ORDER_ALL_NAME
      G_TYPE_INT     //ORDER_ALL_MARK
    );
  } else if(type == CATEGORY_STATS){
    *liststore = gtk_list_store_new(
      CATEGORY_STATS_COLUMNS,
      G_TYPE_POINTER,
      G_TYPE_INT,
      G_TYPE_STRING, //CATEGORY_STATS_CODE
      G_TYPE_STRING, //CATEGORY_STATS_NAME
      G_TYPE_INT,    //CATEGORY_STATS_ORDER_COUNT
      G_TYPE_FLOAT,  //CATEGORY_STATS_SALES_COUNT
      G_TYPE_INT,    //CATEGORY_STATS_MARKL3_COUNT
      G_TYPE_INT     //CATEGORY_STATS_MARKG3_COUNT
    );   
  } else if(type == CLOTHES_YEAR){
    *liststore = gtk_list_store_new(
      CLOTHES_YEAR_COLUMNS,
      G_TYPE_POINTER,
      G_TYPE_INT,
      G_TYPE_STRING, //CLOTHES_YEAR_NAME
      G_TYPE_STRING, //CLOTHES_YEAR_CNAME
      G_TYPE_INT,    //CLOTHES_YEAR_ORDER_COUNT
      G_TYPE_FLOAT,  //CLOTHES_YEAR_SALES_COUNT
      G_TYPE_FLOAT   //CLOTHES_YEAR_MARK
    );   
  } else if(type == CUSTOMER_STATS){
    *liststore = gtk_list_store_new(
      CUSTOMER_STATS_COLUMNS,
      G_TYPE_POINTER,
      G_TYPE_INT,
      G_TYPE_STRING, //CUSTOMER_STATS_NAME
      G_TYPE_INT,    //CUSTOMER_STATS_ORDER_COUNT
      G_TYPE_FLOAT,  //CUSTOMER_STATS_MONEY_COUNT
      G_TYPE_FLOAT   //CUSTOMER_STATS_MARK
    );  
  } else if(type == ALL_STATS){
    *liststore = gtk_list_store_new(
      CUSTOMER_STATS_COLUMNS,
      G_TYPE_POINTER,
      G_TYPE_INT,
      G_TYPE_INT,    //ALL_STATS_ORDER_COUNT
      G_TYPE_FLOAT,  //ALL_STATS_SALES_COUNT
      G_TYPE_INT,    //ALL_STATS_MARKL3_COUNT
      G_TYPE_INT     //ALL_STATS_MARKG3_COUNT
    );  
  }
}

void insert_into_list_store(GtkListStore **liststore, void *data, int type){
  GtkTreeIter iter;
  if(type == CATEGORY_ALL){
    Category **category_itor = (Category **)data;
    gtk_list_store_append(*liststore, &iter);
    gtk_list_store_set(
      *liststore, &iter,
      CATEGORY_ALL_POINTER, category_itor,
      CATEGORY_ALL_TYPE, TYPE_CATEGORY,
      CATEGORY_ALL_CODE, string((*category_itor)->code),
      CATEGORY_ALL_NAME, (*category_itor)->name,
      CATEGORY_ALL_CLOTHES_COUNT, (*category_itor)->clothes_count,
      -1);
  } else if(type == CLOTHES_ALL){
    Clothes **clothes_itor = (Clothes **)data;
    gtk_list_store_append(*liststore, &iter);
    gtk_list_store_set(
      *liststore, &iter,
      CLOTHES_ALL_POINTER, clothes_itor,
      CLOTHES_ALL_TYPE, TYPE_CLOTHES,
      CLOTHES_ALL_CODE, string((*clothes_itor)->category->code),
      CLOTHES_ALL_NAME, (*clothes_itor)->name,
      CLOTHES_ALL_CTYPE, ctype_to_string((*clothes_itor)->type),
      CLOTHES_ALL_PRICE, (*clothes_itor)->price,
      CLOTHES_ALL_MARK, (*clothes_itor)->mark,
      CLOTHES_ALL_ORDER_COUNT, (*clothes_itor)->order_count,
      -1);
  } else if(type == ORDER_ALL){
    Order **order_itor = (Order **)data;
    gtk_list_store_append(*liststore, &iter);
    gtk_list_store_set(
      *liststore, &iter,
      ORDER_ALL_POINTER, order_itor,
      ORDER_ALL_TYPE, TYPE_ORDER,
      ORDER_ALL_CNAME, (*order_itor)->clothes->name,
      ORDER_ALL_DATE, (*order_itor)->date,
      ORDER_ALL_NAME, (*order_itor)->name,
      ORDER_ALL_MARK, (*order_itor)->mark,
      -1);
  }
}

void append_column(char column_title[][20], int column_line[], int cls){
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  renderer = gtk_cell_renderer_text_new();
  int i = 0;
  for(i=0; i<cls; i++){
    column = gtk_tree_view_column_new_with_attributes(
      column_title[i],
      renderer,
      "text", column_line[i],
      NULL);
    gtk_tree_view_column_set_sort_column_id(column, column_line[i]);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
  }
}

void create_column(int type){
  if(type == CATEGORY_ALL){
    char column_title[3][20] = {"分类编码", "分类名称", "服装数"};
    int column_line[3] = {CATEGORY_ALL_CODE, CATEGORY_ALL_NAME, CATEGORY_ALL_CLOTHES_COUNT};
    int cls = 3;
    append_column(column_title, column_line, cls);
  } else if(type == CLOTHES_ALL){ 
    char column_title[6][20] = {"分类编码", "服装名称", "式样", "单价", "评价指数", "售出件数"};
    int column_line[6] = {CLOTHES_ALL_CODE, CLOTHES_ALL_NAME, CLOTHES_ALL_CTYPE, CLOTHES_ALL_PRICE, CLOTHES_ALL_MARK, CLOTHES_ALL_ORDER_COUNT};
    int cls = 6;
    append_column(column_title, column_line, cls);
  } else if(type == ORDER_ALL){
    char column_title[4][20] = {"服装名称", "销售日期", "客户名称", "客户评价"};
    int column_line[4] = {ORDER_ALL_CNAME, ORDER_ALL_DATE, ORDER_ALL_NAME, ORDER_ALL_MARK};
    int cls = 4;
    append_column(column_title, column_line, cls);
  } else if(type == CATEGORY_STATS){
    char column_title[6][20] = {"分类编码", "分类名称", "销售总件数", "销售总额", "评价>=3件数", "评价<3件数"};
    int column_line[6] = {CATEGORY_STATS_CODE, CATEGORY_STATS_NAME, CATEGORY_STATS_ORDER_COUNT, CATEGORY_STATS_SALES_COUNT, CATEGORY_STATS_MARKL3_COUNT, CATEGORY_STATS_MARKG3_COUNT};
    int cls = 6;
    append_column(column_title, column_line, cls);
  } else if(type == CLOTHES_YEAR){
    char column_title[5][20] = {"服装名称", "分类名称", "售出件数", "销售金额", "评价指数"};
    int column_line[5] = {CLOTHES_YEAR_NAME, CLOTHES_YEAR_CNAME, CLOTHES_YEAR_ORDER_COUNT, CLOTHES_YEAR_SALES_COUNT, CLOTHES_YEAR_MARK};
    int cls = 5;
    append_column(column_title, column_line, cls);
  } else if(type == CUSTOMER_STATS){
    char column_title[4][20] = {"客户名称", "所购服装总数", "消费总金额", "总体评价度"};
    int column_line[4] = {CUSTOMER_STATS_NAME, CUSTOMER_STATS_ORDER_COUNT, CUSTOMER_STATS_MONEY_COUNT, CUSTOMER_STATS_MARK};
    int cls = 4;
    append_column(column_title, column_line, cls);
  } else if(type ==ALL_STATS){
    char column_title[4][20] = {"销售总件数", "销售总额", "评价>=3件数", "评价<3件数"};
    int column_line[4] = {ALL_STATS_ORDER_COUNT, ALL_STATS_SALES_COUNT, ALL_STATS_MARKL3_COUNT, ALL_STATS_MARKG3_COUNT};
    int cls = 4;
    append_column(column_title, column_line, cls);
  }
}

void clean_column(){
  int columns;
  GtkTreeViewColumn *column;
  columns = gtk_tree_view_get_n_columns(treeview);

  while(columns){
    column = gtk_tree_view_get_column(treeview, 0);
    gtk_tree_view_remove_column(treeview, column);
    columns--;
  }  
}

char *string(char code){
  char *str = (char *)malloc(sizeof(char) * 2);
  str[0] = code;
  str[1] = '\0';
  return str;
}

char *ctype_to_string(char type){
  char *target = (char *)malloc(sizeof(char) * (2*3 + 1));
  switch(type){
    case '0': strcpy(target, "男式");break;
    case '1': strcpy(target, "女式");break;
    case '9': strcpy(target, "中性");break;
  }
  return target;
}

char string_to_ctype(char *str){
  if( !(strcmp(str, "男式") && strcmp(str, "0")) ){
    return '0';
  } else if( !(strcmp(str, "女式") && strcmp(str, "1")) ){
    return '1';
  } else if( !(strcmp(str, "中性") && strcmp(str, "9")) ){
    return '9';
  } else {
    return 'n';
  }
}

int is_leap_year(int year){
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int date_check(int date){
  int year = date / 10000;
  int month = (date % 10000) / 100;
  int day = date % 100;
  int day_max;
  if(month<1 || month >12){
    return 0;
  }
  switch(month){
    case 1: case 3: case 5: case 7: case 8: case 10: case 12: day_max = 31; break;
    case 4: case 6: case 9: case 11: day_max = 30; break;
    case 2: is_leap_year(year)? (day_max = 29): (day_max = 28); break;
  }
  if(day<1 || day>day_max){
    return 0;
  }
  return 1;
}

int date_get_quarter(int date){
  int month = (date % 10000) / 100;
  return (month-1) / 3;
}

/* End Helper function */

/* Basic I/O */

int save_file(){
  error_out("save_file called.");
  if(!file){
    error_out("save_file: No file loaded.");
    return 0;
  } else {
    Category *category_itor = category_head;

    if(category_itor){
      /* clean file */
      error_out("save_file: clean original file.");
      ftruncate(fileno(file), 0);
    }

    rewind(file);
    while(category_itor){
      fwrite(category_itor, sizeof(Category), 1, file);

      Clothes *clothes_itor = category_itor->clothes;
      while(clothes_itor){
        fwrite(clothes_itor, sizeof(Clothes), 1, file);

        Order *order_itor = clothes_itor->order;
        while(order_itor){
          fwrite(order_itor, sizeof(Order), 1, file);
          order_itor = order_itor->next;
        }

        clothes_itor = clothes_itor->next;
      }

      category_itor = category_itor->next;
    }
    updated = TRUE;
    error_out("save_file: finished saving.");
    return 1;
  }
}

void open_file(char *filename){
  error_out("open_file called.");
  file = fopen(filename, "rb+");
}

int load_file(){
  error_out("load_file called.");
  if(!file){
    error_out("load_file: No file opened.");
    return 0;
  } else {
    /* the ways to load category, clothes, or order are same */
    /* if you want to see how it works, search "load order" is enough */

    /* load category */
    if(!feof(file)){
      int count = 0;
      Category *load_category_head = NULL, *load_category_tail = NULL, *load_category_temp = NULL;
      load_category_head = (Category *)malloc(sizeof(Category));
      load_category_tail = load_category_head;
      load_category_temp = NULL;

      do{
        /* load current category */
        if(!fread(load_category_tail, sizeof(Category), 1, file)){
          /* load failed, file ended */
          break;
        }
        count++;
        load_category_tail->__delete = &category_delete;

          /* load clothes */
          if(load_category_tail->clothes_count){
            Clothes *load_clothes_head = NULL, *load_clothes_tail = NULL, *load_clothes_temp = NULL;
            load_clothes_head = (Clothes *)malloc(sizeof(Clothes));
            load_clothes_tail = load_clothes_head;
            load_clothes_temp = NULL;

            int clothes_processed = 0;

            do{
              /* load current clothes */
              fread(load_clothes_tail, sizeof(Clothes), 1, file);
              load_clothes_tail->category = load_category_tail;
              load_clothes_tail->__delete = &clothes_delete;


                /* load order */
                if(load_clothes_tail->order_count){
                  Order *load_order_head = NULL, *load_order_tail = NULL, *load_order_temp = NULL;
                  load_order_head = (Order *)malloc(sizeof(Order));
                  load_order_tail = load_order_head;
                  load_order_temp = NULL;

                  int order_processed = 0;

                  do{
                    /* load current order */
                    fread(load_order_tail, sizeof(Order), 1, file);
                    load_order_tail->clothes = load_clothes_tail;
                    load_order_tail->__delete = &order_delete;
                    /* end load current order */
                    /* prepare for next order */
                    order_processed++;
                    load_order_temp = load_order_tail;
                    load_order_tail->next = (Order *)malloc(sizeof(Order));
                    //insert_into_container(&order_list_head, (void *)&(load_order_tail->next));
                    load_order_tail = load_order_tail->next;
                  } while(order_processed < load_clothes_tail->order_count);
                  load_order_temp->next = NULL;
                  free(load_order_tail);
                  load_order_tail = NULL;

                  load_clothes_tail->order = load_order_head;
                  //order_list_head->data = (void *)&(load_clothes_tail->order);
                } else {
                  load_clothes_tail->order = NULL;
                }
                /* end load order */
              
              /* end load current clothes */
              /* prepare for next clothes */
              clothes_processed++;
              load_clothes_temp = load_clothes_tail;
              load_clothes_tail->next = (Clothes *)malloc(sizeof(Clothes));
              //insert_into_container(&clothes_list_head, (void *)&(load_clothes_tail->next));
              load_clothes_tail = load_clothes_tail->next;
            } while(clothes_processed < load_category_tail->clothes_count);
            load_clothes_temp->next = NULL;
            free(load_clothes_tail);
            load_clothes_tail = NULL;

            load_category_tail->clothes = load_clothes_head;
            //clothes_list_head->data = (void *)&(load_category_tail->clothes);
          } else {
            load_category_tail->clothes = NULL;
          }
          /* end load clothes */

        /* end load current category */
        /* prepare for next category */
        load_category_temp = load_category_tail;
        load_category_tail->next = (Category *)malloc(sizeof(Category));
        //insert_into_container(&category_list_head, (void *)&(load_category_tail->next));
        load_category_tail = load_category_tail->next;
      } while(!feof(file));
      free(load_category_tail);
      load_category_tail = NULL;

      if(count){
        load_category_temp->next = NULL;
        category_head = load_category_head;
        //category_list_head->data = (void *)&(category_head);
      } else {
        category_head = NULL;
      }
    } else {
      category_head = NULL;
    }
    /* end load category */

    error_out("load_file: finished loading.");
    return 1;
  }
}

void close_file(){
  error_out("close_file called.");
  if(file){
    fclose(file);
    file = NULL;
  }
}

char *file_choose(int type){
  error_out("file_choose called.");
  GtkWidget *dialog = NULL;
  GtkFileChooser *chooser = NULL;

  if(type == FILE_CHOOSE_OPEN){
    dialog = gtk_file_chooser_dialog_new(
      "打开", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
      "取消", GTK_RESPONSE_CANCEL,
      "确定", GTK_RESPONSE_ACCEPT, NULL);
  } else if(type == FILE_CHOOSE_SAVE){
    dialog = gtk_file_chooser_dialog_new(
      "保存", NULL, GTK_FILE_CHOOSER_ACTION_SAVE,
      "取消", GTK_RESPONSE_CANCEL,
      "确定", GTK_RESPONSE_ACCEPT, NULL);
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);
  } else if(type == FILE_CHOOSE_SAVE_AS){
    dialog = gtk_file_chooser_dialog_new(
      "另存为", NULL, GTK_FILE_CHOOSER_ACTION_SAVE,
      "取消", GTK_RESPONSE_CANCEL,
      "确定", GTK_RESPONSE_ACCEPT, NULL);
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);
  }

  if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT){
    char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

    error_out(filename);

    gtk_widget_destroy(dialog);
    return filename;
  } else {
    gtk_widget_destroy(dialog);
    return NULL;
  }

}

void file_new(){
  error_out("file_new called.");
  close_file();
  clean_var();

  /* for test */
  g_print("Add C1\n");
  category_create(&category_head, '1', "a", 0, NULL);
  data_out();
  g_print("Add CL1\n");
  clothes_create(&(category_head->clothes), "clothes 1", '1', 233, 0, 0, category_head, NULL);
  data_out();
  g_print("Add O1\n");
  order_create(&(category_head->clothes->order), "23333333", "熊猫", 3, category_head->clothes);
  data_out();
  g_print("Add O2\n");
  order_create(&(category_head->clothes->order), "33333333", "熊猫2", 5, category_head->clothes);
  data_out();
  g_print("Add O3\n");
  order_create(&(category_head->clothes->order), "13333333", "熊猫3", 4, category_head->clothes);
  data_out();
  g_print("Add CL2\n");
  clothes_create(&(category_head->clothes), "clothes 2", '1', 233, 0, 0, category_head, NULL);
  data_out();
  g_print("Add C2\n");
  category_create(&category_head, '2', "yoo", 0, NULL);
  data_out();
  g_print("Add C3\n");
  category_create(&category_head, '3', "!o", 0, NULL);
  data_out();


  g_print("Del O1\n");
  order_delete(&(category_head->next->next->clothes->next->order->next->next));
  data_out();

  g_print("Del CL1\n");
  clothes_delete(&(category_head->next->next->clothes->next));
  data_out();

  g_print("Del C1\n");
  category_delete(&(category_head->next->next));
  data_out();

  g_print("Del All\n");
  data_delete();
  data_out();


  g_print("Add C1\n");
  category_create(&category_head, '1', "a", 0, NULL);
  g_print("Add CL1\n");
  clothes_create(&(category_head->clothes), "喵", '1', 233, 0, 0, category_head, NULL);
  g_print("Add O1\n");
  order_create(&(category_head->clothes->order), "23333333", "熊猫", 3, category_head->clothes);
  g_print("Add O2\n");
  order_create(&(category_head->clothes->order), "33333333", "熊猫2", 5, category_head->clothes);
  g_print("Add O3\n");
  order_create(&(category_head->clothes->order), "13333333", "熊猫3", 4, category_head->clothes);
  g_print("Add CL2\n");
  clothes_create(&(category_head->clothes), "clothes 2", '1', 233, 0, 0, category_head, NULL);
  g_print("Add CL3\n");
  clothes_create(&(category_head->clothes), "clothes 3", '1', 233, 0, 0, category_head, NULL);
  g_print("Add C2\n");
  category_create(&category_head, '2', "yoo", 0, NULL);
  g_print("Add C3\n");
  category_create(&category_head, '3', "!o", 0, NULL);
  //data_out();

  Category *result_category = *category_search('3');
  Clothes *result_clothes = *clothes_search("喵");
  //Clothes *result_clothes = *clothes_search("clothes 2");
  g_print("Category:\n code: %c\n", (result_category)->code);
  g_print("Clothes:\n name: %s\n", (result_clothes)->name);
  data_out();
  
  result_category = *category_search('1');

  /*
  g_print("Del C3\n");
  data_delete(&category_head, TYPE_CATEGORY);
  data_out();
  g_print("Del C1\n");
  data_delete(&(category_head->next), TYPE_CATEGORY);
  data_out();
  */
}

void file_open(){
  error_out("file_open called.");

  char *filename = file_choose(FILE_CHOOSE_OPEN);
  if(filename){
    if(file){
      close_file();
      clean_var();
    }
    open_file(filename);
    if(file){
      if(!load_file()){
        error_out("Load failed.");
      }
    } else {
      error_out("Open failed.");
    }
  } else {
    error_out("Open failed.");
  }
  free(filename);
  filename = NULL;
}

void file_save(){
  error_out("file_save called.");
  data_out();
  short save_error;
  if(file){
    if(!save_file()){
      save_error = 1;
    }
  } else {
    char *filename = file_choose(FILE_CHOOSE_SAVE);
    if(filename){
      file = fopen(filename, "wb+");
      if( !(file && save_file()) ){
        save_error = 1;
      }
    }
    free(filename);
    filename = NULL;
  }

  if(save_error){
    error_out("Save failed.");
  }
}

void file_save_as(){
  error_out("file_save_as called.");
  g_print("CH: %c%s%d\n", category_head->code, category_head->name, category_head->clothes_count);
  char *filename = file_choose(FILE_CHOOSE_SAVE_AS);
  if(filename){
    close_file();
    file = fopen(filename, "wb+");
    if( !(file && save_file()) ){
      error_out("Save failed.");
    }
  }

  free(filename);
  filename = NULL;
}

void file_quit(){
  error_out("file_quit called.");
  close_file();
  gtk_main_quit();
}
/* End Basic I/O */



/* Query */

void query_category_all(void *pass, int call_type){
  error_out("query_category_all called");
  last_func = &query_category_all;
  clean_column();

  GtkListStore *liststore;
  create_list_store(&liststore, CATEGORY_ALL);

  Category **category_itor = &category_head;
  while(*category_itor){
    /*
    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(
    liststore, &iter,
    CATEGORY_ALL_POINTER, category_itor,
    CATEGORY_ALL_TYPE, TYPE_CATEGORY,
    CATEGORY_ALL_CODE, string((*category_itor)->code),
    CATEGORY_ALL_NAME, (*category_itor)->name,
    CATEGORY_ALL_CLOTHES_COUNT, (*category_itor)->clothes_count,
    -1);
    */
    insert_into_list_store(&liststore, category_itor, CATEGORY_ALL);
    category_itor = &((*category_itor)->next);
  }

  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
  /*
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  renderer = gtk_cell_renderer_text_new();
  char column_title[3][20] = {"分类编码", "分类名称", "服装数"};
  int column_line[3] = {CATEGORY_ALL_CODE, CATEGORY_ALL_NAME, CATEGORY_ALL_CLOTHES_COUNT};
  int i = 0;
  for(i=0; i<3; i++){
    column = gtk_tree_view_column_new_with_attributes(
      column_title[i],
      renderer,
      "text", column_line[i],
      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
  }
  */
  create_column(CATEGORY_ALL);
}

void query_clothes_all(void *pass, int call_type){
  error_out("query_clothes_all called");
  last_func = &query_clothes_all;
  clean_column();

  GtkListStore *liststore;
  create_list_store(&liststore, CLOTHES_ALL);

  Category **category_itor = &category_head;
  while(*category_itor){
    Clothes **clothes_itor = &((*category_itor)->clothes);
    while(*clothes_itor){
      /*
      gtk_list_store_append(liststore, &iter);
      gtk_list_store_set(
      liststore, &iter,
      CLOTHES_ALL_POINTER, clothes_itor,
      CLOTHES_ALL_TYPE, TYPE_CLOTHES,
      CLOTHES_ALL_CODE, string((*category_itor)->code),
      CLOTHES_ALL_NAME, (*clothes_itor)->name,
      CLOTHES_ALL_CTYPE, ctype_to_string((*clothes_itor)->type),
      CLOTHES_ALL_PRICE, (*clothes_itor)->price,
      CLOTHES_ALL_MARK, (*clothes_itor)->mark,
      CLOTHES_ALL_ORDER_COUNT, (*clothes_itor)->order_count,
      -1);
      */
      insert_into_list_store(&liststore, clothes_itor, CLOTHES_ALL);
      clothes_itor = &((*clothes_itor)->next);
    }
    category_itor = &((*category_itor)->next);
  }

  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
  /*
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  renderer = gtk_cell_renderer_text_new();
  char column_title[6][20] = {"分类编码", "服装名称", "式样", "单价", "评价指数", "售出件数"};
  int column_line[6] = {CLOTHES_ALL_CODE, CLOTHES_ALL_NAME, CLOTHES_ALL_CTYPE, CLOTHES_ALL_PRICE, CLOTHES_ALL_MARK, CLOTHES_ALL_ORDER_COUNT};
  int i = 0;
  for(i=0; i<6; i++){
    column = gtk_tree_view_column_new_with_attributes(
      column_title[i],
      renderer,
      "text", column_line[i],
      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
  }
  */
  create_column(CLOTHES_ALL);
}

void query_order_all(void *pass, int call_type){
  error_out("query_order_all called");
  last_func = &query_order_all;
  clean_column();

  GtkListStore *liststore;
  create_list_store(&liststore, ORDER_ALL);

  Category **category_itor = &category_head;
  while(*category_itor){
    Clothes **clothes_itor = &((*category_itor)->clothes);
    while(*clothes_itor){
      Order **order_itor = &((*clothes_itor)->order);
      while(*order_itor){
        /*
        gtk_list_store_append(liststore, &iter);
        gtk_list_store_set(
        liststore, &iter,
        ORDER_ALL_POINTER, order_itor,
        ORDER_ALL_TYPE, TYPE_ORDER,
        ORDER_ALL_CNAME, (*order_itor)->clothes->name,
        ORDER_ALL_DATE, (*order_itor)->date,
        ORDER_ALL_NAME, (*order_itor)->name,
        ORDER_ALL_MARK, (*order_itor)->mark,
        -1);
        */
        insert_into_list_store(&liststore, order_itor, ORDER_ALL);
        order_itor = &((*order_itor)->next);
      }
      clothes_itor = &((*clothes_itor)->next);
    }
    category_itor = &((*category_itor)->next);
  }

  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
  /*
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  renderer = gtk_cell_renderer_text_new();
  char column_title[4][20] = {"服装名称", "销售日期", "客户名称", "客户评价"};
  int column_line[4] = {ORDER_ALL_CNAME, ORDER_ALL_DATE, ORDER_ALL_NAME, ORDER_ALL_MARK};
  int i = 0;
  for(i=0; i<4; i++){
    column = gtk_tree_view_column_new_with_attributes(
      column_title[i],
      renderer,
      "text", column_line[i],
      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
  }
  */
  create_column(ORDER_ALL);
}

void query_category_code(void *pass, int call_type){
  static char code;
  int success = 0;

  if(call_type != CALL_TYPE_REDO){
    int rws = 1;
    char title[100];
    char argi[rws*2+1][100];
    strcpy(argi[0], "查询服装分类");
    strcpy(argi[1], "分类编码");
    strcpy(argi[2], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    GtkEntryBuffer *buffer;
    GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
      validate_message[0] = '\0';
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
      code = gtk_entry_buffer_get_text(buffer)[0];

      /* error check */
      if(!code){
        strcpy(validate_message, "请输入完数据");
      }
      if(validate_message[0] == '\0' && (code<'1' || code>'5')){
        strcpy(validate_message, "分类编码错误(1-5)");
      }

      if(validate_message[0] != '\0'){
        warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
        gtk_widget_show_all(warning_dialog[0]);
        gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
        gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
        continue;
      }
      /* end error check */

      success = 1;
      break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));
    
    free(warning_dialog);
    free(dialog_result);
  }

  if(success || call_type == CALL_TYPE_REDO){
    last_func = &query_category_code;
    clean_column();

    GtkListStore *liststore;
    create_list_store(&liststore, CATEGORY_ALL);

    Category **category_itor = category_search(code);
    if(category_itor){
      insert_into_list_store(&liststore, category_itor, CATEGORY_ALL);
    }
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
    create_column(CATEGORY_ALL);
  }
}

void query_clothes_name(void *pass, int call_type){
  static char name[30];
  int success = 0;

  if(call_type != CALL_TYPE_REDO){
    int rws = 1;
    char title[100];
    char argi[rws*2+1][100];
    strcpy(argi[0], "查询服装信息");
    strcpy(argi[1], "服装名称");
    strcpy(argi[2], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    char us_name[1000];
    GtkEntryBuffer *buffer;
    GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
      validate_message[0] = '\0';
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
      strcpy(us_name, gtk_entry_buffer_get_text(buffer));

      /* error check */
      if(!us_name){
        strcpy(validate_message, "请输入完数据");
      }
      if(validate_message[0] == '\0' && strlen(us_name) > 30){
        strcpy(validate_message, "服装名称过长");
      }

      if(validate_message[0] != '\0'){
        warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
        gtk_widget_show_all(warning_dialog[0]);
        gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
        gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
        continue;
      }
      /* end error check */

      strcpy(name, us_name);
      success = 1;
      break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));
    
    free(warning_dialog);
    free(dialog_result);
  }

  if(success || call_type == CALL_TYPE_REDO){
    last_func = &query_clothes_name;
    clean_column();

    GtkListStore *liststore;
    create_list_store(&liststore, CLOTHES_ALL);

    Category **category_itor = &category_head;
    while(*category_itor){
      Clothes **clothes_itor = &((*category_itor)->clothes);
      while(*clothes_itor){
        if(strstr((*clothes_itor)->name, name)){
          insert_into_list_store(&liststore, clothes_itor, CLOTHES_ALL);
        }
        clothes_itor = &((*clothes_itor)->next);
      }
      category_itor = &((*category_itor)->next);
    }
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
    create_column(CLOTHES_ALL);
  }
}

void query_clothes_code_price(void *pass, int call_type){
  static char code;
  static float price_max;
  static float price_min;
  int success = 0;

  if(call_type != CALL_TYPE_REDO){
    int rws = 3;
    char title[100];
    char argi[rws*2+1][100];
    strcpy(argi[0], "查询服装信息");
    strcpy(argi[1], "分类编码");
    strcpy(argi[2], "价格上限(包含)");
    strcpy(argi[3], "价格下限(包含)");
    strcpy(argi[4], "");
    strcpy(argi[5], "");
    strcpy(argi[6], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    GtkEntryBuffer *buffer;
    GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
      validate_message[0] = '\0';
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
      code = gtk_entry_buffer_get_text(buffer)[0];
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*2+1]));
      price_max = atof(gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*3+1]));
      price_min = atof(gtk_entry_buffer_get_text(buffer));

      /* error check */
      if(!code){
        strcpy(validate_message, "请输入完数据");
      }
      if(validate_message[0] == '\0' && (code<'1' || code>'5')){
        strcpy(validate_message, "分类编码错误(1-5)");
      }

      if(validate_message[0] != '\0'){
        warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
        gtk_widget_show_all(warning_dialog[0]);
        gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
        gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
        continue;
      }
      /* end error check */

      success = 1;
      break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));
    
    free(warning_dialog);
    free(dialog_result);
  }

  if(success || call_type == CALL_TYPE_REDO){
    last_func = &query_clothes_code_price;
    clean_column();

    GtkListStore *liststore;
    create_list_store(&liststore, CLOTHES_ALL);

    Category **category_itor = category_search(code);
    if(category_itor){
      Clothes **clothes_itor = &((*category_itor)->clothes);
      while(*clothes_itor){
        if( (!price_max || (*clothes_itor)->price <= price_max) &&
            (!price_min || (*clothes_itor)->price >= price_min) ){
          insert_into_list_store(&liststore, clothes_itor, CLOTHES_ALL);
        }
        clothes_itor = &((*clothes_itor)->next);
      }
    }
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
    create_column(CLOTHES_ALL);
  }
}

void query_order_customer_date(void *pass, int call_type){
  static char name[20];
  static int date_max;
  static int date_min;
  int success = 0;

  if(call_type != CALL_TYPE_REDO){
    int rws = 3;
    char title[100];
    char argi[rws*2+1][100];
    strcpy(argi[0], "查询销售信息");
    strcpy(argi[1], "顾客姓名");
    strcpy(argi[2], "销售日期上限(包含)");
    strcpy(argi[3], "销售日期下限(包含)");
    strcpy(argi[4], "");
    strcpy(argi[5], "");
    strcpy(argi[6], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    char us_name[1000];
    GtkEntryBuffer *buffer;
    GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
      validate_message[0] = '\0';
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
      strcpy(us_name, gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*2+1]));
      date_max = atoi(gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*3+1]));
      date_min = atoi(gtk_entry_buffer_get_text(buffer));

      /* error check */
      if(!name){
        strcpy(validate_message, "请输入完数据");
      }
      if(validate_message[0] == '\0' && strlen(us_name) > 20){
        strcpy(validate_message, "客户姓名过长");
      }
      if(validate_message[0] == '\0' && date_max && !date_check(date_max)){
        strcpy(validate_message, "日期错误(yyyymmdd)");
      }
      if(validate_message[0] == '\0' && date_min && !date_check(date_min)){
        strcpy(validate_message, "日期错误(yyyymmdd)");
      }

      if(validate_message[0] != '\0'){
        warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
        gtk_widget_show_all(warning_dialog[0]);
        gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
        gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
        continue;
      }
      /* end error check */

      strcpy(name, us_name);
      success = 1;
      break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));
    
    free(warning_dialog);
    free(dialog_result);
  }

  if(success || call_type == CALL_TYPE_REDO){
    last_func = &query_order_customer_date;
    clean_column();

    GtkListStore *liststore;
    create_list_store(&liststore, ORDER_ALL);

    Category **category_itor = &category_head;
    while(*category_itor){
      Clothes **clothes_itor = &((*category_itor)->clothes);
      while(*clothes_itor){
        Order **order_itor = &((*clothes_itor)->order);
        while(*order_itor){
          if( strstr((*order_itor)->name, name) &&
              (!date_max || atoi((*order_itor)->date) <= date_max) &&
              (!date_min || atoi((*order_itor)->date) >= date_min) ){
            insert_into_list_store(&liststore, order_itor, ORDER_ALL);
          }
          order_itor = &((*order_itor)->next);
        }
        clothes_itor = &((*clothes_itor)->next);
      }
      category_itor = &((*category_itor)->next);
    }
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
    create_column(ORDER_ALL);
  }
}


void query_order_name_mark(void *pass, int call_type){
  static char name[30];
  static float mark_max;
  static float mark_min;
  int success = 0;

  if(call_type != CALL_TYPE_REDO){
    int rws = 3;
    char title[100];
    char argi[rws*2+1][100];
    strcpy(argi[0], "查询销售信息");
    strcpy(argi[1], "服装名称");
    strcpy(argi[2], "服装评价上限(包含)");
    strcpy(argi[3], "服装评价下限(包含)");
    strcpy(argi[4], "");
    strcpy(argi[5], "");
    strcpy(argi[6], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    char us_name[1000];
    GtkEntryBuffer *buffer;
    GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
      validate_message[0] = '\0';
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
      strcpy(us_name, gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*2+1]));
      mark_max = atof(gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*3+1]));
      mark_min = atof(gtk_entry_buffer_get_text(buffer));

      /* error check */
      if(!name){
        strcpy(validate_message, "请输入完数据");
      }
      if(validate_message[0] == '\0' && strlen(us_name) > 30){
        strcpy(validate_message, "服装名称过长");
      }
      if(validate_message[0] == '\0' && mark_min && (mark_min<1 || mark_min>5)){
        strcpy(validate_message, "评分错误(1-5)");
      }
      if(validate_message[0] == '\0' && mark_max && (mark_max<1 || mark_max>5)){
        strcpy(validate_message, "评分错误(1-5)");
      }

      if(validate_message[0] != '\0'){
        warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
        gtk_widget_show_all(warning_dialog[0]);
        gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
        gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
        continue;
      }
      /* end error check */

      strcpy(name, us_name);
      success = 1;
      break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));
    
    free(warning_dialog);
    free(dialog_result);
  }

  if(success || call_type == CALL_TYPE_REDO){
    last_func = &query_order_name_mark;
    clean_column();

    GtkListStore *liststore;
    create_list_store(&liststore, ORDER_ALL);

    Category **category_itor = &category_head;
    while(*category_itor){
      Clothes **clothes_itor = &((*category_itor)->clothes);
      while(*clothes_itor){
        if( strstr((*clothes_itor)->name, name) &&
            (!mark_max || (*clothes_itor)->mark <= mark_max) &&
            (!mark_min || (*clothes_itor)->mark >= mark_min) ){
          Order **order_itor = &((*clothes_itor)->order);
          while(*order_itor){
            insert_into_list_store(&liststore, order_itor, ORDER_ALL);
            order_itor = &((*order_itor)->next);
          }
        }
        clothes_itor = &((*clothes_itor)->next);
      }
      category_itor = &((*category_itor)->next);
    }
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
    create_column(ORDER_ALL);
  }
}
/* End Query */

/* Maintenance */

int maintenance_category_dialog(void *self){
  /* init */
  
  Category **category = (Category **)self;
  /* tmp
  char title[100];
  if(!category){
    strcpy(title, "添加服装分类");
  } else {
    strcpy(title, "修改服装分类");
  }

  GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;

  GtkWidget *category_dialog = GTK_WIDGET(gtk_dialog_new_with_buttons(
    title,
    window,
    flags,
    "确定", GTK_RESPONSE_ACCEPT,
    "取消", GTK_RESPONSE_REJECT,
    NULL));

  GtkWidget *label_code = gtk_label_new("分类编码");
  GtkWidget *entry_code = gtk_entry_new();
  GtkWidget *label_name = gtk_label_new("分类名称");
  GtkWidget *entry_name = gtk_entry_new();
  if(category){
    gtk_entry_set_text(GTK_ENTRY(entry_code), string((*category)->code));
    gtk_entry_set_text(GTK_ENTRY(entry_name), (*category)->name);
  }

  GtkWidget *category_grid = gtk_grid_new();
  gtk_grid_insert_column(GTK_GRID(category_grid), 0);
  gtk_grid_insert_column(GTK_GRID(category_grid), 1);
  gtk_grid_insert_row(GTK_GRID(category_grid), 0);
  gtk_grid_insert_row(GTK_GRID(category_grid), 1);
  gtk_grid_set_row_spacing(GTK_GRID(category_grid), 5);
  gtk_grid_set_column_spacing(GTK_GRID(category_grid), 5);
  gtk_grid_attach(GTK_GRID(category_grid), label_code, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(category_grid), label_name, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(category_grid), entry_code, 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(category_grid), entry_name, 1, 1, 1, 1);

  gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(category_dialog))), category_grid);

  gtk_widget_show_all(category_dialog);

  */

  //tmp2
  int rws = 2;
  char title[100];
  char argi[rws*2+1][100];
  if(!category){
    strcpy(title, "添加服装分类");
    strcpy(argi[3], "");
    strcpy(argi[4], "");
  } else {
    strcpy(title, "修改服装分类");
    strcpy(argi[3], string((*category)->code));
    strcpy(argi[4], (*category)->name);
  }
  strcpy(argi[0], title);
  strcpy(argi[1], "分类编码");
  strcpy(argi[2], "分类名称");

  GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
  dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
  gtk_widget_show_all(dialog_result[0]);

  char validate_message[100];
  validate_message[0] = '\0';
  int success = 0;
  GtkEntryBuffer *buffer;
  char code;
  char name[1000];
  GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

  while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
    validate_message[0] = '\0';
    //buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_code));
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
    code = gtk_entry_buffer_get_text(buffer)[0];
    //buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_name));
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*2+1]));
    strcpy(name, gtk_entry_buffer_get_text(buffer));

    /* error check */
    if(!code || name[0] == '\0'){
      strcpy(validate_message, "请输入完数据");
    }
    if(validate_message[0] == '\0' && strlen(name) > 9){
      strcpy(validate_message, "分类名称过长");
    }
    if(validate_message[0] == '\0' && (code<'1' || code>'5')){
      strcpy(validate_message, "分类编码错误(1-5)");
    }
    Category **search_result;
    if(validate_message[0] == '\0' && ((search_result = category_search(code)) && ((!category) || (category && ((*category)->code != code))))){
      strcpy(validate_message, "分类编码重复");
    }

    if(validate_message[0] != '\0'){
      warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
      gtk_widget_show_all(warning_dialog[0]);
      gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
      gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
      continue;
    }
    /* end error check */

    if(!category){
      category_create(&category_head, code, name, 0, NULL);
    } else {
      (*category)->code = code;
      strcpy((*category)->name, name);
    }
    success = 1;
    break;
  }

  gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));
  
  free(warning_dialog);
  free(dialog_result);

  return success;
}

int maintenance_clothes_dialog(void *self){
  error_out("maintenance_clothes_dialog called");
  /* init */
  Clothes **clothes = (Clothes **)self;

  /* argi[0]: title */
  /* argi[1-4]: lable */
  /* argi[5-8]: entry */
  int rws = 4;
  char title[100];
  char argi[rws*4+1][100];
  if(!clothes){
    strcpy(title, "添加服装信息");
    strcpy(argi[5], "");
    strcpy(argi[6], "");
    strcpy(argi[7], "");
    strcpy(argi[8], "");
  } else {
    strcpy(title, "修改服装信息");
    strcpy(argi[5], string((*clothes)->category->code));
    strcpy(argi[6], (*clothes)->name);
    strcpy(argi[7], ctype_to_string((*clothes)->type));
    sprintf(argi[8], "%f", (*clothes)->price);
  }
  strcpy(argi[0], title);
  strcpy(argi[1], "分类编码");
  strcpy(argi[2], "服装名称");
  strcpy(argi[3], "服装式样");
  strcpy(argi[4], "服装单价");

  GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
  dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
  gtk_widget_show_all(dialog_result[0]);

  char validate_message[100];
  validate_message[0] = '\0';
  int success = 0;
  GtkEntryBuffer *buffer;
  char code;
  char name[1000];
  char type;
  float price;
  GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

  while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
    validate_message[0] = '\0';
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
    code = gtk_entry_buffer_get_text(buffer)[0];
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*2+1]));
    strcpy(name, gtk_entry_buffer_get_text(buffer));
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*3+1]));
    type = string_to_ctype((char *)gtk_entry_buffer_get_text(buffer));
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*4+1]));
    price = atof(gtk_entry_buffer_get_text(buffer));

    /* error check */
    if(!code || name[0] == '\0' || !type || !price){
      strcpy(validate_message, "请输入完数据");
    }
    if(validate_message[0] == '\0' && strlen(name) > 30){
      strcpy(validate_message, "服装名称过长");
    }
    if(validate_message[0] == '\0' && (code<'1' || code>'5')){
      strcpy(validate_message, "分类编码错误(1-5)");
    }
    if(validate_message[0] == '\0' && (type != '0' && type != '1' && type != '9' )){
      strcpy(validate_message, "服装类型错误(男式(0) | 女式(1) | 中性(9))");
    }
    Clothes **search_result;
    if(validate_message[0] == '\0' && ((search_result = clothes_search(name)) && ((!clothes) || (clothes && (strcmp((*clothes)->name, name)))))){
      strcpy(validate_message, "服装名称重复");
    }
    Category **category;
    if(validate_message[0] == '\0' && !(category = category_search(code))){
      strcpy(validate_message, "无此分类");
    }

    if(validate_message[0] != '\0'){
      warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
      gtk_widget_show_all(warning_dialog[0]);
      gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
      gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
      continue;
    }
    /* end error check */


    if(!clothes){
      clothes_create(&((*category)->clothes), name, type, price, 0, 0, *category, NULL);
    } else {
      Clothes *clothes_old = *clothes;

      /* remove from original list */
      ((*clothes)->category->clothes_count)--;
      *clothes = (*clothes)->next;

      /* insert into new list */
      clothes_old->next = (*category)->clothes;
      (*category)->clothes = clothes_old;
      clothes_old->category = (*category);
      ((*category)->clothes_count)++;

      strcpy(clothes_old->name, name);
      clothes_old->type = type;
      clothes_old->price = price;
    }
    success = 1;
    break;
  }

  gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));
  
  free(warning_dialog);
  free(dialog_result);

  return success;
}


int maintenance_order_dialog(void *self){
  error_out("maintenance_order_dialog called");
  /* init */
  Order **order = (Order **)self;

  /* argi[0]: title */
  /* argi[1-4]: lable */
  /* argi[5-8]: entry */
  int rws = 4;
  char title[100];
  char argi[rws*4+1][100];
  if(!order){
    strcpy(title, "添加销售信息");
    strcpy(argi[5], "");
    strcpy(argi[6], "");
    strcpy(argi[7], "");
    strcpy(argi[8], "");
  } else {
    strcpy(title, "修改销售信息");
    strcpy(argi[5], ((*order)->clothes->name));
    strcpy(argi[6], (*order)->date);
    strcpy(argi[7], (*order)->name);
    sprintf(argi[8], "%d", (*order)->mark);
  }
  strcpy(argi[0], title);
  strcpy(argi[1], "服饰名称");
  strcpy(argi[2], "销售日期");
  strcpy(argi[3], "客户名称");
  strcpy(argi[4], "客户评价");

  GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
  dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
  gtk_widget_show_all(dialog_result[0]);

  char validate_message[100];
  validate_message[0] = '\0';
  int success = 0;
  GtkEntryBuffer *buffer;
  char cname[1000];
  char date[1000];
  char name[1000];
  int mark;
  GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

  while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
    validate_message[0] = '\0';
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
    strcpy(cname, gtk_entry_buffer_get_text(buffer));
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*2+1]));
    strcpy(date, gtk_entry_buffer_get_text(buffer));
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*3+1]));
    strcpy(name, gtk_entry_buffer_get_text(buffer));
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*4+1]));
    mark = atoi(gtk_entry_buffer_get_text(buffer));

    /* error check */
    if(!cname || date[0] == '\0' || name[0] == '\0' || !mark){
      strcpy(validate_message, "请输入完数据");
    }
    if(validate_message[0] == '\0' && strlen(name) > 20){
      strcpy(validate_message, "客户姓名过长");
    }
    if(validate_message[0] == '\0' && (mark<1 || mark>5)){
      strcpy(validate_message, "评分错误(1-5)");
    }
    if(validate_message[0] == '\0' && (!date_check(atoi(date)))){
      strcpy(validate_message, "日期错误(yyyymmdd)");
    }
    Clothes **clothes;
    if(validate_message[0] == '\0' && !(clothes = clothes_search(cname))){
      strcpy(validate_message, "无此服装");
    }

    if(validate_message[0] != '\0'){
      warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
      gtk_widget_show_all(warning_dialog[0]);
      gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
      gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
      continue;
    }
    /* end error check */


    if(!order){
      order_create(&((*clothes)->order), date, name, mark, *clothes);
    } else {
      Order *order_old = *order;

      /* remove from original list */
      if(((*order)->clothes->order_count) == 1){
        (*order)->clothes->mark = 0;
      } else {
        (*order)->clothes->mark = ( ((*order)->clothes->mark) * ((*order)->clothes->order_count) - ((*order)->mark) ) / (((*order)->clothes->order_count)-1);
      }
      ((*order)->clothes->order_count)--;
      *order = (*order)->next;

      /* insert into new list */
      order_old->next = (*clothes)->order;
      (*clothes)->order = order_old;
      order_old->clothes = (*clothes);
      (*clothes)->mark = ( ((*clothes)->mark) * ((*clothes)->order_count) + (order_old->mark) ) / (((*clothes)->order_count)+1);
      ((*clothes)->order_count)++;
      
      strcpy(order_old->date, date);
      strcpy(order_old->name, name);
      (*clothes)->mark = ( ((*clothes)->mark) * ((*clothes)->order_count) - (order_old->mark) + mark ) / ((*clothes)->order_count);
      order_old->mark = mark;
    }
    success = 1;
    break;
  }

  gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));
  
  free(warning_dialog);
  free(dialog_result);

  return success;
}

void maintenance_add_category(){
  if(maintenance_category_dialog(NULL)){
    call_last_func();
  } else {
    error_out("Add category failed.");
  }
}

void maintenance_add_clothes(){
  if(maintenance_clothes_dialog(NULL)){
    call_last_func();
  } else {
    error_out("Add clothes failed.");
  }
}

void maintenance_add_order(){
  if(maintenance_order_dialog(NULL)){
    call_last_func();
  } else {
    error_out("Add order failed.");
  }
}

void maintenance_delete(){
  GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
  GtkTreeIter iter;
  GtkTreeModel *model;
  gpointer *self;

  if(gtk_tree_selection_get_selected(selection, &model, &iter)){
    /* check */
    gtk_tree_model_get(model, &iter, 0, &self, -1);
    if(!self) return;

    GtkWidget **question_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));
    question_dialog = create_message_dialog(window, "确定要删除吗?", GTK_MESSAGE_QUESTION, question_dialog);
    gtk_widget_show_all(question_dialog[0]);

    if(gtk_dialog_run(GTK_DIALOG(question_dialog[0])) == GTK_RESPONSE_YES){
      gtk_tree_model_get(model, &iter, 0, &self, -1);
      Call_func **target = (Call_func **)self;
      (*((*target)->__delete))(self);
    }
    gtk_widget_destroy(GTK_WIDGET(question_dialog[0]));
    free(question_dialog);
  }

  call_last_func();
}

void maintenance_edit(){
  GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
  GtkTreeIter iter;
  GtkTreeModel *model;
  gpointer *self;
  gint type;
  int success;

  if(gtk_tree_selection_get_selected(selection, &model, &iter)){
    gtk_tree_model_get(model, &iter, 0, &self, -1);
    gtk_tree_model_get(model, &iter, 1, &type, -1);

    switch(type){
      case TYPE_CATEGORY: success = maintenance_category_dialog(self);break;
      case TYPE_CLOTHES: success = maintenance_clothes_dialog(self);break;
      case TYPE_ORDER: success = maintenance_order_dialog(self);break;
      case TYPE_OTHER: return;
    }
    if(success){
      call_last_func();
    } else {
      error_out("Edit failed.");
    }
  } else {
    error_out("Choose first.");
  }
}
/* End Maintenance */

/* Statistics */
void statistics_category(void *pass, int call_type){
  error_out("statistics_category called");
  last_func = &statistics_category;
  clean_column();

  GtkListStore *liststore;
  GtkTreeIter iter;
  create_list_store(&liststore, CATEGORY_STATS);

  Category **category_itor = &category_head;
  while(*category_itor){
    int order_count = 0;
    float sales_count = 0;
    int markl3_count = 0;
    int markg3_count = 0;
    Clothes **clothes_itor = &((*category_itor)->clothes);
    while(*clothes_itor){
      if((*clothes_itor)->mark >= 3){
        markl3_count++;
      } else {
        markg3_count++;
      }
      order_count += ((*clothes_itor)->order_count);
      sales_count += ((*clothes_itor)->order_count) * ((*clothes_itor)->price);
      clothes_itor = &((*clothes_itor)->next);
    }
    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(
      liststore, &iter,
      CATEGORY_STATS_POINTER, category_itor,
      CATEGORY_STATS_TYPE, TYPE_CATEGORY,
      CATEGORY_STATS_CODE, string((*category_itor)->code),
      CATEGORY_STATS_NAME, (*category_itor)->name,
      CATEGORY_STATS_ORDER_COUNT, order_count,
      CATEGORY_STATS_SALES_COUNT, sales_count,
      CATEGORY_STATS_MARKL3_COUNT, markl3_count,
      CATEGORY_STATS_MARKG3_COUNT, markg3_count,
      -1);
    category_itor = &((*category_itor)->next);
  }
  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
  create_column(CATEGORY_STATS);
}

void statistics_year(void *pass, int call_type){
  error_out("statistics_year called");

  static int year_max;
  static int year_min;
  int success = 0;

  if(call_type != CALL_TYPE_REDO){
    int rws = 2;
    char title[100];
    char argi[rws*2+1][100];
    strcpy(argi[0], "统计年度服装销售信息");
    strcpy(argi[1], "年份上限(包含)");
    strcpy(argi[2], "年份下限(包含)");
    strcpy(argi[3], "");
    strcpy(argi[4], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    GtkEntryBuffer *buffer;
    GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
      validate_message[0] = '\0';
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
      year_max = atoi(gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*2+1]));
      year_min = atoi(gtk_entry_buffer_get_text(buffer));

      /* error check */
      if(validate_message[0] != '\0'){
        warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
        gtk_widget_show_all(warning_dialog[0]);
        gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
        gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
        continue;
      }
      /* end error check */

      success = 1;
      break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));
    
    free(warning_dialog);
    free(dialog_result);
  }

  if(success || call_type == CALL_TYPE_REDO){
    last_func = &statistics_year;
    clean_column();

    GtkListStore *liststore;
    GtkTreeIter iter;
    create_list_store(&liststore, CLOTHES_YEAR);

    Category **category_itor = &category_head;
    while(*category_itor){
      Clothes **clothes_itor = &((*category_itor)->clothes);
      while(*clothes_itor){
        int order_count = 0;
        float sales_count = 0;
        float mark = 0;
        Order **order_itor = &((*clothes_itor)->order);
        while(*order_itor){
          if( (!year_max || (atoi((*order_itor)->date) / 10000) <= year_max) &&
              (!year_min || (atoi((*order_itor)->date) / 10000) >= year_min) ){
            mark = (mark * order_count + ((*order_itor)->mark)) / (order_count + 1.0);
            sales_count += (*clothes_itor)->price;
            order_count++;
          }
          order_itor = &((*order_itor)->next);
        }
        gtk_list_store_append(liststore, &iter);
        gtk_list_store_set(
          liststore, &iter,
          CLOTHES_YEAR_POINTER, clothes_itor,
          CLOTHES_YEAR_TYPE, TYPE_CLOTHES,
          CLOTHES_YEAR_NAME, (*clothes_itor)->name,
          CLOTHES_YEAR_CNAME, (*clothes_itor)->category->name,
          CLOTHES_YEAR_ORDER_COUNT, order_count,
          CLOTHES_YEAR_SALES_COUNT, sales_count,
          CLOTHES_YEAR_MARK, mark,
          -1);
        clothes_itor = &((*clothes_itor)->next);
      }
      category_itor = &((*category_itor)->next);
    }
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
    create_column(CLOTHES_YEAR);
  }
}

void statistics_customer(void *pass, int call_type){
  Customer *customer_head = NULL;
  error_out("statistics_customer called");
  last_func = &statistics_customer;
  clean_column();

  GtkListStore *liststore;
  GtkTreeIter iter;
  create_list_store(&liststore, CUSTOMER_STATS);

  Category **category_itor = &category_head;
  while(*category_itor){
    Clothes **clothes_itor = &((*category_itor)->clothes);
    while(*clothes_itor){
      Order **order_itor = &((*clothes_itor)->order);
      while(*order_itor){
        Customer **search_result = customer_search(&customer_head, (*order_itor)->name);
        if(search_result){
          (*search_result)->mark = (((*search_result)->mark) * ((*search_result)->order_count) + ((*order_itor)->mark)) / (((*search_result)->order_count)+1);
          ((*search_result)->money_count) += ((*order_itor)->clothes->price);
          ((*search_result)->order_count)++;
        } else {
          customer_create(&customer_head, (*order_itor)->name, 1, (*order_itor)->clothes->price, (*order_itor)->mark);
        }
        order_itor = &((*order_itor)->next);
      }
      clothes_itor = &((*clothes_itor)->next);
    }
    category_itor = &((*category_itor)->next);
  }

  Customer **customer_itor = &customer_head;
  while(*customer_itor){
    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(
      liststore, &iter,
      CUSTOMER_STATS_POINTER, NULL,
      CUSTOMER_STATS_TYPE, TYPE_OTHER,
      CUSTOMER_STATS_NAME, (*customer_itor)->name,
      CUSTOMER_STATS_ORDER_COUNT, (*customer_itor)->order_count,
      CUSTOMER_STATS_MONEY_COUNT, (*customer_itor)->money_count,
      CUSTOMER_STATS_MARK, (*customer_itor)->mark,
      -1);
    customer_delete(customer_itor);
  }
  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
  create_column(CUSTOMER_STATS);
}

void statistics_quarter(void *pass, int call_type){
  last_func = &statistics_quarter;
  clean_column();

  int season_count[4][5];
  float season_sales[4][5];
  char column_title[6][20] = {"季节", "", "", "", "", ""};
  int column_line[6] = {QUARTER_STATS_NAME, QUARTER_STATS_C1_COUNT, QUARTER_STATS_C2_COUNT, QUARTER_STATS_C3_COUNT, QUARTER_STATS_C4_COUNT, QUARTER_STATS_C5_COUNT};
  int cas = 0;
  int i, m;
  for(i=0; i<4; i++){
    for(m=0; m<5; m++){
      season_count[i][m] = 0;
      season_sales[i][m] = 0;
    }
  }

  Category **category_itor = &category_head;
  while(*category_itor){
    Clothes **clothes_itor = &((*category_itor)->clothes);
    while(*clothes_itor){
      Order **order_itor = &((*clothes_itor)->order);
      while(*order_itor){
        season_count[date_get_quarter(atoi((*order_itor)->date))][cas] += 1;
        season_sales[date_get_quarter(atoi((*order_itor)->date))][cas] += (*order_itor)->clothes->price;
        order_itor = &((*order_itor)->next);
      }
      clothes_itor = &((*clothes_itor)->next);
    }
    cas++;
    strcpy(column_title[cas], (*category_itor)->name);
    category_itor = &((*category_itor)->next);
  }
  char rw_data[8][6][20];
  char season_list[8][20] = {"春季售出件数", "春季总销售额", "夏季售出件数", "夏季总销售额", "秋季售出件数", "秋季总销售额", "冬季售出件数", "冬季总销售额"};
  for(i=0; i<4; i++){
    for(m=0; m<5; m++){
      sprintf(rw_data[2*i][m+1], "%d", season_count[i][m]);
      sprintf(rw_data[2*i+1][m+1], "%f", season_sales[i][m]);
    }
    strcpy(rw_data[2*i][0], season_list[2*i]);
    strcpy(rw_data[2*i+1][0], season_list[2*i+1]);
  }

  GtkListStore *liststore;
  GtkTreeIter iter;

  liststore = gtk_list_store_new(
    QUARTER_STATS_COLUMNS,
    G_TYPE_POINTER,
    G_TYPE_INT,
    G_TYPE_STRING, //QUARTER_STATS_NAME
    G_TYPE_STRING, //QUARTER_STATS_C1_COUNT
    G_TYPE_STRING, //QUARTER_STATS_C2_COUNT
    G_TYPE_STRING, //QUARTER_STATS_C3_COUNT
    G_TYPE_STRING, //QUARTER_STATS_C4_COUNT
    G_TYPE_STRING  //QUARTER_STATS_C5_COUNT
  );

  for(i=0; i<8; i++){
    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(
      liststore, &iter,
      QUARTER_STATS_POINTER, NULL,
      QUARTER_STATS_TYPE, TYPE_OTHER,
      QUARTER_STATS_NAME, rw_data[i][0],
      QUARTER_STATS_C1_COUNT, rw_data[i][1],
      QUARTER_STATS_C2_COUNT, rw_data[i][2],
      QUARTER_STATS_C3_COUNT, rw_data[i][3],
      QUARTER_STATS_C4_COUNT, rw_data[i][4],
      QUARTER_STATS_C5_COUNT, rw_data[i][5],
      -1);
  }
  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
  append_column(column_title, column_line, cas+1);
}

void statistics_all(void *pass, int call_type){
  last_func = &statistics_all;
  clean_column();

  GtkListStore *liststore;
  GtkTreeIter iter;
  create_list_store(&liststore, ALL_STATS);
  int order_count = 0;
  float sales_count = 0;
  int markl3_count = 0;
  int markg3_count = 0;

  Category **category_itor = &category_head;
  while(*category_itor){
    Clothes **clothes_itor = &((*category_itor)->clothes);
    while(*clothes_itor){
      if((*clothes_itor)->mark >= 3){
        markl3_count++;
      } else {
        markg3_count++;
      }
      order_count += ((*clothes_itor)->order_count);
      sales_count += ((*clothes_itor)->order_count) * ((*clothes_itor)->price);
      clothes_itor = &((*clothes_itor)->next);
    }
    category_itor = &((*category_itor)->next);
  }

  gtk_list_store_append(liststore, &iter);
  gtk_list_store_set(
    liststore, &iter,
    ALL_STATS_POINTER, NULL,
    ALL_STATS_TYPE, TYPE_OTHER,
    ALL_STATS_ORDER_COUNT, order_count,
    ALL_STATS_SALES_COUNT, sales_count,
    ALL_STATS_MARKL3_COUNT, markl3_count,
    ALL_STATS_MARKG3_COUNT, markg3_count,
    -1);
  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
  create_column(ALL_STATS);
}
/* End Statistics */

/* Other Function */
void other_about(){
  GtkWidget *about_window = NULL;
  about_window = gtk_about_dialog_new();
  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_window), program_name);
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_window), version);
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_window), comments);
  gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG(about_window), author);
  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(about_window), NULL);
  gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(about_window), GTK_LICENSE_GPL_2_0);
  gtk_widget_show_all(about_window);
}
/* End Other Function */