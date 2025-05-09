
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>


void menuPrincipal() {
    int opcao;
    std::string nomeLogado;
    do {
        std::cout << "\n--- Menu Principal ---\n";
        std::cout << "1. Cadastrar Usuário\n2. Publicar Carona\n3. Listar Caronas\n4. Avaliar Usuário\n5. Sair\nEscolha: ";
        std::cin >> opcao;
        std::cin.ignore();

        switch (opcao) {
            case 1:
                cadastrarUsuario();
                break;
            case 2:
                std::cout << "Nome do motorista logado: ";
                std::getline(std::cin, nomeLogado);
                publicarCarona(nomeLogado);
                break;
            case 3:
                listarCaronas();
                break;
            case 4:
                avaliarUsuario();
                break;
            case 5:
                std::cout << "Encerrando...\n";
                break;
            default:
                std::cout << "Opção inválida.\n";
        }
    } while (opcao != 5);
    return 0;
}
