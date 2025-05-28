package br.me.moraes.cadastro_login.dto;

import br.me.moraes.cadastro_login.model.UserRole;

public record RegisterDTO(String name, String username, String email, String password, UserRole role) {
}
