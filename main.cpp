#include <iostream>
#include <fstream>
#include <cstdint>
#include "lib/Table.hpp"
#include "lib/Heap.hpp"
#include "lib/Tree.hpp"
#include "lib/Code.hpp"


int coder(bool verbose = false)
{
    std::cout <<"- - - C O M P R E S S O R - - -\n";
    std::cout <<"Enter the file name: ";
    std::string FileName; std::cin >> FileName; std::cin.ignore();

    Table * T = getTable(FileName);
    print(T->Q);
    std::uint16_t * CountHeap = getHeap(T);
    print(CountHeap); 
    std::uint16_t TreeRoot = getTree(T, CountHeap);
    print(TreeRoot, T, 0);
    setLength(TreeRoot, T);
    print(T);
    std::uint16_t * LengthHeap = _getHeap(T);
    print(LengthHeap);
    setCode(T, LengthHeap);
    print(T);
    write(FileName, "compressed.huf", T);
    return 0;
}

int main()

{
    while(true)
    {
        coder(true);
        std::cout << "Enter 'e' to exit and any other symbol to restart: ";
        char c = std::cin.get();
        if (c == 'e') break;
    }

    return 0;
}