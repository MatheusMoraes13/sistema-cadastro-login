package br.me.moraes.cadastro_login.repository;

import br.me.moraes.cadastro_login.model.Credential;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface CredentialRepository extends JpaRepository<Credential, String> {

    List<Credential> findByService (String service);

    List<Credential> findByLoginAndPassword(String login, String password);
}
