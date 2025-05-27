package br.me.moraes.cadastro_login.service;

import br.me.moraes.cadastro_login.model.User;
import br.me.moraes.cadastro_login.repository.UserRepository;
import jakarta.validation.constraints.NotNull;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;

@Service
public class UserService {

    UserRepository userRepository;

    public ResponseEntity<String> registerUser(@NotNull User user){
        if (userRepository.getByEmail(user.getEmail())){
            return ResponseEntity.badRequest().body("ERRO: Email já registrado");
        }
        else {
            userRepository.save(user);

            return ResponseEntity.status(HttpStatus.CREATED).body("Usuário cadastrado com sucesso!");
        }
    }
}
