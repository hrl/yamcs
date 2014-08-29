#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <unistd.h>

#include "structs.h"
#include "defines.h"
#include "functions.h"

/* Helper function */
void error_out(char *error){
  g_print("%s\n", error);
}

void clean_var(){
  category_head = NULL;
  category_list_head = NULL;
  clothes_list_head = NULL;
  order_list_head = NULL;
}

void build_UI(){
  GtkBuilder *builder;
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
  GtkWidget *menuitem_file_save_as = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_file_save_as"));
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
  g_signal_connect(G_OBJECT(menuitem_file_save_as), "activate", G_CALLBACK(file_save_as), NULL);
  g_signal_connect(G_OBJECT(menuitem_file_quit), "activate", G_CALLBACK(file_quit), NULL);
  /* -Query menu */
  /* --Query category menu */
  //g_signal_connect(G_OBJECT(menuitem_query_category_all), "activate", G_CALLBACK(query_category_all), treeview);
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

void insert_into_container(Container **head, void **data){
  Container *temp;
  temp = (Container *)malloc(sizeof(Container));
  temp->data = data;
  temp->next = *head;
  *head = temp;
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
      Category *load_category_head, *load_category_tail, *load_category_temp;
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

          /* load clothes */
          if(load_category_tail->clothes_count){
            Clothes *load_clothes_head, *load_clothes_tail, *load_clothes_temp;
            load_clothes_head = (Clothes *)malloc(sizeof(Clothes));
            load_clothes_tail = load_clothes_head;
            load_clothes_temp = NULL;

            int clothes_processed = 0;

            do{
              /* load current clothes */
              fread(load_clothes_tail, sizeof(Clothes), 1, file);
              load_clothes_tail->category = load_category_tail;

                /* load order */
                if(load_clothes_tail->order_count){
                  Order *load_order_head, *load_order_tail, *load_order_temp;
                  load_order_head = (Order *)malloc(sizeof(Order));
                  load_order_tail = load_order_head;
                  load_order_temp = NULL;

                  int order_processed = 0;

                  do{
                    /* load current order */
                    fread(load_order_tail, sizeof(Order), 1, file);
                    load_order_tail->clothes = load_clothes_tail;
                    load_order_tail->category = load_category_tail;
                    /* end load current order */
                    /* prepare for next order */
                    order_processed++;
                    load_order_temp = load_order_tail;
                    load_order_tail->next = (Order *)malloc(sizeof(Order));
                    insert_into_container(&order_list_head, (void **)&(load_order_tail->next));
                    load_order_tail = load_order_tail->next;
                  } while(order_processed < load_clothes_tail->order_count);
                  load_order_temp->next = NULL;
                  free(load_order_tail);

                  load_clothes_tail->order = load_order_head;
                  order_list_head->data = (void **)&(load_clothes_tail->order);
                } else {
                  load_clothes_tail->order = NULL;
                }
                /* end load order */
              
              /* end load current clothes */
              /* prepare for next clothes */
              clothes_processed++;
              load_clothes_temp = load_clothes_tail;
              load_clothes_tail->next = (Clothes *)malloc(sizeof(Clothes));
              insert_into_container(&clothes_list_head, (void **)&(load_clothes_tail->next));
              load_clothes_tail = load_clothes_tail->next;
            } while(clothes_processed < load_category_tail->clothes_count);
            load_clothes_temp->next = NULL;
            free(load_clothes_tail);

            load_category_tail->clothes = load_clothes_head;
            clothes_list_head->data = (void **)&(load_category_tail->clothes);
          } else {
            load_category_tail->clothes = NULL;
          }
          /* end load clothes */

        /* end load current category */
        /* prepare for next category */
        load_category_temp = load_category_tail;
        load_category_tail->next = (Category *)malloc(sizeof(Category));
        insert_into_container(&category_list_head, (void **)&(load_category_tail->next));
        load_category_tail = load_category_tail->next;
      } while(!feof(file));
      free(load_category_tail);

      if(count){
        load_category_temp->next = NULL;
        category_head = load_category_head;
        category_list_head->data = (void **)&(category_head);
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
  GtkWidget *dialog;
  GtkFileChooser *chooser;

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
}

void file_open(){
  error_out("file_open called.");
  if(file){
    close_file();
    clean_var();
  }
  char *filename = file_choose(FILE_CHOOSE_OPEN);
  if(filename){
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
}

void file_save(){
  error_out("file_save called.");
  short save_error;
  if(file){
    if(!save_file()){
      save_error = 1;
    }
  } else {
    char *filename = file_choose(FILE_CHOOSE_SAVE);
    if(filename){
      file = fopen(filename, "wb+");
    }
    if( !(file && save_file()) ){
      save_error = 1;
    }
    free(filename);
  }

  if(save_error){
    error_out("Save failed.");
  }
}

void file_save_as(){
  error_out("file_save_as called.");
  char *filename = file_choose(FILE_CHOOSE_SAVE_AS);
  if(filename){
    close_file();
    file = fopen(filename, "wb+");
  }
  if( !(file && save_file()) ){
    error_out("Save failed.");
  }
  free(filename);
}

void file_quit(){
  error_out("file_quit called.");
  close_file();
  gtk_main_quit();
}
/* End Basic I/O */

/* Other Function */
void other_about(){
  GtkWidget *about_window;
  about_window = gtk_about_dialog_new();
  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_window), program_name);
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_window), version);
  gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG(about_window), author);
  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(about_window), NULL);
  gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(about_window), GTK_LICENSE_GPL_2_0);
  gtk_widget_show_all(about_window);
}
/* End Other Function */