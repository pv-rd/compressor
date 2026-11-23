#pragma once

#include <iostream>
#include <cstdint>
#include "Table.hpp"


int rise(std::uint16_t * heap, int i, std::uint32_t * table);
int down(std::uint16_t * heap, int i, std::uint32_t * table);
int add(std::uint16_t * heap, int i, int end, std::uint32_t * table);
std::uint16_t del(std::uint16_t * heap, int end, std::uint32_t * table);
std::uint16_t * getHeap(std::uint32_t * table);

void report(std::uint16_t * heap, std::string file_name);

int rise(std::uint16_t * heap, int i, std::uint8_t * table);
int down(std::uint16_t * heap, int i, std::uint8_t * table);
int add(std::uint16_t * heap, int i, int end, std::uint8_t * table);
std::uint16_t del(std::uint16_t * heap, int end, std::uint8_t * table);
std::uint16_t * getHeap(std::uint8_t * table);
