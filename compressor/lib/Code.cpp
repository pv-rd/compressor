#include "Code.hpp"
#include <fstream>
#include <cstdint>
#include <string>
#include "Heap.hpp"


bool get_bit(std::uint32_t code, int pos)
{
    std::uint32_t mask = 1 << pos;
    return code & mask;
}

std::uint8_t set_bit(std::uint8_t Byte, int pos, bool bit)
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

void setCode(std::uint32_t * table, std::uint8_t * length, std::uint16_t * heap, int nonzero)
{
    int end = nonzero-1;
    std::uint16_t pre = del(heap, end, length);
    end--;
    int prelen = length[pre];
    table[pre] = 0;

    while (end >=0)
    {
        std::uint16_t sle = del(heap, end, length);
        end--;
        int len = length[sle];
        if (len > prelen)
        {
            table[sle] = (table[pre]+1) << (len-prelen);
        }
        else table[sle] = table[pre]+1;

        pre = sle;
        prelen = len;
    }

}

std::uint32_t write(std::string input_name, std::string output_name, std::uint32_t * table, std::uint8_t * Length, std::uint32_t Size)
{
    std::ifstream input(input_name, std::ios::binary);
    std::ofstream output(output_name, std::ios::binary);
    if (!input.is_open() || !output.is_open()) return 0;
    
    output.put((char)((Size >> 0)  & 255));
    output.put((char)((Size >> 8)  & 255));
    output.put((char)((Size >> 16) & 255));
    output.put((char)((Size >> 24) & 255));

    for (int i = 0; i < 256; i++) output.put((char)Length[i]);
    std::uint32_t outsize = 260;
    char current;
    std::uint8_t buffer = 0;
    std::uint8_t I = 0;
    while(input.get(current))
    {
        
        std::uint32_t code = table[(unsigned char)current];
        std::uint8_t length = Length[(unsigned char)current];
        for (int i = length-1; i >= 0; i--)
        {
            if (I == 8)
            {
                output.put((char)buffer);
                buffer = 0;
                I = 0;
                outsize++;
            }
            buffer = set_bit(buffer, I, get_bit(code, i));
            I++;
        }
    }
    if (I > 0) {outsize++; output.put( (char)buffer);}
    output.close(); input.close();
    return outsize;
}