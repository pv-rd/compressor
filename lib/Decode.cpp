#include "Decode.hpp"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include "Heap.hpp"
#include "Code.hpp"

constexpr int size = 512;

std::uint8_t * getLength(std::string file_name)
{
    std::ifstream file(file_name, std::ios::binary);
    if (!file.is_open()) return nullptr;
    char current;
    std::uint8_t * res = new std::uint8_t[size]();
    for (int i = 0; i < size/2; i++) 
    {
        file.get(current);
        res[i] = (unsigned char) current;
    }
    file.close();
    return res;
}

Node * insert(std::uint16_t i, std::uint8_t len, Table * table, Node * root)
{
    if (len == 0) 
    {
        root->pos = i;
        return root;
    }
    bool bit = get_bit(table->Q[i], len-1);
    if (bit)
    {
        if (root->right == nullptr)
        {
            root->right = new Node{511, nullptr, nullptr};
        }
        return insert(i, len-1, table, root->right);
    }
    if (root->left == nullptr)
    {
        root->left = new Node{511, nullptr, nullptr};
    }
    return insert(i, len-1, table, root->left);

}

void decode(Table * table, Node * root, std::string file_name)
{
    std::ifstream file(file_name, std::ios::binary);
    std::ofstream out("de" + file_name, std::ios::binary);
    if (!file.is_open() || !out.is_open()) return;
    char current;
    for (int i = 0; i < 256; i++) file.get(current);
    int I = 0;
    Node * node = root;
    while(file.get(current))
    {
        while (I < 8)
        {
            bool kuda = get_bit((unsigned char) current, 7 -I);
            if (kuda) node = node->right;
            else node = node->left;
            if (node->pos != 511)
            {
                out.put(node->pos);
                node = root;
            }
            I++;
        }
        I = 0;

    }

    file.close(); out.close();
}