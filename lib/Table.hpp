#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

struct Table {
    std::uint32_t * Q; // количество байт
    std::uint16_t * L; // левые потомки
    std::uint16_t * R; // правые
    std::uint8_t * l; // длины кодов
    std::uint16_t nonzero; // чилсо ненулевых строк (уникальных байтов)
    std::uint32_t size; // сумма строк (число байтов в исх файле)
};

Table * getTable(std::string file_name);

void print(Table * table);
void report(Table * table, std::string file_name);