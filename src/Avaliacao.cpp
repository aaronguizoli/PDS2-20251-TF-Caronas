#include "Avaliacao.hpp"
#include "Usuario.hpp" // Inclui para usar Usuario*

namespace ufmg_carona {
    // Construtor da avaliação
    Avaliacao::Avaliacao(int n, std::string c, Usuario* av, Usuario* ad)
        : _nota(n), _comentario(c), _avaliador(av), _avaliado(ad) {}
    // Retorna a nota da avaliação
    int Avaliacao::get_nota() const { return _nota; }
}