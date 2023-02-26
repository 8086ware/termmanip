test: test.c libtermmanipdebug.a
	gcc $^ -o $@ -L. -ltermmanipdebug

clean:
	$(RM) test

run:
	gdb test --eval-command run
