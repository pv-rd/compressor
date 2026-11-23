#include "Heap.hpp"

#include <cstdint>
#include <fstream>
#include <string>

constexpr int size = 512;
constexpr int null = size-1;

int rise(std::uint16_t * heap, int i, std::uint32_t * table) 
{
    if (i <= 0) return 0;
    if (heap[i] == null) return i;

    int parent = (i - 1) / 2;
    int res = i;

    std::uint32_t Current = table[heap[i]];
    std::uint32_t Parent = table[heap[parent]];

    if (Current < Parent || Current == Parent && heap[i] < heap[parent]) 
    {
        std::swap(heap[i], heap[parent]);
        res = rise(heap, parent, table);
    }

    return res;
}

int down(std::uint16_t * heap, int i, std::uint32_t * table)
{
    int left = 2*i + 1, right = 2*i + 2, child = -1;
    if (left >= size/2 || heap[left] == null) left = -1;
    if (right >= size/2 || heap[right] == null) right = -1;

    if (left >= 0 && right >= 0)
    {
        std::uint32_t Left = table[heap[left]];
        std::uint32_t Right = table[heap[right]];
        if (Right < Left || Right == Left && heap[right] < heap[left])
            child = right;
        else child = left;
    }
    else if (left >= 0) child = left;
    else if (right >= 0) child = right;

    if (child == -1) return i;

    std::uint32_t Child = table[heap[child]];
    std::uint32_t Current = table[heap[i]];

    if (Child < Current || Current==Child && heap[child] < heap[i])
    {
        std::swap(heap[i], heap[child]);
        return down(heap, child, table);
    }
    return i;
}

int add(std::uint16_t * heap, int i, int end, std::uint32_t * table)
{
    heap[end] = i;
    return rise(heap, end, table);
}

std::uint16_t del(std::uint16_t * heap, int end, std::uint32_t * table)
{
    std::uint16_t res = heap[0];
    heap[0] = heap[end];
    heap[end] = null;
    if (end > 0) down(heap, 0, table);
    return res;
}

std::uint16_t * getHeap(std::uint32_t * table)
{
    std::uint16_t * heap = new std::uint16_t[size/2]();
    int end = 0;
    for (int i = 0; i < size/2; i++)
    {
        if (table[i] > 0)
        {
            add(heap, i, end, table);
            end++;
        }
    }
    for (int i = end; i < size/2; i++) heap[i] = null;
    return heap;
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
        file.close();
    }
}


int rise(std::uint16_t * heap, int i, std::uint8_t * table) 
{
    if (i <= 0) return 0;
    if (heap[i] == null) return i;

    int parent = (i - 1) / 2;
    int res = i;

    std::uint8_t Current = table[heap[i]];
    std::uint8_t Parent = table[heap[parent]];

    if (Current < Parent || Current == Parent && heap[i] < heap[parent]) 
    {
        std::swap(heap[i], heap[parent]);
        res = rise(heap, parent, table);
    }

    return res;
}

int down(std::uint16_t * heap, int i, std::uint8_t * table)
{
    int left = 2*i + 1, right = 2*i + 2, child = -1;
    if (left >= size/2 || heap[left] == null) left = -1;
    if (right >= size/2 || heap[right] == null) right = -1;

    if (left >= 0 && right >= 0)
    {
        std::uint8_t Left = table[heap[left]];
        std::uint8_t Right = table[heap[right]];
        if (Right < Left || Right == Left && heap[right] < heap[left])
            child = right;
        else child = left;
    }
    else if (left >= 0) child = left;
    else if (right >= 0) child = right;

    if (child == -1) return i;

    std::uint8_t Child = table[heap[child]];
    std::uint8_t Current = table[heap[i]];

    if (Child < Current || Current==Child && heap[child] < heap[i])
    {
        std::swap(heap[i], heap[child]);
        return down(heap, child, table);
    }
    return i;
}

int add(std::uint16_t * heap, int i, int end, std::uint8_t * table)
{
    heap[end] = i;
    return rise(heap, end, table);
}

std::uint16_t del(std::uint16_t * heap, int end, std::uint8_t * table)
{
    std::uint16_t res = heap[0];
    heap[0] = heap[end];
    heap[end] = null;
    if (end > 0) down(heap, 0, table);
    return res;
}

std::uint16_t * getHeap(std::uint8_t * table)
{
    std::uint16_t * heap = new std::uint16_t[size/2]();
    int end = 0;
    for (int i = 0; i < size/2; i++)
    {
        if (table[i] > 0)
        {
            add(heap, i, end, table);
            end++;
        }
    }
    for (int i = end; i < size/2; i++) heap[i] = null;
    return heap;
}
