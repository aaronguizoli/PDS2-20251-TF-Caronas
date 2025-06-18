// ===============================================
// Arquivo: Usuario.cpp
// ===============================================
#include "Usuario.hpp" // Inclui a declaração da classe
#include <iostream>

// Construtores
Veiculo::Veiculo(std::string mod, std::string c, std::string p) : modelo(mod), cor(c), placa(p) {}
Notificacao::Notificacao(std::string msg) : mensagem(msg) {}
Avaliacao::Avaliacao(int n, std::string c, std::shared_ptr<Usuario> p_avaliador, std::shared_ptr<Usuario> p_avaliado)
    : nota(n), comentario(c), avaliador(p_avaliador), avaliado(p_avaliado) {}
Usuario::Usuario(std::string nome, std::string tel, std::string mail)
    : nomeCompleto(nome), telefone(tel), email(mail), veiculo(nullptr) {}

// Métodos de Veiculo
void Veiculo::exibir() const {
    std::cout << "  - Veiculo: " << modelo << ", " << cor << ", Placa: " << placa << std::endl;
}

// Métodos de Usuario
void Usuario::adicionarVeiculo(std::string modelo, std::string cor, std::string placa) {
    veiculo = std::make_unique<Veiculo>(modelo, cor, placa);
}

double Usuario::getMediaDeAvaliacoes() const {
    if (avaliacoesRecebidas.empty()) {
        return 0.0;
    }
    double soma = 0;
    for (const auto& avaliacao : avaliacoesRecebidas) {
        soma += avaliaco->nota;
    }
    return soma / avaliacoesRecebidas.size();
}

void Usuario::adicionarAvaliacao(std::shared_ptr<Avaliacao> avaliacao) {
    avaliacoesRecebidas.push_back(avaliacao);
}

void Usuario::adicionarNotificacao(const std::string& mensagem) {
    notificacoes.push_back(std::make_shared<Notificacao>(mensagem));
}

void Usuario::exibirPerfil() const {
    std::cout << "\n--- Perfil de " << nomeCompleto << " ---" << std::endl;
    std::cout << "  - E-mail: " << email << std::endl;
    std::cout << "  - Telefone: " << telefone << std::endl;
    std::cout << "  - Avaliacao Media: " << getMediaDeAvaliacoes() << " estrelas" << std::endl;
    if (veiculo) {
        veiculo->exibir();
    }
    std::cout << "---------------------------------" << std::endl;
}


// ===============================================
// Arquivo: Carona.cpp
// ===============================================
#include "Carona.hpp" // Inclui a declaração da classe
#include <iostream>
#include <algorithm>

Carona::Carona(std::string orig, std::string dest, std::string data, int vagas, double valor, std::shared_ptr<Usuario> mot)
    : origem(orig), destino(dest), dataHoraPartida(data), vagasDisponiveis(vagas), valorSugerido(valor), motorista(mot) {}

void Carona::adicionarSolicitacao(std::shared_ptr<Usuario> passageiro) {
    solicitacoesPendentes.push_back(passageiro);
    std::string msg = passageiro->nomeCompleto + " solicitou uma vaga na sua carona de " + origem + " para " + destino + ".";
    motorista->adicionarNotificacao(msg);
}

bool Carona::aprovarSolicitacao(std::shared_ptr<Usuario> passageiro) {
    if (vagasDisponiveis > 0) {
        passageirosAprovados.push_back(passageiro);
        vagasDisponiveis--;
        solicitacoesPendentes.erase(
            std::remove_if(solicitacoesPendentes.begin(), solicitacoesPendentes.end(),
                           [&](const std::shared_ptr<Usuario>& p) { return p->email == passageiro->email; }),
            solicitacoesPendentes.end());
        
        std::string msg = "Sua solicitacao para a carona de " + origem + " para " + destino + " foi APROVADA.";
        passageiro->adicionarNotificacao(msg);
        return true;
    }
    return false;
}

