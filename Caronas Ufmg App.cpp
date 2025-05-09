#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Estruturas básicas
struct Usuario {
    std::string nome;
    std::string tipo;
    std::string contato;
    float reputacao = 0.0;
    int avaliacoesRecebidas = 0;
    int somaAvaliacoes = 0;
};

struct Carona {
    std::string motorista;
    std::string origem;
    std::string destino;
    std::string horario;
    int vagas;
};

// Vetores para armazenar os dados
std::vector<Usuario> usuarios;
std::vector<Carona> caronas;

int main() {
    std::cout << "Bem-vindo ao app de caronas da UFMG!\n";
    // Aqui você irá implementar as funções de cadastro, publicação, avaliação, etc.
    return 0;
}
