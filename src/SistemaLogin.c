#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <sqlite3.h>


GtkBuilder *builder;
GtkWidget *window;
GtkStack *stack;
GtkListStore *modelo_armazenamento;

int id = 0;

void on_main_window_destroy (GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

void mensagem (const char *text, const char *secondary_text, char *icon_name)
{

    GtkMessageDialog *mensagem_dialogo = GTK_MESSAGE_DIALOG( gtk_builder_get_object (builder, "mensagem"));

    g_object_set (mensagem_dialogo, "text", text, NULL);
    g_object_set (mensagem_dialogo, "secondary_text", secondary_text, NULL);
    gtk_window_set_icon_from_file(GTK_WINDOW(mensagem_dialogo), icon_name, NULL);

    gtk_window_set_transient_for(GTK_WINDOW(mensagem_dialogo), GTK_WINDOW(window));
    gtk_widget_show_all (GTK_WIDGET (mensagem_dialogo));
    gtk_dialog_run      (GTK_DIALOG (mensagem_dialogo));
    gtk_widget_hide     (GTK_WIDGET (mensagem_dialogo));

}


void Login (const char *email, const char *senha)
{

    if ((strcmp (email, "admin") == 0) && (strcmp (senha, "admin") == 0))
    {

        mensagem ("Bem Vindo", "Usuario logado com sucesso!", "icons/login-94x94.png");
        gtk_stack_set_visible_child_name (stack, "view_inicial");

    }

    else
    {

        mensagem ("Aviso", "Email ou senhas incorretos! \n tente novamente", "icons/warning-100x100.png");

    }
}



void on_button_login_clicked (GtkWidget *widget, gpointer data)
{
    GtkEntry *entryEmail = GTK_ENTRY (gtk_builder_get_object(builder, "email"));
    GtkEntry *entrySenha = GTK_ENTRY (gtk_builder_get_object(builder, "senha"));

    const gchar *email = gtk_entry_get_text (entryEmail);
    const gchar *senha = gtk_entry_get_text (entrySenha);

    Login (email, senha);

}


void on_button_modificar_inicial_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_modificar");

}


void on_button_listar_inicial_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_listar");

}


void on_button_sair_inicial_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_login");

}


void on_button_cadastrar_login_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack,"view_cadastro");

}


int sqlite_retorno (void *NotUsed, int argc, char **argv, char **coluna){
    for (int i = 0; i < argc; i++){

        printf("%s = %s\n", coluna [i], argv[i] ? argv[i]: "NULL");

    }

    printf("\n");
    return 0;
}


int obter_proximo_id(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    int proximo_id = 1;

    const char *query = "SELECT MAX(id) FROM logins;";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int max_id = sqlite3_column_int(stmt, 0);
            if (max_id > 0)
            {
                proximo_id = max_id + 1;
            }
        }
    }

    sqlite3_finalize(stmt);
    return proximo_id;
}


void on_button_cadastrar_clicked (GtkWidget *widget, gpointer data)
{
    sqlite3 * db = 0;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("Logins.db3", &db);


    GtkEntry *entry_nome = GTK_ENTRY (gtk_builder_get_object(builder, "cad_nome"));
    GtkEntry *entry_email = GTK_ENTRY (gtk_builder_get_object(builder, "cad_email"));
    GtkEntry *entry_senha = GTK_ENTRY (gtk_builder_get_object(builder, "cad_senha"));

    const char *cad_nome = gtk_entry_get_text (entry_nome);
    const char *cad_email = gtk_entry_get_text (entry_email);
    const char *cad_senha = gtk_entry_get_text (entry_senha);

    if (strcmp (cad_nome, "") == 0 || strcmp (cad_email, "") == 0 || strcmp (cad_senha, "") == 0)
    {

        mensagem ("Aviso", "Campo obrigatorio em branco!", "icons/warning-100x100.png");

    }

    else
    {
        int id = obter_proximo_id(db);

        char insert[256];

        sprintf(insert, "INSERT INTO logins (nome, email, senha) VALUES ('%s', '%s', '%s');",
        cad_nome, cad_email, cad_senha);

        char *mensagem_erro = NULL;
        rc = sqlite3_exec(db, insert, sqlite_retorno, 0, &mensagem_erro);

        if (rc != SQLITE_OK) {
        mensagem("Erro", mensagem_erro, "icons/warning-100x100.png");
        sqlite3_free(mensagem_erro);
        return;
        }


        char texto[128];
        g_snprintf(texto, 128, "%s%s%s", "Usuario ", cad_nome, " cadastrado!");
        mensagem ("Aviso", texto, "icons/check_circle-100x100.png");

    }

    sqlite3_close(db);
}


