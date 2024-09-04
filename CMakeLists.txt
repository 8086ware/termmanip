cmake_minimum_required(VERSION 3.10)

project(termmanip)

set(TERMMANIP_SOURCES 
	src/terminal/makeoutput.c
	src/terminal/terminal_size.c 
	src/terminal/append_output.c 
	src/window/window.c 
	src/window/print.c 
	src/window/modify.c 
	src/window/update.c 
	src/window/cursor.c 
	src/window/border.c 
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
)

add_library(termmanip STATIC ${TERMMANIP_SOURCES})

target_include_directories(termmanip PUBLIC include)

install(TARGETS termmanip DESTINATION lib)
install(FILES include/termmanip.h DESTINATION include)

add_executable(termmanip_test test/test.c)
target_link_libraries(termmanip_test termmanip)

if(CMAKE_BUILD_TYPE MATCHES Debug)
	target_compile_options(termmanip PRIVATE -Wall -fsanitize=address)
	target_link_options(termmanip PRIVATE -Wall -fsanitize=address)
	target_compile_options(termmanip_test PRIVATE -fsanitize=address)
	target_link_options(termmanip_test PRIVATE -Wall -fsanitize=address)
endif()
