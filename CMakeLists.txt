cmake_minimum_required(VERSION 3.10)

project(termmanip)

set(TERMMANIP_SOURCES src/terminal/makeoutput.c src/terminal/terminal_size.c src/terminal/append_output.c src/window/window.c src/window/print.c src/window/modify.c src/window/update.c src/window/cursor.c src/init.c src/exit.c src/window/border.c src/window/parent.c src/window/fill.c src/window/attrib.c src/window/background.c src/window/input.c src/signal_handler.c src/widgets/button.c src/widgets/button.c src/widgets/dialog.c src/window/clear.c src/return.c src/window/put.c src/window/scroll.c src/terminal/terminal.c src/terminal/write.c src/terminal/cursor.c src/terminal/update.c src/terminal/resize.c src/window/flags.c src/title.c src/window/timeout.c src/window/process_esc_input.c)

add_library(termmanip STATIC ${TERMMANIP_SOURCES})

target_include_directories(termmanip PRIVATE include)
target_compile_options(termmanip PRIVATE -Wall)

install(TARGETS termmanip DESTINATION lib)
install(FILES include/termmanip.h DESTINATION include)

add_executable(termmanip_test test/test.c)
target_link_libraries(termmanip_test termmanip)
target_include_directories(termmanip_test PRIVATE include)
