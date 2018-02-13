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

    std::map<const Node*, unsigned> nodeMap;
    buildNodeMapping(node, nodeMap);

    outLength = (uint32_t*) nodeMap.size();

    //uint8_t* data = new uint8_t[sizeof(SerNode) * node count + sizeof(uint32_t)];
    uint8_t* data = new uint8_t[sizeof(Node) * (*outLength)];

    while(node)
    {
        Node serNode = *node;
        
        serNode.next = reinterpret_cast<Node*>(nodeMap[node->next]);
        serNode.prev = reinterpret_cast<Node*>(nodeMap[node->prev]);

        // Error
        //data[0] = reinterpret_cast<uint8_t*>(&serNode);
        node = node->next;
    }

    //MyStruct* wholeStruct = static_cast<MyStruct*>(data);

    return data;
}

void Serializer::buildNodeMapping(const Node *node, std::map<const Node*, unsigned>& nodeMap)
{
    while(node)
    {
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

