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
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
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
  /* --Maintenance edit */
  /* --Maintenance delete */
  /* -Statistics menu */
  /* -Other menu */
  g_signal_connect(G_OBJECT(menuitem_other_about), "activate", G_CALLBACK(other_about), NULL);
  /* End Connect signals */

  /* Destroy builder */
  g_object_unref(G_OBJECT(builder));

  /* Show window */
  gtk_widget_show_all(window);
}



int category_create(Category **head ,char code, char name[], int clothes_count, Clothes *clothes){
  Category *tmp = NULL;
  tmp = (Category *)malloc(sizeof(Category));
  tmp->code = code;
  strcpy(tmp->name, name);
  tmp->clothes_count = clothes_count;
  tmp->clothes = clothes;


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
  tmp->category = clothes->category;

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
    g_print("--------------------------\n");

    Clothes *clothes_itor = category_itor->clothes;
    while(clothes_itor){
      g_print("--------------------------\n");
      g_print("Clothes:\n category_name: %s\n name: %s\n type: %c\n price: %f\n mark: %f\n order_count: %d\n",
              clothes_itor->category->name, clothes_itor->name, clothes_itor->type, clothes_itor->price, clothes_itor->mark, clothes_itor->order_count);
      g_print("--------------------------\n");

      Order *order_itor = clothes_itor->order;
      while(order_itor){
        g_print("--------------------------\n");
        g_print("Order:\n date: %s\n name: %s\n mark: %d\n",
                order_itor->date, order_itor->name, order_itor->mark);
        g_print("--------------------------\n");
        order_itor = order_itor->next;
      }
      clothes_itor = clothes_itor->next;
    }
    category_itor = category_itor->next;
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
  char *str = (char *)malloc(2);
  str[0] = code;
  str[1] = '\0';
  return str;
}
/* End Helper function */

/* Basic I/O */

short save_file(){
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

short load_file(){
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
        load_category_tail->__delete = category_delete;

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
              load_clothes_tail->__delete = clothes_delete;


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
                    load_order_tail->category = load_category_tail;
                    load_order_tail->__delete = order_delete;
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

void query_category_all(){
  clean_column();

  GtkListStore *liststore;
  GtkTreeIter iter;

  liststore = gtk_list_store_new(
    CATEGORY_ALL_COLUMNS,
    G_TYPE_STRING,
    G_TYPE_STRING,
    G_TYPE_INT,
    G_TYPE_POINTER);

  Category **category_itor = &category_head;
  while(*category_itor){
    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(
    liststore, &iter,
    CATEGORY_ALL_CODE, string((*category_itor)->code),
    CATEGORY_ALL_NAME, (*category_itor)->name,
    CATEGORY_ALL_CLOTHES_COUNT, (*category_itor)->clothes_count,
    CATEGORY_ALL_POINTER, category_itor,
    -1);

    category_itor = &((*category_itor)->next);
  }

  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));

  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes(
    "分类编码",
    renderer,
    "text", CATEGORY_ALL_CODE,
    NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
  column = gtk_tree_view_column_new_with_attributes(
    "分类名称",
    renderer,
    "text", CATEGORY_ALL_NAME,
    NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
  column = gtk_tree_view_column_new_with_attributes(
    "服装数",
    renderer,
    "text", CATEGORY_ALL_CLOTHES_COUNT,
    NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

}
/* End Query */

/* Other Function */
void other_about(){
  GtkWidget *about_window = NULL;
  about_window = gtk_about_dialog_new();
  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_window), program_name);
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_window), version);
  gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG(about_window), author);
  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(about_window), NULL);
  gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(about_window), GTK_LICENSE_GPL_2_0);
  gtk_widget_show_all(about_window);
}
/* End Other Function */