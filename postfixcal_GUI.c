#define _CRT_SECURE_NO_WARNINGS_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
} *head = NULL;

int Push(float);
int Pop();
float ReadFromFile(char*);
float Fun(char *);
char* ReadExpressionFromFile(char *, char []);

void copy_text(GtkWidget *window, gpointer ptr){
    const char* input=gtk_entry_get_text(GTK_ENTRY (text));
    gtk_label_set_text(GTK_LABEL(ptr), input);
}

int copy_result(GtkWidget *window,gpointer ptr){

    char* ptext=NULL;
    float result=0.0;
    char buffer[MAX_LINE]={0};

    ptext=(char *)gtk_entry_get_text(GTK_ENTRY (text));
    result = Fun(ptext);

    snprintf(buffer, MAX_LINE, " %.2f", result);
    gtk_label_set_text(GTK_LABEL(ptr), buffer);

    if(result == 0)
        head=NULL;

    free(head);
    return END;
}

void expression(GtkFileChooserButton *button, gpointer ptr){

    char *ime=NULL, *pbuffer=NULL;
    char buffer[MAX_LINE]={0};
    char c[MAX_LINE]={0};

    ime=(char *)gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));

    pbuffer=ReadExpressionFromFile(ime,c);

    snprintf(buffer, MAX_LINE, "%s", pbuffer);
    gtk_label_set_text(GTK_LABEL(ptr), buffer);
    free(head);
}

static int file_select(GtkFileChooserButton *button, gpointer ptr){

    float result = 0.0;
    char *ime=NULL;
    char buffer[MAX_LINE]={0};

    ime=(char *)gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));

    result = ReadFromFile(ime);

    snprintf(buffer, MAX_LINE, " %.2f", result);
    gtk_label_set_text(GTK_LABEL(ptr), buffer);

    if(result == 0)
        head=NULL;

    free(head);
    return END;
}

