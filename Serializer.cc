#include "Serializer.h"
#include <iostream>
#include <map>
#include <vector>


uint8_t* Serializer::serialize(const Node *node, uint32_t *outLength) 
{
    if(node == nullptr)
    {
        return nullptr;
    }

    std::map<const Node*, unsigned> nodeMap;
	int cycleIndex;
    buildNodeMapping(node, nodeMap, cycleIndex);

	std::vector<SerializedNode>* buffer = new std::vector<SerializedNode>();

	const Node* currNode = node;
	bool passedCycleStart = false;
	while (node)
	{
		SerializedNode serializedNode;
		serializedNode.name = currNode->name;
		serializedNode.dataCount = currNode->dataCount;

		if (serializedNode.dataCount > 0)
		{
			serializedNode.data = new Data[serializedNode.dataCount * sizeof(Data)];
			for (int j = 0; j < serializedNode.dataCount; j++)
			{
				serializedNode.data[j] = currNode->data[j];
			}
		}

		serializedNode.nextNodeIndex = (currNode->next) ? nodeMap[currNode->next] : -1;
		serializedNode.prevNodeIndex = (currNode->prev) ? nodeMap[currNode->prev] : -1;

		buffer->push_back(serializedNode);

		if (currNode->next == nullptr)
		{
			break;
		}
		else if (static_cast<int>(nodeMap[currNode]) == cycleIndex)
		{
			if (passedCycleStart)
			{
				break;
			}

			passedCycleStart = true;
		}

		currNode = currNode->next;
	}

    *outLength = nodeMap.size();
    return reinterpret_cast<uint8_t*>(buffer->data());
}

void Serializer::buildNodeMapping(const Node *node, std::map<const Node*, unsigned>& nodeMap, int& cycleIndex)
{
	const Node* currNode = node;
	cycleIndex = -1;

    while(currNode)
    {
        unsigned n = nodeMap.size();
        auto ret = nodeMap.insert( std::pair<const Node*, unsigned>(currNode, n));
        
        // Stop if inserted object already exists
        if(ret.second == false)
        {
			cycleIndex = nodeMap[currNode];
            break;
        }

		if (currNode->next == nullptr)
		{
			break;
		}

		currNode = currNode->next;
    }
}

