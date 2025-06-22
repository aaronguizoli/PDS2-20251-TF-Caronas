#include "Rotina.hpp"
namespace ufmg_carona {
    // Construtor da rotina
    Rotina::Rotina(DiaDaSemana dia, const std::string& h, const std::string& l, const std::string& d) : _dia(dia), _horario_saida(h), _local_saida_padrao(l), _destino_final(d) {}
    // Construtor padrão da rotina
    Rotina::Rotina() : _dia(DiaDaSemana::DOMINGO) {}
}