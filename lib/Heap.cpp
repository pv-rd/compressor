#include "Heap.hpp"

#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include "Table.hpp"

constexpr int size = 512;

int rise(std::uint16_t * heap, int i, Table * table) 
{
    if (i <= 0) return 0;
    if (heap[i] == size - 1) return i;

    int parent = (i - 1) / 2;
    int res = i;

    std::uint32_t Current = table->Q[heap[i]];
    std::uint32_t Parent = table->Q[heap[parent]];

    if (Current < Parent || Current == Parent && heap[i] < heap[parent]) 
    {
        std::swap(heap[i], heap[parent]);
        res = rise(heap, parent, table);
    }

    return res;
}

int down(std::uint16_t * heap, int i, Table * table)
{
    int left = 2*i + 1, right = 2*i + 2, child = -1;
    if (left >= size || heap[left] == size-1) left = -1;
    if (right >= size || heap[right] == size-1) right = -1;

    if (left >= 0 && right >= 0)
    {
        std::uint32_t Left = table->Q[heap[left]];
        std::uint32_t Right = table->Q[heap[right]];
        if (Right < Left || Right == Left && heap[right] < heap[left])
            child = right;
        else child = left;
    }
    else if (left >= 0) child = left;
    else if (right >= 0) child = right;

    if (child == -1) return i;

    std::uint32_t Child = table->Q[heap[child]];
    std::uint32_t Current = table->Q[heap[i]];

    if (Child < Current || Current==Child && heap[child] < heap[i])
    {
        std::swap(heap[i], heap[child]);
        return down(heap, child, table);
    }
    return i;
}

int add(std::uint16_t * heap, int i, int end, Table * table)
{
    heap[end] = i;
    return rise(heap, end, table);
}

std::uint16_t del(std::uint16_t * heap, int end, Table * table)
{
    std::uint16_t res = heap[0];
    heap[0] = heap[end];
    heap[end] = size-1;
    if (end > 0) down(heap, 0, table);
    return res;
}

std::uint16_t * getHeap(Table * table)
{
    std::uint16_t * heap = new std::uint16_t[size/2]();
    int end = 0;
    for (int i = 0; i < size/2; i++)
    {
        if (table->Q[i] > 0)
        {
            add(heap, i, end, table);
            end++;
        }
    }
    for (int i = end; i < size/2; i++) heap[i] = size-1;
    return heap;
}

void print(std::uint16_t * heap)
{
    std::cout << "HEAP BY QUANTITY\n";
    for (int i = 0; i < size/2; i++)
    {
        std::cout << i << '\t';
        if (heap[i] == size-1) std::cout << "VOID(511)";
        else std::cout << heap[i];
        std::cout << '\n';
    }
}

void report(std::uint16_t * heap, std::string file_name)
{
    std::ofstream file(file_name, std::ios::app|std::ios::binary);
    if (file.is_open())
    {
        if (heap == nullptr) {file << "NO HEAP\n"; return;}
        file << "HEAP\n";
        for (int i = 0; i < size/2; i++)
        {
            file << i << '\t' << heap[i] << '\n';
        }
        file << "END HEAP\n";
        file.close();
    }
}


int _rise(std::uint16_t * heap, int i, Table * table) 
{
    if (i <= 0) return 0;
    if (heap[i] == size - 1) return i;

    int parent = (i - 1) / 2;
    int res = i;

    std::uint8_t Current = table->l[heap[i]];
    std::uint8_t Parent = table->l[heap[parent]];

    if (Current < Parent || Current == Parent && heap[i] < heap[parent]) 
    {
        std::swap(heap[i], heap[parent]);
        res = _rise(heap, parent, table);
    }

    return res;
}

int _down(std::uint16_t * heap, int i, Table * table)
{
    int left = 2*i + 1, right = 2*i + 2, child = -1;
    if (left >= size || heap[left] == size-1) left = -1;
    if (right >= size || heap[right] == size-1) right = -1;


    if (left >= 0 && right >= 0)
    {
        std::uint8_t Left = table->l[heap[left]];
        std::uint8_t Right = table->l[heap[right]];
        if (Right < Left || Right == Left && heap[right] < heap[left])
            child = right;
        else child = left;
    }
    else if (left >= 0) child = left;
    else if (right >= 0) child = right;

    if (child == -1) return i;

    std::uint8_t Child = table->l[heap[child]];
    std::uint8_t Current = table->l[heap[i]];

    if (Child < Current || Current==Child && heap[child] < heap[i])
    {
        std::swap(heap[i], heap[child]);
        return _down(heap, child, table);
    }
    return i;
}

int _add(std::uint16_t * heap, int i, int end, Table * table)
{
    heap[end] = i;
    return _rise(heap, end, table);
}

std::uint16_t _del(std::uint16_t * heap, int end, Table * table)
{
    std::uint16_t res = heap[0];
    heap[0] = heap[end];
    heap[end] = size-1;
    if (end > 0) _down(heap, 0, table);
    return res;
}

std::uint16_t * _getHeap(Table * table)
{
    std::uint16_t * heap = new std::uint16_t[size/2]();
    int end = 0;
    for (int i = 0; i < size/2; i++)
    {
        if (table->l[i] > 0)
        {
            _add(heap, i, end, table);
            end++;
        }
    }
    for (int i = end; i < size/2; i++) heap[i] = 511;
    return heap;
}
