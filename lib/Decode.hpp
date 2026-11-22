#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include "Heap.hpp"
#include "Code.hpp"

struct Node {std::uint16_t pos; Node * left; Node * right;};

std::uint8_t * getLength(std::string file_name);

Node * insert(std::uint16_t i, std::uint8_t len, Table * table, Node * root);
void decode(Table * table, Node * root, std::string file_name);

