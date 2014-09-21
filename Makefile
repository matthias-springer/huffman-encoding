CC = g++
CFLAGS = -O3 -std=c++11 -c

all: benchmark

benchmark.o: benchmark.cpp huffman.h
	$(CC) $(CFLAGS) benchmark.cpp

benchmark: benchmark.o
	$(CC) benchmark.o -o benchmark

clean:
	-@rm -rf *.o benchmark 2>/dev/null || true

