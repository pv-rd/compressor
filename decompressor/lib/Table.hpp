#pragma once

#include <fstream>
#include <cstdint>
#include <string>

std::uint16_t * children();
std::uint32_t * getTable(std::string file_name);
std::uint16_t getNonzero(std::uint32_t * table);
std::uint32_t getSize(std::uint32_t * table);
void report(std::uint32_t * table, std::string file_name);