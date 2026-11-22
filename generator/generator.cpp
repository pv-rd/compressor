#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <random>
using byte = std::uint8_t;
using big = std::uint32_t;

int main()
{
    std::cout << "Enter the distribution file name: ";
    std::string distName;
    std::getline(std::cin, distName);
    std::ifstream input(distName);
    big distribution[256] = {};
    big sum = 0;

    for (int i = 0; i < 256; i++) 
    {
        input >> distribution[i];
        sum += distribution[i];
    }
    input.close();

    byte * array = new byte[sum]();
    int I = 0;
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < distribution[i]; j++)
        {
            array[I] = (byte)i; I++;
        }
    }

    std::cout << "Enter the output file size: ";
    big size = 0; 
    std::cin >> size;

    const int seed = 10111;
    std::default_random_engine engine(seed);

    const big min = 0, max = sum;
    std::uniform_int_distribution <big> distr(min, max);
    
    std::ofstream output("random.txt");
    for (big i = 0; i < size; i++)
    {
        output << (char) array[distr(engine)];
    }
    output.close();
    
    return 0;
}