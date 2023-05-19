CC=g++
FLAGS=-std=c++20 -Wall

all: ping_pong

ping_pong:
	${CC} ${FLAGS} task.cc -o task

clean:
	rm task
