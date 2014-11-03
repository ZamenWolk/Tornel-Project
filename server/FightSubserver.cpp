#include <vector>

#include "FightSubserver.hpp"

bool findOpenSubserver(std::vector<FightSubserver *> &serverVector, FightSubserver **returnedSubserver)
{
	for (unsigned int i = 0; i < serverVector.size(); i++)
	{
		if (!(serverVector.operator[](i)->isFull()))
		{
			*returnedSubserver = serverVector[i];
			return true;
		}
	}

	return false;
}