void on_button_cad_voltar_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_modificar");

}


void on_button_voltar_login_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_inicial");

}


void on_button_atualizar_login_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_atualizar");

}


void on_button_apagar_login_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_apagar");

}


void on_button_voltar_atualizar_clicked (GtkWidget *widget, gpointer data)
{
    gtk_stack_set_visible_child_name (stack, "view_modificar");
}


void on_button_pesquisar_atualizar_clicked (GtkWidget *widget, gpointer data)
{

    sqlite3 * db = 0;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("Logins.db3", &db);

    GtkEntry *entry_pesquisar_atualizar = GTK_ENTRY (gtk_builder_get_object(builder, "pesquisa_atualizar"));
    const char *pesquisar_atualizar = gtk_entry_get_text(entry_pesquisar_atualizar);

    char *output;
    long modify = strtol (pesquisar_atualizar, &output, 10);
    int id = modify;

    char *mensagem_erro = NULL;

        if (rc != SQLITE_OK)
        {

            mensagem("Erro", mensagem_erro, "icons/warning-100x100.png");
            sqlite3_free (mensagem_erro);
            return;

        }

    char *query = "SELECT nome, email, senha FROM logins WHERE id = ?";

    rc = sqlite3_prepare_v2 (db, query, -1, &stmt, NULL);
    sqlite3_bind_int (stmt, 1, id);

    GtkEntry *entry_nome_atualizar =  GTK_ENTRY (gtk_builder_get_object(builder, "nome_atualizar"));
    GtkEntry *entry_email_atualizar = GTK_ENTRY (gtk_builder_get_object(builder, "email_atualizar"));
    GtkEntry *entry_senha_atualizar = GTK_ENTRY (gtk_builder_get_object(builder, "senha_atualizar"));

    if (sqlite3_step(stmt) == SQLITE_ROW)
        {
        const char *nome  = (const char *)sqlite3_column_text(stmt, 0);
        const char *email = (const char *)sqlite3_column_text(stmt, 1);
        const char *senha = (const char *)sqlite3_column_text(stmt, 2);

        gtk_entry_set_text (entry_nome_atualizar,  nome);
        gtk_entry_set_text (entry_email_atualizar, email);
        gtk_entry_set_text (entry_senha_atualizar, senha);
        }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


void on_button_atualizar_atualizar_clicked (GtkWidget *widget, gpointer data)
{
    sqlite3 * db = 0;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("Logins.db3", &db);
    const char *query = "UPDATE logins SET nome = ?, email = ?, senha = ? WHERE id = ?";

    GtkEntry *entry_pesquisar_atualizar = GTK_ENTRY (gtk_builder_get_object(builder, "pesquisa_atualizar"));
    const char *pesquisar_atualizar = gtk_entry_get_text(entry_pesquisar_atualizar);
    char *output;
    long modify = strtol (pesquisar_atualizar, &output, 10);
    int id = modify;

    GtkEntry *entry_nome_atualizar  = GTK_ENTRY (gtk_builder_get_object(builder, "nome_atualizar"));
    GtkEntry *entry_email_atualizar = GTK_ENTRY (gtk_builder_get_object(builder, "email_atualizar"));
    GtkEntry *entry_senha_atualizar = GTK_ENTRY (gtk_builder_get_object(builder, "senha_atualizar"));

    const char *nome_atualizar = gtk_entry_get_text(entry_nome_atualizar);
    const char *email_atualizar = gtk_entry_get_text(entry_email_atualizar);
    const char *senha_atualizar = gtk_entry_get_text(entry_senha_atualizar);

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        mensagem("Erro", "Erro ao preparar a consulta SQL.", "icons/warning-100x100.png");
        return;
    }

    sqlite3_bind_text(stmt, 1, nome_atualizar,  -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email_atualizar, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, senha_atualizar, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, id);

    rc = sqlite3_step (stmt);

    char texto[128];
    if (rc == SQLITE_DONE)
    {
        g_snprintf(texto, 128, "%s%s%s", "Usuario ", nome_atualizar, " atualizado!");
        mensagem ("Aviso", texto, "icons/check_circle-100x100.png");
    }

    else
    {
        mensagem("Erro", "Falha ao atualizar o usuário!", "icons/warning-100x100.png");
    }

    sqlite3_finalize (stmt);
    sqlite3_close (db);
}


