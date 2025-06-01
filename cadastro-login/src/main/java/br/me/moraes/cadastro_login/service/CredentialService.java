package br.me.moraes.cadastro_login.service;

import br.me.moraes.cadastro_login.model.Credential;
import br.me.moraes.cadastro_login.model.Services;
import br.me.moraes.cadastro_login.repository.CredentialRepository;
import br.me.moraes.cadastro_login.repository.ServicesRepository;
import lombok.AllArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
@AllArgsConstructor
public class CredentialService {

    private CredentialRepository credentialRepository;
    private ServicesRepository servicesRepository;

    public ResponseEntity cadastrateCredential(Credential credential){
        if(hasCredential(credential)){
            return ResponseEntity.badRequest().body("Credencial já cadastrada");
        } else if (!servicesRepository.existsByName(credential.getService())) {
            servicesRepository.save(new Services(credential.getService()));
        }

        credentialRepository.save(credential);

        return ResponseEntity.status(HttpStatus.CREATED).body("Credencial cadastrada com sucesso");
    }

    public ResponseEntity<List<Credential>> getAllCredentials(){
        List<Credential> allCredentials = credentialRepository.findAll();

        if (allCredentials.isEmpty()){
            return ResponseEntity.noContent().build();
        }

        return ResponseEntity.ok(allCredentials);
    }

    public ResponseEntity<List<Credential>> findByService(String service){
        List<Credential> foudByService = credentialRepository.findByService(service);

        if (foudByService.isEmpty()){
            return ResponseEntity.noContent().build();
        }

        return ResponseEntity.ok(foudByService);
    }

    public ResponseEntity<List<Services>> getServices(){
        List<Services> foundServices = servicesRepository.findAll();

        if(foundServices.isEmpty()){
            return ResponseEntity.noContent().build();
        }

        return ResponseEntity.ok(foundServices);
    }

    private boolean hasCredential(Credential credential) {
        List<Credential> foundCredentials = credentialRepository.findByLoginAndPassword(credential.getLogin(), credential.getPassword());

        for(Credential c : foundCredentials) {
            if (c.equals(credential)) {
                return true;
            }
        }

        return false;
    }


}
