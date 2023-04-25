#include "gui_functions.h"
void on_btn_pick_input_file_file_set(GtkFileChooserButton *button, gpointer user_data){
    printf("%s\n",  gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button)));
}
