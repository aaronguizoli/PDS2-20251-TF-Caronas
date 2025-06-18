#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <algorithm>
#include <limits> // Necessário para numeric_limits
#include <fstream> // Para leitura e escrita de arquivos
#include <sstream> // Para manipulação de strings

// --- Protótipos (Forward Declarations) ---
// Usado para resolver dependências circulares entre as classes.
class Usuario;
class Carona;
class Avaliacao;

// --- Classe Veiculo ---
// Armazena informações sobre o veículo de um motorista.
class Veiculo {
public:
    std::string modelo;
    std::string cor;
    std::string placa;

    Veiculo(std::string mod, std::string c, std::string p)
        : modelo(mod), cor(c), placa(p) {}

    void exibir() const {
        std::cout << "  - Veiculo: " << modelo << ", " << cor << ", Placa: " << placa << std::endl;
    }
};

// --- Classe Avaliacao ---
// Representa uma avaliação (nota e comentário) que um usuário faz de outro.
class Avaliacao {
public:
    int nota; // 1 a 5
    std::string comentario;
    std::weak_ptr<Usuario> avaliador; // Quem fez a avaliação
    std::weak_ptr<Usuario> avaliado;  // Quem foi avaliado

    Avaliacao(int n, std::string c, std::shared_ptr<Usuario> p_avaliador, std::shared_ptr<Usuario> p_avaliado)
        : nota(n), comentario(c), avaliador(p_avaliador), avaliado(p_avaliado) {}
};

// --- Classe Notificacao ---
// Representa uma notificação a ser enviada para um usuário.
class Notificacao {
public:
    std::string mensagem;
    bool lida = false;

    Notificacao(std::string msg) : mensagem(msg) {}
};


// --- Classe Usuario ---
// Classe principal para representar tanto Motoristas quanto Passageiros.
class Usuario {
private:
    std::vector<std::shared_ptr<Avaliacao>> avaliacoesRecebidas;

public:
    std::string nomeCompleto;
    std::string telefone;
    std::string email;
    std::unique_ptr<Veiculo> veiculo; // Ponteiro único, pois só um usuário tem um veículo.
    std::vector<std::shared_ptr<Notificacao>> notificacoes;
    std::vector<std::shared_ptr<Carona>> historicoDeCaronas;

    Usuario(std::string nome, std::string tel, std::string mail)
        : nomeCompleto(nome), telefone(tel), email(mail), veiculo(nullptr) {}

    // Adiciona um veículo ao usuário, tornando-o um motorista.
    void adicionarVeiculo(std::string modelo, std::string cor, std::string placa) {
        veiculo = std::make_unique<Veiculo>(modelo, cor, placa);
    }

    // Calcula e retorna a média das avaliações recebidas.
    double getMediaDeAvaliacoes() const {
        if (avaliacoesRecebidas.empty()) {
            return 0.0;
        }
        double soma = 0;
        for (const auto& avaliacao : avaliacoesRecebidas) {
            soma += avaliacao->nota;
        }
        return soma / avaliacoesRecebidas.size();
    }

    void adicionarAvaliacao(std::shared_ptr<Avaliacao> avaliacao) {
        avaliacoesRecebidas.push_back(avaliacao);
    }

    void adicionarNotificacao(const std::string& mensagem) {
        notificacoes.push_back(std::make_shared<Notificacao>(mensagem));
    }
    
    // Exibe o perfil do usuário.
    void exibirPerfil() const {
        std::cout << "\n--- Perfil de " << nomeCompleto << " ---" << std::endl;
        std::cout << "  - E-mail: " << email << std::endl;
        std::cout << "  - Telefone: " << telefone << std::endl;
        std::cout << "  - Avaliacao Media: " << getMediaDeAvaliacoes() << " estrelas" << std::endl;
        if (veiculo) {
            veiculo->exibir();
        }
        std::cout << "---------------------------------" << std::endl;
    }
};


