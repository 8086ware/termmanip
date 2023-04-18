AR=ar
CC=gcc

INCLUDES=include

ARFLAGS=rcs
CFLAGS=-I$(INCLUDES) -Wall

BUILD_TYPE=debug

SRC_DIR=src
BUILD_DIR=bin
OBJ_DIR=$(BUILD_DIR)/obj

OUTPUT_NAME=libtermmanip.a

RM=rm -rf

MD=mkdir -p

OBJECTS=$(OBJ_DIR)/append_output.o \
		$(OBJ_DIR)/exit_log.o \
		$(OBJ_DIR)/screen_size.o \
		$(OBJ_DIR)/window.o \
		$(OBJ_DIR)/print.o \
		$(OBJ_DIR)/modify.o \
		$(OBJ_DIR)/update.o \
		$(OBJ_DIR)/cursor.o \
		$(OBJ_DIR)/getsize.o \
		$(OBJ_DIR)/init.o \
		$(OBJ_DIR)/exit.o \
		$(OBJ_DIR)/border.o \
		$(OBJ_DIR)/parent.o \
		$(OBJ_DIR)/fill.o \
		$(OBJ_DIR)/attrib.o \
		$(OBJ_DIR)/background.o \
		$(OBJ_DIR)/echo.o \
		$(OBJ_DIR)/rawinput.o \
		$(OBJ_DIR)/input.o \
		$(OBJ_DIR)/signal_handler.o \
		$(OBJ_DIR)/button.o \
		$(OBJ_DIR)/dialog.o \
		$(OBJ_DIR)/clear.o \
		$(OBJ_DIR)/error.o \
		$(OBJ_DIR)/inputblock.o \
		$(OBJ_DIR)/put.o \
		$(OBJ_DIR)/scroll.o \
	
debug: CFLAGS += -g
debug: CFLAGS += -DDEBUG
debug: all

release: all

all: $(OBJ_DIR) $(BUILD_DIR) $(BUILD_DIR)/$(OUTPUT_NAME)

$(BUILD_DIR)/$(OUTPUT_NAME): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/exit_log.o: $(SRC_DIR)/exit_log.c
$(OBJ_DIR)/screen_size.o: $(SRC_DIR)/screen_size.c
$(OBJ_DIR)/append_output.o: $(SRC_DIR)/window/append_output.c
$(OBJ_DIR)/window.o: $(SRC_DIR)/window/window.c
$(OBJ_DIR)/print.o: $(SRC_DIR)/window/print.c
$(OBJ_DIR)/modify.o: $(SRC_DIR)/window/modify.c
$(OBJ_DIR)/update.o: $(SRC_DIR)/window/update.c
$(OBJ_DIR)/cursor.o: $(SRC_DIR)/window/cursor.c
$(OBJ_DIR)/getsize.o: $(SRC_DIR)/window/getsize.c
$(OBJ_DIR)/init.o: $(SRC_DIR)/init.c
$(OBJ_DIR)/exit.o: $(SRC_DIR)/exit.c
$(OBJ_DIR)/border.o: $(SRC_DIR)/window/border.c
$(OBJ_DIR)/parent.o: $(SRC_DIR)/window/parent.c
$(OBJ_DIR)/fill.o: $(SRC_DIR)/window/fill.c
$(OBJ_DIR)/attrib.o: $(SRC_DIR)/window/attrib.c
$(OBJ_DIR)/background.o: $(SRC_DIR)/window/background.c
$(OBJ_DIR)/echo.o: $(SRC_DIR)/window/echo.c
$(OBJ_DIR)/rawinput.o: $(SRC_DIR)/window/rawinput.c
$(OBJ_DIR)/input.o: $(SRC_DIR)/window/input.c
$(OBJ_DIR)/signal_handler.o: $(SRC_DIR)/signal_handler.c
$(OBJ_DIR)/button.o: $(SRC_DIR)/widgets/button.c
$(OBJ_DIR)/dialog.o: $(SRC_DIR)/widgets/dialog.c
$(OBJ_DIR)/clear.o: $(SRC_DIR)/window/clear.c
$(OBJ_DIR)/error.o: $(SRC_DIR)/error.c
$(OBJ_DIR)/inputblock.o: $(SRC_DIR)/inputblock.c
$(OBJ_DIR)/put.o: $(SRC_DIR)/window/put.c
$(OBJ_DIR)/scroll.o: $(SRC_DIR)/window/scroll.c

$(OBJECTS):
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean make_dirs test install uninstall

uninstall:
	$(RM) /usr/lib/$(BUILD_DIR)/$(OUTPUT_NAME) && $(RM) /usr/include/termmanip.h

install:
	install $(BUILD_DIR)/$(OUTPUT_NAME) /usr/lib/ && install include/termmanip.h /usr/include/

test:
	$(MAKE) debug && cp $(BUILD_DIR)/$(OUTPUT_NAME) test/ && cp include/termmanip.h test/ && cd test && $(MAKE) && $(MAKE) run

$(BUILD_DIR):
	$(MD) $(BUILD_DIR)

$(OBJ_DIR):
	$(MD) $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR) $(BUILD_DIR) && cd test/ && $(MAKE) clean

