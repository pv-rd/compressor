#include "Table.hpp"

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <bitset>


constexpr int size = 512;

std::uint32_t * count(std::string file_name)
{
    std::ifstream file(file_name, std::ios::binary);
    if (!file.is_open()) return nullptr;
    char current;
    std::uint32_t * res = new std::uint32_t[size]();
    while (file.get(current)) res[(unsigned char)current]++;
    file.close();
    return res;
}

std::uint16_t * indexes()
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

Table * getTable(std::string file_name)
{
    std::uint32_t * table = count(file_name);
    return new Table{table, 
        indexes(), 
        indexes(), 
        new std::uint8_t[size](), 
        getNonzero(table), 
        getSize(table)};
}

void print(std::uint32_t * table)
{
    std::cout << "TABLE OF QUANTITY\n";
    for (int i = 0; i < size; i++)
    {
        std::cout << i << '\t' << table[i] << '\n';
    }
}

void print(Table * table)
{
    std::cout << "TABLE\n";
    for (int i = 0; i < size; i++)
    {
        std::cout << i << '\t' << std::bitset<32>(table->Q[i]) << '\t' << table->L[i] << '\t' << table->R[i] << '\t' << (int) table->l[i]<< '\n';
    }
}

