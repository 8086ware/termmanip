cmake_minimum_required(VERSION 3.10)

project(termmanip)

include(CTest)

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

target_include_directories(termmanip PUBLIC include)

install(TARGETS termmanip DESTINATION lib)
install(FILES include/termmanip.h DESTINATION include)

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
