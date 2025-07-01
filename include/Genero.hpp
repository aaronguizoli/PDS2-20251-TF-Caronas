/**
 * @file Genero.hpp
 * @brief Define o enumerador Genero para representar as opções de identidade de gênero dos usuários.
 */
#ifndef GENERO_HPP
#define GENERO_HPP

namespace ufmg_carona {
    
    /**
     * @brief Representa as opções de identidade de gênero para um perfil de usuário.
     * @note O uso de 'enum class' garante segurança de tipo (type-safety), evitando
     * conversões implícitas para inteiros.
     */
    enum class Genero {
        MASCULINO,              /**< Representa o gênero masculino. */
        FEMININO,               /**< Representa o gênero feminino. */
        OUTRO,                  /**< Para identidades de gênero não-binárias ou outras especificações. */
        PREFIRO_NAO_INFORMAR    /**< Opção para o usuário que não deseja fornecer esta informação. */
    }; 
}

#endif