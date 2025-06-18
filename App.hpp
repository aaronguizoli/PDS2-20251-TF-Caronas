#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>
#include "Usuario.hpp"
#include "Carona.hpp"

class App {
private:
    std::map<std::string, std::shared_ptr<Usuario>> usuariosPorEmail;
    std::vector<std::shared_ptr<Carona>> caronasDisponiveis;
    std::shared_ptr<Usuario> usuarioLogado = nullptr;

    void limparBufferEntrada();
    std::shared_ptr<Usuario> findUsuarioPorNome(const std::string& nome);
    
    void salvarDados() const;
    void carregarDados();
    
    void gerenciarPerfil();
    void telaOferecerCarona();
    void telaGerenciarSolicitacoes();
    void telaBuscarCarona();
    void telaVerNotificacoes();
    void telaHistorico();
    void telaDeAvaliacao();
    void login();

public:
    void rodar();
};
