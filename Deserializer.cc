#include "Deserializer.h"

#include <string>
#include <vector>
#include <iostream>


Node* Deserializer::deserialize(const uint8_t* data, uint32_t dataLength) 
{
    if(data == nullptr)
    {
        return nullptr;
    }

    int currentOffset = 0;
    std::vector<Node>* nodes = new std::vector<Node>();
    Node n;

    deserialize(data, currentOffset, n.name);
    n.dataCount = data[currentOffset];
    currentOffset++;
    
    
    //-------- Deserailize data nodes
    if(n.dataCount > 0)
    {
        // This has to be dynamically allocated because of the node destructor.
        n.data = static_cast<Data *>(malloc(sizeof(Data) * 2));
        
    }
    
    for(int i = 0; i < n.dataCount; i++)
    {
        Data* d = &n.data[i];
        deserialize(data, currentOffset, d->id);
        
        uint32_t v = 0;
        deserialize(data, currentOffset, v);
        d->x = static_cast<float>(v);
        
        deserialize(data, currentOffset, v);
        d->y = static_cast<float>(v);
    }
    //-------- End Data nodes
    
    nodes->push_back(n);

    std::cout << n.name << std::endl;

    return nodes->data();
}

void Deserializer::deserialize(const uint8_t* data, int& currentOffset, std::string& value)
{
    while(data[currentOffset] != '\0')
    {
        value += data[currentOffset];
        currentOffset++;
    }
    
    currentOffset +=1;
}

void Deserializer::deserialize(const uint8_t* data, int& currentOffset, uint32_t& value)
{
    uint32_t value1 = data[currentOffset + 0];
    uint32_t value2 = data[currentOffset + 1];
    uint32_t value3 = data[currentOffset + 2];
    uint32_t value4 = data[currentOffset + 3];
    value = (value1 << 24 | value2 << 16 | value3 << 8 | value4);
    currentOffset += 4;
}
