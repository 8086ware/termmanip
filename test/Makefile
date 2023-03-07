test: test.c libtermmanip.a
	gcc $^ -o $@ -L. -ltermmanip -g

clean:
	$(RM) test libtermmanipdebug.a termmanip.h

run:
	gdb test --eval-command run