void Carona::rejeitarSolicitacao(std::shared_ptr<Usuario> passageiro) {
    solicitacoesPendentes.erase(
        std::remove_if(solicitacoesPendentes.begin(), solicitacoesPendentes.end(),
                       [&](const std::shared_ptr<Usuario>& p) { return p->email == passageiro->email; }),
        solicitacoesPendentes.end());
        
    std::string msg = "Sua solicitacao para a carona de " + origem + " para " + destino + " foi REJEITADA.";
    passageiro->adicionarNotificacao(msg);
}

void Carona::exibirResumo() const {
    std::cout << "  Origem: " << origem << " | Destino: " << destino << " | Data: " << dataHoraPartida << std::endl;
    std::cout << "  Motorista: " << motorista->nomeCompleto << " (" << motorista->getMediaDeAvaliacoes() << " estrelas)" << std::endl;
    std::cout << "  Vagas: " << vagasDisponiveis << " | Valor: R$ " << valorSugerido << std::endl;
}


// ===============================================
// Arquivo: App.cpp
// ===============================================
#include "App.hpp" // Inclui a declaração da classe
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>

void App::limparBufferEntrada() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::shared_ptr<Usuario> App::findUsuarioPorNome(const std::string& nome) {
    for(const auto& par : usuariosPorEmail) {
        if (par.second->nomeCompleto == nome) {
            return par.second;
        }
    }
    return nullptr;
}

void App::salvarDados() const {
    std::ofstream arquivoUsuarios("usuarios.txt");
    if (arquivoUsuarios.is_open()) {
        for (const auto& par : usuariosPorEmail) {
            const auto& usuario = par.second;
            arquivoUsuarios << usuario->nomeCompleto << ";" << usuario->email << ";" << usuario->telefone << ";";
            if (usuario->veiculo) {
                arquivoUsuarios << "1;" << usuario->veiculo->modelo << ";" << usuario->veiculo->cor << ";" << usuario->veiculo->placa << "\n";
            } else {
                arquivoUsuarios << "0;nenhum;nenhum;nenhum\n";
            }
        }
    }
    std::ofstream arquivoCaronas("caronas.txt");
    if(arquivoCaronas.is_open()){
        for(const auto& carona : caronasDisponiveis){
            arquivoCaronas << carona->motorista->nomeCompleto << ";" << carona->origem << ";" << carona->destino << ";"
                           << carona->dataHoraPartida << ";" << carona->vagasDisponiveis << ";" << carona->valorSugerido << ";";
            for(size_t i = 0; i < carona->passageirosAprovados.size(); ++i){
                arquivoCaronas << carona->passageirosAprovados[i]->nomeCompleto << (i == carona->passageirosAprovados.size() - 1 ? "" : ",");
            }
            arquivoCaronas << ";";
            for(size_t i = 0; i < carona->solicitacoesPendentes.size(); ++i){
                arquivoCaronas << carona->solicitacoesPendentes[i]->nomeCompleto << (i == carona->solicitacoesPendentes.size() - 1 ? "" : ",");
            }
            arquivoCaronas << "\n";
        }
    }
}

