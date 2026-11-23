#include "Tree.hpp"

#include <iostream>
#include <fstream>
#include <cstdint>
#include "Heap.hpp"

constexpr int size = 512;

std::uint16_t getTree(std::uint32_t * table, std::uint16_t * children, std::uint16_t * heap)
{
    std::uint16_t qua = table[size/2];
    table[size/2] = 0;
    std::uint16_t extra = size/2;
    while (qua > 1)
    {
        std::uint16_t min = del(heap, qua-1, table);
        std::uint16_t premin = del(heap, qua-2, table);
        table[extra] = table[min] + table[premin];
        children[extra - size/2] = min; children[extra] = premin;
        add(heap, extra, qua-2, table);
        extra++; qua--;
    }
    return del(heap, 0, table);
}

void report(std::uint16_t root, std::uint32_t * table, std::uint16_t * children, std::string file_name)
{
    std::ofstream file(file_name, std::ios::app|std::ios::binary);
    if (file.is_open())
    {
        if (table == nullptr || children == nullptr) {file << "NO TREE\n"; return;}
        file << "TREE\n";
        for (int i = 0; i < size; i++) file << i << '\t' << table[i] << '\t' << children[i] << '\n';
        file.close();
    }
}

void setLength(std::uint16_t root, std::uint16_t * children, std::uint8_t * Length, std::uint8_t length)
{
    if (root < size/2 && length == 0) {Length[root] = 1; return;}
    if (root < size/2) Length[root] = length;
    if (root >= size/2 && children[root-size/2] != size-1) setLength(children[root-size/2], children, Length, length+1);
    if (root >= size/2 && children[root] != size-1) setLength(children[root], children, Length, length+1);
}

void report(std::uint8_t * length, std::string file_name)
{
    std::ofstream file(file_name, std::ios::app|std::ios::binary);
    if (file.is_open())
    {
        if (length == nullptr) {file << "NO LENGTHES\n"; return;}
        file << "LENGTHES\n";
        for (int i = 0; i < size/2; i++) file << i << '\t' << (int) length[i] << '\n';
        file.close();
    }
}