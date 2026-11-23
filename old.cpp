#include <iostream>
#include <fstream>
#include <cstdint>

constexpr int size = 512;
constexpr int input_buffer = 256;

using byte = std::uint8_t;
using index = std::uint16_t;
using big = std::uint32_t;

// построение таблицы частот

big * get_table(const char * file_name, bool count_size = true)
{
    std::ifstream file(file_name, std::ios::binary);
    if (!file.is_open()) return nullptr;
    char current;
    big * res = new big[size]();
    while (file.get(current)) 
    {
        res[(index)(unsigned char)current]++;
        if (count_size) res[size/2]++;
    }
    file.close();
    return res;
}

int count_nonzero(big * table)
{
    int res = 0;
    for (int i = 0; i < size; i++) if (table[i] > 0) res++;
    return res;
}

int count_nonzero(byte ** table)
{
    int res = 0;
    for (int i = 0; i < size; i++) if (table[i] != nullptr) res++;
    return res;
}

enum PrintMode : char {Full, Half, Nonzero};
void print(big * table, PrintMode mode)
{
    if (table == nullptr)
    {
    std::cout << "No table\n"; return;
    }
    
    std::cout << "Table of byte quantity\n";
    if (mode == PrintMode::Full)
    {
        for (int i = 0; i < size; i++)
        {
            std::cout <<  i << "\t" << table[i] << '\n';
        }
        return;
    }
    if (mode == PrintMode::Half)
    {
        for (int i = 0; i < size/2; i++)
        {
            std::cout <<  i << "\t" << table[i] << '\n';
        }
        return;
    }
    if (mode == PrintMode::Nonzero)
    {
        for (int i = 0; i < size; i++)
        {
            if (table[i] > 0) std::cout <<  i << "\t" << table[i] << '\n';
        }
        return;
    }
        
    
}

// узел дерева Хаффмана

/*на индексе pos, равному байту, 
в Qtable храним количество байтов,
в Ltable - длину кода */

struct Node
{
    index pos;
    Node * left;
    Node * right;
};

Node * get_node(index Pos, Node * Left = nullptr, Node * Right=nullptr)
{
    return new Node{Pos, Left, Right};
}


Node * get_parent(Node * Left, Node * Right, big * Qtable, index extra)
{
    if (Left != nullptr) Qtable[extra] += Qtable[Left->pos];
    if (Right != nullptr) Qtable[extra] += Qtable[Left->pos];

    return new Node{extra, Left, Right};
}

// минимальная куча

int get_size(Node ** heap)
{
    int start = size;
    while (start > 1 && heap[start-1] == nullptr) start--;
    return start;
}

int rise(Node ** heap, int i, big * table) 
{
    if (heap == nullptr || table == nullptr || i >= size) return -1;
    if (i <= 0) return 0;

    int parent = (i - 1) / 2;
    int res = i;

    if (heap[i] == nullptr) return i;

    big Current = table[heap[i]->pos];
    big Parent = table[heap[parent]->pos];

    if (Current < Parent || Current == Parent && heap[i]->pos < heap[parent]->pos) 
    {
        std::swap(heap[i], heap[parent]);
        res = rise(heap, parent, table);
    }

    return res;
}

int down(Node ** heap, int i, big * table)
{
    if (heap == nullptr || table == nullptr || i < 0 || i >= size) return -1;
    //int hsize = get_size(heap);
    int left = 2*i + 1, right = 2*i + 2, child = -1;
    if (left >= size) left = -1;
    if (right >= size) right = -1;


    if (left >= 0 && heap[left] != nullptr && right >= 0 && heap[right] != nullptr)
    {
        big Left = table[heap[left]->pos];
        big Right = table[heap[right]->pos];
        if (Right < Left || Right == Left && heap[right]->pos < heap[left]->pos)
            child = right;
        else child = left;
    }
    else if (left >= 0 && heap[left] != nullptr) child = left;
    else if (right >= 0 && heap[right] != nullptr) child = right;

    if (child == -1) return i;

    big Child = table[heap[child]->pos];
    big Current = table[heap[i]->pos];

    if (Child < Current || Current==Child && heap[child]->pos < heap[i]->pos)
    {
        std::swap(heap[i], heap[child]);
        return down(heap, child, table);
    }
    return i;
}

int add(Node ** heap, Node * node, int end, big * table)
{
    if (end > get_size(heap) || end < 0) return -1;
    if (heap[end] != nullptr) return -1;
    heap[end] = node;
    return rise(heap, end, table);
}

Node * del(Node ** heap, int end, big * table)
{
    if (end >= get_size(heap) || end < 0) return nullptr;
    Node * res = heap[0];
    heap[0] = heap[end];
    heap[end] = nullptr;
    if (end > 0) down(heap, 0, table);
    return res;
}

Node ** get_heap(big * table)
{
    Node ** heap = new Node*[size]();
    int end = 0;
    for (int i = 0; i < size; i++)
    {
        if (table[i] > 0)
        {
            Node * node = new Node {i, nullptr, nullptr};
            add(heap, node, end, table);
            end++;
        }
    }
    return heap;
}

