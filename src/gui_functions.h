#ifndef __GUI_FUNCTIONS__
#define __GUI_FUNCTIONS__
#include <stdio.h>
#include <gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gtk/gtkx.h>
#include <glib-2.0/glib.h>
#include <stdlib.h>
#include <stddef.h>
void set_lbl_info_text(GtkWidget *lbl_info, int success_code, int operation_code, int time);
#endif