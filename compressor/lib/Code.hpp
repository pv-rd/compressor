#pragma once

#include <fstream>
#include <cstdint>
#include <string>
#include "Heap.hpp"

bool get_bit(std::uint32_t code, int pos);
std::uint8_t set_bit(std::uint8_t Byte, int pos, bool bit = true);
int byte_size(int bit_size);
void setCode(std::uint32_t * table, std::uint8_t * length, std::uint16_t * heap, int nonzero);
std::uint32_t write(std::string input_name, std::string output_name, std::uint32_t * table, std::uint8_t * Length, std::uint32_t Size);