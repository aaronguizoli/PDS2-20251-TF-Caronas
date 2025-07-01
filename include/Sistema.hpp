/**
 * @file Sistema.hpp
 * @brief Define a classe Sistema, o orquestrador central de toda a aplicação de caronas.
 */
#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <vector>
#include <string>
#include <tuple>
#include <fstream>
#include <ctime>
#include <map>

#include "Usuario.hpp"
#include "Motorista.hpp"
#include "Carona.hpp"
#include "Solicitacao.hpp"
#include "Genero.hpp"
#include "Veiculo.hpp"
#include "Avaliacao.hpp"
#include "Zona.hpp"

namespace ufmg_carona {

    /**
     * @brief A classe principal que gerencia o estado, os dados e os fluxos de interação do usuário.
     * Atua como um orquestrador para toda a aplicação, inicializando subsistemas,
     * controlando o loop principal e garantindo a persistência dos dados.
     * @note Esta classe é a **proprietária (owner)** de todos os objetos alocados dinamicamente
     * cujos ponteiros são armazenados em seus vetores (ex: _usuarios, _solicitacoes, _avaliacoes_globais).
     * Seu destrutor é responsável por liberar toda essa memória para evitar memory leaks.
     */
    class Sistema {
    private:
        /** @name Contêineres de Dados Principais */
        ///@{
        /**
         * @brief Vetor de ponteiros para todos os usuários cadastrados. O Sistema é o dono desses objetos.
         */
        std::vector<Usuario*> _usuarios;
        
        /**
         * @brief Vetor de todos os objetos de carona. Armazenados por valor, o gerenciamento de memória é automático.
         */
        std::vector<Carona> _caronas;

        /**
         * @brief Vetor de ponteiros para todas as solicitações de carona. O Sistema é o dono desses objetos.
         */
        std::vector<Solicitacao*> _solicitacoes;

        /**
         * @brief Vetor de ponteiros para todas as avaliações realizadas no sistema. O Sistema é o dono desses objetos.
         */
        std::vector<Avaliacao*> _avaliacoes_globais;
        ///@}

        /** @name Estado da Aplicação */
        ///@{
        /**
         * @brief Ponteiro não-proprietário para o usuário atualmente logado na sessão. `nullptr` se ninguém estiver logado.
         */
        Usuario* _usuario_logado;
        ///@}
        
        /** @name Utilitários de Conversão */
        ///@{
        /**
         * @brief Mapas para conversão entre enums e tipos primitivos/strings, usados para I/O e persistência.
         */
        std::map<int, Zona> _int_para_zona;
        std::map<Zona, std::string> _zona_para_string;
        std::map<int, UFMGPosicao> _int_para_ufmg_posicao;
        std::map<UFMGPosicao, std::string> _ufmg_posicao_para_string;
        ///@}

        /** @name Persistência de Dados */
        ///@{
        /** @brief Carrega todos os dados de arquivos de texto no início da execução. */
        void carregar_dados_iniciais();
        /** @brief Salva os dados de usuários em arquivo. */
        void salvar_dados_usuarios();
        /** @brief Salva os dados de veículos em arquivo. */
        void salvar_dados_veiculos();
        /** @brief Salva as caronas ativas em arquivo. */
        void salvar_dados_caronas();
        /** @brief Carrega as caronas ativas de arquivo. */
        void carregar_dados_caronas();
        /** @brief Carrega as solicitações de arquivo. */
        void carregar_dados_solicitacoes();
        /** @brief Salva as solicitações em arquivo. */
        void salvar_dados_solicitacoes();
        /** @brief Salva as avaliações em arquivo. */
        void salvar_dados_avaliacoes();
        /** @brief Carrega as avaliações de arquivo. */
        void carregar_dados_avaliacoes();
        ///@}

        /** @name Buscas Internas */
        ///@{
        /** @brief Procura um usuário pelo seu CPF. @return Ponteiro para o Usuario se encontrado, senão `nullptr`. */
        Usuario* buscar_usuario_por_cpf(const std::string& cpf);
        /** @brief Procura uma carona pelo seu ID. @return Ponteiro para a Carona se encontrada, senão `nullptr`. */
        Carona* buscar_carona_por_id(int id);
        /** @brief Procura um veículo pela placa dentro da lista de um motorista específico. @return Ponteiro para o Veiculo se encontrado, senão `nullptr`. */
        Veiculo* buscar_veiculo_por_placa_motorista(Motorista* motorista, const std::string& placa);
        /** @brief Simula uma consulta a uma base de dados externa da UFMG. @return Uma tupla contendo (sucesso, nome, vínculo, detalhe_vínculo, email). */
        std::tuple<bool, std::string, std::string, std::string, std::string> buscar_dados_ufmg_por_cpf(const std::string& cpf_buscado);
        ///@}

