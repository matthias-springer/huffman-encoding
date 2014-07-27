#include "huffman.h"
#include <iostream>

using namespace std;

int main()
{
    word_t arr[10] = {1,2,5,1,3,11,3,1,34,2};
    Node* tree = generate_tree(arr, 10);
    char* output;
    long new_size = encode(arr, 10, output, tree);
    word_t* decoded;
    decode(output, 10, decoded, tree);
    cout << decoded[6];

    return 0;
}
