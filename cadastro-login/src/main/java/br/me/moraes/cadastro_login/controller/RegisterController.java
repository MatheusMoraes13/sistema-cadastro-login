package br.me.moraes.cadastro_login.controller;

import br.me.moraes.cadastro_login.model.User;
import br.me.moraes.cadastro_login.service.UserService;
import feign.Response;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/register")
public class RegisterController {

    private UserService userService;

    @PostMapping
    public Response registerUsers(@RequestBody User user){

        userService.registerUser(user);

        return Response.builder().build();
    }
}
