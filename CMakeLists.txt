cmake_minimum_required(VERSION 3.16)

project(neumann CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
set(PROJECT_SOURCE_DIR       ${CMAKE_SOURCE_DIR}/src)

file(GLOB SRC_main
	${PROJECT_SOURCE_DIR}/*.cpp
	${PROJECT_SOURCE_DIR}/*.h
	${PROJECT_SOURCE_DIR}/*.hpp
)

file(GLOB SRC_memory
	${PROJECT_SOURCE_DIR}/memory/*.cpp
	${PROJECT_SOURCE_DIR}/memory/*.h
	${PROJECT_SOURCE_DIR}/memory/*.hpp
)

file(GLOB SRC_vector
	${PROJECT_SOURCE_DIR}/vector/*.cpp
	${PROJECT_SOURCE_DIR}/vector/*.h
	${PROJECT_SOURCE_DIR}/vector/*.hpp
)

file(GLOB SRC_pair
	${PROJECT_SOURCE_DIR}/pair/*.cpp
	${PROJECT_SOURCE_DIR}/pair/*.h
	${PROJECT_SOURCE_DIR}/pair/*.hpp
)

file(GLOB SRC_instruction
	${PROJECT_SOURCE_DIR}/instruction/*.cpp
	${PROJECT_SOURCE_DIR}/instruction/*.h
	${PROJECT_SOURCE_DIR}/instruction/*.hpp
)

file(GLOB SRC_test
	${PROJECT_SOURCE_DIR}/test/*.cpp
	${PROJECT_SOURCE_DIR}/test/*.h
	${PROJECT_SOURCE_DIR}/test/*.hpp
)

file(GLOB SRC_cpu
	${PROJECT_SOURCE_DIR}/cpu/*.cpp
	${PROJECT_SOURCE_DIR}/cpu/*.h
	${PROJECT_SOURCE_DIR}/cpu/*.hpp
)

file(GLOB SRC_lang
	${PROJECT_SOURCE_DIR}/lang/*.cpp
	${PROJECT_SOURCE_DIR}/lang/*.h
	${PROJECT_SOURCE_DIR}/lang/*.hpp
)

file(GLOB SRC_machine
	${PROJECT_SOURCE_DIR}/machine/*.cpp
	${PROJECT_SOURCE_DIR}/machine/*.h
	${PROJECT_SOURCE_DIR}/machine/*.hpp
)

# MEMORY
add_library(memory
	${SRC_memory}
 	${SRC_vector}
)

target_include_directories(memory
	PUBLIC ${PROJECT_SOURCE_DIR}
)

# INSTRUCTION
add_library(instruction
	${SRC_instruction}
 	${SRC_vector}
	${SRC_pair}
)

target_link_libraries(instruction
	memory
)

target_include_directories(instruction
	PUBLIC ${PROJECT_SOURCE_DIR}
)

# LANG
add_library(lang
 	${SRC_lang}
 	${SRC_vector}
)

target_link_libraries(lang
	instruction
)

target_include_directories(lang
	PUBLIC ${PROJECT_SOURCE_DIR}
)

# CPU
add_library(cpu
	${SRC_cpu}
)

target_link_libraries(cpu
	memory
	instruction
)

target_include_directories(cpu
	PUBLIC ${PROJECT_SOURCE_DIR}
)

# MACHINE
add_library(machine
	${SRC_machine}
)

target_link_libraries(machine
	memory
	cpu
	lang
)

target_include_directories(machine
	PUBLIC ${PROJECT_SOURCE_DIR}
)

# NEUMANN
add_executable(neumann
	${SRC_main}
)

target_link_libraries(neumann
	machine
)

target_include_directories(neumann
	PUBLIC ${PROJECT_SOURCE_DIR}
)

# TEST
if(CMAKE_BUILD_TYPE MATCHES "Debug")
	add_executable(test_neumann
		${SRC_test}
		${SRC_vector}
		${SRC_pair}
	)

	target_link_libraries(test_neumann
		memory
		instruction
		cpu
		lang
	)

	target_include_directories(test_neumann
		PUBLIC ${PROJECT_SOURCE_DIR}
	)
endif(CMAKE_BUILD_TYPE MATCHES "Debug")
