#ifndef FUN_H
#define FUN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#define END (0)
#define ERROR (-1)
#define MAX_LINE (1024)

static GtkWidget *text;

typedef struct Stog;
typedef struct Stog* Position;
struct Stog {
    float broj;
    Position next;
};

void copy_text(GtkWidget *window, gpointer ptr);
int copy_result(GtkWidget *window,gpointer ptr);
void expression(GtkFileChooserButton *button, gpointer ptr);
int file_select(GtkFileChooserButton *button, gpointer ptr);
void open_dialog1(GtkWidget *window, gpointer ptr);
void open_dialog2(GtkWidget *window, gpointer ptr);
int Push(float r);
float Pop();
float ReadFromFile(char* c);
float Fun(char *c);
char* ReadExpressionFromFile(char *c, char a[]);

#endif
