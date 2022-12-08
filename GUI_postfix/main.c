#define _CRT_SECURE_NO_WARNINGS_

#include <stdio.h>
#include <gtk/gtk.h>
#include "fun.h"

int main(int argc, char *argv[]){

    gtk_init(&argc, &argv);

    GtkWidget *window, *button1, *button2, *box, *label;

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    box=gtk_box_new( GTK_ORIENTATION_VERTICAL, 0);

    button1=gtk_button_new_with_label("Input postfix through file");
    gtk_widget_set_size_request(GTK_WIDGET(button1), 50, 30);
    button2=gtk_button_new_with_label("Input postfix through keyboard");
    gtk_widget_set_size_request(GTK_WIDGET(button2), 50, 30);

    label=gtk_label_new("Choose a method you want");
    gtk_widget_set_size_request(GTK_WIDGET(button2), 50, 30);

    gtk_window_set_title(GTK_WINDOW(window), "POSTFIX CALCULATOR");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 300);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 25);
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 25);

    g_signal_connect (button1, "clicked", G_CALLBACK(open_dialog1), NULL);
    g_signal_connect (button2, "clicked", G_CALLBACK(open_dialog2), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return END;
}
