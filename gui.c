#include <stdio.h>
#include <gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gtk/gtkx.h>
#include <glib-2.0/glib.h>
#include <stdlib.h>
#include <stddef.h>
#include "src/main_functions.h"
#include "src/wav_file_structure.h"
#include "src/wav_operations.h"
#include "src/gui_functions.h"
#include "src/log.h"
#include <string.h>
#define MESSAGE_SIZE 128
GtkWidget *window;
GtkWidget *fixed_layout;
GtkWidget *btn_file_chooser;
GtkWidget *txt_length;
GtkWidget *btn_resize;
GtkWidget *lbl_info;
GtkBuilder *builder;
int overwrite_flag = 0,silent_flag = 0, gui_flag = 0;
char *input_filename;
FILE *input_file, *output_file;
char  *output_filename;//, new_wav_length[WAV_LENGTH_FORMAT_SIZE];
wav_header_t header_metadata;
void init_gtk_elements(int argc, char **argv);

int main(int argc, char **argv){
    
    init_gtk_elements(argc, argv);
    log_function(silent_flag, start_of_the_program);
    return EXIT_SUCCESS;
}
void btn_resize_clicked(GtkButton *button){
    char *new_wav_length = gtk_entry_get_text((GtkEntry*)txt_length);
    puts(new_wav_length);
    int error = check_if_the_filename_is_invalid_and_exit_if_it_is(input_filename, silent_flag);
    if(error != 0){
        set_lbl_info_text(lbl_info, error,1,10);
        return;
    }
    output_filename = return_new_output_filename(input_filename, silent_flag);
    input_file = open_wav_file_and_exit_if_error_encountered(input_filename,silent_flag);
    read_the_metadata_for_the_wav_file(&header_metadata, input_file);
    error = check_if_the_wav_file_has_correct_metadata_structure_and_exit_if_not(header_metadata,silent_flag);
    if(error != 0){
        set_lbl_info_text(lbl_info, error,0,0);
        return;
    }
    print_out_wav_file_metadata(header_metadata,silent_flag);
    print_out_wav_file_length_in_specified_format(header_metadata,silent_flag);
    output_file = open_the_output_file_and_exit_if_error_encountered(output_filename,silent_flag);
    uint32_t old_size = return_length_of_wav_file_in_seconds(header_metadata,silent_flag);
    uint32_t new_size = return_length_in_seconds_from_string_format(new_wav_length,silent_flag);
    if(old_size == -1 || new_size == -1){
        set_lbl_info_text(lbl_info, 2,0,0);
        return;
    }
    check_if_new_size_is_zero_and_exit_if_true(new_size);
    determine_whether_to_trim_extend_or_quit(old_size, new_size, header_metadata, input_file, output_file,
    input_filename, output_filename,silent_flag, lbl_info);
    remove_old_file_if_overwrite_flag_is_present(overwrite_flag, input_filename,silent_flag);
    free(output_filename);
}
void on_btn_pick_input_file_file_set(GtkFileChooserButton *button, gpointer user_data){
    input_filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));
    printf("%s\n",  input_filename);
}
void init_gtk_elements(int argc, char **argv){
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
    gtk_widget_show(window);
    gtk_main();
}
void set_lbl_info_text(GtkWidget *lbl_info, int success_code, int operation_code, int time){
    //success_code = 0 | bad file
    //operation_code = 0  extend |operation_code = 1  trim|
    char message[128];
    if(success_code == 0){
        if(operation_code){
            sprintf(message, "File succesfully trimmed with:%d seconds", time);
            gtk_label_set_text(GTK_LABEL(lbl_info),message);
        }
        else{
            sprintf(message, "File succesfully extended with:%d seconds", time);
            gtk_label_set_text(GTK_LABEL(lbl_info),message);
        }
        return;
    } else{
            sprintf(message, "Not a correct .wav file or wrong input!");
            gtk_label_set_text(GTK_LABEL(lbl_info),message);
    }
}