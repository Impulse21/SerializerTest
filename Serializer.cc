#include "Serializer.h"

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
	bool passedCycleStart = false;

	const Node* currNode = node;
	while (currNode)
	{
		SerializedNode serializedNode;
		serializeNodeData(currNode, nodeMap, serializedNode);

		buffer->push_back(serializedNode);

		if (isEndOfCycle(static_cast<int>(nodeMap[currNode]), cycleIndex, passedCycleStart))
		{
			break;
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

bool Serializer::isEndOfCycle(int currIndex, int cycleIndex, bool& passedCycleStart)
{
	bool isEndOfLast = false;

	if (currIndex == cycleIndex)
	{
		if (passedCycleStart)
		{
			isEndOfLast = true;
		}

		passedCycleStart = true;
	}

	return isEndOfLast;
}

void Serializer::serializeNodeData(const Node * node, std::map<const Node*, unsigned>& mapping, SerializedNode & serializedNode)
{
	serializedNode.name = node->name;
	serializedNode.dataCount = node->dataCount;

	if (serializedNode.dataCount > 0)
	{
		serializedNode.data = new Data[serializedNode.dataCount * sizeof(Data)];
		for (int j = 0; j < serializedNode.dataCount; j++)
		{
			serializedNode.data[j] = node->data[j];
		}
	}

	serializedNode.nextNodeIndex = (node->next) ? mapping[node->next] : -1;
	serializedNode.prevNodeIndex = (node->prev) ? mapping[node->prev] : -1;
}