void App::carregarDados() {
    std::ifstream arquivoUsuarios("usuarios.txt");
    std::string linha, nome, email, tel, temVeiculo, modelo, cor, placa;
    if (arquivoUsuarios.is_open()) {
        while (std::getline(arquivoUsuarios, linha)) {
            std::stringstream ss(linha);
            std::getline(ss, nome, ';');
            std::getline(ss, email, ';');
            std::getline(ss, tel, ';');
            std::getline(ss, temVeiculo, ';');
            auto novoUsuario = std::make_shared<Usuario>(nome, tel, email);
            if (temVeiculo == "1") {
                std::getline(ss, modelo, ';');
                std::getline(ss, cor, ';');
                std::getline(ss, placa, ';');
                novoUsuario->adicionarVeiculo(modelo, cor, placa);
            }
            usuariosPorEmail[email] = novoUsuario;
        }
    }
    std::ifstream arquivoCaronas("caronas.txt");
    if(arquivoCaronas.is_open()){
        while (std::getline(arquivoCaronas, linha)) {
            std::stringstream ss(linha);
            std::string nomeMotorista, origem, destino, data, vagasStr, valorStr, aprovadosStr, pendentesStr;
            int vagas;
            double valor;
            std::getline(ss, nomeMotorista, ';');
            std::getline(ss, origem, ';');
            std::getline(ss, destino, ';');
            std::getline(ss, data, ';');
            std::getline(ss, vagasStr, ';');
            std::getline(ss, valorStr, ';');
            std::getline(ss, aprovadosStr, ';');
            std::getline(ss, pendentesStr, ';');
            auto motoristaPtr = findUsuarioPorNome(nomeMotorista);
            if(motoristaPtr){
                vagas = std::stoi(vagasStr);
                valor = std::stod(valorStr);
                auto novaCarona = std::make_shared<Carona>(origem, destino, data, vagas, valor, motoristaPtr);
                if (!aprovadosStr.empty()) {
                    std::stringstream ssAprovados(aprovadosStr);
                    std::string nomeAprovado;
                    while(std::getline(ssAprovados, nomeAprovado, ',')){
                        auto passageiroPtr = findUsuarioPorNome(nomeAprovado);
                        if(passageiroPtr) novaCarona->passageirosAprovados.push_back(passageiroPtr);
                    }
                }
                if (!pendentesStr.empty()) {
                    std::stringstream ssPendentes(pendentesStr);
                    std::string nomePendente;
                    while(std::getline(ssPendentes, nomePendente, ',')){
                         auto passageiroPtr = findUsuarioPorNome(nomePendente);
                        if(passageiroPtr) novaCarona->solicitacoesPendentes.push_back(passageiroPtr);
                    }
                }
                caronasDisponiveis.push_back(novaCarona);
                motoristaPtr->historicoDeCaronas.push_back(novaCarona);
                for(const auto& p : novaCarona->passageirosAprovados) p->historicoDeCaronas.push_back(novaCarona);
                for(const auto& p : novaCarona->solicitacoesPendentes) p->historicoDeCaronas.push_back(novaCarona);
            }
        }
    }
}

void App::gerenciarPerfil() {
    if (!usuarioLogado) return;
    int opcao;
    std::cout << "\n--- Gerenciar Perfil ---\n1. Editar Nome e Telefone\n2. Adicionar/Modificar Veiculo\n0. Voltar\nEscolha: ";
    std::cin >> opcao;
    limparBufferEntrada();
    if (opcao == 1) {
        std::cout << "Novo nome completo: ";
        std::getline(std::cin, usuarioLogado->nomeCompleto);
        std::cout << "Novo telefone: ";
        std::getline(std::cin, usuarioLogado->telefone);
        std::cout << "Perfil atualizado com sucesso!" << std::endl;
    } else if (opcao == 2) {
        std::string modelo, cor, placa;
        std::cout << "Modelo do veiculo: ";
        std::getline(std::cin, modelo);
        std::cout << "Cor do veiculo: ";
        std::getline(std::cin, cor);
        std::cout << "Placa do veiculo: ";
        std::getline(std::cin, placa);
        usuarioLogado->adicionarVeiculo(modelo, cor, placa);
        std::cout << "Veiculo atualizado com sucesso!" << std::endl;
    }
}

