# using gcc
CC=gcc

all: main singleRead captureEngine captureFilter pcap

main:
	$(CC) main.c -o main -lpcap
	
singleRead:
	$(CC) singleRead.c -o singleRead -lpcap

captureEngine:
	$(CC) captureEngine.c -o captureEngine -lpcap

captureFilter:
	$(CC) captureFilter.c -o captureFilter -lpcap

pcap:
	$(CC) pcap.c -o pcap -lpcap -Wall -pedantic

clean:
	rm -rf *.o

# remove all the executable files 
git:
	ls | grep -v "\." | grep -v Makefile | xargs rm
