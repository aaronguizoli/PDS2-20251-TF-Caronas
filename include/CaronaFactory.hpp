/**
 * @file Carona_factory.hpp
 * @brief Define a classe CaronaFactory, responsável pela criação de instâncias da classe Carona.
 */
#ifndef CARONA_FACTORY_HPP
#define CARONA_FACTORY_HPP

#include "Carona.hpp"
#include "Zona.hpp" 
#include <string>

namespace ufmg_carona {
    
    // Forward declarations para evitar inclusões desnecessárias.
    class Usuario;
    class Veiculo;

    /**
     * @brief Implementa o padrão de projeto "Factory Method" para a criação de objetos Carona.
     * * Esta classe abstrai e centraliza o processo de instanciação de caronas, permitindo
     * que a lógica de criação seja isolada e facilmente mantida ou estendida no futuro,
     * sem que o código cliente precise conhecer os detalhes da construção de uma Carona.
     * * @note Como todos os seus métodos são estáticos, esta classe não foi projetada para ser instanciada.
     * Ela serve como um utilitário de construção.
     */
    class CaronaFactory {
    public:
        /**
         * @brief Cria e retorna uma nova instância de um objeto Carona.
         * * @param origem_nome Nome do local de origem.
         * @param destino_nome Nome do local de destino.
         * @param origem_zona Zona da cidade de origem.
         * @param destino_zona Zona da cidade de destino.
         * @param ufmg_posicao Ponto de referência na UFMG.
         * @param data Data e hora de partida no formato "DD/MM/AAAA HH:MM".
         * @param motorista Ponteiro para o usuário motorista.
         * @param veiculo_usado Ponteiro para o veículo a ser utilizado.
         * @param apenas_mulheres True se a carona for exclusiva para mulheres, false caso contrário.
         * @param tipo O tipo da carona (AGENDADA ou IMEDIATA).
         * @return Um objeto Carona totalmente inicializado.
         * * @note Os ponteiros para motorista e veiculo_usado são repassados para o construtor
         * da Carona. A fábrica não assume a propriedade (ownership) desses ponteiros.
         */
        static Carona criar_carona(std::string origem_nome, std::string destino_nome, Zona origem_zona, Zona destino_zona, UFMGPosicao ufmg_posicao, std::string data, Usuario* motorista, Veiculo* veiculo_usado, bool apenas_mulheres, TipoCarona tipo);
    };
}
#endif