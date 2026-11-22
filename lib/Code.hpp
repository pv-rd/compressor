#include <iostream>
#include <fstream>
#include <cstdint>
#include "Table.hpp"
#include "Heap.hpp"
void setCode(Table * table, std::uint16_t * heap);
bool write(std::string input_name, std::string output_name, Table * T);
bool get_bit(std::uint32_t code, int pos);