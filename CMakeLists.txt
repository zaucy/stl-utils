cmake_minimum_required(VERSION 3.0)

project(stl-utils)

set(UTILS_HEADERS
	include/utils.h
	include/utils/basic_string.h
)

file(GLOB TEST_SOURCES tests/*.cpp)

set(GENERATED_TEST_SOURCE ${CMAKE_SOURCE_DIR}/src/generated/utils_test.cpp)

file(WRITE ${GENERATED_TEST_SOURCE} "#include <iostream>\n#include <exception>\n")


foreach(TEST_SRC_FILE ${TEST_SOURCES})
	get_filename_component(TEST_NAME ${TEST_SRC_FILE} NAME_WE)
	
	string(SUBSTRING ${TEST_NAME} 0 1 TEST_NAME_FIRST_CHAR)
	
	if(TEST_NAME_FIRST_CHAR STREQUAL "_")
		set(COMMON_SOURCES ${COMMON_SOURCES} ${TEST_SRC_FILE})
	else()
		add_library(${TEST_NAME} STATIC ${TEST_SRC_FILE})
		target_include_directories(${TEST_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
		set_property(TARGET ${TEST_NAME}  PROPERTY CXX_STANDARD 11)
		set_property(TARGET ${TEST_NAME}  PROPERTY CXX_STANDARD_REQUIRED ON)
		add_dependencies(${TEST_NAME} tests_common)
		target_compile_definitions(${TEST_NAME} PRIVATE -DUTILS_TEST_NAME=${TEST_NAME})
		SET(GENERATED_TEST_SOURCE_BODY
		"${GENERATED_TEST_SOURCE_BODY}
		try {
			if(${TEST_NAME}()) { std::cout << \"========= TEST '${TEST_NAME}' SUCCESS!\\n\";} else { std::cout << \"========= TEST '${TEST_NAME}' FAILED!\\n\"; }
		} catch(std::exception& err) { std::cout << \"========= TEST '${TEST_NAME}' FAILED WITH EXCEPTION!\\n\" << err.what() << std::endl; }")
		file(APPEND ${GENERATED_TEST_SOURCE} "extern bool ${TEST_NAME}();\n")
		set(TEST_NAMES "${TEST_NAMES};${TEST_NAME}")
	endif()
	
endforeach()

file(APPEND ${GENERATED_TEST_SOURCE} "int main() { ${GENERATED_TEST_SOURCE_BODY}\n\t return 0;  \n}\n")

add_library(tests_common STATIC ${COMMON_SOURCES})

add_executable(utils_test ${GENERATED_TEST_SOURCE})
target_link_libraries(utils_test ${TEST_NAMES})
message(STATUS ${TEST_NAMES})

add_custom_target(list_utils_headers
	SOURCES
		${UTILS_HEADERS}
)