// --- Classe Carona ---
// Representa uma viagem oferecida por um motorista.
class Carona {
public:
    std::string origem;
    std::string destino;
    std::string dataHoraPartida;
    int vagasDisponiveis;
    double valorSugerido;
    std::shared_ptr<Usuario> motorista;
    std::vector<std::shared_ptr<Usuario>> passageirosAprovados;
    std::vector<std::shared_ptr<Usuario>> solicitacoesPendentes;

    Carona(std::string orig, std::string dest, std::string data, int vagas, double valor, std::shared_ptr<Usuario> mot)
        : origem(orig), destino(dest), dataHoraPartida(data), vagasDisponiveis(vagas), valorSugerido(valor), motorista(mot) {}

    // Adiciona uma solicitação de um passageiro.
    void adicionarSolicitacao(std::shared_ptr<Usuario> passageiro) {
        solicitacoesPendentes.push_back(passageiro);
        std::string msg = passageiro->nomeCompleto + " solicitou uma vaga na sua carona de " + origem + " para " + destino + ".";
        motorista->adicionarNotificacao(msg);
    }

    // Aprova uma solicitação, se houver vagas.
    bool aprovarSolicitacao(std::shared_ptr<Usuario> passageiro) {
        if (vagasDisponiveis > 0) {
            passageirosAprovados.push_back(passageiro);
            vagasDisponiveis--;
            // Remove da lista de pendentes
            solicitacoesPendentes.erase(
                std::remove_if(solicitacoesPendentes.begin(), solicitacoesPendentes.end(),
                               [&](const std::shared_ptr<Usuario>& p) { return p->nomeCompleto == passageiro->nomeCompleto; }),
                solicitacoesPendentes.end());
            
            std::string msg = "Sua solicitacao para a carona de " + origem + " para " + destino + " foi APROVADA.";
            passageiro->adicionarNotificacao(msg);
            return true;
        }
        return false;
    }
    
    // Rejeita uma solicitação.
    void rejeitarSolicitacao(std::shared_ptr<Usuario> passageiro) {
        // Remove da lista de pendentes
        solicitacoesPendentes.erase(
            std::remove_if(solicitacoesPendentes.begin(), solicitacoesPendentes.end(),
                           [&](const std::shared_ptr<Usuario>& p) { return p->nomeCompleto == passageiro->nomeCompleto; }),
            solicitacoesPendentes.end());
            
        std::string msg = "Sua solicitacao para a carona de " + origem + " para " + destino + " foi REJEITADA.";
        passageiro->adicionarNotificacao(msg);
    }

    // Exibe um resumo da carona na lista de busca.
    void exibirResumo() const {
        std::cout << "  Origem: " << origem << " | Destino: " << destino << " | Data: " << dataHoraPartida << std::endl;
        std::cout << "  Motorista: " << motorista->nomeCompleto << " (" << motorista->getMediaDeAvaliacoes() << " estrelas)" << std::endl;
        std::cout << "  Vagas: " << vagasDisponiveis << " | Valor: R$ " << valorSugerido << std::endl;
    }
};

// --- Classe App ---
// Classe principal que gerencia o estado do sistema (usuários, caronas, etc.)
class App {
private:
    std::map<std::string, std::shared_ptr<Usuario>> usuarios;
    std::vector<std::shared_ptr<Carona>> caronasDisponiveis;
    std::shared_ptr<Usuario> usuarioLogado = nullptr;