        /** @name Interface com Usuário (Menus) */
        ///@{
        /** @brief Exibe o menu para usuários não autenticados. */
        void exibir_menu_inicial_nao_logado();
        /** @brief Exibe o menu principal para usuários autenticados. */
        void exibir_menu_logado();
        /** @brief Exibe as opções específicas para o modo passageiro. */
        void exibir_menu_passageiro();
        /** @brief Exibe as opções específicas para o modo motorista. */
        void exibir_menu_motorista();
        /** @brief Orquestra qual menu deve ser exibido com base no estado de login. */
        void exibir_menu(); 
        ///@}

        /** @name Processamento de Comandos */
        ///@{
        /** @brief Processa uma entrada de comando do usuário logado. */
        void processar_comando_logado(const std::string& comando_str);
        ///@}

        /** @name Fluxos de Interação do Usuário */
        ///@{
        void fluxo_cadastro();
        void fluxo_login();
        void fluxo_logout();
        void fluxo_oferecer_carona();
        void fluxo_solicitar_carona();
        void fluxo_status_caronas();
        void fluxo_cadastrar_veiculo();
        void fluxo_editar_perfil();
        void fluxo_passageiro_menu();
        void fluxo_motorista_menu();
        void fluxo_editar_perfil_ou_veiculos();
        void fluxo_tornar_motorista();
        void fluxo_gerenciar_veiculos();
        void fluxo_editar_veiculo(Motorista* motorista);
        void fluxo_excluir_veiculo(Motorista* motorista);
        void fluxo_gerenciar_caronas();
        void fluxo_solicitacoes_pendentes_motorista();
        void fluxo_minhas_caronas(Motorista* motorista_logado);
        void fluxo_avaliacoes();
        void fluxo_avaliar_carona_passageiro();
        void fluxo_avaliar_passageiros_motorista();
        void exibir_minhas_avaliacoes_recebidas();
        void exibir_avaliacoes_que_fiz();
        ///@}

        /** @name Lógica de Negócio e Helpers */
        ///@{
        /** @brief Envia uma notificação para um usuário. */
        void enviar_notificacao(Usuario* usuario, const std::string& mensagem, bool enviar_para_motorista = true);
        /** @brief Verifica se um passageiro cumpre os pré-requisitos para solicitar uma carona. */
        bool pode_solicitar_carona(Usuario* passageiro, const Carona& carona);
        /** @brief Cancela automaticamente outras solicitações de um passageiro quando uma é aceita. */
        void cancelar_outras_solicitacoes_passageiro(Usuario* passageiro, const Carona& carona_aceita);
        /** @brief Finaliza uma carona e todas as suas solicitações associadas. */
        void finalizar_carona_completa(Carona* carona_para_finalizar);
        /** @brief Cancela uma carona e notifica todos os envolvidos. */
        void cancelar_carona_completa(Carona* carona_para_cancelar);
        /** @brief Remove da memória as caronas que já aconteceram. */
        void remover_caronas_passadas();
        ///@}
        
        /** @name Utilitários de Input/Output e Conversão */
        ///@{
        int coletar_int_input(const std::string& prompt, int min_val, int max_val);
        std::string coletar_string_input(const std::string& prompt);
        Zona coletar_zona_input(const std::string& prompt);
        UFMGPosicao coletar_ufmg_posicao_input(const std::string& prompt);
        std::string zona_to_string(Zona z) const;
        Zona string_to_zona(const std::string& s) const;
        std::string ufmg_posicao_to_string(UFMGPosicao up) const;
        UFMGPosicao string_to_ufmg_posicao(const std::string& s) const;
        std::tm parse_datetime_string(const std::string& dt_str) const;
        std::string get_current_datetime_string() const;
        bool is_datetime_in_past(const std::string& dt_str) const;
        ///@}

    public:
        /**
         * @brief Construtor do Sistema. Inicializa os contêineres e carrega os dados iniciais dos arquivos.
         */
        Sistema();

        /**
         * @brief Destrutor do Sistema. Garante que todos os dados sejam salvos e, crucialmente,
         * libera toda a memória alocada dinamicamente para os objetos nos vetores de ponteiros.
         */
        ~Sistema();

        /**
         * @brief Ponto de entrada público que inicia e executa o loop principal da aplicação.
         */
        void executar();
    };
}
#endif