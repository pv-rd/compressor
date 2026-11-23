#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include "lib/Heap.hpp"
#include "lib/Table.hpp"
#include "lib/Code.hpp"
#include "lib/Decode.hpp"


int decoder(bool verbose = false, std::string report_name = "report.txt")
{
    std::cout <<"* * * D E C O M P R E S S O R * * *\n";
    std::cout <<"Enter the file name: ";
    std::string FileName; std::cin >> FileName; std::cin.ignore();

    std::uint8_t * Length = getLength(FileName);
    if (verbose) report(Length, report_name);
    if (Length == nullptr) return 1;
    
    int nonzero = 0;
    for (int i = 0; i < 256; i++) if (Length[i] > 0) nonzero++;

    std::uint16_t * Heap = getHeap(Length);
    if (verbose) report(Heap, report_name);
    if (Heap == nullptr) {delete[] Length; return 2;}

    std::uint32_t * Code = new std::uint32_t[256]();
    setCode(Code, Length, Heap, nonzero);
    if (verbose) report(Code, report_name);

    Node * Root = new Node{511, nullptr, nullptr};
    for (int i = 0; i < 256; i++) if (Length[i] > 0) insert(i, Length[i], Code, Root);

    std::uint32_t outputSize = decode(Code, Length, Root, FileName, FileName.substr(0, FileName.size() - 4));

    std::cout << "The decompressed file size is " << outputSize << " byte(s)\n";

    Root = erase(Root);

    delete[] Code; delete[] Heap; delete[] Length;
    return 0;

}


int main()

{
    while(true)
    {
        decoder(true);
        std::cout << "Enter 'e' to exit or only 'Enter' to restart: ";
        char c = std::cin.get();
        if (c == 'e') break;
    }

    return 0;
}