/**
 * @file Avaliacao.hpp
 * @brief Define a classe Avaliacao, que encapsula os dados de uma avaliação feita 
 * por um usuário a outro no contexto de uma carona específica.
 */
#ifndef AVALIACAO_HPP
#define AVALIACAO_HPP

#include <string>

namespace ufmg_carona {

    // Forward declarations para evitar inclusões circulares e otimizar a compilação.
    class Usuario; 
    class Carona;

    /**
     * [cite_start]@brief Modela uma avaliação que um usuário faz a outro após uma carona. [cite: 18]
     * @note Esta classe armazena ponteiros brutos para os objetos Usuario e Carona.
     * Ela não gerencia o tempo de vida (ownership) desses objetos, ou seja, a
     * [cite_start]responsabilidade pela alocação e liberação da memória é externa. [cite: 30]
     */
    class Avaliacao {
    private:
        /**
         * @brief Nota da avaliação. Deve ser um valor inteiro em uma escala pré-definida (ex: 1 a 5).
         */
        int _nota;
        
        /**
         * @brief Comentário textual opcional que detalha a avaliação.
         */
        std::string _comentario;
        
        /**
         * @brief Ponteiro para o usuário que realizou a avaliação.
         */
        Usuario* _avaliador;
        
        /**
         * @brief Ponteiro para o usuário que foi o alvo da avaliação.
         */
        Usuario* _avaliado;
        
        /**
         * @brief Ponteiro para a carona à qual esta avaliação se refere.
         */
        Carona* _carona_referencia;

    public:
        /**
         * @brief Construtor da classe Avaliacao.
         * @param nota A nota numérica da avaliação.
         * @param comentario O comentário textual da avaliação.
         * @param avaliador Ponteiro para o usuário que está fazendo a avaliação.
         * @param avaliado Ponteiro para o usuário que está sendo avaliado.
         * @param carona_ref Ponteiro para a carona de referência.
         */
        Avaliacao(int nota, std::string comentario, Usuario* avaliador, Usuario* avaliado, Carona* carona_ref);

        /**
         * @brief Obtém a nota da avaliação.
         * @return A nota como um valor inteiro.
         */
        int get_nota() const;

        /**
         * @brief Obtém o comentário da avaliação.
         * @return Uma referência constante para a string do comentário, evitando cópias desnecessárias.
         */
        const std::string& get_comentario() const;

        /**
         * @brief Obtém o usuário que realizou a avaliação.
         * @return Um ponteiro para o objeto Usuario do avaliador.
         */
        Usuario* get_avaliador() const;

        /**
         * @brief Obtém o usuário que foi avaliado.
         * @return Um ponteiro para o objeto Usuario do avaliado.
         */
        Usuario* get_avaliado() const;

        /**
         * @brief Obtém a carona a qual a avaliação se refere.
         * @return Um ponteiro para o objeto Carona de referência.
         */
        Carona* get_carona_referencia() const;
    };
}
#endif