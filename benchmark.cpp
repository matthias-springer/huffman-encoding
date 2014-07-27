#include "huffman.h"
#include <iostream>

using namespace std;

// change word size in huffman.h

int main()
{
    int size = 500000;
    word_t* input = new word_t[size];
    char* output;

    for (int i = 0; i < size; ++i)
        input[i] = rand() % 9000;

    Node* tree = generate_tree(input, size);
    long compressed_size = encode(input, size, output, tree);

    cout << "Compression: " << sizeof(word_t)*size << " -> " << compressed_size << endl;
    cout << "Compression rate: " << compressed_size*1. / (sizeof(word_t)*size) << "%" << endl;

    return 0;
}
