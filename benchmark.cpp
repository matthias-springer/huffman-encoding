#include "huffman.h"
#include <iostream>

using namespace std;

#define word_t unsigned long

int main()
{
    // generate random input data
    int size = 500000;
    word_t* input = new word_t[size];

    for (int i = 0; i < size; ++i)
        input[i] = rand() % 45000;

    // build Huffman tree and two arrays representing the tree (for spatial locality in memory)
    word_t* huffman_array;
    bool* terminator_array;
    Node<word_t>* tree;
    generate_array_tree_representation(input, size, huffman_array, terminator_array, tree);
    
    // generate encoding dictionary from tree
    encoding_dict<word_t> encoding_dict;
    build_inverse_mapping(tree, encoding_dict);

    // compress 
    char* compressed;
    long compressed_size = encode(input, size, compressed, encoding_dict);

    cout << "Compression: " << sizeof(word_t)*size << " -> " << compressed_size << endl;
    cout << "Compression rate: " << compressed_size*100. / (sizeof(word_t)*size) << "%" << endl;

    word_t* decompressed;
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
