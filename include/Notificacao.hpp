/**
 * @file Notificacao.hpp
 * @brief Define a classe Notificacao, uma entidade simples para representar mensagens enviadas aos usuários.
 */
#ifndef NOTIFICACAO_HPP
#define NOTIFICACAO_HPP

#include <string>

namespace ufmg_carona {

    /**
     * @brief Encapsula uma mensagem e seu estado (lida/não lida) para comunicação com o usuário.
     * Esta classe é usada para informar os usuários sobre eventos importantes, como a aceitação
     * de uma solicitação de carona ou uma nova avaliação recebida.
     */
    class Notificacao {
    private:
        /**
         * @brief O conteúdo textual da notificação a ser exibido ao usuário.
         */
        std::string _mensagem;

        /**
         * @brief Flag booleana que indica se a notificação já foi visualizada pelo usuário.
         */
        bool _lida;

    public:
        /**
         * @brief Constrói um novo objeto Notificacao.
         * @param mensagem O texto da mensagem para a notificação.
         * @note Uma notificação é sempre criada com o estado "não lida" (`_lida = false`).
         */
        Notificacao(std::string mensagem);

        /**
         * @brief Altera o estado da notificação para "lida".
         * @note Esta é uma operação idempotente; chamar este método múltiplas vezes
         * não altera o estado após a primeira chamada.
         */
        void marcar_como_lida();

        /**
         * @brief Obtém a mensagem da notificação.
         * @return Uma referência constante para a string da mensagem, evitando cópias.
         */
        const std::string& get_mensagem() const;

        /**
         * @brief Verifica se a notificação foi marcada como lida.
         * @return `true` se a notificação foi lida, `false` caso contrário.
         */
        bool is_lida() const;
    };
}

#endif