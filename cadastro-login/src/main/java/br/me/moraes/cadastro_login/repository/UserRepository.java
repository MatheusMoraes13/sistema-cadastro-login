package br.me.moraes.cadastro_login.repository;

import br.me.moraes.cadastro_login.model.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface UserRepository extends JpaRepository<User, String> {

    User findByEmail(String email);
    Boolean existsByEmail(String email);

}
