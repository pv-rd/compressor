#include "Tree.hpp"

#include <iostream>
#include <fstream>
#include <cstdint>
#include "Heap.hpp"


constexpr int size = 512;

std::uint16_t getTree(Table * table, std::uint16_t * heap)
{
    int qua = 0;
    for (int i = 0; i < size/2; i++) if (table->Q[i] != 0) qua++;
    std::uint16_t extra = size/2;
    while (qua > 1)
    {
        std::uint16_t min = del(heap, qua-1, table);
        std::uint16_t premin = del(heap, qua-2, table);
        table->Q[extra] = table->Q[min] + table->Q[premin];
        table->L[extra] = min; table->R[extra] = premin;
        add(heap, extra, qua-2, table);
        extra++; qua--;
    }
    return del(heap, 0, table);
}

void print(std::uint16_t root, Table * table, int align)
{
    if (align == 0) std::cout << "TREE\n";
    for (int i = 0; i < align; i++) std::cout << "|";
    std::cout << "~" <<root << " : " << table->Q[root];
    std::cout << '\n';
    if (table->L[root] != size-1) print(table->L[root], table, align+1);
    if (table->R[root] != size-1) print(table->R[root], table, align+1);
}

void setLength(std::uint16_t root, Table * table, std::uint8_t length)
{
    if (root < size/2) table->l[root] = length;
    if (table->L[root] != size-1) setLength(table->L[root], table, length+1);
    if (table->R[root] != size-1) setLength(table->R[root], table, length+1);
}