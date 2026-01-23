cmake_minimum_required(VERSION 3.14)

project(TreeProject 
    VERSION 1.0.0
    DESCRIPTION "Tree data structure project"
    LANGUAGES C
)

# Проверяем существование файлов
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")
    message(FATAL_ERROR "File src/main.c not found!")
endif()

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/tree.c")
    message(FATAL_ERROR "File src/tree.c not found!")
endif()

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/inc")
    message(WARNING "Include directory 'inc' not found!")
endif()

# Настройки компилятора
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Исполняемый файл
add_executable(database
    src/main.c
    src/tree.c
    src/file_parsing.c
)

# Заголовочные файлы
target_sources(database PRIVATE
    inc/main.h
    inc/tree.h
    inc/file_parsing.h
)

# Директории include
target_include_directories(database PRIVATE inc)

# Информация о проекте
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
