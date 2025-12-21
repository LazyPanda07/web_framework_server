cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_BUILD_TYPE Release CACHE STRING "")
set(WEB_FRAMEWORK_TAG CACHE STRING "")

project(web_framework_server)

find_package(WebFramework QUIET)

if (NOT ${WebFramework_FOUND})
	if (WEB_FRAMEWORK_TAG STREQUAL "")
		message(FATAL_ERROR "WEB_FRAMEWORK_TAG must be provided")
	endif()

	set(FETCHCONTENT_QUIET OFF CACHE BOOL "")

	include(FetchContent)

	set(WEB_FRAMEWORK_URL https://github.com/LazyPanda07/WebFramework/releases/download/${WEB_FRAMEWORK_TAG})

	if (UNIX)
		set(WEB_FRAMEWORK_URL ${WEB_FRAMEWORK_URL}/linux.zip)
	else()
		set(WEB_FRAMEWORK_URL ${WEB_FRAMEWORK_URL}/windows.zip)
	endif()

	FetchContent_Declare(
		WebFramework
		URL ${WEB_FRAMEWORK_URL}
	)

	FetchContent_MakeAvailable(WebFramework)

	if (UNIX)
		set(WEB_FRAMEWORK_SDK ${webframework_SOURCE_DIR})
	else()
		set(WEB_FRAMEWORK_SDK ${webframework_SOURCE_DIR}/Release_Windows)
	endif()

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
