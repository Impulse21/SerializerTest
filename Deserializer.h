#pragma once

#include "Structures.h"


class Deserializer {
public:
	/**
	 * This is the function that you get to implement!
	 */
    static Node* deserialize(const uint8_t* data, uint32_t dataLength);

private:
	static void deserialize(const uint8_t* data, int& currentOffset, std::string& value);
    
	static void deserialize(const uint8_t* data, int& currentOffset, uint32_t& value);
};
