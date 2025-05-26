package br.me.moraes.cadastro_login.repository;

import br.me.moraes.cadastro_login.model.Users;
import org.springframework.data.jpa.repository.JpaRepository;

public interface UsersRepository extends JpaRepository<Users, String> {
}
