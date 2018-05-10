#pragma once
#include <vector>
#include <algorithm>

#include <iostream>

#include "Edge.h"

struct less_than_key
{
	inline bool operator() (const Edge& struct1, const Edge& struct2)
	{
		return (struct1.weight < struct2.weight);
	}
};