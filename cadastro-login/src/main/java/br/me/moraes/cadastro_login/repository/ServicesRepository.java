package br.me.moraes.cadastro_login.repository;

import br.me.moraes.cadastro_login.model.Services;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface ServicesRepository extends JpaRepository<Services, Integer> {

    public boolean existsByName(String name);
}
