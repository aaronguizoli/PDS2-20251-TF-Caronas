/**
 * @file Excecoes.hpp
 * @brief Define a hierarquia de exceções customizadas para a aplicação de caronas.
 * Centralizar as exceções em um único arquivo promove um tratamento de erros consistente
 * e padronizado em todo o sistema.
 */
#ifndef EXCECOES_HPP
#define EXCECOES_HPP

#include <stdexcept>
#include <string>

namespace ufmg_carona {

    /**
     * @brief Classe base para todas as exceções específicas da aplicação.
     * @note Herdar de std::runtime_error permite que essas exceções se integrem
     * ao sistema de exceções padrão do C++. Todas as exceções do projeto devem
     * herdar desta classe para permitir a captura genérica de erros da aplicação
     * através de um bloco `catch (const AppExcecao& e)`.
     */
    class AppExcecao : public std::runtime_error { 
    public: 
        explicit AppExcecao(const std::string& message) : std::runtime_error(message) {} 
    };

    /**
     * @brief Exceção lançada quando uma tentativa de login falha.
     * @note Deve ser utilizada quando as credenciais (CPF e senha) fornecidas
     * pelo usuário não correspondem a um registro válido no sistema.
     */
    class AutenticacaoFalhouException : public AppExcecao { 
    public: 
        AutenticacaoFalhouException() : AppExcecao("CPF ou senha invalidos.") {} 
    };

    /**
     * @brief Exceção lançada ao tentar solicitar participação em uma carona sem vagas.
     */
    class CaronaLotadaException : public AppExcecao { 
    public: 
        CaronaLotadaException() : AppExcecao("A carona selecionada nao possui mais vagas disponiveis.") {} 
    };

    /**
     * @brief Exceção lançada quando o sistema recebe um comando de usuário não reconhecido.
     * @note Útil em interfaces de linha de comando (CLI) para sinalizar que a entrada
     * do usuário não corresponde a nenhuma ação válida.
     */
    class ComandoInvalidoException : public AppExcecao { 
    public: 
        /**
         * @brief Construtor da exceção de comando inválido.
         * @param comando A string exata do comando que foi inserido pelo usuário e não foi reconhecido.
         */
        ComandoInvalidoException(const std::string& comando) : AppExcecao("Comando '" + comando + "' nao reconhecido.") {} 
    };
}

#endif