void on_button_pesquisar_apagar_clicked (GtkWidget *widget, gpointer data)
{

    sqlite3 * db = 0;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("Logins.db3", &db);

    GtkEntry *entry_pesquisar_apagar = GTK_ENTRY (gtk_builder_get_object(builder, "pesquisar_apagar"));
    const char *pesquisar_apagar = gtk_entry_get_text(entry_pesquisar_apagar);

    char *output;
    long modify = strtol (pesquisar_apagar, &output, 10);
    int id = modify;

    char *mensagem_erro = NULL;

        if (rc != SQLITE_OK)
        {

            mensagem("Erro", mensagem_erro, "icons/warning-100x100.png");
            sqlite3_free (mensagem_erro);
            return;

        }

    char *query = "SELECT nome, email, senha FROM logins WHERE id = ?";

    rc = sqlite3_prepare_v2 (db, query, -1, &stmt, NULL);
    sqlite3_bind_int (stmt, 1, id);

    GtkEntry *entry_nome_apagar =  GTK_ENTRY (gtk_builder_get_object(builder, "nome_apagar"));
    GtkEntry *entry_email_apagar = GTK_ENTRY (gtk_builder_get_object(builder, "email_apagar"));
    GtkEntry *entry_senha_apagar = GTK_ENTRY (gtk_builder_get_object(builder, "senha_apagar"));

    if (sqlite3_step(stmt) == SQLITE_ROW)
        {
        const char *nome  = (const char *)sqlite3_column_text(stmt, 0);
        const char *email = (const char *)sqlite3_column_text(stmt, 1);
        const char *senha = (const char *)sqlite3_column_text(stmt, 2);

        gtk_entry_set_text (entry_nome_apagar,  nome);
        gtk_entry_set_text (entry_email_apagar, email);
        gtk_entry_set_text (entry_senha_apagar, senha);
        }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

}


void on_button_apagar_apagar_clicked (GtkWidget *widget, gpointer data)
{
    sqlite3 * db = 0;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("Logins.db3", &db);
    const char *query = "DELETE FROM logins WHERE id = ?";


    GtkEntry *entry_pesquisar_apagar = GTK_ENTRY (gtk_builder_get_object(builder, "pesquisar_apagar"));
    const char *pesquisar_apagar = gtk_entry_get_text(entry_pesquisar_apagar);
    char *output;
    long modify = strtol (pesquisar_apagar, &output, 10);
    int id = modify;

    GtkCheckButton *check_confirmar = GTK_CHECK_BUTTON (gtk_builder_get_object(builder, "confirmar_apagar"));
    GtkEntry *entry_nome_apagar = GTK_ENTRY (gtk_builder_get_object(builder, "nome_apagar"));

    const char *nome_apagar = gtk_entry_get_text (entry_nome_apagar);
    bool confirmar = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(check_confirmar));

    if (confirmar == 1)
    {
        rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
        if (rc != SQLITE_OK)
        {
            mensagem("Erro", "Erro ao preparar a consulta SQL.", "icons/warning-100x100.png");
            return;
        }

        sqlite3_bind_int(stmt, 1, id);

        rc = sqlite3_step (stmt);

        char texto[128];
        if (rc == SQLITE_DONE)
        {
            g_snprintf(texto, 128, "%s%s%s", "Usuario ", nome_apagar, " apagado!");
            mensagem ("Aviso", texto, "icons/check_circle-100x100.png");
        }

        else
        {
            mensagem("Erro", "Falha ao apagar o usuário!", "icons/warning-100x100.png");
        }

        sqlite3_finalize (stmt);
    }

    if (confirmar == 0)
    {
       mensagem ("Aviso", "É preciso confirmar que deseja apagar", "icons/warning-100x100.png");
    }

    sqlite3_close (db);

}


