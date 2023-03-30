OUTPUT=test

$(OUTPUT): test.c libtermmanip.a
	$(CC) $^ -o $@ -L. -ltermmanip -g

clean:
	$(RM) $(OUTPUT) libtermmanip.a termmanip.h

run:
	gdb $(OUTPUT)
