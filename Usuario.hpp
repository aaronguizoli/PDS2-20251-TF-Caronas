#pragma once // Evita que o arquivo seja incluído múltiplas vezes

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>

// Forward declarations to avoid circular dependencies
class Carona;
class Avaliacao;

class Veiculo {
public:
    std::string modelo;
    std::string cor;
    std::string placa;

    Veiculo(std::string mod, std::string c, std::string p);
    void exibir() const;
};

class Notificacao {
public:
    std::string mensagem;
    bool lida = false;

    Notificacao(std::string msg);
};

class Usuario {
private:
    std::vector<std::shared_ptr<Avaliacao>> avaliacoesRecebidas;

public:
    std::string nomeCompleto;
    std::string telefone;
    std::string email;
    std::unique_ptr<Veiculo> veiculo;
    std::vector<std::shared_ptr<Notificacao>> notificacoes;
    std::vector<std::shared_ptr<Carona>> historicoDeCaronas;

    Usuario(std::string nome, std::string tel, std::string mail);
    
    void adicionarVeiculo(std::string modelo, std::string cor, std::string placa);
    double getMediaDeAvaliacoes() const;
    void adicionarAvaliacao(std::shared_ptr<Avaliacao> avaliacao);
    void adicionarNotificacao(const std::string& mensagem);
    void exibirPerfil() const;
};

class Avaliacao {
public:
    int nota;
    std::string comentario;
    std::weak_ptr<Usuario> avaliador;
    std::weak_ptr<Usuario> avaliado;

    Avaliacao(int n, std::string c, std::shared_ptr<Usuario> p_avaliador, std::shared_ptr<Usuario> p_avaliado);
};
