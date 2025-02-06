#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>


GtkBuilder *builder;
GtkWidget *window;

void on_main_window_destroy (GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

void on_button_cadastrar_inicial_clicked (GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}


void on_button_listar_inicial_clicked (GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

void Login (char *email, char *senha, bool lembrar)
{

    if ((strcmp (email, "admin") == 0) && (strcmp (senha, "admin") == 0))
    {

        g_print ("Usuario logado com sucesso");

    }

    else
    {

        g_print ("Email ou senha incorretos");

    }
}

void on_button_login_clicked (GtkWidget *widget, gpointer data)
{
    GtkEntry *entryEmail = GTK_ENTRY (gtk_builder_get_object(builder, "email"));
    GtkEntry *entrySenha = GTK_ENTRY (gtk_builder_get_object(builder, "senha"));
    GtkCheckButton *checkLembrar = GTK_CHECK_BUTTON (gtk_builder_get_object (builder, "lembrar"));

    const gchar *email = gtk_entry_get_text (entryEmail);
    const gchar *senha = gtk_entry_get_text (entrySenha);
    bool lembrar = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkLembrar));

    Login (email, senha, lembrar);

    if (lembrar == 1){

        g_print ("\n Lembrando");

    }
}


void on_button_sair_inicial_clicked (GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}


void on_button_cadastrar_clicked (GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}


void on_button_cad_voltar_clicked (GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}


void on_button_listar_clicked (GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}


int main (int argc, char *argv[])
{

    gtk_init ( &argc, &argv);

    builder = gtk_builder_new_from_file ("ui.glade");

    gtk_builder_add_callback_symbols(
        builder,
        "on_button_login_clicked",                  G_CALLBACK(on_button_login_clicked),
        "on_main_window_destroy",                   G_CALLBACK(on_main_window_destroy),
        "on_button_cadastrar_inicial_clicked",      G_CALLBACK(on_button_cadastrar_inicial_clicked),
        "on_button_listar_inicial_clicked",         G_CALLBACK(on_button_listar_inicial_clicked),
        "on_button_sair_inicial_clicked",           G_CALLBACK(on_button_sair_inicial_clicked),
        "on_button_cadastrar_clicked",              G_CALLBACK(on_button_cadastrar_clicked),
        "on_button_cad_voltar_clicked",             G_CALLBACK(on_button_cad_voltar_clicked),
        "on_button_listar_clicked",                 G_CALLBACK(on_button_listar_clicked),
        NULL);

    gtk_builder_connect_signals (builder, NULL);

    window = GTK_WIDGET (gtk_builder_get_object (builder, "main_window"));

    gtk_widget_show_all (window);
    gtk_main ();
    return 0;
}
