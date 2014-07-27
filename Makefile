CC = g++
CFLAGS = -O3 -std=c++11 -c

all: benchmark

huffman.o: huffman.cpp huffman.h
	$(CC) $(CFLAGS) huffman.cpp

benchmark.o: benchmark.cpp
	$(CC) $(CFLAGS) benchmark.cpp

benchmark: benchmark.o huffman.o
	$(CC) benchmark.o huffman.o -o benchmark

clean:
	-@rm -rf *.o benchmark 2>/dev/null || true

