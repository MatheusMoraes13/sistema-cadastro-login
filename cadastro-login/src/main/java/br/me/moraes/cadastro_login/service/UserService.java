package br.me.moraes.cadastro_login.service;

import br.me.moraes.cadastro_login.model.User;
import feign.Response;
import jakarta.validation.constraints.NotNull;
import org.springframework.stereotype.Service;

@Service
public class UserService {

    public Response registerUser(@NotNull User user){

    }
}
