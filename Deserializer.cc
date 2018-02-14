#include "Deserializer.h"

#include "Serializer.h"
#include <string>
#include <vector>
#include <iostream>



Node* Deserializer::deserialize(const uint8_t* data, uint32_t dataLength) 
{
    if(data == nullptr)
    {
        return nullptr;
    }

    const SerializedNode* serializedNode = reinterpret_cast<const SerializedNode*>(data);

    std::vector<Node>* nodes = new std::vector<Node>();

    for(int i = 0; i < dataLength; i++)
    {
        Node n;
        n.name = serializedNode[i].name;
        n.dataCount = serializedNode[i].dataCount;
        
        if(n.dataCount > 0)
        {
            n.data = new Data[sizeof(Data) * n.dataCount];
            n.data = serializedNode[i].data;
        }
        
        nodes->push_back(n);
    }

    std::cout << nodes->size() << std::endl;
    for(int i = 0; i < dataLength; i++)
    {
        unsigned int nextIndex = serializedNode[i].nextNodeIndex;

        std::cout << nextIndex << std::endl;

        unsigned int prevIndex = serializedNode[i].prevNodeIndex;

        std::cout << prevIndex << std::endl;
    }

    return &nodes->data()[0];
}
