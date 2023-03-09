PLATFORM=unix

ifeq ($(PLATFORM), windows)
	CC=x86_64-w64-mingw32-gcc
	DEBUGGER=x86_64-w64-mingw32-gdb
	OUTPUT=test.exe
endif

ifeq ($(PLATFORM), unix)
	CC=gcc
	DEBUGGER=gdb
	OUTPUT=test
endif

$(OUTPUT): test.c libtermmanip.a
	$(CC) $^ -o $@ -L. -ltermmanip -g

clean:
	$(RM) $(OUTPUT) libtermmanip.a termmanip.h

run:
	$(DEBUGGER) $(OUTPUT)
