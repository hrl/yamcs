#include <stdlib.h>
#include <gtk/gtk.h>
#include "functions.h"

enum{
    TITLE_COLUMN,
    AUTHOR_COLUMN,
    COLUMNS
};


void tree_selection_changed(GtkTreeSelection *selection, gpointer data){
  GtkTreeIter iter;
  GtkTreeModel *model;
  gchar *author;

  if (gtk_tree_selection_get_selected (selection, &model, &iter)){
    gtk_tree_model_get(model, &iter, AUTHOR_COLUMN, &author, -1);
    g_print("You selected a book by %s\n", author);
    g_free(author);
  }
}

void query_category_2all(GtkWidget *z, GtkTreeView *treeview){
  GtkTreeStore *store = gtk_tree_store_new(
    COLUMNS,
    G_TYPE_STRING,
    G_TYPE_STRING);

  GtkTreeIter iter;
  gtk_tree_store_append(store, &iter, NULL);
  gtk_tree_store_set(
    store, &iter,
    TITLE_COLUMN, "haha",
    AUTHOR_COLUMN, "oh",
    -1);
  gtk_tree_store_append(store, &iter, NULL);
  gtk_tree_store_set(
    store, &iter,
    TITLE_COLUMN, "haha2",
    AUTHOR_COLUMN, "oh2",
    -1);
  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));

  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes(
    "Author",
    renderer,
    "text", AUTHOR_COLUMN,
    NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
  column = gtk_tree_view_column_new_with_attributes(
    "Title",
    renderer,
    "text", TITLE_COLUMN,
    NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

  GtkTreeSelection *select;
  select = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
  gtk_tree_selection_set_mode(select, GTK_SELECTION_SINGLE);
  g_signal_connect(G_OBJECT(select), "changed", G_CALLBACK(tree_selection_changed), NULL);
}

int main(int argc, char *argv[]){

  gtk_init(&argc, &argv);

  build_UI();
  file_new();

  gtk_main();

  return 0;
}