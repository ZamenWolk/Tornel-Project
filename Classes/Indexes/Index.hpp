#ifndef CLASSES_INDEXES_INDEX_HPP
#define CLASSES_INDEXES_INDEX_HPP

#include <string>
#include <vector>

#include "../../global/functions.hpp"

template<class T>
class Index
{

public:

    Index(std::string identifier) :
            index(),
            identifier(identifier)
    {

    }

    T *searchByName(std::string searchName = "")
    {
        if (searchName == "")
        {
            return &index[0];
        }

        for (typename std::vector<T>::iterator it = index.begin(); it != index.end(); it++)
        {
            if (it->getName() == searchName)
            {
                return &*it;
            }
        }

        std::string errorMessage(searchName + " doesn't exist in the " + identifier + " index");

        errorReport(errorMessage);
        return &index[0];
    }

    bool doesEntryExist(std::string searchEntry)
    {
        for (typename std::vector<T>::iterator it = index.begin(); it != index.end(); it++)
        {
            if (it->getName() == searchEntry)
            {
                return true;
            }
        }

        return false;
    }

    virtual bool addEntry(T entryToAdd)
    {
        if (!doesEntryExist(entryToAdd.getName()))
        {
            index.push_back(entryToAdd);
        }

        return true;
    }

    std::string getIdentifier() const
    {
        return identifier;
    }

protected:

    std::vector<T>    index;
    const std::string identifier;
};

template<class T>
class EquipmentIndex : public Index<T>
{

public:

    EquipmentIndex(std::string identifier) :
            Index<T>(identifier),
            typeIndex()
    {

    }

    bool doesTypeExist(std::string searchType)
    {
        for (std::vector<std::string>::iterator it = typeIndex.begin(); it != typeIndex.end(); it++)
        {
            if (*it == searchType)
            {
                return true;
            }
        }

        return false;
    }

    bool addType(std::string typeToAdd)
    {
        if (!doesTypeExist(typeToAdd))
        {
            typeIndex.push_back(typeToAdd);
        }

        return true;
    }

    virtual bool addEntry(T entryToAdd)
    {
        if (!this->doesEntryExist(entryToAdd.getName()) && doesTypeExist(entryToAdd.getType()))
        {
            this->index.push_back(entryToAdd);
        }

        return true;
    }

protected:

    std::vector<std::string> typeIndex;
};

#endif