void App::telaOferecerCarona() {
    if (!usuarioLogado || !usuarioLogado->veiculo) {
        std::cout << "Voce precisa cadastrar um veiculo para oferecer caronas." << std::endl;
        return;
    }
    std::string origem, destino, data;
    int vagas;
    double valor;
    std::cout << "\n--- Oferecer Carona ---\nOrigem: ";
    std::getline(std::cin, origem);
    std::cout << "Destino: ";
    std::getline(std::cin, destino);
    std::cout << "Data e Hora (DD/MM/AAAA HH:MM): ";
    std::getline(std::cin, data);
    std::cout << "Vagas: ";
    std::cin >> vagas;
    std::cout << "Valor (R$): ";
    std::cin >> valor;
    limparBufferEntrada();
    auto novaCarona = std::make_shared<Carona>(origem, destino, data, vagas, valor, usuarioLogado);
    caronasDisponiveis.push_back(novaCarona);
    usuarioLogado->historicoDeCaronas.push_back(novaCarona);
    std::cout << "\nCarona oferecida com sucesso!" << std::endl;
}

void App::telaGerenciarSolicitacoes() {
    if (!usuarioLogado) return;
    std::vector<std::shared_ptr<Carona>> minhasCaronas;
    for(const auto& carona : caronasDisponiveis) {
        if (carona->motorista == usuarioLogado && !carona->solicitacoesPendentes.empty()) {
            minhasCaronas.push_back(carona);
        }
    }
    if (minhasCaronas.empty()) {
        std::cout << "\nNenhuma solicitacao pendente." << std::endl;
        return;
    }
    std::cout << "\n--- Caronas com Solicitacoes Pendentes ---" << std::endl;
    for (size_t i = 0; i < minhasCaronas.size(); ++i) {
        std::cout << "\nCarona " << i + 1 << ":" << std::endl;
        minhasCaronas[i]->exibirResumo();
        std::cout << "  Solicitacoes:" << std::endl;
        for(const auto& passageiro : minhasCaronas[i]->solicitacoesPendentes) {
            std::cout << "   - " << passageiro->nomeCompleto << std::endl;
        }
    }
    int escolhaCarona;
    std::cout << "\nEscolha a carona (0 para sair): ";
    std::cin >> escolhaCarona;
    if (escolhaCarona <= 0 || escolhaCarona > minhasCaronas.size()) return;
    auto caronaGerenciada = minhasCaronas[escolhaCarona-1];
    std::string nomePassageiro;
    limparBufferEntrada();
    std::cout << "Digite o nome do passageiro: ";
    std::getline(std::cin, nomePassageiro);
    std::shared_ptr<Usuario> passageiroEscolhido = nullptr;
    for(const auto& p : caronaGerenciada->solicitacoesPendentes) {
        if (p->nomeCompleto == nomePassageiro) {
            passageiroEscolhido = p;
            break;
        }
    }
    if(!passageiroEscolhido){
        std::cout << "Passageiro nao encontrado." << std::endl;
        return;
    }
    int acao;
    std::cout << "1. Aceitar | 2. Rejeitar: ";
    std::cin >> acao;
    if(acao == 1) {
        if(caronaGerenciada->aprovarSolicitacao(passageiroEscolhido))
             std::cout << "Passageiro aceito!" << std::endl;
        else
             std::cout << "Nao ha vagas." << std::endl;
    } else if (acao == 2) {
        caronaGerenciada->rejeitarSolicitacao(passageiroEscolhido);
        std::cout << "Passageiro rejeitado." << std::endl;
    }
}

