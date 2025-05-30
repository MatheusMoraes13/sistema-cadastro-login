package br.me.moraes.cadastro_login.dto;

public record CredentialDTO(String id,
        String service,
        String site,
        String name,
        String username,
        String login,
        String password) {

}
