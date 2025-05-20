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

if(CMAKE_BUILD_TYPE MATCHES Debug)
	target_compile_options(termmanip PUBLIC -Wall -fsanitize=address)
	target_link_options(termmanip PUBLIC -Wall -fsanitize=address)
endif()

function(new_termmanip_test test_name test_exec_name source_file)
	add_executable(${test_exec_name} ${source_file})
	target_link_libraries(${test_exec_name} termmanip)
	add_test(${test_name} ${test_exec_name})
endfunction()

new_termmanip_test(blockspam test_blockspam test/blockspam.c)
new_termmanip_test(scroll test_scroll test/scroll.c)
new_termmanip_test(modify test_modify test/modify.c)
new_termmanip_test(dialog_select test_dialogselect test/dialog_select.c)
