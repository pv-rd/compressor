#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <bitset>

struct Table {
    std::uint32_t * Q; // количество байт
    std::uint16_t * L; // левые потомки
    std::uint16_t * R; // правые
    std::uint8_t * l; // длины кодов
    std::uint16_t nonzero; // чилсо ненулевых строк (уникальных байтов)
    std::uint32_t size; // сумма строк (число байтов в исх файле)
};


std::uint16_t * indexes();

std::uint16_t getNonzero(std::uint32_t * table);

std::uint32_t getSize(std::uint32_t * table);

Table * getTable(std::string file_name);
void print(std::uint32_t * table);
void print(Table * table);
