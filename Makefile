# using gcc
CC=gcc

all: main singleRead

main:
	$(CC) main.c -o main -lpcap
	
singleRead:
	$(CC) singleRead.c -o singleRead -lpcap

clean:
	rm -rf *.o

# remove all the executable files 
git:
	ls | grep -v "\." | grep -v Makefile | xargs rm
