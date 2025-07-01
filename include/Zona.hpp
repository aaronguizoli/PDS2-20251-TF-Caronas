/**
 * @file Zona.hpp
 * @brief Define os enumeradores geográficos utilizados para classificar as rotas das caronas.
 */
#ifndef ZONA_HPP
#define ZONA_HPP

namespace ufmg_carona {
    
    /**
     * @brief Representa as zonas geográficas (regionais) de Belo Horizonte.
     * Utilizado para agrupar e buscar caronas com base na localização de
     * origem ou destino na cidade.
     */
    enum class Zona {
        PAMPULHA,
        CENTRO_SUL,
        NOROESTE,
        LESTE,
        OESTE,
        NORTE,
        VENDA_NOVA,
        BARREIRO
    };

    /**
     * @brief Especifica se o campus da UFMG é o ponto de partida ou de chegada de uma carona.
     * Facilita a busca por rotas que começam ou terminam na universidade.
     */
    enum class UFMGPosicao {
        ORIGEM,   /**< A carona se inicia na UFMG e tem como destino uma zona da cidade. */
        DESTINO   /**< A carona se inicia em uma zona da cidade e tem como destino a UFMG. */
    }; 
}

#endif