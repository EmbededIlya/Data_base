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

# Настройки для разных конфигураций
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

# Исполняемый файл
add_executable(tree_project
    src/main.c
    src/tree.c
)

# Заголовочные файлы
target_sources(tree_project PRIVATE
    inc/main.h
    inc/tree.h
)

# Директории include
target_include_directories(tree_project PRIVATE inc)

# Копирование данных
add_custom_target(copy_data ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/src/data.txt
        ${CMAKE_CURRENT_BINARY_DIR}/data.txt
    COMMENT "Copying data.txt"
    DEPENDS tree_project
)

# Опции проекта
option(WITH_DEBUG "Enable debug output" OFF)
if(WITH_DEBUG)
    target_compile_definitions(tree_project PRIVATE DEBUG_OUTPUT=1)
endif()

# Информация о проекте
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")