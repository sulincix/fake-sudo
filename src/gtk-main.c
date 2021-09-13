#include <gtk/gtk.h>
#include <libsudo.h>
#include <token.h>

GtkWindow *window;
GtkLabel *label;
GtkEntry *pass;
GtkWidget *header;
char* fargv[];
int fargv;

void button_event(GtkWidget *button, gpointer *data){
    const gchar *passwd = gtk_entry_get_text (GTK_ENTRY (pass));
    if(STREQ(passwd,"")){
        return;
    }
    setenv("HASH",HASH,1);
    if(system("[ $HASH == $(sha1sum $(which gtk-sudo-helper) | cut -f 1 -d ' ') ]")!=0){
        return 1;
    }
    setenv("PASSWORD",passwd,1);
    setenv("TOKEN",TOKEN,1);
    if(system("gtk-sudo-helper")==0){
        gtk_widget_hide(window);
        char *cmd[fargc];
        cmd[0] = "gtk-sudo-helper";
        for(int i=0;i<fargc-1;i++){
            cmd[i+1] = fargv[i+1];
        }
        cmd[fargc-1] = NULL;
        execvp(which(fargv[1]),cmd);
        gtk_main_quit();
    }
}

int main(int argc,char *argv[]){
    gtk_init (&argc, &argv);
    fargv = argv;
    fargc = argc;
    
    GtkWidget *button, *cancel, *box, *bbox;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(window, FALSE);
    gtk_window_set_position (window, GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); 

    gtk_window_set_title (GTK_WINDOW (window), "Authentication");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 0);

    label = gtk_label_new("Authentication required.");
    pass = gtk_entry_new();
    gtk_entry_set_visibility(pass,FALSE);
    button = gtk_button_new_with_label("OK");
    cancel = gtk_button_new_with_label("Cancel");
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    bbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    
    g_signal_connect (button, "pressed",
			G_CALLBACK (button_event), "pressed");

    g_signal_connect (cancel, "pressed",
			G_CALLBACK(gtk_main_quit), "pressed");

    gtk_container_add(GTK_CONTAINER(box), label);
    gtk_container_add(GTK_CONTAINER(box), pass);
    gtk_box_pack_start(GTK_CONTAINER(bbox), button, TRUE, TRUE,0);
    gtk_box_pack_end(GTK_CONTAINER(bbox), cancel, TRUE, TRUE,0);
    gtk_container_add(GTK_CONTAINER(box), bbox);
    gtk_container_add(GTK_CONTAINER(window), box);

    ccmd = arg2cmd(argc,argv);
    gtk_widget_show_all (window);
    gtk_main();
    return 0;
}
