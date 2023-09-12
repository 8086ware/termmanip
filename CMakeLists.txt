cmake_minimum_required(VERSION 3.10)

project(termmanip)

include(CTest)

set(TERMMANIP_SOURCES src/screen_size.c src/screen/append_output.c src/window/window.c src/window/print.c src/window/modify.c src/window/update.c src/window/cursor.c src/init.c src/exit.c src/window/border.c src/window/parent.c src/window/fill.c src/window/attrib.c src/window/background.c src/window/input.c src/signal_handler.c src/widgets/button.c src/widgets/button.c src/widgets/dialog.c src/window/clear.c src/error.c src/window/put.c src/window/scroll.c src/screen/screen.c src/screen/write.c src/screen/bufferwrite.c src/screen/cursor.c src/screen/update.c src/screen/resize.c src/term.c src/window/flags.c src/title.c src/window/timeout.c)

add_library(termmanip STATIC ${TERMMANIP_SOURCES})

target_include_directories(termmanip PRIVATE include)
target_compile_options(termmanip PRIVATE -Wall)

install(TARGETS termmanip DESTINATION lib)
install(FILES include/termmanip.h DESTINATION include)

add_executable(termmanip_test test/test.c)
target_link_libraries(termmanip_test termmanip)
target_include_directories(termmanip_test PRIVATE include)
add_test(NAME termmanip_test COMMAND termmanip_test)
