#ifndef INDEX_HPP_INCLUDED
#define INDEX_HPP_INCLUDED

#include <string>
#include <SFML/Window.hpp>
#include <vector>
#include <Thor/Input.hpp>

#include "Skill.hpp"
#include "Equipment.hpp"
#include "mathfuncs.hpp"
#include "IndexClasses.hpp"

/**
* \file Index.hpp
* \brief Contains all the classes and structures to form indexes
*/

/**
* \addtogroup both
* @{
*/

/**
* \brief Contains the characteristics of a certain kind of thing in the game
*/

template<class T>
class Index
{

public:

	/// \param[in] identifier Name of the index for use in the error reports
	Index(std::string identifier) :
			index(),
			identifier(identifier)
	{

	}

	/**
	* 	\brief Checks if the name searched for exists in the index
	* 	\param[in] searchName Name to check
	* 	\return true if the name exists
	*/

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

	/**
	* \param[in] searchEntry name of the name to search for
	* \return true if the entry given exists in the index
	*/

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

	/**
	* 	\brief Add an entry into the index
	* 	\param[in] entryToAdd Entry to add to the index
	* \return True if the entry is in the index after the function
	*/

	virtual bool addEntry(T entryToAdd)
	{
		if (!doesEntryExist(entryToAdd.getName()))
		{
			index.push_back(entryToAdd);
		}

		return true;
	}

	/// \return Identifier of the index
	std::string getIdentifier() const
	{
		return identifier;
	}

protected:

	std::vector<T>    index; ///< Index of all the entries
	const std::string identifier; ///< Name of the index
};

/**
* \brief Index class with more functions, most notably handling types (i.e. for weapons)
*/

template<class T>
class EquipmentIndex : public Index<T>
{

public:

	/// \param[in] identifier Name of the index for use in the error reports
	EquipmentIndex(std::string identifier) :
			Index<T>(identifier),
			typeIndex()
	{

	}

	/**
	* \param[in] searchType name of the type to search for
	* \return true if the type given exists in the index
	*/

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

	/**
	* \brief Adds the type given in argument to the index
	* \param[in] typeToAdd type to add to the index
	* \return true if type exists in the index after the function
	*/

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

	std::vector<std::string> typeIndex; ///< Index of all the types of entries
};

/// @}

#endif // INDEX_HPP_INCLUDED
