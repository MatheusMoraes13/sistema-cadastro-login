#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <sqlite3.h>


GtkBuilder *builder;
GtkWidget *window;
GtkStack *stack;
GtkListStore *modelo_armazenamento;

typedef struct usuario
{
    int id;
    char nome [100];
    char email [100];
    char senha [100];
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


void mensagem (const char text [100], const char secondary_text [100], char icon_name [100])
{

    GtkMessageDialog *mensagem_dialogo = GTK_MESSAGE_DIALOG( gtk_builder_get_object (builder, "mensagem"));

    g_object_set (mensagem_dialogo, "text", text, NULL);
    g_object_set (mensagem_dialogo, "secondary_text", secondary_text, NULL);
    g_object_set (mensagem_dialogo, "icon_name", icon_name, NULL);

    gtk_widget_show_all (GTK_WIDGET (mensagem_dialogo));
    gtk_dialog_run      (GTK_DIALOG (mensagem_dialogo));
    gtk_widget_hide     (GTK_WIDGET (mensagem_dialogo));

}

void Login (const char *email, const char *senha, bool lembrar)
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

int sqlite_retorno (void *NotUsed, int argc, char **argv, char **coluna){
    for (int i = 0; i < argc; i++){

        printf("%s = %s\n", coluna [i], argv[i] ? argv[i]: "NULL");

    }

    printf("\n");
    return 0;
}

void on_button_cadastrar_clicked (GtkWidget *widget, gpointer data)
{
    sqlite3 * db = 0;
    int rc = sqlite3_open("Logins.db3", &db);

    GtkEntry *entry_nome = GTK_ENTRY (gtk_builder_get_object(builder, "cad_nome"));
    GtkEntry *entry_email = GTK_ENTRY (gtk_builder_get_object(builder, "cad_email"));
    GtkEntry *entry_senha = GTK_ENTRY (gtk_builder_get_object(builder, "cad_senha"));

    const char *cad_nome = gtk_entry_get_text (entry_nome);
    const char *cad_email = gtk_entry_get_text (entry_email);
    const char *cad_senha = gtk_entry_get_text (entry_senha);

    if (strcmp (cad_nome, "") == 0)
    {

        mensagem ("Aviso", "Campo \"Nome\" obrigatorio!", "dialog-error");

    }

    if (strcmp (cad_email, "") == 0)
    {

        mensagem ("Aviso", "Campo \"Email\" obrigatorio!", "dialog-error");

    }

    if (strcmp (cad_senha, "") == 0)
    {

        mensagem ("Aviso", "Campo \"Senha\" obrigatorio!", "dialog-error");

    }

    else
    {
        if (proximo_user == NULL) {
            proximo_user = (user *)malloc(sizeof(user));
            if (proximo_user == NULL) {
                mensagem("Erro", "Falha ao alocar memória!", "dialog-error");
                return;
            }
        }

        id++;
        proximo_user -> id = id;
        strcpy(proximo_user -> nome, cad_nome);
        strcpy(proximo_user -> email, cad_email);
        strcpy(proximo_user -> senha, cad_senha);

        char insert[256];

        sprintf(insert, "INSERT INTO logins (id, nome, email, senha) VALUES (%d, '%s', '%s', '%s');",
        id, cad_nome, cad_email, cad_senha);

        char *mensagem_erro = NULL;
        rc = sqlite3_exec(db, insert, sqlite_retorno, 0, &mensagem_erro);

        if (rc != SQLITE_OK) {
        mensagem("Erro", mensagem_erro, "dialog-error");
        sqlite3_free(mensagem_erro);
        return;
        }


        char texto[100];
        g_snprintf(texto, 100, "%s%s%s", "Usuario", proximo_user->nome, "cadastrado!");
        mensagem ("Aviso", texto, "dialog_mensage_default");
        
        proximo_user->proximo = (user *) malloc(sizeof(user));
        if (proximo_user->proximo == NULL) {
        mensagem("Erro", "Falha ao alocar memória para o próximo usuário!", "dialog-error");
        return;
        }

        proximo_user -> proximo = (user *) malloc (sizeof (user));
        proximo_user = proximo_user -> proximo;

    }

}


void on_button_cad_voltar_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_inicial");

}


void on_button_listar_clicked (GtkWidget *widget, gpointer data)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("Logins.db3", &db);

    if (rc != SQLITE_OK)
    {
        mensagem("Erro", "Não foi possível conectar ao banco de dados!", "dialog-error");
        return;
    }

    const char *query = "SELECT id, nome, email, senha FROM logins;";
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        mensagem("Erro", "Falha ao preparar a consulta!", "dialog-error");
        sqlite3_close(db);
        return;
    }


    GtkTreeIter iter;
    gtk_list_store_clear (modelo_armazenamento);

    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const char *nome = (const char *)sqlite3_column_text(stmt, 1);
        const char*email = (const char *)sqlite3_column_text(stmt, 2);
        const char*senha = (const char *)sqlite3_column_text(stmt, 3);
        gtk_list_store_append(modelo_armazenamento, &iter);
        gtk_list_store_set(modelo_armazenamento, &iter ,
                           0, id,
                           1, nome,
                           2, email,
                           3, senha,
                           -1);
    }
}

void on_button_listar_voltar_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_inicial");

}


int main (int argc, char *argv[])
{
    //Criando e abrindo o banco de dados
    char *mensagem_erro = NULL;
    sqlite3 * db = 0;

    int rc = sqlite3_open("Logins.db3", &db);

    if (rc != SQLITE_OK){
        mensagem("Erro", "Falha ao abrir o banco de dados!", "dialog-error");
        sqlite3_close(db);
        return 1;
    }

    char create[] = "CREATE TABLE logins( "
                    "id INTEGER PRIMARY KEY, "
                    "nome TEXT,"
                    "email TEXT,"
                    "senha TEXT)";

    rc = sqlite3_exec(db, create, sqlite_retorno, 0, &mensagem_erro);


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
    modelo_armazenamento = GTK_LIST_STORE (gtk_builder_get_object (builder, "liststore1"));

    gtk_widget_show_all (window);
    gtk_main ();
    sqlite3_close(db);
    return 0;
}
