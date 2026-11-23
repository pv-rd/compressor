#include "Table.hpp"

#include <fstream>
#include <cstdint>
#include <string>

constexpr int size = 512;


std::uint16_t * children()
{
    std::uint16_t * res = new std::uint16_t[size]();
    for (int i = 0; i < size; i++) res[i] = size-1; // в эту ячейку никогда не попадём (индикатор отсутствия потомка!)
    return res;
}

std::uint16_t getNonzero(std::uint32_t * table)
{
    std::uint16_t res = 0;
    for (int i = 0; i < size; i++) if (table[i] > 0) res++;
    return res;
}

std::uint32_t getSize(std::uint32_t * table)
{
    std::uint32_t res = 0;
    for (int i = 0; i < size; i++) if (table[i] > 0) res+=table[i];
    return res;
}

std::uint32_t * getTable(std::string file_name)
{
    std::ifstream file(file_name, std::ios::binary); // говорят, что виндовс так не будет менять /n на /r/n
    if (!file.is_open()) return nullptr;
    char current;
    std::uint32_t * res = new std::uint32_t[size]();
    while (file.get(current)) res[(unsigned char)current]++;
    file.close();
    return res;
}

void report(std::uint32_t * table, std::string file_name)
{
    std::ofstream file(file_name, std::ios::app|std::ios::binary);
    if (file.is_open())
    {
        if (table == nullptr) {file << "NO TABLE\n"; return;}
        file << "TABLE\n";
        for (int i = 0; i < size/2; i++) file << i << '\t' << table[i] << '\n';
        file.close();
    }
}

