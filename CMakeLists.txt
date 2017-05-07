cmake_minimum_required(VERSION 3.1)

project(gmockautogen)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Clang REQUIRED)

add_definitions("-fno-exceptions -fno-rtti")

set(SOURCE_FILES
    src/main.cpp
    src/ast_consumer.h
    src/ast_visitor.h
    src/frontend_action.h
    )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} clangAST)
target_link_libraries(${PROJECT_NAME} clangTooling)
target_link_libraries(${PROJECT_NAME} clangFrontendTool)
