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

    const SerializedNode* buffer = reinterpret_cast<const SerializedNode*>(data);

    std::vector<Node*> nodes;

    for(uint32_t i = 0; i < dataLength; i++)
    {
		Node* n = new Node();
        n->name = buffer[i].name;
        n->dataCount = buffer[i].dataCount;
        
        if(n->dataCount > 0)
        {
            n->data = new Data[sizeof(Data) * n->dataCount];
			for (int j = 0; j < n->dataCount; j++)
			{
				n->data[j] = buffer[i].data[j];
			}
        }
        
        nodes.push_back(n);
    }

    for(uint32_t i = 0; i < dataLength; i++)
    {
        int nextIndex = buffer[i].nextNodeIndex;

		nodes[i]->next = (nextIndex != -1 ) ? nodes[nextIndex] : nullptr;

        int prevIndex = buffer[i].prevNodeIndex;

		nodes[i]->prev = (prevIndex != -1) ? nodes[prevIndex] : nullptr;
    }

    return nodes.data()[0];
}
