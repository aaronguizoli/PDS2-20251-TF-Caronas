#include "Usuario.hpp" // Inclui a declaração da classe
#include <iostream>

// --- Construtores ---
Veiculo::Veiculo(std::string mod, std::string c, std::string p) : modelo(mod), cor(c), placa(p) {}

Notificacao::Notificacao(std::string msg) : mensagem(msg) {}

Avaliacao::Avaliacao(int n, std::string c, std::shared_ptr<Usuario> p_avaliador, std::shared_ptr<Usuario> p_avaliado)
    : nota(n), comentario(c), avaliador(p_avaliador), avaliado(p_avaliado) {}

Usuario::Usuario(std::string nome, std::string tel, std::string mail)
    : nomeCompleto(nome), telefone(tel), email(mail), veiculo(nullptr) {}


// --- Métodos da Classe Veiculo ---
void Veiculo::exibir() const {
    std::cout << "  - Veiculo: " << modelo << ", " << cor << ", Placa: " << placa << std::endl;
}


// --- Métodos da Classe Usuario ---
void Usuario::adicionarVeiculo(std::string modelo, std::string cor, std::string placa) {
    veiculo = std::make_unique<Veiculo>(modelo, cor, placa);
}

double Usuario::getMediaDeAvaliacoes() const {
    if (avaliacoesRecebidas.empty()) {
        return 0.0;
    }
    double soma = 0;
    for (const auto& avaliacao : avaliacoesRecebidas) {
        soma += avaliacao->nota;
    }
    return soma / avaliacoesRecebidas.size();
}

void Usuario::adicionarAvaliacao(std::shared_ptr<Avaliacao> avaliacao) {
    avaliacoesRecebidas.push_back(avaliacao);
}

void Usuario::adicionarNotificacao(const std::string& mensagem) {
    notificacoes.push_back(std::make_shared<Notificacao>(mensagem));
}

void Usuario::exibirPerfil() const {
    std::cout << "\n--- Perfil de " << nomeCompleto << " ---" << std::endl;
    std::cout << "  - E-mail: " << email << std::endl;
    std::cout << "  - Telefone: " << telefone << std::endl;
    std::cout << "  - Avaliacao Media: " << getMediaDeAvaliacoes() << " estrelas" << std::endl;
    if (veiculo) {
        veiculo->exibir();
    }
    std::cout << "---------------------------------" << std::endl;
}
