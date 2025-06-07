package br.me.moraes.cadastro_login.controller;

import br.me.moraes.cadastro_login.dto.AuthenticationDTO;
import br.me.moraes.cadastro_login.dto.RegisterDTO;
import br.me.moraes.cadastro_login.service.UserService;
import jakarta.validation.Valid;
import lombok.AllArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("auth")
@AllArgsConstructor
public class AuthenticationController {

    private UserService userService;

    @PostMapping("/login")
    public ResponseEntity login(@RequestBody @Valid AuthenticationDTO data){
        return userService.login(data);
    }

    @PostMapping("/register")
    public ResponseEntity register(@RequestBody @Valid RegisterDTO data){
        return userService.register(data);
    }

}
