#include "Serializer.h"
#include <iostream>
#include <map>
#include <vector>

/** 
 * Data layout:
 *      | name field | '\0' | dataCount | id (8-bits) | id (8-bits) | id (8-bits) | id (8-bits)
 */
uint8_t* Serializer::serialize(const Node *node, uint32_t *outLength) 
{
    if(node == nullptr)
    {
        return nullptr;
    }

    std::vector<uint8_t>* buffer = new std::vector<uint8_t>();

    serialize(buffer, node->name);
    
    //------ Serialize Nodes
    buffer->push_back(node->dataCount);

    for(int i = 0; i < node->dataCount; i++)
    {
        Data d = node->data[i];

        serialize(buffer, d.id);
        serialize(buffer, d.x);
        serialize(buffer, d.y);
    }
    //------ End nodes
    
    buffer->shrink_to_fit();
    *outLength = static_cast<uint32_t>(buffer->size());
    return reinterpret_cast<uint8_t*>(buffer->data());
}

void Serializer::serialize(std::vector<uint8_t>* buffer, uint32_t const& value)
{
    buffer->push_back((value >> 24 & 0xFF));
    buffer->push_back((value >> 16 & 0xFF));
    buffer->push_back((value >> 8 & 0xFF));
    buffer->push_back((value & 0xFF));
}

void Serializer::serialize(std::vector<uint8_t>* buffer, std::string const& value)
{
    buffer->insert(buffer->end(), value.begin(), value.end());
    // Add null terminating character
    buffer->push_back('\0');
}
