/**
 * @file Carona.hpp
 * @brief Define a classe Carona, a entidade central do sistema que representa uma viagem oferecida.
 */
#ifndef CARONA_HPP
#define CARONA_HPP

#include <string>
#include <vector>
#include "Zona.hpp" // Assumindo que UFMGPosicao também está aqui.

namespace ufmg_carona {
    
    // Forward declarations para evitar dependências circulares e otimizar a compilação.
    class Usuario;
    class Solicitacao;
    class Veiculo;

    /**
     * @brief Define o tipo de uma carona, se é agendada para o futuro ou imediata.
     */
    enum class TipoCarona {
        AGENDADA,  /**< A carona tem uma data e hora de partida futuras. */
        IMEDIATA   /**< A carona está pronta para partir assim que lotar. */
    };

    /**
     * @brief Representa os diferentes estados possíveis de uma carona durante seu ciclo de vida.
     */
    enum class StatusCarona {
        AGUARDANDO, /**< A carona está aguardando passageiros. */
        LOTADA,     /**< Todas as vagas foram preenchidas. */
        EM_VIAGEM,  /**< A carona está em andamento. */
        FINALIZADA, /**< A carona foi concluída com sucesso. */
        CANCELADA   /**< A carona foi cancelada pelo motorista. */
    };

    /**
     * @brief A entidade central do sistema, agregando todas as informações de uma carona.
     * @note Esta classe armazena ponteiros brutos (raw pointers) para várias outras entidades
     * (Usuario, Veiculo, Solicitacao). Ela não gerencia o tempo de vida (ownership) desses
     * objetos. A responsabilidade pela alocação e liberação da memória é externa a esta classe,
     * tipicamente controlada por uma classe "Gerenciador".
     */
    class Carona {
    private:
        /**
         * @brief Identificador numérico único para cada instância de Carona.
         */
        int _id;

        /**
         * @brief Contador estático para garantir a unicidade dos IDs gerados para novas caronas.
         */
        static int _proximo_id;
        
        /**
         * @brief Descrição textual do local de partida (ex: "Shopping Del Rey").
         */
        std::string _origem_nome;

        /**
         * @brief Descrição textual do local de destino (ex: "Reitoria UFMG").
         */
        std::string _destino_nome;

        /**
         * @brief Zona geográfica da cidade onde a carona se inicia.
         */
        Zona _origem_zona;

        /**
         * @brief Zona geográfica da cidade onde a carona termina.
         */
        Zona _destino_zona;

        /**
         * @brief Ponto de encontro ou dispersão dentro do campus da UFMG.
         */
        UFMGPosicao _ufmg_posicao;
        
        /**
         * @brief Data e hora de partida da carona, no formato "DD/MM/AAAA HH:MM".
         */
        std::string _data_hora_partida;

        /**
         * @brief Ponteiro para o objeto Usuario que está oferecendo a carona.
         */
        Usuario* _motorista;

        /**
         * @brief Ponteiro para o objeto Veiculo utilizado na carona.
         */
        Veiculo* _veiculo_usado;

        /**
         * @brief Vetor de ponteiros para os objetos Usuario dos passageiros confirmados.
         */
        std::vector<Usuario*> _passageiros;

        /**
         * @brief Vetor de ponteiros para as solicitações de participação pendentes de aprovação.
         */
        std::vector<Solicitacao*> _solicitacoes_pendentes;

        /**
         * @brief Número de assentos ainda disponíveis na carona.
         */
        int _vagas_disponiveis;

        /**
         * @brief Flag que indica se a carona é exclusiva para mulheres.
         */
        bool _apenas_mulheres;

        /**
         * @brief O estado atual da carona no seu ciclo de vida.
         */
        StatusCarona _status;

        /**
         * @brief O tipo da carona (agendada ou imediata).
         */
        TipoCarona _tipo;

