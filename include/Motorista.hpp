/**
 * @file Motorista.hpp
 * @brief Define a classe Motorista, uma especialização da classe Usuario que representa um motorista no sistema.
 */
#ifndef MOTORISTA_HPP
#define MOTORISTA_HPP

#include "Usuario.hpp"
#include "Veiculo.hpp"
#include <vector>

namespace ufmg_carona {

    /**
     * @brief Representa um usuário que também pode atuar como motorista, oferecendo caronas.
     * * Esta classe herda de Usuario, adicionando funcionalidades e atributos específicos
     * de um motorista, como o número da CNH e uma lista de veículos cadastrados.
     * * @note A classe Motorista armazena uma coleção de ponteiros brutos para objetos Veiculo.
     * Ela **não gerencia o tempo de vida (ownership)** desses objetos. A responsabilidade
     * pela criação e destruição dos veículos é de um componente externo (ex: GerenciadorVeiculos).
     */
    class Motorista : public Usuario {
    private:
        /**
         * @brief Vetor de ponteiros para os veículos pertencentes a este motorista.
         */
        std::vector<Veiculo*> _veiculos;

        /**
         * @brief Número de registro da Carteira Nacional de Habilitação (CNH) do motorista.
         */
        std::string _cnh_numero;

    public:
        /**
         * @brief Construtor da classe Motorista.
         * * @param nome Nome completo do usuário.
         * @param cpf Cadastro de Pessoa Física (deve ser único).
         * @param telefone Número de telefone para contato.
         * @param data_nascimento Data de nascimento no formato "DD/MM/AAAA".
         * @param email Endereço de e-mail (deve ser único).
         * @param senha Senha para acesso ao sistema.
         * @param genero Identidade de gênero do usuário.
         * @param vinculo_tipo Tipo de vínculo com a UFMG (ex: "Aluno", "Professor").
         * @param detalhe_vinculo Detalhe do vínculo (ex: "Ciência da Computação", "DCC").
         * @param cnh_numero Número da CNH do motorista.
         */
        Motorista(std::string nome, std::string cpf, std::string telefone, std::string data_nascimento,
                  std::string email, std::string senha, Genero genero, std::string vinculo_tipo,
                  std::string detalhe_vinculo, std::string cnh_numero);

        /**
         * @brief Destrutor da classe Motorista.
         * @note Este destrutor **não** libera a memória dos objetos Veiculo apontados
         * pelos ponteiros no vetor _veiculos. Ele apenas destrói o vetor de ponteiros.
         */
        ~Motorista() override;

        /**
         * @brief Sobrescreve o método da classe base para exibir o perfil completo do motorista.
         * @note Inclui informações específicas do motorista, como a CNH e a lista de veículos.
         */
        void imprimir_perfil() const override;

        /**
         * @brief Adiciona um veículo à lista do motorista.
         * @param veiculo Ponteiro para o objeto Veiculo a ser adicionado. A posse não é transferida.
         */
        void adicionar_veiculo(Veiculo* veiculo);

        /**
         * @brief Identifica o tipo do objeto polimorficamente.
         * @return Sempre `true` para instâncias da classe Motorista.
         */
        bool is_motorista() const override;
        
        /**
         * @brief Obtém o número da CNH do motorista.
         * @return Referência constante para a string do número da CNH.
         */
        const std::string& get_cnh_numero() const;

        /**
         * @brief Obtém a lista de veículos do motorista.
         * @return Referência constante para o vetor de ponteiros de Veiculo.
         */
        const std::vector<Veiculo*>& get_veiculos() const;

        /**
         * @brief Busca um veículo na lista do motorista pela placa.
         * @param placa A placa do veículo a ser buscado.
         * @return Um ponteiro para o objeto Veiculo se encontrado, caso contrário, `nullptr`.
         */
        Veiculo* buscar_veiculo_por_placa(const std::string& placa) const;

        /**
         * @brief Busca um veículo na lista do motorista pelo seu índice no vetor.
         * @param indice O índice do veículo a ser buscado.
         * @return Um ponteiro para o objeto Veiculo se o índice for válido, caso contrário, `nullptr`.
         * @note O chamador deve garantir que o índice está dentro dos limites do vetor.
         */
        Veiculo* buscar_veiculo_por_indice(size_t indice) const;

        /**
         * @brief Remove um veículo da lista do motorista com base na placa.
         * @param placa A placa do veículo a ser removido.
         * @return `true` se o veículo foi encontrado e removido, `false` caso contrário.
         * @note Esta função apenas remove o ponteiro do vetor, não deleta o objeto Veiculo.
         */
        bool remover_veiculo(const std::string& placa);
    };
}

#endif