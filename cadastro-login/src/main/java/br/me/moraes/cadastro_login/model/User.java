package br.me.moraes.cadastro_login.model;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Entity(name = "tab_usuarios")
@Getter @Setter
@AllArgsConstructor
@NoArgsConstructor

public class User {

    @Id
    @GeneratedValue(strategy = GenerationType.UUID)
    private String id;

    @Column(unique = true, length = 20)
    private String name;

    @Column(unique = true, length = 30)
    private String username;

    @Column(length = 50)
    private String password;

}