void open_dialog1(GtkWidget *window, gpointer ptr){

    GtkWidget *dialog,*box, *label1, *tab, *lbl1, *lbl2, *lbl3, *lbl4, *button;

    dialog=gtk_dialog_new_with_buttons("Input postfix through file", GTK_WINDOW(ptr), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,"Exit",1,NULL);
    gtk_window_set_position(GTK_DIALOG(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_DIALOG(dialog), 400, 200);

    box=gtk_box_new( GTK_ORIENTATION_VERTICAL, 0);
    tab=gtk_table_new(1,0,TRUE);
    label1=gtk_label_new("Input file");
    lbl1=gtk_label_new("Expression from file:");
    lbl2=gtk_label_new(" ");
    lbl3=gtk_label_new("Result:");
    lbl4=gtk_label_new(" ");
    button=gtk_file_chooser_button_new("Select file", GTK_FILE_CHOOSER_ACTION_OPEN);

    gtk_table_attach_defaults(GTK_TABLE(tab), lbl1, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(tab), lbl2, 1, 2, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(tab), lbl3, 0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(tab), lbl4, 1, 2, 1, 2);

    gtk_container_add(gtk_dialog_get_content_area(GTK_DIALOG(dialog)), label1);
    gtk_container_add(gtk_dialog_get_content_area(GTK_DIALOG(dialog)), button);
    gtk_container_add(gtk_dialog_get_content_area(GTK_DIALOG(dialog)), tab);

    g_signal_connect(button, "file-set", G_CALLBACK(file_select), lbl4);
    g_signal_connect(button, "file-set", G_CALLBACK(expression), lbl2);

    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void open_dialog2(GtkWidget *window, gpointer ptr){

    GtkWidget *dialog, *box, *label1, *tab, *button, *lbl1, *lbl2, *lbl3, *lbl4;

    dialog=gtk_dialog_new_with_buttons("Input postfix through keyboard", GTK_WINDOW(ptr), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,"Exit", 1, NULL);
    gtk_window_set_position(GTK_DIALOG(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_DIALOG(dialog), 400, 200);

    box=gtk_box_new( GTK_ORIENTATION_VERTICAL, 0);
    tab=gtk_table_new(1,0,TRUE);
    label1=gtk_label_new("Input postfix expression");
    lbl1=gtk_label_new("Input:");
    lbl2=gtk_label_new("");
    lbl3=gtk_label_new("Result:");
    lbl4=gtk_label_new("");
    button=gtk_button_new_with_label("Enter");

    g_signal_connect(button, "clicked", G_CALLBACK(copy_text), lbl2);
    text=gtk_entry_new();
    g_signal_connect(button, "clicked", G_CALLBACK(copy_result), lbl4);

    gtk_table_attach_defaults(GTK_TABLE(tab), text, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(tab), button, 1, 2, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(tab), lbl1, 0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(tab), lbl2, 1, 2, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(tab), lbl3, 0, 1, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(tab), lbl4, 1, 2, 2, 3);

    gtk_container_add(gtk_dialog_get_content_area(GTK_DIALOG(dialog)), label1);
    gtk_container_add(gtk_dialog_get_content_area(GTK_DIALOG(dialog)), tab);

    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

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

float ReadFromFile(char* filename) {

    char buffer[MAX_LINE] = { 0 }, mark[MAX_LINE] = { 0 };
    char* p = NULL;
    float num1 = 0.0, num2 = 0.0, value=0.0;
    int n = 0;

    FILE* fp = NULL;
    fp = fopen(filename, "a+");

    if (fp == NULL) {
        printf("File did not open!");
        return ERROR;
    }

    fgets(buffer, MAX_LINE, fp);
    p = buffer;

    while (strlen(p) > 0)
    {
        if (sscanf(p, "%f %n", &value, &n) <= 0){
            sscanf(p, "%s %n", mark, &n);

            if (strcmp(mark, "+") != 0 && strcmp(mark, "-") != 0 && strcmp(mark, "*") != 0 && strcmp(mark, "/") != 0) {
                printf("The operation or value is not correct!");

                GtkWidget *dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO ,GTK_BUTTONS_NONE,"ERROR!\nThe operation or value is not correct!\nTry again!");
                gtk_window_set_position(GTK_DIALOG(dialog), GTK_WIN_POS_CENTER);
                gtk_window_set_default_size(GTK_DIALOG(dialog), 40, 20);
                gtk_widget_show (dialog);

                fclose(fp);
                return END;
            }

            if (head == NULL) {
                printf("Error, operation can not be first!");

                GtkWidget *dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO ,GTK_BUTTONS_NONE,"ERROR!\nOperation can not be first!\nTry again!");
                gtk_window_set_position(GTK_DIALOG(dialog), GTK_WIN_POS_CENTER);
                gtk_window_set_default_size(GTK_DIALOG(dialog), 40, 20);
                gtk_widget_show (dialog);

                fclose(fp);
                return END;
            }

            num1 = Pop();
            num2 = Pop();

            if (strcmp(mark, "+") == 0)
                Push(num2 + num1);

            else if (strcmp(mark, "-") == 0)
                Push(num2 - num1);

            else if (strcmp(mark, "*") == 0)
                Push(num2 * num1);

            else{
               if (num1 == 0.0) {
                    printf("Undefined!");

                    GtkWidget *dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO ,GTK_BUTTONS_NONE,"ERROR!\nUndefined!\nTry again!");
                    gtk_window_set_position(GTK_DIALOG(dialog), GTK_WIN_POS_CENTER);
                    gtk_window_set_default_size(GTK_DIALOG(dialog), 40, 20);
                    gtk_widget_show (dialog);

                    Pop();
                    fclose(fp);
                    return END;
                }
                else
                    Push(num2 / num1);
            }
        }
        else
            Push(value);

        p += n;
    }

    if (head != NULL && head->next == NULL) {
        fclose(fp);
        return Pop();
    }

    printf("There is more than one element left in stack!\n");

    GtkWidget *dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO ,GTK_BUTTONS_NONE,"ERROR!\nThere is more than one element left in stack!\nTry again!");
    gtk_window_set_position(GTK_DIALOG(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_DIALOG(dialog), 40, 20);
    gtk_widget_show (dialog);

    fclose(fp);
    return END;
}

int Push(float x){

    Position temp =NULL;
    temp = (Position)malloc(sizeof(struct Stog));

    if (temp == NULL)
    {
        printf("ERROR!");
        return ERROR;
    }

    temp->broj = x;
    temp->next = NULL;

    temp->next = head;
    head = temp;

    return END;
}

int Pop(){

    Position temp;
    float result = 0.0;

    temp = head;
    result = temp->broj;

    head = head->next;
    free(temp);
    temp = NULL;

    return result;
}

float Fun(char *p) {

    char mark[MAX_LINE] = { 0 };
    float num1 = 0.0, num2 = 0.0, value = 0.0;
    int n = 0;

    while (strlen(p) > 0)
    {
        if (sscanf(p, "%f %n", &value, &n) <= 0) {
            sscanf(p, "%s %n", mark, &n);

            if (strcmp(mark, "+") != 0 && strcmp(mark, "-") != 0 && strcmp(mark, "*") != 0 && strcmp(mark, "/") != 0) {
                printf("The operation or value is not correct!");

                GtkWidget *dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO ,GTK_BUTTONS_NONE,"ERROR!\nThe operation or value is not correct!\nTry again!");
                gtk_window_set_position(GTK_DIALOG(dialog), GTK_WIN_POS_CENTER);
                gtk_window_set_default_size(GTK_DIALOG(dialog), 40, 20);
                gtk_widget_show (dialog);

                return END;
            }

            if (head == NULL) {
                printf("Error, operation can not be first!");

                GtkWidget *dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO ,GTK_BUTTONS_NONE,"ERROR!\nOperation can not be first!\nTry again!");
                gtk_window_set_position(GTK_DIALOG(dialog), GTK_WIN_POS_CENTER);
                gtk_window_set_default_size(GTK_DIALOG(dialog), 40, 20);
                gtk_widget_show (dialog);

                return END;
            }

            num1 = Pop();
            num2 = Pop();

            if (strcmp(mark, "+") == 0)
                Push(num2 + num1);

            else if (strcmp(mark, "-") == 0)
                Push(num2 - num1);

            else if (strcmp(mark, "*") == 0)
                Push(num2 * num1);

            else {
                if (num1 == 0.0) {
                    printf("Undefined!");

                    GtkWidget *dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO ,GTK_BUTTONS_NONE,"ERROR!\nUndefined!\nTry again!");
                    gtk_window_set_position(GTK_DIALOG(dialog), GTK_WIN_POS_CENTER);
                    gtk_window_set_default_size(GTK_DIALOG(dialog), 40, 20);
                    gtk_widget_show (dialog);

                    Pop();
                    return END;
                }
                else
                    Push(num2 / num1);
            }
        }
        else
            Push(value);

        p += n;
    }

    if (head != NULL && head->next == NULL) {
        return Pop();
    }

    printf("There is more than one element left in stack!\n");

    GtkWidget *dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO ,GTK_BUTTONS_NONE,"ERROR!\nThere is more than one element left in stack!\nTry again!");
    gtk_window_set_position(GTK_DIALOG(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_DIALOG(dialog), 40, 20);
    gtk_widget_show (dialog);

    return END;
}

char* ReadExpressionFromFile(char *filename, char c[]){

    FILE *fp=NULL;
    char buffer[MAX_LINE]= { 0 };

    fp=fopen(filename, "a+");
    if (fp == NULL) {
        printf("File did not open!");
        return ERROR;
    }

    fgets(buffer, MAX_LINE, fp);
    strcat(c,buffer);

    fclose(fp);
    return c;
}
