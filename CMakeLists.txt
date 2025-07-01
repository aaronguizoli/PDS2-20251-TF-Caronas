# Define a versão mínima do CMake necessária para este projeto.
cmake_minimum_required(VERSION 3.10)

# Define o nome do projeto.
project(SistemaDeCaronas VERSION 1.0)

# Define o padrão da linguagem C++ a ser utilizado.
# O seu projeto parece ser compatível com C++11.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adiciona o diretório 'include' à lista de diretórios onde o compilador
# procurará por arquivos de cabeçalho (#include <..._>).
include_directories(include)

# Encontra todos os arquivos .cpp dentro da pasta 'src' e os armazena
# na variável 'SOURCES'. Isso evita ter que listar cada arquivo manualmente.
file(GLOB SOURCES "src/*.cpp")

# Cria um executável chamado 'programa_carona' a partir dos arquivos de código-fonte
# encontrados e armazenados na variável SOURCES.
add_executable(programa_carona ${SOURCES})

# Mensagem final para o usuário após a configuração.
message(STATUS "Configuração do CMake concluída. Para compilar, use 'cmake --build .'")
