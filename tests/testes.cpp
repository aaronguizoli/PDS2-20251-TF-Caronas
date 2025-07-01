#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Usuario.hpp"
#include "Motorista.hpp"
#include "Carona.hpp"
#include "Solicitacao.hpp"
#include "Avaliacao.hpp"
#include "Veiculo.hpp"
#include "Notificacao.hpp"
#include "Genero.hpp"
#include "Zona.hpp"
#include "Sistema.hpp" 

namespace ufmg_carona {

TEST_CASE("Testes da Classe Usuario") {
    SUBCASE("Construtor e Getters Basicos") {
        Usuario user("Joao Silva", "12345678900", "31999998888", "01/01/2000", "joao@email.com", "senha123", Genero::MASCULINO, "aluno", "Ciencia da Computacao");

        CHECK(user.get_nome() == "Joao Silva");
        CHECK(user.get_cpf() == "12345678900");
        CHECK(user.get_telefone() == "31999998888");
        CHECK(user.get_data_nascimento() == "01/01/2000");
        CHECK(user.get_email() == "joao@email.com");
        CHECK(user.verificar_senha("senha123") == true); 
        CHECK(user.get_genero() == Genero::MASCULINO);
        CHECK(user.get_vinculo_raw() == "aluno");
        CHECK(user.get_detalhe_vinculo() == "Ciencia da Computacao");
        CHECK(user.is_motorista() == false);
    }

    SUBCASE("Verificar Senha") {
        Usuario user("Maria", "11122233344", "987654321", "05/05/1995", "maria@email.com", "maria123", Genero::FEMININO, "funcionario", "DCC");

        CHECK(user.verificar_senha("maria123") == true);
        CHECK(user.verificar_senha("senhaerrada") == false);
    }

    SUBCASE("Get Vinculo") {
        Usuario aluno("Pedro", "000", "000", "000", "pedro@ufmg.br", "123", Genero::MASCULINO, "aluno", "Engenharia Civil");
        Usuario func_setor("Ana", "111", "111", "111", "ana@ufmg.br", "123", Genero::FEMININO, "funcionario", "DRH");
        Usuario func_generico("Carlos", "222", "222", "222", "carlos@ufmg.br", "123", Genero::MASCULINO, "funcionario", "0");
        Usuario desconhecido("Julia", "333", "333", "333", "julia@ufmg.br", "123", Genero::OUTRO, "outro", "Detalhe");

        CHECK(aluno.get_vinculo() == "Aluno do curso de Engenharia Civil");
        CHECK(func_setor.get_vinculo() == "Funcionario do setor DRH");
        CHECK(func_generico.get_vinculo() == "Funcionario");
        CHECK(desconhecido.get_vinculo() == "Vinculo desconhecido");
    }

    SUBCASE("Adicionar Avaliacoes e Media") {
        Usuario user("Lucas", "99988877766", "111222333", "10/10/1990", "lucas@email.com", "lucas123", Genero::MASCULINO, "aluno", "Matematica");
        
        CHECK(user.get_media_avaliacoes() == 0.0); 
        CHECK(user.get_medalha() == "Nenhuma (sem avaliacoes ou media 0)");

        Usuario avaliador1("Avaliador1", "1", "1", "1", "a1@a.com", "1", Genero::MASCULINO, "a", "a");
        Usuario avaliador2("Avaliador2", "2", "2", "2", "a2@a.com", "2", Genero::MASCULINO, "a", "a");
        Usuario avaliador3("Avaliador3", "3", "3", "3", "a3@a.com", "3", Genero::MASCULINO, "a", "a");
        Motorista motorista_dummy("M_dummy", "4", "4", "4", "m@m.com", "4", Genero::MASCULINO, "m", "m", "123");
        Veiculo veiculo_dummy("ABC1234", "Fiat", "Uno", "Preto", 4);
        Carona carona_dummy("Origem", "Destino", Zona::PAMPULHA, Zona::CENTRO_SUL, UFMGPosicao::ORIGEM, "01/01/2030 10:00", &motorista_dummy, &veiculo_dummy, false, TipoCarona::AGENDADA);


        Avaliacao* aval1 = new Avaliacao(5, "Otimo!", &avaliador1, &user, &carona_dummy);
        user.adicionar_avaliacao_recebida(aval1);
        CHECK(user.get_media_avaliacoes() == 5.0);
        CHECK(user.get_medalha() == "Ouro");

        Avaliacao* aval2 = new Avaliacao(3, "Bom.", &avaliador2, &user, &carona_dummy);
        user.adicionar_avaliacao_recebida(aval2);
        CHECK(doctest::Approx(user.get_media_avaliacoes()) == 4.0); 
        CHECK(user.get_medalha() == "Prata"); 

        Avaliacao* aval3 = new Avaliacao(1, "Ruim.", &avaliador3, &user, &carona_dummy);
        user.adicionar_avaliacao_recebida(aval3);
        CHECK(doctest::Approx(user.get_media_avaliacoes()) == 3.0); 
        CHECK(user.get_medalha() == "Prata"); 

        Avaliacao* aval4 = new Avaliacao(2, "Mais ou menos.", &avaliador1, &user, &carona_dummy);
        user.adicionar_avaliacao_recebida(aval4);
        CHECK(doctest::Approx(user.get_media_avaliacoes()) == 2.75); 
        CHECK(user.get_medalha() == "Bronze"); 
    }

    SUBCASE("Setters") {
        Usuario user("Teste", "000", "000", "000", "teste@email.com", "senha", Genero::OUTRO, "outro", "nenhum"); 

        user.set_email("novo@email.com");
        CHECK(user.get_email() == "novo@email.com");

        user.set_telefone("987654321");
        CHECK(user.get_telefone() == "987654321");

        user.set_senha("novasenha");
        CHECK(user.get_senha() == "novasenha");

        user.set_genero(Genero::FEMININO);
        CHECK(user.get_genero() == Genero::FEMININO);
    }

    SUBCASE("Notificacoes") {
        Usuario user("Nathy", "44455566677", "987654321", "01/01/2000", "nathy@email.com", "123", Genero::FEMININO, "aluno", "Design");
        Notificacao n1("Carona confirmada!");
        Notificacao n2("Nova solicitacao!");

        user.adicionar_notificacao(n1);
        CHECK(user.get_notificacoes().size() == 1);
        CHECK(user.get_notificacoes()[0].get_mensagem() == "Carona confirmada!");

        user.adicionar_notificacao(n2);
        CHECK(user.get_notificacoes().size() == 2);
        CHECK(user.get_notificacoes()[1].get_mensagem() == "Nova solicitacao!");

        user.get_notificacoes_mutavel()[0].marcar_como_lida();
        CHECK(user.get_notificacoes()[0].is_lida() == true);
    }
}

TEST_CASE("Testes da Classe Carona") {
    Motorista motorista_teste("Motorista Teste", "12312312300", "31911112222", "10/01/1985", "mot@email.com", "pass", Genero::MASCULINO, "funcionario", "DCC", "123456789");
    Veiculo veiculo_teste("ABC1D23", "Toyota", "Corolla", "Prata", 4);
    Usuario passageiro_teste("Passageiro Teste", "09876543210", "31933334444", "02/02/2000", "pas@email.com", "pass", Genero::FEMININO, "aluno", "Engenharia");

    SUBCASE("Construtor e Getters") {
        Carona carona1("Centro", "Pampulha", Zona::CENTRO_SUL, Zona::PAMPULHA, UFMGPosicao::DESTINO, "20/07/2025 14:00", &motorista_teste, &veiculo_teste, false, TipoCarona::AGENDADA);

        CHECK(carona1.get_origem() == "Centro");
        CHECK(carona1.get_destino() == "Pampulha");
        CHECK(carona1.get_origem_zona() == Zona::CENTRO_SUL);
        CHECK(carona1.get_destino_zona() == Zona::PAMPULHA);
        CHECK(carona1.get_ufmg_posicao() == UFMGPosicao::DESTINO);
        CHECK(carona1.get_data_hora() == "20/07/2025 14:00");
        CHECK(carona1.get_motorista()->get_nome() == "Motorista Teste");
        CHECK(carona1.get_veiculo_usado()->get_placa() == "ABC1D23");
        CHECK(carona1.get_apenas_mulheres() == false);
        CHECK(carona1.get_vagas_disponiveis() == 3); 
        CHECK(carona1.get_status() == StatusCarona::AGUARDANDO);
        CHECK(Carona::gerar_proximo_id() > 1); 
    }

    SUBCASE("Set Status") {
        Carona carona2("Casa", "UFMG", Zona::NOROESTE, Zona::PAMPULHA, UFMGPosicao::DESTINO, "25/07/2025 08:00", &motorista_teste, &veiculo_teste, false, TipoCarona::AGENDADA);
        CHECK(carona2.get_status() == StatusCarona::AGUARDANDO);

        carona2.set_status(StatusCarona::EM_VIAGEM);
        CHECK(carona2.get_status() == StatusCarona::EM_VIAGEM);

        carona2.set_status(StatusCarona::FINALIZADA);
        CHECK(carona2.get_status() == StatusCarona::FINALIZADA);
    }

    SUBCASE("Adicionar e Remover Passageiro") {
        Carona carona3("Origem X", "Destino Y", Zona::LESTE, Zona::OESTE, UFMGPosicao::ORIGEM, "30/07/2025 18:00", &motorista_teste, &veiculo_teste, false, TipoCarona::AGENDADA);
        Usuario p1("P1", "p1", "p1", "p1", "p1", "p1", Genero::MASCULINO, "p", "p");
        Usuario p2("P2", "p2", "p2", "p2", "p2", "p2", Genero::FEMININO, "p", "p");
        
        CHECK(carona3.get_vagas_disponiveis() == 3);

        carona3.adicionar_passageiro(&p1);
        CHECK(carona3.get_vagas_disponiveis() == 2);

        carona3.adicionar_passageiro(&p2);
        CHECK(carona3.get_vagas_disponiveis() == 1);

        Usuario p3("P3", "p3", "p3", "p3", "p3", "p3", Genero::MASCULINO, "p", "p");
        Usuario p4("P4", "p4", "p4", "p4", "p4", "p4", Genero::FEMININO, "p", "p");

        carona3.adicionar_passageiro(&p3);
        CHECK(carona3.get_vagas_disponiveis() == 0);

        carona3.adicionar_passageiro(&p4); 
        CHECK(carona3.get_vagas_disponiveis() == 0);

        carona3.remover_passageiro(&p1);
        CHECK(carona3.get_vagas_disponiveis() == 1);

        carona3.remover_passageiro(&p4); 
        CHECK(carona3.get_vagas_disponiveis() == 1);
    }

    SUBCASE("Adicionar Solicitacao e Verificar Pendentes") {
        Carona carona4("Zona A", "Zona B", Zona::BARREIRO, Zona::VENDA_NOVA, UFMGPosicao::ORIGEM, "01/08/2025 09:00", &motorista_teste, &veiculo_teste, false, TipoCarona::AGENDADA);
        Usuario sol_req1("Solicitante1", "s1", "s1", "s1", "s1", "s1", Genero::MASCULINO, "s", "s");
        Usuario sol_req2("Solicitante2", "s2", "s2", "s2", "s2", "s2", Genero::FEMININO, "s", "s");

        Solicitacao* s1 = new Solicitacao(&sol_req1, &carona4, "Local A1", "Local B1");
        Solicitacao* s2 = new Solicitacao(&sol_req2, &carona4, "Local A2", "Local B2");

        CHECK(carona4.tem_solicitacoes_pendentes() == false);
        CHECK(carona4.get_solicitacoes_pendentes().empty() == true);

        carona4.adicionar_solicitacao(s1);
        CHECK(carona4.tem_solicitacoes_pendentes() == true);
        CHECK(carona4.get_solicitacoes_pendentes().size() == 1);
        CHECK(carona4.get_solicitacoes_pendentes()[0]->get_passageiro()->get_nome() == "Solicitante1");

        carona4.adicionar_solicitacao(s2);
        CHECK(carona4.get_solicitacoes_pendentes().size() == 2);
        CHECK(carona4.get_solicitacoes_pendentes()[1]->get_passageiro()->get_nome() == "Solicitante2");

        delete s1;
        delete s2;
    }
}

TEST_CASE("Testes da Classe Solicitacao") {
    Usuario passageiro_sol("P Sol", "p_sol", "p_sol", "p_sol", "p_sol", "p_sol", Genero::MASCULINO, "aluno", "Quimica");
    Motorista motorista_sol("M Sol", "m_sol", "m_sol", "m_sol", "m_sol", "m_sol", Genero::FEMININO, "funcionario", "Biblioteca", "987654321");
    Veiculo veiculo_sol("DEF4E56", "Honda", "Civic", "Azul", 5);
    Carona carona_sol("Local Origem", "Local Destino", Zona::PAMPULHA, Zona::CENTRO_SUL, UFMGPosicao::ORIGEM, "15/08/2025 16:00", &motorista_sol, &veiculo_sol, false, TipoCarona::AGENDADA);

    SUBCASE("Construtor e Getters") {
        Solicitacao solicitacao(&passageiro_sol, &carona_sol, "Rua A", "Rua B");

        CHECK(solicitacao.get_passageiro()->get_nome() == "P Sol");
        CHECK(solicitacao.get_carona()->get_id() == carona_sol.get_id());
        CHECK(solicitacao.get_local_embarque_passageiro() == "Rua A");
        CHECK(solicitacao.get_local_desembarque_passageiro() == "Rua B");
        CHECK(solicitacao.get_status() == StatusSolicitacao::PENDENTE);
        CHECK(solicitacao.get_status_string() == "PENDENTE");
        CHECK(solicitacao.get_passageiro_avaliou_motorista() == false);
        CHECK(solicitacao.get_motorista_avaliou_passageiro() == false);
    }

    SUBCASE("Aceitar e Recusar Solicitacao") {
        Solicitacao solicitacao_aceitar(&passageiro_sol, &carona_sol, "Ponto 1", "Ponto 2");
        solicitacao_aceitar.aceitar();
        CHECK(solicitacao_aceitar.get_status() == StatusSolicitacao::ACEITA);
        CHECK(solicitacao_aceitar.get_status_string() == "ACEITA");

        Solicitacao solicitacao_recusar(&passageiro_sol, &carona_sol, "Ponto 3", "Ponto 4");
        solicitacao_recusar.recusar();
        CHECK(solicitacao_recusar.get_status() == StatusSolicitacao::RECUSADA);
        CHECK(solicitacao_recusar.get_status_string() == "RECUSADA");
    }

    SUBCASE("Propor e Responder Locais do Motorista") {
        Solicitacao solicitacao_proposta(&passageiro_sol, &carona_sol, "Local Pass. Org", "Local Pass. Dest");

        solicitacao_proposta.propor_locais_motorista("Local Mot. Org", "Local Mot. Dest");
        CHECK(solicitacao_proposta.get_status() == StatusSolicitacao::AGUARDANDO_RESPOSTA_PASSAGEIRO);
        CHECK(solicitacao_proposta.get_status_string() == "AGUARDANDO RESPOSTA DO PASSAGEIRO");
        CHECK(solicitacao_proposta.get_local_embarque_motorista_proposto() == "Local Mot. Org");
        CHECK(solicitacao_proposta.get_local_desembarque_motorista_proposto() == "Local Mot. Dest");

        solicitacao_proposta.aceitar_proposta_motorista();
        CHECK(solicitacao_proposta.get_status() == StatusSolicitacao::ACEITA);
        CHECK(solicitacao_proposta.get_status_string() == "ACEITA");

        Solicitacao solicitacao_proposta2(&passageiro_sol, &carona_sol, "Local Pass. Org2", "Local Pass. Dest2");
        solicitacao_proposta2.propor_locais_motorista("Local Mot. Org2", "Local Mot. Dest2");
        solicitacao_proposta2.recusar_proposta_motorista();
        CHECK(solicitacao_proposta2.get_status() == StatusSolicitacao::RECUSADA_PROPOSTA_MOTORISTA);
        CHECK(solicitacao_proposta2.get_status_string() == "RECUSADA (PROPOSTA DO MOTORISTA)");
    }

    SUBCASE("Set Status Direto") {
        Solicitacao solicitacao_set_status(&passageiro_sol, &carona_sol, "A", "B");
        solicitacao_set_status.set_status(StatusSolicitacao::PENDENTE);
        CHECK(solicitacao_set_status.get_status() == StatusSolicitacao::PENDENTE);
        solicitacao_set_status.set_status(StatusSolicitacao::ACEITA);
        CHECK(solicitacao_set_status.get_status() == StatusSolicitacao::ACEITA);
    }

    SUBCASE("Setar Flags de Avaliacao") {
        Solicitacao sol_avaliacoes(&passageiro_sol, &carona_sol, "E", "F");

        CHECK(sol_avaliacoes.get_passageiro_avaliou_motorista() == false);
        sol_avaliacoes.set_passageiro_avaliou_motorista(true);
        CHECK(sol_avaliacoes.get_passageiro_avaliou_motorista() == true);

        CHECK(sol_avaliacoes.get_motorista_avaliou_passageiro() == false);
        sol_avaliacoes.set_motorista_avaliou_passageiro(true);
        CHECK(sol_avaliacoes.get_motorista_avaliou_passageiro() == true);
    }
}

} // namespace ufmg_carona