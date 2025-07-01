/**
 * @file Solicitacao.hpp
 * @brief Define a classe Solicitacao, que modela a requisição de um passageiro para entrar em uma carona.
 */
#ifndef SOLICITACAO_HPP
#define SOLICITACAO_HPP

#include <string>

namespace ufmg_carona {

    // Forward declarations para evitar dependências circulares.
    class Usuario;
    class Carona;

    /**
     * @brief Define o ciclo de vida e os estados possíveis de uma solicitação de carona.
     * Representa a máquina de estados do processo de negociação entre passageiro e motorista.
     */
    enum class StatusSolicitacao {
        PENDENTE,                        /**< A solicitação foi enviada e aguarda ação do motorista. */
        ACEITA,                          /**< O motorista aceitou o passageiro na carona. */
        RECUSADA,                        /**< O motorista recusou a solicitação. */
        AGUARDANDO_RESPOSTA_PASSAGEIRO,  /**< O motorista fez uma contraproposta de local e aguarda a resposta do passageiro. */
        RECUSADA_PROPOSTA_MOTORISTA      /**< O passageiro recusou a contraproposta do motorista. */
    };

    /**
     * @brief Modela uma solicitação de um passageiro para participar de uma carona.
     * Esta classe encapsula todo o fluxo de negociação, incluindo propostas de locais
     * e o estado final da solicitação, além de rastrear o status das avaliações pós-viagem.
     * @note Armazena ponteiros brutos para Usuario and Carona, mas não gerencia seu
     * tempo de vida (ownership). A responsabilidade pela memória desses objetos é externa.
     */
    class Solicitacao {
    private:
        /**
         * @brief Ponteiro para o usuário passageiro que fez a solicitação.
         */
        Usuario* _passageiro;

        /**
         * @brief Ponteiro para a carona que é o alvo da solicitação.
         */
        Carona* _carona_alvo;

        /**
         * @brief O estado atual da solicitação dentro do fluxo de negociação.
         */
        StatusSolicitacao _status;

        /**
         * @brief Ponto de encontro sugerido pelo passageiro.
         */
        std::string _local_embarque_passageiro;

        /**
         * @brief Ponto de desembarque sugerido pelo passageiro.
         */
        std::string _local_desembarque_passageiro;

        /**
         * @brief Contraproposta de local de embarque feita pelo motorista.
         */
        std::string _local_embarque_motorista_proposto;

        /**
         * @brief Contraproposta de local de desembarque feita pelo motorista.
         */
        std::string _local_desembarque_motorista_proposto;
        
        /**
         * @brief Flag para rastrear se o passageiro já avaliou o motorista após esta carona.
         */
        bool _passageiro_avaliou_motorista;

        /**
         * @brief Flag para rastrear se o motorista já avaliou o passageiro após esta carona.
         */
        bool _motorista_avaliou_passageiro;

    public:
        /**
         * @brief Construtor de uma nova solicitação.
         * @param passageiro Ponteiro para o usuário que faz a solicitação.
         * @param carona Ponteiro para a carona desejada.
         * @param local_embarque_p Ponto de embarque sugerido pelo passageiro.
         * @param local_desembarque_p Ponto de desembarque sugerido pelo passageiro.
         * @note Uma solicitação é criada com o status inicial PENDENTE.
         */
        Solicitacao(Usuario* passageiro, Carona* carona, std::string local_embarque_p, std::string local_desembarque_p);
        
        /** @name Métodos de Ação e Negociação */
        ///@{
        /** @brief Altera o status da solicitação para ACEITA. */
        void aceitar();
        /** @brief Altera o status da solicitação para RECUSADA. */
        void recusar();
        /** @brief Registra uma contraproposta do motorista e altera o status para AGUARDANDO_RESPOSTA_PASSAGEIRO. */
        void propor_locais_motorista(std::string local_embarque_m, std::string local_desembarque_m);
        /** @brief Ação do passageiro para aceitar a contraproposta. Altera o status para ACEITA. */
        void aceitar_proposta_motorista();
        /** @brief Ação do passageiro para recusar a contraproposta. Altera o status para RECUSADA_PROPOSTA_MOTORISTA. */
        void recusar_proposta_motorista();
        ///@}
        
        /** @name Setters */
        ///@{
        /** @brief Define manualmente o status da solicitação. */
        void set_status(StatusSolicitacao novo_status);
        /** @brief Associa a solicitação a um novo objeto de carona. */
        void set_carona(Carona* new_carona_ptr);
        ///@}

        /** @name Getters */
        ///@{
        Usuario* get_passageiro() const;
        Carona* get_carona() const;
        StatusSolicitacao get_status() const;
        /** @brief Obtém uma representação textual do status atual. @return String com o nome do status. */
        std::string get_status_string() const;
        const std::string& get_local_embarque_passageiro() const;
        const std::string& get_local_desembarque_passageiro() const;
        const std::string& get_local_embarque_motorista_proposto() const;
        const std::string& get_local_desembarque_motorista_proposto() const;
        ///@}

        /** @name Métodos de Exibição */
        ///@{
        /** @brief Exibe informações gerais da solicitação no console. */
        void exibir_info() const;
        /** @brief Exibe as informações da solicitação sob a perspectiva do motorista. */
        void exibir_para_motorista() const;
        ///@}

        /** @name Rastreamento de Avaliações */
        ///@{
        bool get_passageiro_avaliou_motorista() const;
        void set_passageiro_avaliou_motorista(bool avaliou);
        bool get_motorista_avaliou_passageiro() const;
        void set_motorista_avaliou_passageiro(bool avaliou);
        ///@}
    };
}
#endif