    public:
        /**
         * @brief Construtor da classe Carona.
         * @param origem_nome Nome do local de origem.
         * @param destino_nome Nome do local de destino.
         * @param origem_zona Zona da cidade de origem.
         * @param destino_zona Zona da cidade de destino.
         * @param ufmg_posicao Ponto de referência na UFMG.
         * @param data Data e hora de partida no formato "DD/MM/AAAA HH:MM".
         * @param motorista Ponteiro para o usuário motorista.
         * @param veiculo_usado Ponteiro para o veículo a ser utilizado.
         * @param apenas_mulheres True se a carona for exclusiva para mulheres, false caso contrário.
         * @param tipo O tipo da carona (AGENDADA ou IMEDIATA).
         */
        Carona(std::string origem_nome, std::string destino_nome, Zona origem_zona, Zona destino_zona, UFMGPosicao ufmg_posicao, std::string data, Usuario* motorista, Veiculo* veiculo_usado, bool apenas_mulheres, TipoCarona tipo);
        
        /**
         * @brief Gera e retorna o próximo ID único para uma nova carona.
         * @return Um inteiro representando o próximo ID.
         */
        static int gerar_proximo_id();

        /**
         * @brief Obtém o ID único desta carona.
         * @return O ID da carona.
         */
        int get_id() const;

        /**
         * @brief Obtém o motorista desta carona.
         * @return Ponteiro para o objeto Usuario do motorista.
         */
        Usuario* get_motorista() const;

        /**
         * @brief Obtém o veículo utilizado nesta carona.
         * @return Ponteiro para o objeto Veiculo.
         */
        Veiculo* get_veiculo_usado() const;

        /**
         * @brief Obtém o nome do local de origem.
         * @return Referência constante para a string de origem.
         */
        const std::string& get_origem() const;

        /**
         * @brief Obtém o nome do local de destino.
         * @return Referência constante para a string de destino.
         */
        const std::string& get_destino() const;

        /**
         * @brief Obtém a zona de origem da carona.
         * @return O enum Zona correspondente à origem.
         */
        Zona get_origem_zona() const;

        /**
         * @brief Obtém a zona de destino da carona.
         * @return O enum Zona correspondente ao destino.
         */
        Zona get_destino_zona() const;

        /**
         * @brief Obtém o ponto de referência na UFMG.
         * @return O enum UFMGPosicao correspondente.
         */
        UFMGPosicao get_ufmg_posicao() const;

        /**
         * @brief Obtém o status atual da carona.
         * @return O enum StatusCarona correspondente.
         */
        StatusCarona get_status() const;

        /**
         * @brief Atualiza o status da carona.
         * @param novo_status O novo estado para a carona.
         */
        void set_status(StatusCarona novo_status);

        /**
         * @brief Obtém a data e hora de partida.
         * @return Referência constante para a string com a data e hora.
         */
        const std::string& get_data_hora() const;

        /**
         * @brief Obtém o número de vagas ainda disponíveis.
         * @return O número de vagas.
         */
        int get_vagas_disponiveis() const;

        /**
         * @brief Verifica se a carona é exclusiva para mulheres.
         * @return True se for apenas para mulheres, false caso contrário.
         */
        bool get_apenas_mulheres() const;

        /**
         * @brief Exibe no console um resumo das informações da carona.
         */
        void exibir_info() const;

        /**
         * @brief Exibe no console informações detalhadas da carona, incluindo passageiros.
         */
        void exibir_info_detalhada() const;

        /**
         * @brief Adiciona uma nova solicitação à lista de pendências da carona.
         * @param solicitacao Ponteiro para o objeto Solicitacao a ser adicionado.
         */
        void adicionar_solicitacao(Solicitacao* solicitacao);

        /**
         * @brief Obtém a lista de solicitações pendentes.
         * @return Referência constante para o vetor de ponteiros de Solicitacao.
         */
        const std::vector<Solicitacao*>& get_solicitacoes_pendentes() const;
        
        /**
         * @brief Verifica se existem solicitações pendentes para esta carona.
         * @return True se houver solicitações, false caso contrário.
         */
        bool tem_solicitacoes_pendentes() const;

        /**
         * @brief Adiciona um passageiro à lista de confirmados e decrementa as vagas.
         * @param passageiro Ponteiro para o objeto Usuario a ser adicionado.
         */
        void adicionar_passageiro(Usuario* passageiro);

        /**
         * @brief Remove um passageiro da lista de confirmados e incrementa as vagas.
         * @param passageiro Ponteiro para o objeto Usuario a ser removido.
         */
        void remover_passageiro(Usuario* passageiro);
    };
}
#endif