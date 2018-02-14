#pragma once

#include "Structures.h"


class Deserializer {
public:
	/**
	 * This is the function that you get to implement!
	 */
    static Node* deserialize(const uint8_t* data, uint32_t dataLength);

private:
	/**
	* This method deserialize the serial node.
	*
	* Note:
	*	This method will not set up the linked list pointers
	*
	* Params:
	*		serializedNode: node to deserialize
	*		node: deserialized node
	*		
	*/
	static void deserializeNodeData(SerializedNode const& serializedNode, Node* node);
};
