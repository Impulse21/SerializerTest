#include "Deserializer.h"

#include <vector>

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
		deserializeNodeData(buffer[i], n);     
        nodes.push_back(n);
    }

	// Rebuild the pointers
    for(uint32_t i = 0; i < dataLength; i++)
    {
        int nextIndex = buffer[i].nextNodeIndex;
		nodes[i]->next = (nextIndex != -1 ) ? nodes[nextIndex] : nullptr;

        int prevIndex = buffer[i].prevNodeIndex;
		nodes[i]->prev = (prevIndex != -1) ? nodes[prevIndex] : nullptr;
    }

    return nodes.data()[0];
}

void Deserializer::deserializeNodeData(SerializedNode const& serializedNode, Node* node)
{
	if (node == nullptr)
	{
		node = new Node();
	}

	node->name = serializedNode.name;
	node->dataCount = serializedNode.dataCount;

	if (node->dataCount > 0)
	{
		node->data = new Data[sizeof(Data) * node->dataCount];
		for (int j = 0; j < node->dataCount; j++)
		{
			node->data[j] = serializedNode.data[j];
		}
	}
}
