#include "CaronaFactory.hpp"
#include "Usuario.hpp" // Para Usuario*

namespace ufmg_carona {
    // Cria uma nova carona
    Carona CaronaFactory::criar_carona(std::string o, std::string d, std::string dt, Usuario* m, bool am, TipoCarona t) {
        // Retorna um objeto Carona
        return Carona(o, d, dt, m, am, t);
    }
}