package br.me.moraes.cadastro_login.service;

import br.me.moraes.cadastro_login.dto.AuthenticationDTO;
import br.me.moraes.cadastro_login.dto.LoginResponseDTO;
import br.me.moraes.cadastro_login.dto.RegisterDTO;
import br.me.moraes.cadastro_login.model.User;
import br.me.moraes.cadastro_login.repository.UserRepository;
import jakarta.validation.Valid;
import lombok.AllArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;

@Service
@AllArgsConstructor
public class UserService {

    AuthenticationManager authenticationManager;
    UserRepository userRepository;
    TokenService tokenService;

    public ResponseEntity login (AuthenticationDTO data){
        var usernamePassword = new UsernamePasswordAuthenticationToken(data.email(), data.password());
        var auth = this.authenticationManager.authenticate(usernamePassword);

        var token = tokenService.generateToken((User) auth.getPrincipal());

        return ResponseEntity.ok(new LoginResponseDTO(token));
    }

    public ResponseEntity register(@Valid RegisterDTO data) {
        if(this.userRepository.findByEmail(data.email()) != null) return  ResponseEntity.badRequest().build();

        String encryptedPassword = new BCryptPasswordEncoder().encode(data.password());
        User newUser = new User(data.name(), data.username(), data.email(), encryptedPassword, data.role());

        this.userRepository.save(newUser);

        return ResponseEntity.status(HttpStatus.CREATED).body("Usuário cadastrado com sucesso!");
    }
}
