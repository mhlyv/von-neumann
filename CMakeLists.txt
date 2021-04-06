cmake_minimum_required(VERSION 3.16)

project(neumann CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -O2 -g")
set(EXECUTABLE_OUTPUT_PATH       ${CMAKE_SOURCE_DIR}/bin)
set(ARCHIVE_OUTPUT_DIRECTORY     ${CMAKE_SOURCE_DIR}/lib)
set(LIBRARY_OUTPUT_DIRECTORY     ${CMAKE_SOURCE_DIR}/lib)
set(PROJECT_SOURCE_DIR           ${CMAKE_SOURCE_DIR}/src)
SET(CMAKE_CURRENT_BINARY_DIR     ${CMAKE_SOURCE_DIR}/build)

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

file(GLOB SRC_instruction
	${PROJECT_SOURCE_DIR}/instruction/*.cpp
	${PROJECT_SOURCE_DIR}/instruction/*.h
	${PROJECT_SOURCE_DIR}/instruction/*.hpp
)

# VECTOR
add_library(vector
	${SRC_vector}
)

target_include_directories(vector
	PUBLIC ${PROJECT_SOURCE_DIR}
)

# MEMORY
add_library(memory
	${SRC_memory}
)

target_link_libraries(memory
	vector
)

target_include_directories(memory
	PUBLIC ${PROJECT_SOURCE_DIR}
)

# INSTRUCTION
add_library(instruction
	${SRC_instruction}
)

target_link_libraries(instruction
	vector
	memory
)

target_include_directories(instruction
	PUBLIC ${PROJECT_SOURCE_DIR}
)

# NEUMANN
add_executable(neumann
	${SRC_main}
)

target_link_libraries(neumann
	vector
	memory
	instruction
)

target_include_directories(neumann
	PUBLIC ${PROJECT_SOURCE_DIR}
)
