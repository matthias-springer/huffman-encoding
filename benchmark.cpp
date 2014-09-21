#include "huffman.h"
#include <iostream>

using namespace std;

//template void decode<unsigned short>(char* input, long length, word_t*& output, word_t* huffman_array, bool* terminator_array);

// change word size in huffman.h
int main()
{
    int size = 500000;
    unsigned short* input = new unsigned short[size];
    char* compressed;

    for (int i = 0; i < size; ++i)
        input[i] = rand() % 45000;

    unsigned short* huffman_array;
    bool* terminator_array;
    Node<unsigned short>* tree;
    generate_array_tree_representation(input, size, huffman_array, terminator_array, tree);
    
    long compressed_size = encode(input, size, compressed, tree);

    cout << "Compression: " << sizeof(unsigned short)*size << " -> " << compressed_size << endl;
    cout << "Compression rate: " << compressed_size*1. / (sizeof(unsigned short)*size) << "%" << endl;

    unsigned short* decompressed;
    decode(compressed, size, decompressed, huffman_array, terminator_array);

    bool self_test_success = true;
    for (int i = 0; i < size; ++i)
    {
        if (decompressed[i] != input[i])
        {
            cout << "Self test failed: decompressed[" << i << "] = " << decompressed[i] << " differs from input[" << i << "] = " << input[i] << "." << endl;
            self_test_success = false;
        }
    }

    if (self_test_success)
    {
        cout << "Self test passed." << endl;
    }
    else
    {
        cout << "Self test failed." << endl;
    }

    return 0;
}
