cmake_minimum_required(VERSION 3.16)

project(neumann CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

set(EXECUTABLE_OUTPUT_PATH       ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${EXECUTABLE_OUTPUT_PATH}/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXECUTABLE_OUTPUT_PATH}/release)

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

file(GLOB SRC_control_unit
	${PROJECT_SOURCE_DIR}/control_unit/*.cpp
	${PROJECT_SOURCE_DIR}/control_unit/*.h
	${PROJECT_SOURCE_DIR}/control_unit/*.hpp
)

file(GLOB SRC_processing_unit
	${PROJECT_SOURCE_DIR}/processing_unit/*.cpp
	${PROJECT_SOURCE_DIR}/processing_unit/*.h
	${PROJECT_SOURCE_DIR}/processing_unit/*.hpp
)

file(GLOB SRC_cpu
	${PROJECT_SOURCE_DIR}/cpu/*.cpp
	${PROJECT_SOURCE_DIR}/cpu/*.h
	${PROJECT_SOURCE_DIR}/cpu/*.hpp
)

# MEMORY
add_library(memory
	${SRC_memory}
 	${SRC_vector}
)

# target_link_libraries(memory
# )

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

# CONTROL_UNIT
add_library(control_unit
	${SRC_control_unit}
)

target_link_libraries(control_unit
	memory
	instruction
)

target_include_directories(control_unit
	PUBLIC ${PROJECT_SOURCE_DIR}
)

# PROCESSING_UNIT
add_library(processing_unit
	${SRC_processing_unit}
)

target_link_libraries(processing_unit
	memory
	instruction
)

target_include_directories(processing_unit
	PUBLIC ${PROJECT_SOURCE_DIR}
)

# CPU
add_library(cpu
	${SRC_cpu}
)

target_link_libraries(cpu
	memory
	instruction
	processing_unit
	control_unit
)

target_include_directories(cpu
	PUBLIC ${PROJECT_SOURCE_DIR}
)

# NEUMANN
add_executable(neumann
	${SRC_main}
 	${SRC_vector}
	${SRC_pair}
)

target_link_libraries(neumann
	memory
	instruction
	control_unit
	processing_unit
	cpu
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
		control_unit
		processing_unit
		cpu
	)

	target_include_directories(test_neumann
		PUBLIC ${PROJECT_SOURCE_DIR}
	)
endif(CMAKE_BUILD_TYPE MATCHES "Debug")
