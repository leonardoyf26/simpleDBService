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
)

# Lista de arquivos fonte
set(SOURCES
    src/app/console_app.cpp

    src/parser/parser.cpp

    src/storage/database.cpp

    src/engine/engine.cpp

    src/persistence/storage.cpp
)

# Executável
add_executable(simpledb ${SOURCES})