void App::telaBuscarCarona() {
    if (!usuarioLogado) return;
    std::string origem, destino;
    std::cout << "\n--- Buscar Carona ---\nOrigem (deixe em branco para ignorar): ";
    std::getline(std::cin, origem);
    std::cout << "Destino (deixe em branco para ignorar): ";
    std::getline(std::cin, destino);
    std::vector<std::shared_ptr<Carona>> resultados;
    for(const auto& carona : caronasDisponiveis) {
        bool matchOrigem = origem.empty() || carona->origem == origem;
        bool matchDestino = destino.empty() || carona->destino == destino;
        if (matchOrigem && matchDestino && carona->vagasDisponiveis > 0 && carona->motorista != usuarioLogado) {
            resultados.push_back(carona);
        }
    }
    if (resultados.empty()) {
        std::cout << "Nenhuma carona encontrada." << std::endl;
        return;
    }
    std::cout << "\n--- Caronas Encontradas ---" << std::endl;
    for (size_t i = 0; i < resultados.size(); ++i) {
        std::cout << "\n--- Opcao " << i + 1 << " ---" << std::endl;
        resultados[i]->exibirResumo();
    }
    int escolha;
    std::cout << "\nSolicitar carona (0 para voltar): ";
    std::cin >> escolha;
    limparBufferEntrada();
    if (escolha > 0 && escolha <= resultados.size()) {
        auto caronaEscolhida = resultados[escolha - 1];
        caronaEscolhida->adicionarSolicitacao(usuarioLogado);
        usuarioLogado->historicoDeCaronas.push_back(caronaEscolhida);
        std::cout << "Solicitacao enviada!" << std::endl;
    }
}

void App::telaVerNotificacoes() {
    if (!usuarioLogado || usuarioLogado->notificacoes.empty()) {
        std::cout << "\nNenhuma notificacao." << std::endl;
        return;
    }
    std::cout << "\n--- Suas Notificacoes ---" << std::endl;
    for (const auto& notif : usuarioLogado->notificacoes) {
        if(!notif->lida) {
            std::cout << "  - " << notif->mensagem << std::endl;
            notif->lida = true;
        }
    }
    std::cout << "-------------------------" << std::endl;
}

void App::telaHistorico() {
    if (!usuarioLogado || usuarioLogado->historicoDeCaronas.empty()) {
        std::cout << "\nSem historico de caronas." << std::endl;
        return;
    }
    std::cout << "\n--- Historico de Caronas ---\n\n-- Caronas Oferecidas --" << std::endl;
    bool ofereceuAlguma = false;
    for(const auto& carona : usuarioLogado->historicoDeCaronas) {
        if (carona->motorista == usuarioLogado) {
            carona->exibirResumo();
            std::cout << "   Passageiros: ";
            if(carona->passageirosAprovados.empty()) std::cout << "Nenhum";
            for(const auto& p : carona->passageirosAprovados) std::cout << p->nomeCompleto << " ";
            std::cout << std::endl;
            ofereceuAlguma = true;
        }
    }
    if(!ofereceuAlguma) std::cout << "Nenhuma." << std::endl;
    std::cout << "\n-- Caronas que Voce Participou --" << std::endl;
    bool participouDeAlguma = false;
    for(const auto& carona : usuarioLogado->historicoDeCaronas) {
        for(const auto& p : carona->passageirosAprovados){
            if(p == usuarioLogado){
                carona->exibirResumo();
                participouDeAlguma = true;
                break;
            }
        }
    }
    if(!participouDeAlguma) std::cout << "Nenhuma." << std::endl;
}