void on_button_voltar_apagar_clicked (GtkWidget *widget, gpointer data)
{

    gtk_stack_set_visible_child_name (stack, "view_modificar");

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
        const char *nome  = (const char *)sqlite3_column_text(stmt, 1);
        const char *email = (const char *)sqlite3_column_text(stmt, 2);
        const char *senha = (const char *)sqlite3_column_text(stmt, 3);
        gtk_list_store_append(modelo_armazenamento, &iter);
        gtk_list_store_set(modelo_armazenamento, &iter ,
                           0, id,
                           1, nome,
                           2, email,
                           3, senha,
                           -1);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


void on_button_listar_voltar_clicked (GtkWidget *widget, gpointer data)
{
    gtk_list_store_clear (modelo_armazenamento);
    gtk_stack_set_visible_child_name (stack, "view_inicial");

}


int main (int argc, char *argv[])
{

    char *mensagem_erro = NULL;
    sqlite3 * db = 0;

    int rc = sqlite3_open("Logins.db3", &db);

    if (rc != SQLITE_OK){
        mensagem("Erro", "Falha ao abrir o banco de dados!", "icons/warning-100x100.png");
        sqlite3_close(db);
        return 1;
    }

    char create[] = "CREATE TABLE logins( "
                    "id INTEGER PRIMARY KEY,"
                    "nome TEXT,"
                    "email TEXT,"
                    "senha TEXT)";

    rc = sqlite3_exec(db, create, sqlite_retorno, 0, &mensagem_erro);


    gtk_init ( &argc, &argv);

    builder = gtk_builder_new_from_file ("UI.glade");

    gtk_builder_add_callback_symbols(
        builder,
        "on_button_login_clicked",                  G_CALLBACK (on_button_login_clicked),
        "on_main_window_destroy",                   G_CALLBACK (on_main_window_destroy),
        "on_button_modificar_inicial_clicked",      G_CALLBACK (on_button_modificar_inicial_clicked),
        "on_button_listar_inicial_clicked",         G_CALLBACK (on_button_listar_inicial_clicked),
        "on_button_sair_inicial_clicked",           G_CALLBACK (on_button_sair_inicial_clicked),
        "on_button_cadastrar_clicked",              G_CALLBACK (on_button_cadastrar_clicked),
        "on_button_cad_voltar_clicked",             G_CALLBACK (on_button_cad_voltar_clicked),
        "on_button_listar_clicked",                 G_CALLBACK (on_button_listar_clicked),
        "on_button_listar_voltar_clicked",          G_CALLBACK (on_button_listar_voltar_clicked),
        "on_button_voltar_login_clicked",           G_CALLBACK (on_button_voltar_login_clicked),
        "on_button_apagar_login_clicked",           G_CALLBACK (on_button_apagar_login_clicked),
        "on_button_atualizar_login_clicked",        G_CALLBACK (on_button_atualizar_login_clicked),
        "on_button_cadastrar_login_clicked",        G_CALLBACK (on_button_cadastrar_login_clicked),
        "on_button_atualizar_login_clicked",        G_CALLBACK (on_button_atualizar_login_clicked),
        "on_button_atualizar_atualizar_clicked",    G_CALLBACK (on_button_atualizar_atualizar_clicked),
        "on_button_voltar_atualizar_clicked",       G_CALLBACK (on_button_voltar_atualizar_clicked),
        "on_button_pesquisar_atualizar_clicked",    G_CALLBACK (on_button_pesquisar_atualizar_clicked),
        "on_button_voltar_atualizar_clicked",       G_CALLBACK (on_button_voltar_atualizar_clicked),
        "on_button_pesquisar_apagar_clicked",       G_CALLBACK (on_button_pesquisar_apagar_clicked),
        "on_button_apagar_apagar_clicked",          G_CALLBACK (on_button_apagar_apagar_clicked),
        "on_button_voltar_apagar_clicked",          G_CALLBACK (on_button_voltar_apagar_clicked),
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
