test: test.c
	gcc $^ -o $@ -L. -ltermmanipdebug

clean:
	$(RM) test

run:
	gdb test
