#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <random>
using byte = std::uint8_t;
using big = std::uint32_t;

int main()
{
    std::ifstream input("distr.txt");
    big distribution[33][256];
    big sum[33] = {};

    for (int i = 0; i < 256; i++) 
    {
        for (int j = 0; j < 33; j++)
        {
            input >> distribution[j][i];
            sum[j] += distribution[j][i];
        }
    }
    input.close();

    const int seed = 10111;
    std::default_random_engine engine(seed);
    big size = 1024*1024;
    for (int k = 0; k < 100; k++)
    {
        int j = 16;
        byte * array = new byte[sum[j]]();
        int I = 0;
        for (int i = 0; i < 256; i++)
        {
            for (int k = 0; k < distribution[j][i]; k++)
            {
                array[I] = (byte)i; I++;
            }
        }

        const big min = 0, max = sum[j];
        std::uniform_int_distribution <big> distr(min, max);
        
        std::ofstream output(std::to_string(k) + ".txt");

        for (big i = 0; i < size; i++)
        {
            output << (char) array[distr(engine)];
        }
        size += 1024*1024;
        output.close();
        delete[] array;
    }
    return 0;
}