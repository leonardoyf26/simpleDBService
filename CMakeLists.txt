cmake_minimum_required(VERSION 3.10)

project(SimpleDB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Inclui diretórios de headers
include_directories(
    src/parser
    src/storage
    src/engine
    src/persistence
    src/app
    src/server
)

# Lista de arquivos fonte
set(SOURCES
    src/main.cpp
    src/app/console_app.cpp

    src/parser/parser.cpp

    src/storage/database.cpp

    src/engine/Engine.cpp

    src/persistence/Storage.cpp
    
    src/server/Server.cpp
)

# Executável
add_executable(simpledb ${SOURCES})

# Linkar com pthread para suporte a mutex e signals
target_link_libraries(simpledb pthread)