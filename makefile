main: main.c
	gcc -fsanitize=undefined -g -Wall -pedantic -o main main.c -I.

clean:
	-rm main