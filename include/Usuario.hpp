/**
 * @file Usuario.hpp
 * @brief Define a classe Usuario, a classe base polimórfica para todos os tipos de usuários no sistema.
 */
#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include <vector>
#include "Notificacao.hpp"
#include "Avaliacao.hpp"
#include "Genero.hpp"

namespace ufmg_carona {

    /**
     * @brief Classe base que encapsula os dados e comportamentos comuns a todos os usuários.
     * Serve como a fundação para o polimorfismo no sistema, permitindo que diferentes
     * tipos de usuários (como Motorista) sejam tratados de forma uniforme.
     * @note Esta classe armazena ponteiros brutos em `_avaliacoes_recebidas`. Ela **não**
     * gerencia o tempo de vida (ownership) desses objetos `Avaliacao`. A responsabilidade
     * pela alocação e liberação da memória é de um componente externo (ex: a classe Sistema).
     */
    class Usuario {
    protected:
        /** @name Atributos do Usuário */
        ///@{
        std::string _nome, _cpf, _email, _senha;
        std::string _telefone;
        /**
         * @brief Data de nascimento do usuário, armazenada no formato "DD/MM/AAAA".
         */
        std::string _data_nascimento;
        Genero _genero;
        /**
         * @brief Vetor de ponteiros não-proprietários para as avaliações recebidas pelo usuário.
         */
        std::vector<Avaliacao*> _avaliacoes_recebidas;
        /**
         * @brief Vetor de notificações do usuário. Armazenadas por valor.
         */
        std::vector<Notificacao> _notificacoes;
        /**
         * @brief Tipo de vínculo com a UFMG (ex: "Aluno", "Professor", "Funcionario").
         */
        std::string _vinculo_tipo;
        /**
         * @brief Detalhe do vínculo (ex: "Ciência da Computação", "Departamento de Química").
         */
        std::string _detalhe_vinculo;
        ///@}

    public:
        /**
         * @brief Construtor da classe base Usuario.
         * @param nome Nome completo.
         * @param cpf CPF (usado como identificador único).
         * @param telefone Telefone de contato.
         * @param data_nascimento Data de nascimento no formato "DD/MM/AAAA".
         * @param email Endereço de e-mail (usado como identificador único).
         * @param senha Senha para autenticação.
         * @param genero Identidade de gênero.
         * @param vinculo_tipo Tipo de vínculo com a universidade.
         * @param detalhe_vinculo Detalhes do vínculo (curso, departamento, etc.).
         */
        Usuario(std::string nome, std::string cpf, std::string telefone, std::string data_nascimento, std::string email, std::string senha, Genero genero, std::string vinculo_tipo, std::string detalhe_vinculo);

        /**
         * @brief Destrutor virtual.
         * @note Essencial para garantir que os destrutores de classes derivadas (como Motorista)
         * sejam chamados corretamente durante a destruição polimórfica.
         */
        virtual ~Usuario();

        /** @name Getters de Informações Pessoais e de Vínculo */
        ///@{
        std::string get_vinculo() const;
        std::string get_vinculo_raw() const;
        std::string get_detalhe_vinculo() const;
        const std::string& get_email() const;
        const std::string& get_senha() const;
        Genero get_genero() const;
        const std::string& get_cpf() const;
        const std::string& get_nome() const;
        const std::string& get_telefone() const;
        const std::string& get_data_nascimento() const;
        ///@}

        /** @name Métodos de Autenticação e Identificação */
        ///@{
        /** @brief Compara a senha fornecida com a senha armazenada. @return `true` se as senhas coincidirem. */
        bool verificar_senha(const std::string& senha) const;
        
        /**
         * @brief Verifica se o usuário é um motorista.
         * @return Por padrão, retorna `false`. Classes derivadas como Motorista devem sobrescrever este método.
         */
        virtual bool is_motorista() const;
        ///@}
        
        /** @name Métodos de Avaliação e Reputação */
        ///@{
        /** @brief Calcula e retorna a média das notas das avaliações recebidas. @return A média, ou 0.0 se não houver avaliações. */
        double get_media_avaliacoes() const;
        /** @brief Determina a "medalha" de reputação do usuário com base na média de suas avaliações. @return Uma string com o nome da medalha (ex: "Bronze", "Ouro"). */
        std::string get_medalha() const;
        /** @brief Adiciona uma nova avaliação recebida à lista do usuário. @param avaliacao Ponteiro não-proprietário para a avaliação. */
        void adicionar_avaliacao_recebida(Avaliacao* avaliacao);
        ///@}

        /** @name Métodos de Perfil e Notificações */
        ///@{
        /** @brief Imprime as informações do perfil do usuário no console. É virtual para ser sobrescrito. */
        virtual void imprimir_perfil() const;
        /** @brief Adiciona uma nova notificação à lista do usuário. */
        void adicionar_notificacao(const Notificacao& notificacao);
        /** @brief Obtém acesso de leitura à lista de notificações. */
        const std::vector<Notificacao>& get_notificacoes() const;
        /** * @brief Obtém acesso de escrita à lista de notificações.
         * @return Uma referência mutável para o vetor de notificações.
         * @note Use com cuidado, pois permite a modificação direta do vetor interno. Útil para, por exemplo, marcar notificações como lidas.
         */
        std::vector<Notificacao>& get_notificacoes_mutavel();
        ///@}

        /** @name Setters para Modificação de Perfil */
        ///@{
        void set_email(const std::string& email);
        void set_telefone(const std::string& telefone);
        void set_senha(const std::string& senha);
        void set_genero(Genero genero);
        ///@}
    };
}
#endif