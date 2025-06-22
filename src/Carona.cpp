#include "Carona.hpp"
#include "Usuario.hpp" // Para Usuario*
#include "Veiculo.hpp"
#include "Solicitacao.hpp" // Para Solicitacao*
#include <iostream>
#include <iomanip>
#include <algorithm> // Para std::find

namespace ufmg_carona {
    // Inicializa o ID da próxima carona
    int Carona::_proximo_id = 1;

    // Construtor da carona
    Carona::Carona(std::string origem, std::string destino, std::string data, Usuario* motorista, bool apenas_mulheres, TipoCarona tipo)
        : _id(gerar_proximo_id()),
          _origem(origem),
          _destino(destino),
          _data_hora_partida(data),
          _motorista(motorista),
          _passageiros(),
          _solicitacoes_pendentes(),
          _vagas_disponiveis(0),
          _apenas_mulheres(apenas_mulheres),
          _status(StatusCarona::AGUARDANDO),
          _tipo(tipo) {

        // Define as vagas disponíveis com base no veículo do motorista
        if (motorista && motorista->is_motorista()) {
            _vagas_disponiveis = motorista->get_veiculo().get_lugares() - 1;
        }
    }

    // Gera o próximo ID para a carona
    int Carona::gerar_proximo_id() { return _proximo_id++; }

    // Retorna o ID da carona
    int Carona::get_id() const { return _id; }
    // Retorna o motorista da carona
    Usuario* Carona::get_motorista() const { return _motorista; }
    // Retorna a origem da carona
    const std::string& Carona::get_origem() const { return _origem; }
    // Retorna o destino da carona
    const std::string& Carona::get_destino() const { return _destino; }
    // Retorna a data e hora da partida
    const std::string& Carona::get_data_hora() const { return _data_hora_partida; }
    // Retorna o número de vagas disponíveis
    int Carona::get_vagas_disponiveis() const { return _vagas_disponiveis; }
    // Verifica se a carona é apenas para mulheres
    bool Carona::get_apenas_mulheres() const { return _apenas_mulheres; }

    // Exibe as informações básicas da carona
    void Carona::exibir_info() const {
        std::cout << "\n--- Carona ID: " << _id << " ---" << std::endl;
        std::cout << "De: " << _origem << " -> Para: " << _destino << std::endl;
        std::cout << "Data/Hora: " << _data_hora_partida << std::endl;
        if (_motorista) {
            std::cout << "Motorista: " << _motorista->get_nome() << " | Avaliacao: "
                      << std::fixed << std::setprecision(1) << _motorista->get_media_avaliacoes() << " estrelas" << std::endl;
        }
        std::cout << "Vagas restantes: " << _vagas_disponiveis << std::endl;
        if (_apenas_mulheres) {
            std::cout << ">> Viagem exclusiva para mulheres <<" << std::endl;
        }
    }

    // Exibe informações detalhadas da carona
    void Carona::exibir_info_detalhada() const {
        exibir_info();
        std::cout << "Passageiros confirmados: " << _passageiros.size() << std::endl;
        std::cout << "Solicitacoes pendentes: " << _solicitacoes_pendentes.size() << std::endl;
    }

    // Adiciona uma solicitação à lista de pendentes
    void Carona::adicionar_solicitacao(Solicitacao* solicitacao) {
        _solicitacoes_pendentes.push_back(solicitacao);
    }

    // Retorna as solicitações pendentes
    const std::vector<Solicitacao*>& Carona::get_solicitacoes_pendentes() const {
        return _solicitacoes_pendentes;
    }

    // Verifica se existem solicitações pendentes
    bool Carona::tem_solicitacoes_pendentes() const {
        return !_solicitacoes_pendentes.empty();
    }

    // Adiciona um passageiro à carona
    void Carona::adicionar_passageiro(Usuario* passageiro) {
        if (_vagas_disponiveis > 0) {
            _passageiros.push_back(passageiro);
            _vagas_disponiveis--;
        }
    }

    // Remove um passageiro da carona
    void Carona::remover_passageiro(Usuario* passageiro) {
        auto it = std::find(_passageiros.begin(), _passageiros.end(), passageiro);
        if (it != _passageiros.end()) {
            _passageiros.erase(it);
            _vagas_disponiveis++;
        }
    }
}