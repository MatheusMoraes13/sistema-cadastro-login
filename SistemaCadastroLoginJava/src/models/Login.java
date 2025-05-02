package models;

public class Login {
    private final String servico;
    private final String login;
    private String gmail;
    private String contato;
    private String senha;

    public Login (String servico, String login, String senha){
        this.servico = servico;
        this.login = login;
        this.senha = senha;
    }

    public void adicionarContato (String contato){
        this.contato = contato;
    }

    public void adicionarGmail (String gmail){
        this.gmail = gmail;
    }

    public void atualizarSenha (String senha){
        this.senha = senha;

        System.out.println("Senha atualizada com sucesso!");
    }

    public String getServico() {
        return servico;
    }

    public String getLogin() {
        return login;
    }

    public String getGmail() {
        return gmail;
    }

    public String getContato() {
        return contato;
    }

    public String getSenha() {
        return senha;
    }

    @Override
    public String toString() {
        return "Usuarios [servico=" + servico + ", login=" + login + ", gmail=" + gmail + ", contato=" + contato
                + ", senha=" + senha + "]";
    }
}
