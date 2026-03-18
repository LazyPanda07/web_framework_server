cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_BUILD_TYPE Release CACHE STRING "")
set(WEB_FRAMEWORK_TAG CACHE STRING "")
set(PACKAGE_NAME CACHE STRING "")

project(web_framework_server)

find_package(WebFramework QUIET)

if (NOT ${WebFramework_FOUND})
	if ("${WEB_FRAMEWORK_TAG}" STREQUAL "")
		set(WEB_FRAMEWORK_URL https://github.com/LazyPanda07/WebFramework/releases/latest/download/)
	else()
		set(WEB_FRAMEWORK_URL https://github.com/LazyPanda07/WebFramework/releases/download/${WEB_FRAMEWORK_TAG})
	endif()

	set(FETCHCONTENT_QUIET OFF CACHE BOOL "")

	include(FetchContent)

	if ("${PACKAGE_NAME}" STREQUAL "")
		if (UNIX)
			set(WEB_FRAMEWORK_URL ${WEB_FRAMEWORK_URL}/Linux-WITH_PYTHON_EXECUTORS.OFF-BUILD_PYTHON_API.OFF--WITH_DOTNET_EXECUTORS.OFF-BUILD_CSHARP_API.OFF-BUILD_CC_API.ON.zip)
		else()
			set(WEB_FRAMEWORK_URL ${WEB_FRAMEWORK_URL}/Windows-WITH_PYTHON_EXECUTORS.OFF-BUILD_PYTHON_API.OFF--WITH_DOTNET_EXECUTORS.OFF-BUILD_CSHARP_API.OFF-BUILD_CC_API.ON.zip)
		endif()
	else()
		set(WEB_FRAMEWORK_URL ${WEB_FRAMEWORK_URL}/${PACKAGE_NAME})
	endif()

	FetchContent_Declare(
		WebFramework
		URL ${WEB_FRAMEWORK_URL}
	)

	FetchContent_MakeAvailable(WebFramework)

	set(WEB_FRAMEWORK_SDK ${webframework_SOURCE_DIR})

	list(APPEND CMAKE_PREFIX_PATH ${WEB_FRAMEWORK_SDK})

	find_package(WebFramework REQUIRED)
endif()

add_executable(
	${PROJECT_NAME}
	main.cpp
)

target_link_libraries(
	${PROJECT_NAME} PRIVATE
	WebFramework::CXX_API
)

install(TARGETS ${PROJECT_NAME} DESTINATION .)
