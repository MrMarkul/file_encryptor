cmake_minimum_required(VERSION 3.10)
project(FileEncryptor)

set(CMAKE_C_STANDARD 11)

# Указываем директории с заголовочными файлами
include_directories(include)

# Указываем файлы исходного кода
set(SOURCES
    src/main.c
    src/encrypt.c
    src/decrypt.c
    src/keygen.c
)

# Создаем исполняемый файл
add_executable(file_encryptor ${SOURCES})

# Подключаем библиотеки OpenSSL
find_package(OpenSSL REQUIRED)
target_link_libraries(file_encryptor OpenSSL::Crypto)
