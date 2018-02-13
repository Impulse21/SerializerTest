#pragma once

#include <vector>
#include <unordered_map>

#include "Structures.h"

class Serializer 
{
public:
	/**
	 * This is the function that you get to implement!
	 */
    static uint8_t* serialize(const Node *node, uint32_t *outLength);

private:
	static void serialize(std::vector<uint8_t>* buffer, uint32_t const& value);

	static void serialize(std::vector<uint8_t>* buffer, std::string const& value);

};
