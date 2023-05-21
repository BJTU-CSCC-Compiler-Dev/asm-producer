cmake_minimum_required(VERSION 3.18)
project(AsmProducer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_MACOSX_RPATH OFF)

add_compile_options(
	-g -Wall -Werror -Wextra -pthread
	-Wno-unused-parameter
	-Wno-unused-variable
	-Wno-unknown-pragmas
)
add_link_options(-lpthread -lm -v -pthread)

#add_subdirectory(third_party/moe)
#include_directories(third_party/moe)
#
include(${CMAKE_SOURCE_DIR}/third_party/conan/conanbuildinfo.cmake)
conan_basic_setup()
link_libraries(${CONAN_LIBS})

file(GLOB sysyCppFiles sysy/include/*.cpp)

add_executable(
	asm-producer
	${sysyCppFiles}
	third_party/include/moe/rt_check.cpp
	src/main.cpp
	src/config.cpp
	src/mir/usedef.cpp
	src/mir/ssa.cpp
	src/mir/type.cpp
	src/mir/pass.cpp
	src/front/ast_visitor.cpp
	src/front/symbol_table.cpp
	src/front/ast_visitor_func.cpp
	src/front/ast_visitor_exp.cpp
	src/front/ast_visitor_blockitem.cpp
	src/front/ast_visitor_var.cpp
	src/front/ast_visitor_helper.cpp
)
target_include_directories(
	asm-producer PUBLIC
	sysy/include
	third_party/include
	src
)
#target_link_libraries(asm-producer moe)