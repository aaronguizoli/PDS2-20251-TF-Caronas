#include "Solicitacao.hpp"
#include "Usuario.hpp" // Para Usuario*
#include "Carona.hpp"
#include <iostream>

namespace ufmg_carona {
    // Construtor da solicitação
    Solicitacao::Solicitacao(Usuario* p, Carona* c) : _passageiro(p), _carona_alvo(c), _status(StatusSolicitacao::PENDENTE) {}

    // Aceita a solicitação
    void Solicitacao::aceitar() { _status = StatusSolicitacao::ACEITA; }
    // Recusa a solicitação
    void Solicitacao::recusar() { _status = StatusSolicitacao::RECUSADA; }

    // Retorna o passageiro da solicitação
    Usuario* Solicitacao::get_passageiro() const { return _passageiro; }
    // Retorna a carona alvo da solicitação
    Carona* Solicitacao::get_carona() const { return _carona_alvo; }
    // Retorna o status da solicitação
    StatusSolicitacao Solicitacao::get_status() const { return _status; }

    // Retorna o status da solicitação como string
    std::string Solicitacao::get_status_string() const {
        switch (_status) {
            case StatusSolicitacao::PENDENTE: return "PENDENTE";
            case StatusSolicitacao::ACEITA: return "ACEITA";
            case StatusSolicitacao::RECUSADA: return "RECUSADA";
            default: return "DESCONHECIDO";
        }
    }

    // Exibe as informações da solicitação
    void Solicitacao::exibir_info() const {
        std::cout << "Carona ID: " << _carona_alvo->get_id()
                  << " | Status: " << get_status_string() << std::endl;
    }

    // Exibe as informações da solicitação para o motorista
    void Solicitacao::exibir_para_motorista() const {
        std::cout << "Solicitacao de: " << _passageiro->get_nome()
                  << " | Carona ID: " << _carona_alvo->get_id()
                  << " | Status: " << get_status_string() << std::endl;
    }
}