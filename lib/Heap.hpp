#pragma once

#include <iostream>
#include <cstdint>
#include "Table.hpp"


int rise(std::uint16_t * heap, int i, Table * table);
int down(std::uint16_t * heap, int i, Table * table);
int add(std::uint16_t * heap, int i, int end, Table * table);
std::uint16_t del(std::uint16_t * heap, int end, Table * table);
std::uint16_t * getHeap(Table * table);
void print(std::uint16_t * heap);

int _rise(std::uint16_t * heap, int i, Table * table);
int _down(std::uint16_t * heap, int i, Table * table);
int _add(std::uint16_t * heap, int i, int end, Table * table);
std::uint16_t _del(std::uint16_t * heap, int end, Table * table);
std::uint16_t * _getHeap(Table * table);
