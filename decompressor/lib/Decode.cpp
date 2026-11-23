#include "Decode.hpp"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include "Code.hpp"

constexpr int size = 512;

std::uint8_t * getLength(std::string file_name)
{
    std::ifstream file(file_name, std::ios::binary);
    if (!file.is_open()) return nullptr;
    char current;
    std::uint8_t * res = new std::uint8_t[size/2]();
    for (int i = 0; i < 4; i++) file.get(current);
    for (int i = 0; i < size/2; i++) 
    {
        file.get(current);
        res[i] = (unsigned char) current;
    }
    file.close();
    return res;
}

void report(std::uint8_t * Length, std::string report_name)
{
    std::ofstream file(report_name, std::ios::app | std::ios::binary);
    if (!file.is_open()) return;
    if (Length == nullptr) {file << "NO LENGTH TABLE\n"; return;}
    file << "LENGTH TABLE\n";
    for (int i = 0; i < size/2; i++) file << i << '\t' << (int) Length[i] << '\n';
    file.close();
}

Node * insert(std::uint16_t symbol, std::uint8_t length, std::uint32_t * code, Node * root)
{
    if (length == 0) 
    {
        root->pos = symbol;
        return root;
    }
    bool bit = get_bit(code[symbol], length-1);
    if (bit)
    {
        if (root->right == nullptr)
        {
            root->right = new Node{511, nullptr, nullptr};
        }
        return insert(symbol, length-1, code, root->right);
    }
    if (root->left == nullptr)
    {
        root->left = new Node{511, nullptr, nullptr};
    }
    return insert(symbol, length-1, code, root->left);

}

Node * erase(Node * root)
{
    if (root == nullptr) return nullptr;
    if (root->left != nullptr) erase(root->left);
    if (root->right != nullptr) erase(root->right);
    delete root;
    return nullptr;
}

std::uint32_t decode(std::uint32_t * code, std::uint8_t * length, Node * root, std::string input_name, std::string output_name)
{
    std::ifstream input(input_name, std::ios::binary);
    std::ofstream output(output_name, std::ios::binary);
    if (!input.is_open() || !output.is_open()) return 0;
    
    std::uint32_t Size = 0;
    char current;
    for (int i = 0; i < 4; i++)
    {
        input.get(current);
        Size |= (std::uint32_t)(unsigned char)current << (8 * i);
    }
    for (int i = 0; i < 256; i++) input.get(current);
    int I = 0;
    Node * node = root;
    std::uint32_t res = 0;
    std::cout << "The decompressed file size must be " << Size <<" byte(s)\n";
    while(Size > 0 && input.get(current))
    {
        while (I < 8)
        {
            bool kuda = get_bit((unsigned char) current, 7 - I);
            
            if (kuda) node = node->right;
            else node = node->left;
            if (node == nullptr) {
                input.close(); output.close();
                return res;
            }
            if (node->pos != 511)
            {
                output.put(node->pos);
                res++;
                Size--;  if (Size == 0) break;
                node = root;
            }
            I++;
        }
        I = 0;

    }
    input.close(); output.close();
    return res;
}
