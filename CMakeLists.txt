cmake_minimum_required(VERSION 3.10)

project(termmanip LANGUAGES C VERSION 0.5.1 DESCRIPTION "A FOSS library that enables you to make TUIs and manipulate the text on your terminal on POSIX and windows systems")

include(CTest)

set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)

include(CPack)

set(TERMMANIP_SOURCES 
	src/terminal/makeoutput.c
	src/terminal/terminal_size.c 
	src/terminal/append_output.c 
	src/window/window.c 
	src/window/print.c 
	src/window/modify.c 
	src/window/cursor.c 
	src/window/parent.c 
	src/window/fill.c 
	src/window/attrib.c 
	src/window/background.c 
	src/window/input.c 
	src/window/clear.c 
	src/return.c 
	src/window/put.c 
	src/window/scroll.c 
	src/terminal/terminal.c 
	src/terminal/write.c 
	src/terminal/update.c 
	src/terminal/resize.c 
	src/window/flags.c 
	src/title.c 
	src/window/timeout.c 
	src/window/process_esc_input.c 
	src/terminal/win_write.c
	src/window/update.c 
	src/terminal/order.c
	src/terminal/win_select.c
)

add_library(termmanip STATIC ${TERMMANIP_SOURCES})

target_include_directories(termmanip PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)

install(TARGETS termmanip EXPORT termmanipTargets DESTINATION lib)
install(FILES include/termmanip.h DESTINATION include)

install(EXPORT termmanipTargets FILE termmanipTargets.cmake DESTINATION lib/cmake/termmanip)

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in termmanipConfig.cmake INSTALL_DESTINATION lib/cmake/termmanip)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/termmanipConfigVersion.cmake VERSION ${termmanip_VERSION_MAJOR}.${termmanip_VERSION_MINOR} COMPATIBILITY AnyNewerVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/termmanipConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/termmanipConfigVersion.cmake DESTINATION lib/cmake/termmanip)

export(PACKAGE termmanip)

if(CMAKE_BUILD_TYPE MATCHES Debug)
	target_compile_options(termmanip PUBLIC -Wall -fsanitize=address)
	target_link_options(termmanip PUBLIC -Wall -fsanitize=address)
endif()

add_executable(test_blockspam test/blockspam.c)
target_link_libraries(test_blockspam termmanip)
add_test(blockspam test_blockspam)

add_executable(test_scroll test/scroll.c)
target_link_libraries(test_scroll termmanip)
add_test(scroll test_scroll)

add_executable(test_modify test/modify.c)
target_link_libraries(test_modify termmanip)
add_test(modify test_modify)

add_executable(test_dialogselect test/dialog_select.c)
target_link_libraries(test_dialogselect termmanip)
add_test(dialogselect test_dialogselect)
