#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include "lib/Table.hpp"
#include "lib/Heap.hpp"
#include "lib/Tree.hpp"
#include "lib/Code.hpp"
#include "lib/Decode.hpp"


int coder(bool verbose = false, std::string report_name = "report.txt")
{
    std::cout <<"* * * C O M P R E S S O R * * *\n";
    std::cout <<"Enter the file name: ";
    std::string FileName; std::cin >> FileName; std::cin.ignore();

    Table * table = getTable(FileName);
    report(table, report_name);
    if (table == nullptr) return 1;

    std::uint16_t * CountHeap = getHeap(table);
    report(CountHeap, report_name);
    if (CountHeap == nullptr) return 2;

    std::uint16_t TreeRoot = getTree(table, CountHeap);
    report(table, report_name);
    setLength(TreeRoot, table);
    report(table, report_name);

    std::uint16_t * LengthHeap = _getHeap(table);
    report(LengthHeap, report_name);

    setCode(table, LengthHeap);
    report(table, report_name);
    write(FileName, "compressed.huf", table);
    return 0;
}


int decoder(bool verbose = false)
{
    std::cout <<"* * * D E C O M P R E S S O R * * *\n";
    std::cout <<"Enter the file name: ";
    std::string FileName; std::cin >> FileName; std::cin.ignore();

    std::uint8_t * Length = getLength(FileName);
    int nonzero = 0;
    for (int i = 0; i < 256; i++) if (Length[i] > 0) nonzero++;

    Table * table = new Table{new uint32_t[512](), new uint16_t[512](), new uint16_t[512](), Length, nonzero, 0};
    std::uint16_t * Heap = _getHeap(table);
    setCode(table, Heap);
    print(table);

    Node * root = new Node{511, nullptr, nullptr};
    for (int i =0; i < 256; i++) insert(i, table->l[i], table, root);

    decode(table, root, FileName);

}
int main()

{
    while(true)
    {
        decoder(true);
        std::cout << "Enter 'e' to exit and any other symbol to restart: ";
        char c = std::cin.get();
        if (c == 'e') break;
    }

    return 0;
}