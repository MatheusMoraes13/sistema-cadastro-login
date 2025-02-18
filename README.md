# Sistema de Cadastro e Login

## Descrição
Este projeto é um sistema de cadastro e login desenvolvido em C, utilizando a biblioteca GTK3 para a interface gráfica e a ferramenta Glade para facilitar a construção da UI.

## Tecnologias Utilizadas
- **C**: Linguagem de programação principal.
- **GTK3**: Biblioteca para interface gráfica.
- **Glade**: Ferramenta para construção da UI.
- **SQLlite3**: Ferramenta de banco de dados utilizada para armazenamento das informações dos logins.

## Funcionalidades
- Cadastro de novos usuários.
- Login de usuários cadastrados.
- Validação de credenciais.
- Interface gráfica amigável.
- Armazenamento  senhas.

## Estrutura do Projeto
```
/SistemaCadastroLogin
├── src
│   ├── main.c
│   ├── interface.c
│   ├── database.c
│   ├── auth.c
├── ui
│   ├── UI.glade
├── build
├── README.md
```

## Requisitos
- GTK3 instalado (`libgtk-3-dev` para Linux).
- Glade para edição da UI.
- Compilador C (gcc ou outro compatível).

## Como Compilar e Executar
### Instalação das dependências (Linux)
```sh
sudo apt update
sudo apt install libgtk-3-dev glade
```

### Compilação do projeto
```sh
gcc src/main.c src/interface.c src/database.c src/auth.c -o cadastro_login `pkg-config --cflags --libs gtk+-3.0`
```

### Execução
```sh
./cadastro_login
```


## Licença
Este projeto é distribuído sob a licença MIT.
