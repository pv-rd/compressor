#include "Table.hpp"

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>


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

Table * getTable(std::string file_name)
{
    std::uint32_t * table = count(file_name);
    if (table == nullptr) return nullptr;
    return new Table
    {
        table, 
        children(), 
        children(), 
        new std::uint8_t[size](), 
        getNonzero(table), 
        getSize(table)
    };
}


void print(Table * table)
{
    std::cout << "TABLE\n";
    for (int i = 0; i < size; i++)
    {
        std::cout << i << '\t' << table->Q[i] << '\t' << table->L[i] << '\t' << table->R[i] << '\t' << (int) table->l[i]<< '\n';
    }
}

void report(Table * table, std::string file_name)
{
    std::ofstream file(file_name, std::ios::app|std::ios::binary);
    if (file.is_open())
    {
        if (table == nullptr) {file << "NO TABLE\n"; return;}
        file << "TABLE\n";
        for (int i = 0; i < size; i++)
        {
            file << i << '\t' << table->Q[i] << "\t\t" << table->L[i] << '\t' << table->R[i] << '\t' << (int) table->l[i]<< '\n';
        }
        file << "END TABLE\n";
        file.close();
    }
}

