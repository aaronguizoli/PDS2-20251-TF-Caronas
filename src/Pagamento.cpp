#include "Pagamento.hpp"
#include <cmath> // Para std::abs

namespace ufmg_carona {
    // Definição das constantes de taxa
    const double Pagamento::TAXA_BASE = 2.00;
    const double Pagamento::ADICIONAL_POR_ZONA = 1.50;

    // Construtor do pagamento
    Pagamento::Pagamento(Zona origem, Zona destino) : _efetuado(false) {
        this->_valor = calcular_valor(origem, destino);
    }

    // Calcula o valor do pagamento com base nas zonas de origem e destino
    double Pagamento::calcular_valor(Zona origem, Zona destino) {
        int z1 = static_cast<int>(origem);
        int z2 = static_cast<int>(destino);
        int diferenca_zonas = std::abs(z1 - z2);

        if (diferenca_zonas == 0) {
            return TAXA_BASE;
        }
        
        return TAXA_BASE + (diferenca_zonas * ADICIONAL_POR_ZONA);
    }

    // Retorna o valor do pagamento
    double Pagamento::get_valor() const {
        return this->_valor;
    }

    // Verifica se o pagamento foi efetuado
    bool Pagamento::is_efetuado() const {
        return this->_efetuado;
    }

    // Marca o pagamento como efetuado
    void Pagamento::efetuar_pagamento() {
        this->_efetuado = true;
    }
}