    // Limpa o buffer do 'cin' para evitar problemas de leitura.
    void limparBufferEntrada() {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Salva os dados dos usuários e caronas em arquivos.
    void salvarDados() const {
        // Salva usuários
        std::ofstream arquivoUsuarios("usuarios.txt");
        if (arquivoUsuarios.is_open()) {
            for (const auto& par : usuarios) {
                const auto& usuario = par.second;
                arquivoUsuarios << usuario->nomeCompleto << ";"
                                << usuario->email << ";"
                                << usuario->telefone << ";";
                if (usuario->veiculo) {
                    arquivoUsuarios << "1;" << usuario->veiculo->modelo << ";"
                                    << usuario->veiculo->cor << ";"
                                    << usuario->veiculo->placa << "\n";
                } else {
                    arquivoUsuarios << "0;nenhum;nenhum;nenhum\n";
                }
            }
        }
        arquivoUsuarios.close();

        // Salva caronas
        std::ofstream arquivoCaronas("caronas.txt");
        if(arquivoCaronas.is_open()){
            for(const auto& carona : caronasDisponiveis){
                arquivoCaronas << carona->motorista->nomeCompleto << ";"
                               << carona->origem << ";" << carona->destino << ";"
                               << carona->dataHoraPartida << ";" << carona->vagasDisponiveis << ";"
                               << carona->valorSugerido << ";";
                // Salva passageiros aprovados
                for(size_t i = 0; i < carona->passageirosAprovados.size(); ++i){
                    arquivoCaronas << carona->passageirosAprovados[i]->nomeCompleto << (i == carona->passageirosAprovados.size() - 1 ? "" : ",");
                }
                arquivoCaronas << ";";
                 // Salva solicitações pendentes
                for(size_t i = 0; i < carona->solicitacoesPendentes.size(); ++i){
                    arquivoCaronas << carona->solicitacoesPendentes[i]->nomeCompleto << (i == carona->solicitacoesPendentes.size() - 1 ? "" : ",");
                }
                arquivoCaronas << "\n";
            }
        }
        arquivoCaronas.close();
    }

    // Carrega os dados dos usuários e caronas dos arquivos.
    void carregarDados() {
        // Carrega usuários
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
                usuarios[nome] = novoUsuario;
            }
        }
        arquivoUsuarios.close();
        
        // Carrega caronas
        std::ifstream arquivoCaronas("caronas.txt");
        if(arquivoCaronas.is_open()){
             while (std::getline(arquivoCaronas, linha)) {
                std::stringstream ss(linha);
                std::string nomeMotorista, origem, destino, data, vagasStr, valorStr;
                std::string aprovadosStr, pendentesStr;
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

                if(usuarios.count(nomeMotorista)){
                    vagas = std::stoi(vagasStr);
                    valor = std::stod(valorStr);
                    auto novaCarona = std::make_shared<Carona>(origem, destino, data, vagas, valor, usuarios[nomeMotorista]);
                    
                    // Adiciona passageiros aprovados
                    std::stringstream ssAprovados(aprovadosStr);
                    std::string nomeAprovado;
                    while(std::getline(ssAprovados, nomeAprovado, ',')){
                        if(usuarios.count(nomeAprovado)) novaCarona->passageirosAprovados.push_back(usuarios[nomeAprovado]);
                    }

                    // Adiciona solicitações pendentes
                    std::stringstream ssPendentes(pendentesStr);
                    std::string nomePendente;
                    while(std::getline(ssPendentes, nomePendente, ',')){
                        if(usuarios.count(nomePendente)) novaCarona->solicitacoesPendentes.push_back(usuarios[nomePendente]);
                    }

                    caronasDisponiveis.push_back(novaCarona);
                    // Adiciona ao histórico de todos os envolvidos
                    usuarios[nomeMotorista]->historicoDeCaronas.push_back(novaCarona);
                    for(const auto& p : novaCarona->passageirosAprovados) p->historicoDeCaronas.push_back(novaCarona);
                    for(const auto& p : novaCarona->solicitacoesPendentes) p->historicoDeCaronas.push_back(novaCarona);
                }
             }
        }
        arquivoCaronas.close();
    }


