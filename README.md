================================== App de Caronas UFMG ==================================

Alunos: Ricardo Rocha, Aaron Guizoli, Italo Avelar e Igor Hendrix



Apresentação do Problema:

A comunidade acadêmica da UFMG, composta por milhares de alunos, professores e
funcionários, enfrenta desafios diários de mobilidade. A grande extensão do
campus Pampulha, somada à dispersão dos membros da comunidade por diversas
regiões de Belo Horizonte, resulta em dificuldades de locomoção. A falta de uma
plataforma centralizada e segura para a organização de caronas solidárias impede
que motoristas com vagas ociosas se conectem de forma eficiente com passageiros
que fazem rotas similares.

O problema central é a ausência de um sistema confiável que facilite a
coordenação de caronas, verifique a identidade dos participantes através do
vínculo com a universidade e ofereça um ambiente seguro, especialmente para
públicos que demandam maior segurança, como as mulheres.



Objetivo:

Implementar uma plataforma de caronas solidárias em C++ para a comunidade da UFMG, com o objetivo de otimizar a mobilidade e fortalecer a segurança dos usuários. O sistema conecta motoristas e passageiros de forma eficiente, garantindo a identidade dos participantes através da validação institucional e fomentando uma comunidade confiável por meio de um sistema de reputação.



Visão Geral da Solução:

Este projeto, o "App de Caronas UFMG", é uma aplicação que simula um sistema
completo de caronas solidárias, projetado para atender às necessidades da
comunidade da UFMG. A solução foca em segurança, usabilidade e uma arquitetura
robusta e modular.



O sistema permite que usuários, após validarem seu CPF em uma base de dados
simulada da UFMG, se cadastrem na plataforma. Uma vez cadastrados, eles podem:



* Como Passageiro: Buscar caronas disponíveis com base em zonas de origem e
  destino, solicitar participação, negociar pontos de embarque e avaliar os
  motoristas após a viagem.



* Como Motorista: Cadastrar seus veículos, oferecer caronas (agendadas ou
  imediatas), gerenciar solicitações de passageiros, e avaliar os passageiros
  após a viagem.



A segurança é um pilar central, com funcionalidades como a opção de caronas
exclusivas para mulheres e um sistema de avaliação mútua que constrói uma
reputação para cada usuário, incentivando um comportamento cordial e seguro.



Estrutura e Funcionamento do Programa:

O projeto foi desenvolvido em C++11, seguindo os princípios da Programação
Orientada a Objetos para garantir modularidade, manutenibilidade e
escalabilidade. A arquitetura é dividida em classes de entidade, classes de
serviço (gerenciadores) e uma classe orquestradora principal.



Principais Estruturas de Dados e Classes:

Entidades:


* Usuario: Classe base polimórfica que contém dados comuns (nome, cpf, etc.).
  Motorista: Classe derivada de Usuario, com funcionalidades adicionais
  como CNH e uma lista de Veiculo.
* Veiculo: Armazena dados de um veículo (placa, modelo, cor, lugares).
* Carona: A entidade central, que agrega informações de rota, horário,
  motorista, passageiros e status.
* Solicitacao: Modela o processo de um passageiro pedindo para entrar em uma
  carona, incluindo o status da negociação.
* Avaliacao: Representa a nota e o comentário que um usuário faz a outro.
* Notificacao: Mensagens simples enviadas aos usuários.



Gerenciadores (Classes de Serviço):
A lógica de negócio é encapsulada em classes "Gerenciador", cada uma com uma
responsabilidade única:


* GerenciadorUsuarios: Controla cadastro, login e perfis.
* GerenciadorVeiculos: Gerencia os veículos de um motorista.
* GerenciadorCaronas: Orquestra a criação e o ciclo de vida das caronas.
* GerenciadorSolicitacoes: Media a interação entre passageiros e caronas.
* GerenciadorAvaliacoes: Controla o processo de avaliação mútua.



Orquestração e Interface:

* Sistema: A classe principal que inicializa todos os subsistemas, gerencia
  o estado da aplicação (ex: usuário logado) e contém o loop principal do programa.
* TerminalIO: Uma classe de serviço que abstrai toda a interação com o
  console, responsável por exibir menus e coletar dados do usuário.
* Utilitarios: Fornece funções auxiliares, como manipulação de datas e
  conversão de enums para strings.

Funcionamento:

1. A main.cpp instancia e executa a classe Sistema.
2. O construtor de Sistema inicializa todos os gerenciadores, que por sua vez
   carregam os dados de arquivos de texto (simulando um banco de dados).
3. O Sistema entra em um loop, exibindo o menu apropriado (logado ou não logado).
4. As ações do usuário são delegadas aos gerenciadores correspondentes, que
   manipulam as entidades e a lógica de negócio.
5. Ao encerrar, o destrutor de Sistema garante que todos os dados sejam salvos
   de volta nos arquivos de texto.



Principais Dificuldades Encontradas:


* Gerenciamento de Memória e Propriedade (Ownership): A decisão de usar
  ponteiros brutos para representar associações entre objetos (ex: Carona
  apontando para Usuario) exigiu um design cuidadoso para evitar memory leaks
  e dangling pointers. Foi crucial definir claramente qual classe "gerenciador"
  seria a proprietária (owner) de cada tipo de objeto e responsável por sua
  desalocação, documentando isso rigorosamente.
* Manutenção do Estado e Polimorfismo: Converter um Usuario em Motorista
  após o login foi complexo. A solução adotada foi criar uma nova instância de
  Motorista, copiar os dados do Usuario original, e então deletar o objeto
  antigo, atualizando o ponteiro do usuário logado no Sistema. Isso exigiu
  cuidado para manter a consistência dos dados e gerenciar a memória corretamente.



Extras Implementados
Além dos requisitos básicos, as seguintes funcionalidades foram implementadas para
tornar o sistema mais robusto e completo:

* Sistema de Reputação ("Medalhas"): Foi criado um sistema de reputação
  visual. Com base na média de avaliações recebidas, os usuários recebem
  "medalhas" (Bronze, Prata, Ouro), que são exibidas em seus perfis, incentivando
  a boa conduta na plataforma.
* Persistência de Dados em Arquivos: Todo o estado do sistema (usuários,
  veículos, caronas, etc.) é salvo em arquivos de texto ao final da execução e
  recarregado no início. Isso simula um banco de dados e torna o estado da
  aplicação persistente entre as sessões.
* Fluxo de Negociação de Carona: Em vez de um simples "aceitar/recusar", o
  sistema permite que o motorista faça uma contraproposta de locais de embarque
  e desembarque, que o passageiro pode então aceitar ou recusar, tornando o
  processo de solicitação mais flexível e realista.