void print_heap(Node ** heap, big * table)
{
    std::cout << "Heap\n";
    for (int i = 0; i < get_size(heap); i++)
    {
        std::cout << i << "\t";
        if (heap[i] == nullptr) std::cout << "NULL\n";
        else
        {
            std::cout << heap[i]->pos << "\t" << table[heap[i]->pos] << '\n';
        }
    }
}


// для длин

int get_size(byte * heap)
{
    int start = size/2;
    while (start > 1 && heap[start-1] == 0) start--;
    return start;
}

int rise(byte * heap, int i, byte * table) 
{
    if (heap == nullptr || table == nullptr || i >= size/2) return -1;
    if (i <= 0) return 0;

    int parent = (i - 1) / 2;
    int res = i;

    byte Current = table[heap[i]];
    byte Parent = table[heap[parent]];

    if (Current < Parent || Current == Parent && heap[i]< heap[parent]) 
    {
        std::swap(heap[i], heap[parent]);
        res = rise(heap, parent, table);
    }

    return res;
}

int down(byte * heap, int i, byte * table)
{
    if (heap == nullptr || table == nullptr || i < 0 || i >= size/2) return -1;
    int hsize = get_size(heap);
    int left = 2*i + 1, right = 2*i + 2, child = -1;
    if (left >= hsize) left = -1;
    if (right >= hsize) right = -1;


    if (left >= 0 && right >= 0)
    {
        byte Left = table[heap[left]];
        byte Right = table[heap[right]];
        if (Right < Left || Right == Left && heap[right] < heap[left])
            child = right;
        else child = left;
    }
    else if (left >= 0) child = left;
    else if (right >= 0) child = right;

    if (child == -1 || heap[child] == 0) return i;

    byte Child = table[heap[child]];
    byte Current = table[heap[i]];

    if (Child < Current || Current==Child && heap[child] < heap[i])
    {
        std::swap(heap[i], heap[child]);
        return down(heap, child, table);
    }
    return i;
}

int add(byte * heap, byte node, int end, byte * table)
{
    if (end > size/2 || end < 0) return -1;
    heap[end] = node;
    return rise(heap, end, table);
}

byte del(byte * heap, int end, byte * table)
{
    if (end >= size/2 || end < 0) return 0;
    byte res = heap[0];
    heap[0] = heap[end];
    heap[end] = 0;
    if (end > 0) down(heap, 0, table);
    return res;
}

byte * get_heap(byte * table)
{
    byte * heap = new byte[size/2]();
    int end = 0;
    for (int i = 0; i < size/2; i++)
    {
        if (table[i] > 0)
        {
            add(heap, i, end, table);
            end++;
        }
    }
    return heap;
}

void print_heap(byte * heap, byte * table)
{
    std::cout << "Heap\n";
    for (int i = 0; i < size/2; i++)
    {
        std::cout << i << "\t";
        std::cout <<(int) heap[i] << "\t" << (int) table[heap[i]] << '\n';
    }
}



// дерево Хаффмана

Node * get_tree(Node ** heap, big * table)
{
    int hsize = get_size(heap);
    index extra = size/2;

    while (hsize > 1)
    {
        Node * Min = del(heap, hsize-1, table);
        hsize--;
        Node * Premin = del(heap, hsize-1, table);
        hsize--;
        Node * parent = get_parent(Min, Premin, table, extra);
        extra++;
        add(heap, parent, hsize, table);
        hsize++;  
    }

    return heap[0];
}

void print(Node * root, big * Qtable, byte * Ltable, int align = 0)
{
    if (root == nullptr)
    {
        std::cout << "No tree\n";
        return;
    } 
    if (align == 0) std::cout << "Tree. Format: |...|~byte : quantity , code_length\n";
    for (int i = 0; i < align; i++) std::cout << "|";
    std::cout << "~" <<root->pos << " : " << Qtable[root->pos] << " , " << (int)Ltable[root->pos];
    std::cout << '\n';
    if (root->left != nullptr) print(root->left,Qtable, Ltable, align+1);
    if (root->right != nullptr) print(root->right,Qtable, Ltable, align + 1);
}

void erase_tree(Node * root)
{
    if (root->left != nullptr) erase_tree(root->left);
    if (root->right != nullptr) erase_tree(root->right);
    delete root;
}

void set_len(Node * root, byte * Ltable, byte Len = 0)
{
    if(root->left == nullptr && root->right == nullptr & Len == 0) 
    {
        Ltable[root->pos] = 1; return;
    }
    Ltable[root->pos] = Len;
    if (root->left != nullptr) set_len(root->left, Ltable, Len+1);
    if (root->right != nullptr) set_len(root->right, Ltable, Len+1);
}




bool get_bit(byte Byte, int pos = 0)
{
    byte mask = 0b10000000 >> pos;
    return Byte & mask;
}

byte set_bit(byte Byte, int pos, bool bit = true)
{
    byte mask = 0b10000000 >> pos;
    if (bit)
        return Byte | mask;
    else
        return Byte & (~mask);
}

int byte_size(int bit_size)
{
    if (bit_size == 0) return 0;
    return (bit_size - 1) / 8 + 1;
}

// кодировочная таблица

