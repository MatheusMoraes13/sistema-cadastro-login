#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>


GtkBuilder *builder;
GtkWidget *window;
GtkStack *stack;

typedef struct usuario
{
    int id;
    char nome [100];
    char email [100];
    struct usuario *proximo;
} user;

int id = 0;
user *cabecalho_user;
user *proximo_user;

void on_main_window_destroy (GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

void on_button_cadastrar_inicial_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_cadastro");

}


void on_button_listar_inicial_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_listar");

}


void mensagem (char text [100], char secundary_text [100], char icon_name [100])
{

    GtkMessageDialog *mensagem_dialogo = gtk_builder_get_object (builder, "mensagem");

    g_object_set (mensagem_dialogo, "text", text, NULL);
    g_object_set (mensagem_dialogo, "secundary_text", secundary_text, NULL);
    g_object_set (mensagem_dialogo, "icon_name", icon_name, NULL);

    gtk_widget_show_all (mensagem_dialogo);
    gtk_dialog_run      (mensagem_dialogo);
    gtk_widget_hide     (mensagem_dialogo);

}

void Login (char *email, char *senha, bool lembrar)
{

    if ((strcmp (email, "admin") == 0) && (strcmp (senha, "admin") == 0))
    {

        mensagem ("Bem Vindo", "Usuario logado com sucesso!", "dialog-ok");
        gtk_stack_set_visible_child_name (stack, "view_inicial");
        g_object_set (window, "icon_name", "avatar-default", NULL);

    }

    else
    {

        mensagem ("Aviso", "Email ou senhas incorretos! \n tente novamente", "dialog-error");

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

}


void on_button_sair_inicial_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_login");

}


void on_button_cadastrar_clicked (GtkWidget *widget, gpointer data)
{

    char *cad_nome = gtk_entry_get_text (gtk_builder_get_object (builder, "cad_nome"));
    char *cad_email = gtk_entry_get_text (gtk_builder_get_object (builder, "cad_email"));

    if (strcmp (cad_nome, "") == 0)
    {

        mensagem ("Aviso", "Campo \"Nome\" obrigatorio!", "dialog-error");

    }
    else
    {
        id++;
        proximo_user -> id = id;
        strcpy(proximo_user -> nome, cad_nome);
        strcpy(proximo_user -> email, cad_email);

    }

    g_print ("\n%s", cad_nome);
    g_print ("\n%s", cad_email);


}


void on_button_cad_voltar_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_inicial");

}


void on_button_listar_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_listar");

}

void on_button_listar_voltar_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_inicial");

}

int main (int argc, char *argv[])
{
    cabecalho_user = (user *)malloc (sizeof (user));
    proximo_user = cabecalho_user;

    gtk_init ( &argc, &argv);

    builder = gtk_builder_new_from_file ("UI.glade");

    gtk_builder_add_callback_symbols(
        builder,
        "on_button_login_clicked",                  G_CALLBACK (on_button_login_clicked),
        "on_main_window_destroy",                   G_CALLBACK (on_main_window_destroy),
        "on_button_cadastrar_inicial_clicked",      G_CALLBACK (on_button_cadastrar_inicial_clicked),
        "on_button_listar_inicial_clicked",         G_CALLBACK (on_button_listar_inicial_clicked),
        "on_button_sair_inicial_clicked",           G_CALLBACK (on_button_sair_inicial_clicked),
        "on_button_cadastrar_clicked",              G_CALLBACK (on_button_cadastrar_clicked),
        "on_button_cad_voltar_clicked",             G_CALLBACK (on_button_cad_voltar_clicked),
        "on_button_listar_clicked",                 G_CALLBACK (on_button_listar_clicked),
        "on_button_listar_voltar_clicked",           G_CALLBACK (on_button_listar_voltar_clicked),
        NULL);

    gtk_builder_connect_signals (builder, NULL);

    stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
    window = GTK_WIDGET (gtk_builder_get_object (builder, "main_window"));

    gtk_widget_show_all (window);
    gtk_main ();
    return 0;
}
