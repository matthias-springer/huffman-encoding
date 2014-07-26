#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>

#define word_t short

using namespace std;

class Node
{
    public:
        Node* left;
        Node* right;
        word_t value;
        long counter;
        bool is_terminal;

        bool operator<(const Node &other) const
        {
            return this->counter < other.counter;
        }

        Node(Node* _left, Node* _right, long _counter, bool _is_terminal, long _value) :
            left(_left), right(_right), value(_value), counter(_counter), is_terminal(_is_terminal) {}
};

Node* generate_tree(word_t* input, long length)
{
    unordered_map<word_t, long> frequencies;

    for (long l = 0; l < length; ++l)
        frequencies[input[l]]++;

    priority_queue<Node*> subtrees;
    for (auto it = frequencies.begin(); it != frequencies.end(); ++it)
        subtrees.push(new Node(NULL, NULL, it->second, true, it->first));

    while (subtrees.size() > 1)
    {
        Node* left = subtrees.top();
        subtrees.pop();
        Node* right = subtrees.top();
        subtrees.pop();
        subtrees.push(new Node(left, right, left->counter + right->counter, false, 0));
    }

    return subtrees.top();
}

struct inverse_map_builder_state {
    Node* node;
    char* bits;
    int count_bits;

    inverse_map_builder_state(Node* _node, char* _bits, int _count_bits) :
        node(_node), bits(_bits), count_bits(_count_bits) {}

    inverse_map_builder_state() {}
};

long encode(word_t* input, long length, char*& output, Node* tree)
{
    output = new char[length * sizeof(word_t) / sizeof(char)]();

    // build inverse map
    struct inverse_map_builder_state state(tree, NULL, 0);

    unordered_map<word_t, struct inverse_map_builder_state> inverse_mapping;
    stack<struct inverse_map_builder_state> traversal_state;
    traversal_state.push(state);

    while (!traversal_state.empty())
    {
        state = traversal_state.top();
        traversal_state.pop();

        if (state.node->is_terminal)
        {
            // input has only one word (possibly repeatedly)
            state.bits = new char[1] {0};
            state.count_bits = 1;
            inverse_mapping[state.node->value] = state;
            break;
        }

        struct inverse_map_builder_state left(state.node->left, new char[state.count_bits + 1],
                state.count_bits + 1);
        if (state.count_bits > 0)
            memcpy(left.bits, state.bits, state.count_bits);
        left.bits[state.count_bits] = 0;
        if (left.node->is_terminal)
            inverse_mapping[left.node->value] = left;
        else
            traversal_state.push(left);

        struct inverse_map_builder_state right(state.node->right, new char[state.count_bits + 1],
                state.count_bits + 1);
        if (state.count_bits > 0)
            memcpy(right.bits, state.bits, state.count_bits);
        right.bits[state.count_bits] = 1;
        if (right.node->is_terminal)
            inverse_mapping[right.node->value] = right;
        else
            traversal_state.push(right);
    }

    // encode
    long byte_pos = 0, bit_pos = 0;
    for (long l = 0; l < length; ++l)
    {
        struct inverse_map_builder_state word = inverse_mapping[input[l]];
        for (int i = 0; i < word.count_bits; ++i)
        {
            // write a single bit
            output[byte_pos] |= word.bits[i] << (7-bit_pos);
            ++bit_pos;

            if (bit_pos == 8)
            {
                bit_pos = 0;
                ++byte_pos;
            }
        }
    }

    return byte_pos + 1;
}

int main()
{
    short arr[10] = {29, 29, 29, 129, 529, 4542, 229, 629, 129, 29};
    Node* tree = generate_tree(arr, 10);
    char* output;
    long new_size = encode(arr, 10, output, tree);
    cout << new_size << endl;
}