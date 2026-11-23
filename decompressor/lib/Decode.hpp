#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include "Code.hpp"

struct Node {std::uint16_t pos; Node * left; Node * right;};

std::uint8_t * getLength(std::string file_name);
void report(std::uint8_t * Length, std::string report_name);

Node * insert(std::uint16_t symbol, std::uint8_t length, std::uint32_t * code, Node * root);
Node * erase(Node * root);

std::uint32_t decode(std::uint32_t * code,std::uint8_t * length, Node * root, std::string input_name, std::string output_name);