public:
    // User Story 5: Manter perfil atualizado
    void gerenciarPerfil() {
        if (!usuarioLogado) return;
        
        int opcao;
        std::cout << "\n--- Gerenciar Perfil ---" << std::endl;
        std::cout << "1. Editar Nome, Email e Telefone" << std::endl;
        std::cout << "2. Adicionar/Modificar Veiculo" << std::endl;
        std::cout << "0. Voltar" << std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;
        limparBufferEntrada();

        if (opcao == 1) {
            std::cout << "Novo nome completo: ";
            std::getline(std::cin, usuarioLogado->nomeCompleto);
            std::cout << "Novo email: ";
            std::getline(std::cin, usuarioLogado->email);
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
    
    // User Story 1: Oferecer carona
    void telaOferecerCarona() {
        if (!usuarioLogado) return;
        if (!usuarioLogado->veiculo) {
            std::cout << "Voce precisa cadastrar um veiculo em seu perfil para oferecer caronas." << std::endl;
            return;
        }

        std::string origem, destino, data;
        int vagas;
        double valor;

        std::cout << "\n--- Oferecer Carona ---" << std::endl;
        std::cout << "Origem (ex: UFMG): ";
        std::getline(std::cin, origem);
        std::cout << "Destino (ex: Savassi): ";
        std::getline(std::cin, destino);
        std::cout << "Data e Hora (ex: 20/10/2024 18:00): ";
        std::getline(std::cin, data);
        std::cout << "Numero de vagas disponiveis: ";
        std::cin >> vagas;
        std::cout << "Valor sugerido por passageiro (R$): ";
        std::cin >> valor;
        limparBufferEntrada();

        auto novaCarona = std::make_shared<Carona>(origem, destino, data, vagas, valor, usuarioLogado);
        caronasDisponiveis.push_back(novaCarona);
        usuarioLogado->historicoDeCaronas.push_back(novaCarona);

        std::cout << "\nCarona oferecida com sucesso!" << std::endl;
    }

    // User Story 2: Gerenciar solicitações de carona
    void telaGerenciarSolicitacoes() {
        if (!usuarioLogado) return;
        std::vector<std::shared_ptr<Carona>> minhasCaronas;
        for(const auto& carona : caronasDisponiveis) {
            if (carona->motorista == usuarioLogado && !carona->solicitacoesPendentes.empty()) {
                minhasCaronas.push_back(carona);
            }
        }
        
        if (minhasCaronas.empty()) {
            std::cout << "\nNenhuma solicitacao pendente no momento." << std::endl;
            return;
        }

        std::cout << "\n--- Suas Caronas com Solicitacoes Pendentes ---" << std::endl;
        for (size_t i = 0; i < minhasCaronas.size(); ++i) {
            std::cout << "\nCarona " << i + 1 << ":" << std::endl;
            minhasCaronas[i]->exibirResumo();
            std::cout << "  Solicitacoes:" << std::endl;
            for(const auto& passageiro : minhasCaronas[i]->solicitacoesPendentes) {
                std::cout << "   - " << passageiro->nomeCompleto << std::endl;
            }
        }

        int escolhaCarona;
        std::cout << "\nEscolha a carona para gerenciar (ou 0 para sair): ";
        std::cin >> escolhaCarona;
        if (escolhaCarona == 0 || escolhaCarona > minhasCaronas.size()) return;

        auto caronaGerenciada = minhasCaronas[escolhaCarona-1];
        std::string nomePassageiro;
        limparBufferEntrada();
        std::cout << "Digite o nome completo do passageiro para gerenciar: ";
        std::getline(std::cin, nomePassageiro);
        
        std::shared_ptr<Usuario> passageiroEscolhido = nullptr;
        for(const auto& p : caronaGerenciada->solicitacoesPendentes) {
            if (p->nomeCompleto == nomePassageiro) {
                passageiroEscolhido = p;
                break;
            }
        }

        if(!passageiroEscolhido){
            std::cout << "Passageiro nao encontrado nas solicitacoes." << std::endl;
            return;
        }

        int acao;
        std::cout << "1. Aceitar | 2. Rejeitar: ";
        std::cin >> acao;
        if(acao == 1) {
            if(caronaGerenciada->aprovarSolicitacao(passageiroEscolhido)){
                 std::cout << "Passageiro aceito com sucesso!" << std::endl;
            } else {
                 std::cout << "Nao ha vagas disponiveis." << std::endl;
            }
        } else if (acao == 2) {
            caronaGerenciada->rejeitarSolicitacao(passageiroEscolhido);
            std::cout << "Passageiro rejeitado." << std::endl;
        }
    }

    // User Story 3 & 4: Buscar e solicitar carona
    void telaBuscarCarona() {
        if (!usuarioLogado) return;
        std::string origem, destino, data;
        std::cout << "\n--- Buscar Carona ---" << std::endl;
        std::cout << "Origem (deixe em branco para ignorar): ";
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
            std::cout << "Nenhuma carona encontrada com os criterios informados." << std::endl;
            return;
        }

        std::cout << "\n--- Caronas Encontradas ---" << std::endl;
        for (size_t i = 0; i < resultados.size(); ++i) {
            std::cout << "\n--- Opcao " << i + 1 << " ---" << std::endl;
            resultados[i]->exibirResumo();
        }

        int escolha;
        std::cout << "\nDigite o numero da carona para solicitar (ou 0 para voltar): ";
        std::cin >> escolha;
        limparBufferEntrada();

        if (escolha > 0 && escolha <= resultados.size()) {
            auto caronaEscolhida = resultados[escolha - 1];
            caronaEscolhida->adicionarSolicitacao(usuarioLogado);
            usuarioLogado->historicoDeCaronas.push_back(caronaEscolhida);
            std::cout << "Solicitacao enviada com sucesso! Aguarde a aprovacao do motorista." << std::endl;
        }
    }

    // User Story 8: Ver notificações
    void telaVerNotificacoes() {
        if (!usuarioLogado || usuarioLogado->notificacoes.empty()) {
            std::cout << "\nNenhuma notificacao nova." << std::endl;
            return;
        }
        std::cout << "\n--- Suas Notificacoes ---" << std::endl;
        for (const auto& notif : usuarioLogado->notificacoes) {
            if(!notif->lida) {
                std::cout << "  - " << notif->mensagem << std::endl;
                notif->lida = true; // Marca como lida
            }
        }
        std::cout << "-------------------------" << std::endl;
    }
    
    // User Story 7: Histórico de caronas
    void telaHistorico() {
        if (!usuarioLogado || usuarioLogado->historicoDeCaronas.empty()) {
            std::cout << "\nVoce nao participou de nenhuma carona ainda." << std::endl;
            return;
        }

        std::cout << "\n--- Seu Historico de Caronas ---" << std::endl;
        std::cout << "\n-- Caronas Oferecidas --" << std::endl;
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

    // User Story 6: Avaliar usuários
    void telaDeAvaliacao() {
        if (!usuarioLogado) return;
        // Simulação: Aqui o sistema escolheria uma carona concluída recentemente.
        // Para simplificar, vamos listar todas as caronas do histórico para avaliação.
        if (usuarioLogado->historicoDeCaronas.empty()) {
            std::cout << "Nao ha caronas no seu historico para avaliar." << std::endl;
            return;
        }

        std::cout << "Qual carona do seu historico voce gostaria de avaliar?" << std::endl;
        for(size_t i = 0; i < usuarioLogado->historicoDeCaronas.size(); ++i) {
            std::cout << i+1 << ". " << usuarioLogado->historicoDeCaronas[i]->origem << " -> " << usuarioLogado->historicoDeCaronas[i]->destino << std::endl;
        }
        int escolha;
        std::cin >> escolha;
        if(escolha <= 0 || escolha > usuarioLogado->historicoDeCaronas.size()) return;
        
        auto caronaParaAvaliar = usuarioLogado->historicoDeCaronas[escolha-1];
        limparBufferEntrada();

        // Se eu sou o motorista, avalio os passageiros
        if (caronaParaAvaliar->motorista == usuarioLogado) {
            if(caronaParaAvaliar->passageirosAprovados.empty()){
                std::cout << "Esta carona nao teve passageiros para avaliar." << std::endl;
                return;
            }
            for(const auto& passageiro : caronaParaAvaliar->passageirosAprovados) {
                std::cout << "\nAvaliando o passageiro: " << passageiro->nomeCompleto << std::endl;
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
        } else { // Se eu sou passageiro, avalio o motorista
             std::cout << "\nAvaliando o motorista: " << caronaParaAvaliar->motorista->nomeCompleto << std::endl;
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


    void login() {
        std::string nome;
        std::cout << "Digite seu nome de usuario para entrar ou criar uma conta: ";
        std::getline(std::cin, nome);

        if (usuarios.find(nome) != usuarios.end()) {
            usuarioLogado = usuarios[nome];
            std::cout << "Bem-vindo(a) de volta, " << nome << "!" << std::endl;
        } else {
            std::string email, tel;
            std::cout << "Parece que voce e novo por aqui! Vamos criar seu perfil." << std::endl;
            std::cout << "Seu email: ";
            std::getline(std::cin, email);
            std::cout << "Seu telefone: ";
            std::getline(std::cin, tel);
            usuarios[nome] = std::make_shared<Usuario>(nome, tel, email);
            usuarioLogado = usuarios[nome];
            std::cout << "Conta criada com sucesso! Bem-vindo(a), " << nome << "!" << std::endl;
        }
    }
    
    // Loop principal da aplicação.
    void rodar() {
        carregarDados();
        login();

        int opcao = -1;
        while (opcao != 0) {
            if (usuarioLogado) {
                 long naoLidas = 0;
                 for(const auto& n : usuarioLogado->notificacoes) if(!n->lida) naoLidas++;
                 std::cout << "\n--- Menu Principal (" << usuarioLogado->nomeCompleto << " | " << naoLidas << " notificacoes novas) ---" << std::endl;
            }
           
            std::cout << "1. Sou Motorista" << std::endl;
            std::cout << "2. Sou Passageiro" << std::endl;
            std::cout << "3. Meu Perfil" << std::endl;
            std::cout << "4. Ver Notificacoes" << std::endl;
            std::cout << "5. Historico de Caronas" << std::endl;
            std::cout << "6. Avaliar Usuario de Carona Anterior" << std::endl;
            std::cout << "0. Sair" << std::endl;
            std::cout << "Escolha uma opcao: ";
            std::cin >> opcao;
            limparBufferEntrada();

            switch (opcao) {
                case 1: { // Menu Motorista
                    int subOpcao;
                    std::cout << "\n-- Menu Motorista --\n1. Oferecer Carona\n2. Gerenciar Solicitacoes\n0. Voltar\nEscolha: ";
                    std::cin >> subOpcao;
                    limparBufferEntrada();
                    if(subOpcao == 1) telaOferecerCarona();
                    if(subOpcao == 2) telaGerenciarSolicitacoes();
                    break;
                }
                case 2: // Menu Passageiro
                    telaBuscarCarona();
                    break;
                case 3:
                    gerenciarPerfil();
                    break;
                case 4:
                    telaVerNotificacoes();
                    break;
                case 5:
                    telaHistorico();
                    break;
                case 6:
                    telaDeAvaliacao();
                    break;
                case 0:
                    salvarDados(); // Salva os dados antes de sair
                    std::cout << "Dados salvos. Ate logo!" << std::endl;
                    break;
                default:
                    std::cout << "Opcao invalida. Tente novamente." << std::endl;
            }
        }
    }
};


int main() {
    App sistemaDeCaronas;
    sistemaDeCaronas.rodar();
    return 0;
}