void App::telaDeAvaliacao() {
    if (!usuarioLogado || usuarioLogado->historicoDeCaronas.empty()) {
        std::cout << "Nao ha caronas no historico para avaliar." << std::endl;
        return;
    }
    std::cout << "Qual carona do historico voce quer avaliar?" << std::endl;
    for(size_t i = 0; i < usuarioLogado->historicoDeCaronas.size(); ++i) {
        std::cout << i+1 << ". " << usuarioLogado->historicoDeCaronas[i]->origem << " -> " << usuarioLogado->historicoDeCaronas[i]->destino << std::endl;
    }
    int escolha;
    std::cin >> escolha;
    if(escolha <= 0 || escolha > usuarioLogado->historicoDeCaronas.size()) return;
    auto caronaParaAvaliar = usuarioLogado->historicoDeCaronas[escolha-1];
    limparBufferEntrada();
    if (caronaParaAvaliar->motorista == usuarioLogado) {
        if(caronaParaAvaliar->passageirosAprovados.empty()){
            std::cout << "Carona sem passageiros para avaliar." << std::endl;
            return;
        }
        for(const auto& passageiro : caronaParaAvaliar->passageirosAprovados) {
            std::cout << "\nAvaliando passageiro: " << passageiro->nomeCompleto << std::endl;
            int nota;
            std::string comentario;
            std::cout << "Nota (1-5): ";
            std::cin >> nota;
            limparBufferEntrada();
            std::cout << "Comentario (opcional): ";
            std::getline(std::cin, comentario);
            auto avaliacao = std::make_shared<Avaliacao>(nota, comentario, usuarioLogado, passageiro);
            passageiro->adicionarAvaliacao(avaliacao);
            std::cout << "Avaliacao enviada!" << std::endl;
        }
    } else {
         std::cout << "\nAvaliando motorista: " << caronaParaAvaliar->motorista->nomeCompleto << std::endl;
        int nota;
        std::string comentario;
        std::cout << "Nota (1-5): ";
        std::cin >> nota;
        limparBufferEntrada();
        std::cout << "Comentario (opcional): ";
        std::getline(std::cin, comentario);
        auto avaliacao = std::make_shared<Avaliacao>(nota, comentario, usuarioLogado, caronaParaAvaliar->motorista);
        caronaParaAvaliar->motorista->adicionarAvaliacao(avaliacao);
        std::cout << "Avaliacao enviada!" << std::endl;
    }
}

void App::login() {
    std::string email;
    std::cout << "Digite seu email para entrar ou criar uma conta: ";
    std::getline(std::cin, email);
    if (usuariosPorEmail.count(email)) {
        usuarioLogado = usuariosPorEmail[email];
        std::cout << "Bem-vindo(a) de volta, " << usuarioLogado->nomeCompleto << "!" << std::endl;
    } else {
        std::string nome, tel;
        std::cout << "Perfil novo. Vamos criar sua conta.\nSeu nome completo: ";
        std::getline(std::cin, nome);
        std::cout << "Seu telefone: ";
        std::getline(std::cin, tel);
        auto novoUsuario = std::make_shared<Usuario>(nome, tel, email);
        usuariosPorEmail[email] = novoUsuario;
        usuarioLogado = novoUsuario;
        std::cout << "Conta criada! Bem-vindo(a), " << nome << "!" << std::endl;
    }
}

void App::rodar() {
    carregarDados();
    login();
    int opcao = -1;
    while (opcao != 0) {
        if (usuarioLogado) {
             long naoLidas = 0;
             for(const auto& n : usuarioLogado->notificacoes) if(!n->lida) naoLidas++;
             std::cout << "\n--- Menu Principal (" << usuarioLogado->nomeCompleto << " | " << naoLidas << " notificacoes novas) ---" << std::endl;
        }
        std::cout << "1. Sou Motorista\n2. Sou Passageiro\n3. Meu Perfil\n4. Ver Notificacoes\n5. Historico de Caronas\n6. Avaliar Usuario\n0. Sair\nEscolha: ";
        std::cin >> opcao;
        limparBufferEntrada();
        switch (opcao) {
            case 1: {
                int subOpcao;
                std::cout << "\n-- Menu Motorista --\n1. Oferecer Carona\n2. Gerenciar Solicitacoes\n0. Voltar\nEscolha: ";
                std::cin >> subOpcao;
                limparBufferEntrada();
                if(subOpcao == 1) telaOferecerCarona();
                if(subOpcao == 2) telaGerenciarSolicitacoes();
                break;
            }
            case 2: telaBuscarCarona(); break;
            case 3: gerenciarPerfil(); break;
            case 4: telaVerNotificacoes(); break;
            case 5: telaHistorico(); break;
            case 6: telaDeAvaliacao(); break;
            case 0:
                salvarDados();
                std::cout << "Dados salvos. Ate logo!" << std::endl;
                break;
            default:
                std::cout << "Opcao invalida." << std::endl;
        }
    }
}
