all:
	gcc -o main-base main-base.c
	gcc -o main-fork main-fork.c
	gcc -o main-thread main-thread.c -lpthread
base:
	gcc -o main-base main-base.c
	./main-base -s 1000000000 -m 1000000
fork:
	gcc -o main-fork main-fork.c
	./main-fork -s 1000000000 -m 1000000
thread:
	gcc -o main-thread main-thread.c -lpthread
	./main-thread -s 1000000000 -m 1000000
thread-mutex:
	gcc -o main-thread-mutex main-thread-mutex.c -lpthread
	./main-thread-mutex -s 1000000000 -m 1000000

clean:
	rm main-base
	rm main-fork
	rm main-thread