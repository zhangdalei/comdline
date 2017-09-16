zshell: type_prompt.o read_command.o zshell.o
	gcc -o $@ $^
%.o: %.c
	gcc -c -o $@ $< -I include -fno-stack-protector
.PHONY:clean
clean:
	rm -f *.o zshell