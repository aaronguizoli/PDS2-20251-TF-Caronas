#include "Carona.hpp" // Inclui a declaração da classe
#include <iostream>
#include <algorithm>

Carona::Carona(std::string orig, std::string dest, std::string data, int vagas, double valor, std::shared_ptr<Usuario> mot)
    : origem(orig), destino(dest), dataHoraPartida(data), vagasDisponiveis(vagas), valorSugerido(valor), motorista(mot) {}

void Carona::adicionarSolicitacao(std::shared_ptr<Usuario> passageiro) {
    solicitacoesPendentes.push_back(passageiro);
    std::string msg = passageiro->nomeCompleto + " solicitou uma vaga na sua carona de " + origem + " para " + destino + ".";
    motorista->adicionarNotificacao(msg);
}

bool Carona::aprovarSolicitacao(std::shared_ptr<Usuario> passageiro) {
    if (vagasDisponiveis > 0) {
        passageirosAprovados.push_back(passageiro);
        vagasDisponiveis--;
        // Remove da lista de pendentes pelo e-mail
        solicitacoesPendentes.erase(
            std::remove_if(solicitacoesPendentes.begin(), solicitacoesPendentes.end(),
                           [&](const std::shared_ptr<Usuario>& p) { return p->email == passageiro->email; }),
            solicitacoesPendentes.end());
        
        std::string msg = "Sua solicitacao para a carona de " + origem + " para " + destino + " foi APROVADA.";
        passageiro->adicionarNotificacao(msg);
        return true;
    }
    return false;
}

void Carona::rejeitarSolicitacao(std::shared_ptr<Usuario> passageiro) {
    // Remove da lista de pendentes pelo e-mail
    solicitacoesPendentes.erase(
        std::remove_if(solicitacoesPendentes.begin(), solicitacoesPendentes.end(),
                       [&](const std::shared_ptr<Usuario>& p) { return p->email == passageiro->email; }),
        solicitacoesPendentes.end());
        
    std::string msg = "Sua solicitacao para a carona de " + origem + " para " + destino + " foi REJEITADA.";
    passageiro->adicionarNotificacao(msg);
}

void Carona::exibirResumo() const {
    std::cout << "  Origem: " << origem << " | Destino: " << destino << " | Data: " << dataHoraPartida << std::endl;
    std::cout << "  Motorista: " << motorista->nomeCompleto << " (" << motorista->getMediaDeAvaliacoes() << " estrelas)" << std::endl;
    std::cout << "  Vagas: " << vagasDisponiveis << " | Valor: R$ " << valorSugerido << std::endl;
}
