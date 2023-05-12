cmake_minimum_required(VERSION 3.10)

project(termmanip)

set(SOURCES src/exit_log.c src/screen_size.c src/window/append_output.c src/window/window.c src/window/print.c src/window/modify.c src/window/update.c src/window/cursor.c src/window/getsize.c src/init.c src/exit.c src/window/border.c src/window/parent.c src/window/fill.c src/window/attrib.c src/window/background.c src/window/echo.c src/window/rawinput.c src/window/input.c src/signal_handler.c src/widgets/button.c src/widgets/button.c src/widgets/dialog.c src/window/clear.c src/error.c src/terminal/inputblock.c src/window/put.c src/window/scroll.c src/screen.c src/window/inputnoblock.c src/terminal/write.c)

add_library(termmanip STATIC ${SOURCES})

target_include_directories(termmanip PRIVATE include)

install(TARGETS termmanip DESTINATION /usr/lib)
install(FILES include/termmanip.h DESTINATION /usr/include)
