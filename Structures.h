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

/** 
 * Seralized Node
 * This struct is used to store a serialized version of the node above.
 */
struct SerializedNode
{
int prevNodeIndex;
int nextNodeIndex;

std::string name;

uint8_t dataCount;
Data *data;
};
