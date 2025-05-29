package br.me.moraes.cadastro_login.repository;

import br.me.moraes.cadastro_login.model.Credential;
import org.springframework.data.jpa.repository.JpaRepository;

public interface CredentialsRepository extends JpaRepository<Credential, String> {
}
