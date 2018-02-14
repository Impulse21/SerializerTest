#pragma once

#include "Structures.h"
#include <map>

class Serializer 
{
public:
	/**
	 * This is the function that you get to implement!
	 */
    static uint8_t* serialize(const Node *node, uint32_t *outLength);

private:
	/**
	 * This method is used to build Node mapping. It is used to replace the next and prev 
	 * node pointers to an index value.
	 *
	 * Params:
	 *		node: array list to iterate through
	 *		map: outputs node mapping that is build
	 *		cycleIndex: outputs the index at which the cycle starts
	 *		
	 * Note:
	 *		This method also is used return the index the key value at which the cycle starts 
	 */
	static void buildNodeMapping(const Node *node, std::map<const Node*, unsigned>& map, int& cycleIndex);

	/**
	 * This function is used to determine if we have reached the end of a linked list.
	 *
	 * Params:
	 *		currIndex: the current index we are working with. This is the value in the Mapping.
	 *		cycleIndex: the index of the node that the cycleStarts
	 *		passedCycleStart: the flag that is used to determine if we have passed the Cycle Start
	 */
	static bool isEndOfCycle(int currIndex, int cycleIndex, bool& passedCycleStart);

	/**
	 * This method serialized the node.
	 *
	 * Params:
	 *		node: node to serialize
	 *		mapping: node mapping for translating next and prev Node pointers to indices.
	 *		serializedNode: ouputs a serailized node
	 */
	static void serializeNodeData(const Node* node, std::map<const Node*, unsigned>& mapping, SerializedNode& serializedNode);
};
