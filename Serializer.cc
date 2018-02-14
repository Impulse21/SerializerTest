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
    int dataCount = 0;
    buildNodeMapping(node, nodeMap, dataCount);

    int count = nodeMap.size();

    //uint8_t* data = new uint8_t[sizeof(SerNode) * node count + sizeof(uint32_t)];
    uint8_t* data = new uint8_t[(sizeof(Node) * count) + (sizeof(Data) * dataCount)];

    SerializedNode* serializedNode = reinterpret_cast<SerializedNode*>(data);

    for(int i = 0; i < count; i++)
    {
        serializedNode[i].name = node[i].name;
        serializedNode[i].dataCount = node[i].dataCount;
        serializedNode[i].data = node[i].data;

        serializedNode[i].nextNodeIndex = nodeMap[node[i].next];
        serializedNode[i].prevNodeIndex = nodeMap[node[i].prev];

    }

    *outLength = count;
    return data;
}

void Serializer::buildNodeMapping(const Node *node, std::map<const Node*, unsigned>& nodeMap, int& dataCount)
{
    while(node)
    {
        dataCount += node->dataCount;
        unsigned n = nodeMap.size();
        auto ret = nodeMap.insert( std::pair<const Node*, unsigned>(node, n));
        
        // Stop if inserted object already exists
        if(ret.second == false)
        {
            break;
        }

        node = node->next;
    }
}

