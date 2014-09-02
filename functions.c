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
  /* --Query clothes menu */
  /* --Query order menu */
  /* -Maintenance menu */
  /* --Maintenance add menu */
  g_signal_connect(G_OBJECT(menuitem_maintenance_add_category), "activate", G_CALLBACK(maintenance_add_category), NULL);
  /* --Maintenance edit */
  g_signal_connect(G_OBJECT(menuitem_maintenance_edit), "activate", G_CALLBACK(maintenance_edit), NULL);
  /* --Maintenance delete */
  g_signal_connect(G_OBJECT(menuitem_maintenance_delete), "activate", G_CALLBACK(maintenance_delete), NULL);
  /* -Statistics menu */
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

GtkWidget **create_edit_dialog(GtkWindow *fwindow, int rws, char argi[][30], GtkWidget **dialog_response){

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
  category->clothes_count = category->clothes_count + 1;

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
  tmp->clothes->order_count += 1;

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
  *target = needfreeor->next;
  free(needfreeor);
  needfreeor = NULL;

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
  char *str = (char *)malloc(2);
  str[0] = code;
  str[1] = '\0';
  return str;
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
  GtkTreeIter iter;

  liststore = gtk_list_store_new(
    CATEGORY_ALL_COLUMNS,
    G_TYPE_POINTER,
    G_TYPE_INT,
    G_TYPE_STRING,
    G_TYPE_STRING,
    G_TYPE_INT);

  Category **category_itor = &category_head;
  while(*category_itor){
    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(
    liststore, &iter,
    CATEGORY_ALL_POINTER, category_itor,
    CATEGORY_ALL_TYPE, TYPE_CATEGORY,
    CATEGORY_ALL_CODE, string((*category_itor)->code),
    CATEGORY_ALL_NAME, (*category_itor)->name,
    CATEGORY_ALL_CLOTHES_COUNT, (*category_itor)->clothes_count,
    -1);
    category_itor = &((*category_itor)->next);
  }

  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));

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
}

void query_clothes_all(void *pass, int call_type){
  error_out("query_clothes_all called");
  last_func = &query_clothes_all;
  clean_column();

  GtkListStore *liststore;
  GtkTreeIter iter;

  liststore = gtk_list_store_new(
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

  Category **category_itor = &category_head;
  while(*category_itor){
    Clothes **clothes_itor = &((*category_itor)->clothes);
    while(*clothes_itor){
      gtk_list_store_append(liststore, &iter);
      gtk_list_store_set(
      liststore, &iter,
      CLOTHES_ALL_POINTER, clothes_itor,
      CLOTHES_ALL_TYPE, TYPE_CLOTHES,
      CLOTHES_ALL_CODE, string((*category_itor)->code),
      CLOTHES_ALL_NAME, (*category_itor)->name,
      CLOTHES_ALL_CTYPE, (*category_itor)->clothes_count,
      CLOTHES_ALL_PRICE, (*category_itor)->clothes_count,
      CLOTHES_ALL_MARK, (*category_itor)->clothes_count,
      CLOTHES_ALL_ORDER_COUNT, (*category_itor)->clothes_count,
      -1);
      clothes_itor&((*clothes_itor)->next);
    }
    category_itor = &((*category_itor)->next);
  }

  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));

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
  char title[30];
  char argi[rws*2+1][30];
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

  char validate_message[30];
  validate_message[0] = '\0';
  int success = 0;
  GtkEntryBuffer *buffer;
  char code;
  char name[10];
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
      strcpy(validate_message, "blank input");
    }
    if(validate_message[0] == '\0' && strlen(name) > 9){
      strcpy(validate_message, "name too long");
    }
    if(validate_message[0] == '\0' && (code<'1' || code>'5')){
      strcpy(validate_message, "invalid code(1-5)");
    }
    Category **search_result;
    if(validate_message[0] == '\0' && ((search_result = category_search(code)) && ((!category) || (category && ((*category)->code != code))))){
      strcpy(validate_message, "duplicate code");
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

void maintenance_add_category(){
  if(maintenance_category_dialog(NULL)){
    call_last_func();
  } else {
    error_out("Add category failed.");
  }
}

void maintenance_add_clothes(){

}

void maintenance_add_order(){

}

void maintenance_delete(){
  GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
  GtkTreeIter iter;
  GtkTreeModel *model;
  gpointer *self;

  if(gtk_tree_selection_get_selected(selection, &model, &iter)){

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