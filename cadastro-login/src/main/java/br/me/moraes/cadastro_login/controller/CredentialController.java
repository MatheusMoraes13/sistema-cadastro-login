package br.me.moraes.cadastro_login.controller;

import br.me.moraes.cadastro_login.model.Credential;
import br.me.moraes.cadastro_login.service.CredentialService;
import lombok.AllArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/credential-service")
@AllArgsConstructor
public class CredentialController {

    private CredentialService credentialService;

    @PostMapping
    public ResponseEntity cadastrateCredential(@RequestBody Credential credential){
        return credentialService.cadastrateCredential(credential);
    }

    @GetMapping
    public ResponseEntity getAllCredentials(){
        return credentialService.getAllCredentials();
    }

    @GetMapping("/{service}")
    public ResponseEntity findByService(@PathVariable String service){
        return credentialService.findByService(service);
    }

//    public ResponseEntity deleteById(){}

    @GetMapping("/services")
    public ResponseEntity getServices(){
        return credentialService.getServices();
    }

}
