all:
	gcc -o main-base main-base.c
	gcc -o main-fork main-fork.c
	gcc -o main-thread main-thread.c -lpthread
	gcc -o main-thread-mutex main-thread-mutex.c -lpthread
base:
	gcc -o main-base main-base.c
	./main-base -s 1000000000 -m 1000000 -i 5
fork:
	gcc -o main-fork main-fork.c
	./main-fork -s 1000000000 -m 1000000 -n 5 -i 5
thread:
	gcc -o main-thread main-thread.c -lpthread
	./main-thread -s 1000000000 -m 1000000 -n 5 -i 5 -h
thread-mutex:
	gcc -o main-thread-mutex main-thread-mutex.c -lpthread
	./main-thread-mutex -s 1000000000 -m 1000000 -n 5 -i 5 -h

plot: 
	python3 plot_result.py
clean:
	rm main-base
	rm main-fork
	rm main-thread
	rm main-thread-mutex