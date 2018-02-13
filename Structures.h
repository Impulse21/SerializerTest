#pragma once

#include <cstdint>
#include <string>

struct Data 
{
    uint32_t id;

    float x;    
    float y;
};

struct Node 
{
    Node();
    ~Node();

    Node *prev;         // Byte
    Node *next;         // Byte

    std::string name;   //

    uint8_t dataCount;  // Bytes
    Data *data;         // Bytes
};
