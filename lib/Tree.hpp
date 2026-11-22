#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include "Heap.hpp"

std::uint16_t getTree(Table * table, std::uint16_t * heap);
void print(std::uint16_t root, Table * table, int align);

void setLength(std::uint16_t root, Table * table, std::uint8_t length = 0);
