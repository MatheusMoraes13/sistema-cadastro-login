package br.me.moraes.cadastro_login.repository;

import br.me.moraes.cadastro_login.model.User;
import org.springframework.data.jpa.repository.JpaRepository;

public interface UserRepository extends JpaRepository<User, String> {

    Boolean getByEmail(String email);

}
