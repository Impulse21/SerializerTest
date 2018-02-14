#pragma once

#include "Structures.h"
#include <map>


struct SerializedNode
{
	unsigned int prevNodeIndex;
    unsigned int nextNodeIndex;  

    std::string name;

    uint8_t dataCount;
    Data *data;   
};

class Serializer 
{
public:
	/**
	 * This is the function that you get to implement!
	 */
    static uint8_t* serialize(const Node *node, uint32_t *outLength);

private:
	static void buildNodeMapping(const Node *node, std::map<const Node*, unsigned>& map, int& dataCount);
};
