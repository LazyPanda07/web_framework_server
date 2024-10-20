cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR} CACHE STRING "")
set(CMAKE_BUILD_TYPE Release CACHE STRING "")
set(WEB_FRAMEWORK_PATH ${CMAKE_BINARY_DIR}/WebFramework)
set(WEB_FRAMEWORK_TAG CACHE STRING "")

if (WEB_FRAMEWORK_TAG STREQUAL "")
    message(FATAL_ERROR "WEB_FRAMEWORK_TAG must be provided")
endif()

project(web_framework_server)

include(ProcessorCount)

ProcessorCount(PHYSICAL_CORES)

set(WEB_FRAMEWORK_SDK ${PROJECT_SOURCE_DIR}/WebFrameworkLibrary)

if (NOT EXISTS ${WEB_FRAMEWORK_PATH})
	execute_process(
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMAND git clone https://github.com/LazyPanda07/WebFramework.git --recursive -b ${WEB_FRAMEWORK_TAG} ${WEB_FRAMEWORK_PATH}
	)

	execute_process(
		WORKING_DIRECTORY ${WEB_FRAMEWORK_PATH}
		COMMAND ${CMAKE_COMMAND} -E make_directory build
	)

	execute_process(
		WORKING_DIRECTORY ${WEB_FRAMEWORK_PATH}/build
		COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${WEB_FRAMEWORK_SDK} ..
	)

	execute_process(
		WORKING_DIRECTORY ${WEB_FRAMEWORK_PATH}/build
		COMMAND ${CMAKE_COMMAND} --build . --parallel ${PHYSICAL_CORES} --config ${CMAKE_BUILD_TYPE} --target install
	)
endif()

list(APPEND CMAKE_MODULE_PATH ${WEB_FRAMEWORK_SDK})

find_package(WebFramework REQUIRED)

add_executable(
	${PROJECT_NAME}
	main.cpp
)

target_link_libraries(
	${PROJECT_NAME} PRIVATE
	${WEB_FRAMEWORK_LIBS}
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
