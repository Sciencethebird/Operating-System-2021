all:
	gcc -o main-base main-base.c
	gcc -o main-fork main-fork.c
	gcc -o main-thread main-thread.c -lpthread
base:
	gcc -o main-base main-base.c
	./main-base
fork:
	gcc -o main-fork main-fork.c
	./main-fork
thread:
	gcc -o main-thread main-thread.c -lpthread
	./main-thread
clean:
	rm main-base
	rm main-fork
	rm main-thread