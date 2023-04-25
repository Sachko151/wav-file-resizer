#include <stdio.h>
#include <gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gtk/gtkx.h>
#include <glib-2.0/glib.h>
#include <stdlib.h>
#include <stddef.h>

GtkWidget *window;
GtkWidget *fixed_layout;
GtkWidget *btn_file_chooser;
GtkWidget *txt_length;
GtkWidget *btn_resize;
GtkWidget *lbl_info;
GtkWidget *lbl_additional_info;
GtkBuilder *builder;
int main(int argc, char **argv){
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("user_interface.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);
    fixed_layout = GTK_WIDGET(gtk_builder_get_object(builder, "fixed_layout"));
    btn_file_chooser = gtk_file_chooser_button_new(("Select a file"), GTK_FILE_CHOOSER_ACTION_OPEN);
    txt_length = GTK_WIDGET(gtk_builder_get_object(builder, "txt_length"));
    btn_resize = GTK_WIDGET(gtk_builder_get_object(builder, "btn_resize"));
    lbl_info = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_info"));
    lbl_additional_info = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_additional_info"));
    gtk_widget_show(window);
    gtk_main();
    return 0;
}
void btn_resize_clicked(GtkButton *button){
    const char *new_format = gtk_entry_get_text((GtkEntry*)txt_length);
    printf("resizing with %s\n", new_format);
}