void plus(byte * bits)
{
    byte bit_len = bits[0];
    byte byte_len = byte_size(bit_len);
    byte incr = 0b10000000 >> ((bit_len-1)%8);
    if ((byte)(bits[byte_len] + incr) == 0)
    {
        bits[byte_len] = 0;
        for (int i = byte_len-1; i >= 1; i--)
        {
            if (bits[i] == 0b11111111)
            {
                bits[i] = 0;
            }
            else
            {
                bits[i]+= 1; break;
            }
        }
    }
    else {bits[byte_len] += incr;}
    
}

byte * extend(byte * bits, byte total_len)
{
    byte bit_len = bits[0];
    byte byte_len = byte_size(bit_len);
    byte new_byte_len = byte_size(total_len);
    byte * res = new byte[new_byte_len+1]();
    res[0] = total_len;
    for (int i = 1; i <= byte_len; i++) res[i] = bits[i];
    return res;
}

byte ** get_Ctable(byte* heap, byte * table)
{
    byte ** res = new byte*[size/2]();
    int hsize = get_size(heap);

    byte pre = del(heap, hsize-1, table);
    hsize--;
    byte prelen = table[pre];
    byte * precode= new byte[byte_size(prelen) + 1]();
    precode[0] = prelen;
    res[pre] = precode;

    while (hsize > 0)
    {
        byte sle = del(heap, hsize-1, table);
        hsize--;
        byte len = table[sle];
        byte * code = nullptr;
        code = extend(precode, prelen);
        plus(code);
        code = extend(code, len);

        res[sle] = code;
        pre = sle;
        prelen = len;
        precode = code;
    }
    return res;

}

void print(byte * code)
{
    if (code != nullptr)
    {
        for (int i = 1; i < byte_size(code[0]) + 1; i++) 
        {
            for (int j = 0; j < 8; j++)
            {
                if ((i-1)*8 + j >= code[0]) break;
                std::cout << get_bit(code[i], j);
            }
        }
    }
}

void print(byte ** table)
{
    for (int i = 0; i < size/2; i++)
    {
        std::cout << i << " : "; print(table[i]); std::cout << '\n';
    }
}

bool code_file(byte ** code_table, byte * Ltable, const char * input_name, const char * output_name = "compressed.huf")
{
    std::ifstream input(input_name, std::ios::binary);
    std::ofstream output(output_name, std::ios::binary);
    if (!input.is_open() || !output.is_open()) return false;
    
    byte N = count_nonzero(code_table);
    output << (char)N;

    for (int i = 0; i < size/2; i++)
    {
        if (Ltable[i] != 0)
        {
            output << (char)i << (char)Ltable[i];
        }
    }

    char in;
    char out;
    byte buffer = 0;
    int pos = 0;
    while (input.get(in)) {
        byte * code = code_table[(index)(unsigned char)in];
        int bit_length = code[0];
        for (int i = 0; i < bit_length; i++)
        {
            buffer = set_bit(buffer, pos, get_bit(code[byte_size(i) + 1], i%8));
            pos++;
            if (pos > 7)
            {
                output << (char)buffer;
                buffer = 0;
                pos = 0;
            }
        }
    }
    if (pos > 0) output << (char) buffer;
    input.close(); output.close();
    return true;
}


int coder(bool verbose = false, PrintMode mode = PrintMode::Full)
{
    std::cout <<"- - - C O M P R E S S O R - - -\n";
    std::cout <<"Enter the file name: ";
    char input[input_buffer] = {};
    std::cin.getline(input, 256);
    const char * fileName = input;
    
    big * Table = get_table(fileName);
    if (Table == nullptr)
    {
        std::cout << "Error: file is not opened\n";
        return 1;
    }
    big fileSize = Table[size/2];
    Table[size/2] = 0;
    big nonZero = count_nonzero(Table);
    std::cout <<"The file size is " << fileSize 
        << " byte(s).\nQuantity of the unique bytes is "
        << nonZero << '\n';

    if (verbose) print(Table, mode);

    Node ** Heap = get_heap(Table);
    if (Heap == nullptr)
    {
        std::cout << "Error: heap is not made\n";
        return 2;
    }
    if (verbose) print_heap(Heap, Table);

    Node * Tree = get_tree(Heap, Table);
    if (Tree == nullptr)
    {
        std::cout << "Error: tree is not made\n";
        return 3;
    }
    byte * Length = new byte[size]();
    set_len(Tree,Length);
    if (verbose) print(Tree, Table, Length);

    byte * Heap2 = get_heap(Length);
    if (Heap2 == nullptr)
    {
        std::cout << "Error: heap is not made\n";
        return 4;
    }
    if (verbose) print_heap(Heap2, Length);

    byte ** codeTable = get_Ctable(Heap2, Length);
    
    print(codeTable);

    code_file(codeTable, Length, fileName);

    erase_tree(Tree);
    delete[] Table;
    return 0;
}

int main()

{
    while(true)
    {
        coder(true, Nonzero);
        std::cout << "Enter 'e' to exit and any other symbol to restart: ";
        char c = std::cin.get();
        if (c == 'e') break;
    }

    return 0;
}