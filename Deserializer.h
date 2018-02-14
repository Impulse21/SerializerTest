#pragma once

#include "Structures.h"


class Deserializer {
public:
	/**
	 * This is the function that you get to implement!
	 */
    static Node* deserialize(const uint8_t* data, uint32_t dataLength);
};
