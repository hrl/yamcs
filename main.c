#include <stdlib.h>
#include <gtk/gtk.h>
#include "functions.h"

int main(int argc, char *argv[]){

  gtk_init(&argc, &argv);

  build_UI();
  file_new();

  gtk_main();

  return 0;
}