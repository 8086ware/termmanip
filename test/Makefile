test: test.c libtermmanipdebug.a
	gcc $^ -o $@ -L. -ltermmanipdebug -g

clean:
	$(RM) test libtermmanipdebug.a termmanip.h

run:
	gdb test --eval-command run
