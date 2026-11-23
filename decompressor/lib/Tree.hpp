#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include "Heap.hpp"

std::uint16_t getTree(std::uint32_t * table, std::uint16_t * children, std::uint16_t * heap);
void report(std::uint16_t root, std::uint32_t * table, std::uint16_t * children, std::string file_name);
void setLength(std::uint16_t root, std::uint16_t * children, std::uint8_t * Length, std::uint8_t length = 0);
void report(std::uint8_t * length, std::string file_name);
