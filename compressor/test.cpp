#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <chrono>
#include "lib/Table.hpp"
#include "lib/Heap.hpp"
#include "lib/Tree.hpp"
#include "lib/Code.hpp"


int coder(std::string FileName, bool verbose = false, std::string report_name = "report.txt")
{
    std::cout <<"* * * C O M P R E S S O R * * *\n";
    auto begin = std::chrono::steady_clock::now();
    std::uint32_t * Quantity = getTable(FileName);
    if (verbose) report(Quantity, report_name);
    if (Quantity == nullptr) return 1;
    std::uint32_t fileSize = getSize(Quantity);
    std::uint16_t nonzero = getNonzero(Quantity);
    Quantity[256] = nonzero;

    std::cout << "The file has " << nonzero << " unique byte(s)\n" << "The file size is " << fileSize << " byte(s)\n";

    auto end1 = std::chrono::steady_clock::now();

    std::uint16_t * Heap1 = getHeap(Quantity);
    if (verbose) report(Heap1, report_name);
    if (Heap1 == nullptr) return 2;

    std::uint16_t * Children = children();

    std::uint16_t Root = getTree(Quantity, Children, Heap1);
    if (verbose) report(Root, Quantity, Children, report_name);

    std::uint8_t * Length = new std::uint8_t[256]();
    setLength(Root, Children, Length);
    if (verbose) report(Length, report_name);

    std::uint16_t * Heap2 = getHeap(Length);
    if (verbose) report(Heap2, report_name);
    if (Heap2 == nullptr) return 3;

    setCode(Quantity, Length, Heap2, nonzero);
    if (verbose) report(Quantity, report_name);

    auto end2 = std::chrono::steady_clock::now();

    std::uint32_t outputSize = write(FileName, FileName + ".huf", Quantity, Length, fileSize);

    std::cout << "The compressed file size is " << outputSize << " byte(s)\n";

    double K = (double) outputSize / fileSize;
    std::cout << "The compression coefficient is " << K << "\n";

    auto end3 = std::chrono::steady_clock::now();
    auto span1 = std::chrono::duration_cast<std::chrono::microseconds>(end1-begin);
    auto span2 = std::chrono::duration_cast<std::chrono::microseconds>(end2-end1);
    auto span3 = std::chrono::duration_cast<std::chrono::microseconds>(end3-end1);
    if (!verbose) 
    {
        std::ofstream report(report_name, std::ios::app);
        report << span1.count() << ' ' << span2.count() << ' '<< span3.count() << '\n';
        report.close();
    }
    delete[] Heap2;
    delete[] Length;
    delete[] Children;
    delete[] Heap1;
    delete[] Quantity;
    return 0;
}

int main()

{
    for (int i = 0; i < 60; i++)
    {
        coder(std::to_string(i)+".txt", false);
    }
    return 0;
}