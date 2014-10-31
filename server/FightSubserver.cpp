#include <vector>

#include "FightSubserver.hpp"

bool findOpenSubserver(std::vector<FightSubserver*> &serverVector, FightSubserver **returnedSubserver)
{
    for (int i = 0; i < serverVector.size(); i++)
    {
        if(!(serverVector.operator[](i)->isFull()))
        {
            *returnedSubserver = serverVector.operator[](i);
            return true;
        }
    }

    return false;
}
