#include "Code.hpp"
#include <iostream>
#include <fstream>
#include <cstdint>
#include "Table.hpp"
#include "Heap.hpp"


bool get_bit(std::uint32_t code, int pos = 0)
{
    std::uint32_t mask = 1 << pos;
    return code & mask;
}

std::uint8_t set_bit(std::uint8_t Byte, int pos, bool bit = true)
{
    std::uint8_t mask = 0b10000000 >> pos;
    if (bit)
        return Byte | mask;
    else
        return Byte & (~mask);
}

int byte_size(int bit_size)
{
    if (bit_size == 0) return 0;
    return (bit_size - 1) / 8 + 1;
}

void setCode(Table * table, std::uint16_t * heap)
{
    int end = table->nonzero-1;
    std::uint8_t pre = _del(heap, end, table);
    end--;
    int prelen = table->l[pre];
    table->Q[pre] = 0;

    while (end >=0)
    {
        std::uint8_t sle = _del(heap, end, table);
        end--;
        int len = table->l[sle];
        if (len > prelen)
        {
            table->Q[sle] = (table->Q[pre]+1) << (len-prelen);
        }
        else table->Q[sle] = table->Q[pre]+1;

        pre = sle;
        prelen = len;
    }

}

bool write(std::string input_name, std::string output_name, Table * T)
{
    std::ifstream input(input_name, std::ios::binary);
    std::ofstream output(output_name, std::ios::binary);
    if (!input.is_open() || !output.is_open()) return false;

    for (int i = 0; i < 256; i++) output << (char) T->l[i];

    char current;
    std::uint8_t buffer = 0;
    std::uint8_t I = 0;
    while(input.get(current))
    {
        std::uint32_t code = T->Q[(unsigned char)current];
        std::uint8_t length = T->l[(unsigned char)current];
        for (int i = length-1; i >= 0; i--)
        {
            if (I == 8)
            {
                output << (char)buffer;
                buffer = 0;
                I = 0;
            }
            buffer = set_bit(buffer, I, get_bit(code, i));
            I++;
        }
    }
    if (I > 0) output << (char)buffer;
    output.close(); input.close();
    return true;
}