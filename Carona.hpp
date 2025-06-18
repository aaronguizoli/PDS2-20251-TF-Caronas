#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Usuario.hpp" // Carona precisa conhecer a definição de Usuario

class Carona {
public:
    std::string origem;
    std::string destino;
    std::string dataHoraPartida;
    int vagasDisponiveis;
    double valorSugerido;
    std::shared_ptr<Usuario> motorista;
    std::vector<std::shared_ptr<Usuario>> passageirosAprovados;
    std::vector<std::shared_ptr<Usuario>> solicitacoesPendentes;

    Carona(std::string orig, std::string dest, std::string data, int vagas, double valor, std::shared_ptr<Usuario> mot);

    void adicionarSolicitacao(std::shared_ptr<Usuario> passageiro);
    bool aprovarSolicitacao(std::shared_ptr<Usuario> passageiro);
    void rejeitarSolicitacao(std::shared_ptr<Usuario> passageiro);
    void exibirResumo() const;
};
