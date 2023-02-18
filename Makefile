CC=gcc
AR=ar

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

ifeq ($(BUILD_TYPE),debug)
	CFLAGS+=-g3
	CFLAGS+=-DDEBUG
	
	OUTPUT_NAME=libtermmanipdebug.a
else
	CFLAGS+=-O3
	CFLAGS+=-DDEBUG
endif

OBJECTS=$(OBJ_DIR)/exit_log.o \
		$(OBJ_DIR)/window.o \

all: make_dirs $(BUILD_DIR)/$(OUTPUT_NAME)

$(BUILD_DIR)/$(OUTPUT_NAME): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/exit_log.o: $(SRC_DIR)/exit_log.c
$(OBJ_DIR)/window.o: $(SRC_DIR)/window/window.c

$(OBJECTS):
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean make_dirs test install uninstall

uninstall:
	$(RM) /usr/lib/$(BUILD_DIR)/$(OUTPUT_NAME) && $(RM) /usr/include/termmanip.h

install:
	install $(BUILD_DIR)/$(OUTPUT_NAME) /usr/lib/ && install include/termmanip.h /usr/include/

test:
	$(MAKE) && $(MAKE) install && cd test && (MAKE) && $(MAKE) run

make_dirs:
	$(MD) $(BUILD_DIR) $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR) $(BUILD_DIR)

