import models.Login;

public class App {
    public static void main(String[] args) throws Exception {
        Login login = new Login("Teste 01", "teste.logins", "teste123");

        System.out.println(login);
    }
}
