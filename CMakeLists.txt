cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR} CACHE STRING "")
set(CMAKE_BUILD_TYPE Release CACHE STRING "")
set(WEB_FRAMEWORK_TAG CACHE STRING "")

project(web_framework_server)

find_package(WebFramework QUIET)

if (NOT ${WebFramework_FOUND})
	if (WEB_FRAMEWORK_TAG STREQUAL "")
		message(FATAL_ERROR "WEB_FRAMEWORK_TAG must be provided")
	endif()

	set(WEB_FRAMEWORK_SDK ${CMAKE_BINARY_DIR}/WebFrameworkLibrary)
	set(WEB_FRAMEWORK_PATH ${CMAKE_BINARY_DIR}/WebFramework)

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
			COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${WEB_FRAMEWORK_SDK} -DWITH_STACKTRACE=ON -DBUILD_CC_API=OFF -DBUILD_CSHARP_API=OFF -DBUILD_PYTHON_API=OFF -DBUILD_FLUTTER_API=OFF -G ${CMAKE_GENERATOR} ..
		)

		execute_process(
			WORKING_DIRECTORY ${WEB_FRAMEWORK_PATH}/build
			COMMAND ${CMAKE_COMMAND} --build . -j --config Release
		)

		execute_process(
			WORKING_DIRECTORY ${WEB_FRAMEWORK_PATH}/build
			COMMAND ${CMAKE_COMMAND} --install . --config Release
		)
	endif()

	list(APPEND CMAKE_MODULE_PATH ${WEB_FRAMEWORK_SDK})

	find_package(WebFramework REQUIRED)
endif()

add_executable(
	${PROJECT_NAME}
	main.cpp
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
