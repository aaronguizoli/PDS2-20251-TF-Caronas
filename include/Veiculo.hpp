/**
 * @file Veiculo.hpp
 * @brief Define a classe Veiculo, que encapsula os dados de um veículo cadastrado no sistema.
 */
#ifndef VEICULO_HPP
#define VEICULO_HPP

#include <string>

namespace ufmg_carona {

    /**
     * @brief Modela um veículo, contendo todas as suas informações relevantes.
     * Esta classe atua como uma estrutura de dados para armazenar os detalhes
     * de um veículo que pode ser utilizado em uma carona.
     */
    class Veiculo {
    private:
        /**
         * @brief Placa do veículo, usada como identificador único (ex: "ABC-1234" ou "ABC1D23").
         */
        std::string _placa;
        std::string _marca;
        std::string _modelo;
        std::string _cor;
        
        /**
         * @brief Número total de lugares no veículo, incluindo o assento do motorista.
         */
        int _total_de_lugares;

    public:
        /**
         * @brief Construtor principal para criar um objeto Veiculo totalmente inicializado.
         * @param placa A placa do veículo (identificador único).
         * @param marca A fabricante do veículo (ex: "Fiat", "Chevrolet").
         * @param modelo O modelo do veículo (ex: "Uno", "Onix").
         * @param cor A cor predominante do veículo.
         * @param lugares O número total de assentos, incluindo o do motorista.
         */
        Veiculo(const std::string& placa, const std::string& marca, const std::string& modelo, const std::string& cor, int lugares);

        /**
         * @brief Construtor padrão.
         * @note Cria um objeto Veiculo em um estado padrão (vazio). Útil para cenários
         * onde um objeto precisa ser criado e seus dados preenchidos posteriormente.
         */
        Veiculo();

        /** @name Getters */
        ///@{
        /**
         * @brief Obtém o número total de lugares do veículo.
         * @return O número total de assentos (incluindo o do motorista).
         */
        int get_lugares() const;

        const std::string& get_placa() const;
        const std::string& get_marca() const;
        const std::string& get_modelo() const;
        const std::string& get_cor() const;
        ///@}

        /** @name Setters
         * @note Note que a placa do veículo é imutável após a construção para garantir
         * a integridade do identificador.
        */
        ///@{
        void set_marca(const std::string& marca);
        void set_modelo(const std::string& modelo);
        void set_cor(const std::string& cor);
        void set_lugares(int lugares);
        ///@}

        /**
         * @brief Exibe as informações formatadas do veículo no console.
         * Útil para fins de depuração e interface com o usuário.
         */
        void exibir_info() const;
    };
}

#endif