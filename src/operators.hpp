#ifndef OPERATORS_HPP_INCLUDED
#define OPERATORS_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <typeinfo>

#include "constants.hpp"
#include "../enums.hpp"

class CombatEntity;

struct Skill;
struct CombatEffects;
struct EntityInformations;
struct VersionNumber;
struct InteractionInfos;
struct FightAction;

/**
* \file operators.hpp
* \brief Contains all the operators of the program
*/

/**
* \addtogroup both
* @{
*/

/**
* \brief Completion of the packet with a Skill
* \param[out] packet Packet to complete
* \param[in] source Skill to flux into the packet
* \return Updated packet
*/

sf::Packet &operator<<(sf::Packet &packet, const std::vector<Skill *> &source);

/**
* \brief Extraction from a packet to an ActionType
* \param[in] packet Packet to extract from
* \param[out] action ActionType to get from the packet
* \return Updated packet
*/

sf::Packet &operator>>(sf::Packet &packet, ActionType &action);

/**
* \brief Extraction from a packet to a SpecialAttribute
* \param[in] packet Packet to extract from
* \param[out] attribute SpecialAttribute to get from the packet
* \return Updated packet
*/

sf::Packet &operator>>(sf::Packet &packet, SpecialAttribute &attribute);

/**
* \brief Extraction from a packet to an AttackType
* \param[in] packet Packet to extract from
* \param[out] attackType AttackType to get from the packet
* \return Updated packet
*/

sf::Packet &operator>>(sf::Packet &packet, AttackType &attackType);

/**
* \brief Completion of the packet with a CombatEffect
* \param[out] packet Packet to complete
* \param[in] source CombatEffect to flux into the packet
* \return Updated packet
*/

sf::Packet &operator<<(sf::Packet &packet, const CombatEffects &source);

/**  \brief Extraction from a packet to an EntityInformations
* \param[in] packet Packet to extract from
* \param[out] source CombatEffects to get from the packet
* \return Updated packet
*/

sf::Packet &operator>>(sf::Packet &packet, CombatEffects &source);

/**
* \brief Extraction from a packet to an EntityInformations
* \param[in] packet Packet to extract from
* \param[out] entity EntityInformations to get from the packet
* \return Updated packet
*/

sf::Packet &operator>>(sf::Packet &packet, EntityInformations &entity);

/**
* \brief Extraction from a packet to a vector of EntityInformations
* \param[in] packet Packet to extract from
* \param[out] teamVector vector to get from the Packet
* \return Updated packet
*/

sf::Packet &operator>>(sf::Packet &packet, std::vector<EntityInformations> &teamVector);

/**
* \brief Completion of the packet with a CombatEntity
* \param[out] packet Packet to complete
* \param[in] entity CombatEntity to flux into the packet
* \return Updated packet
*/

sf::Packet &operator<<(sf::Packet &packet, const CombatEntity &entity);

sf::Packet &operator<<(sf::Packet &packet, const EntityInformations &entity);

/**
* \brief Completion of the packet with an InteractionInfos
* \param[out] packet Packet to complete
* \param[in] infos InteractionInfos to flux into the packet
* \return Updated packet
*/

sf::Packet &operator<<(sf::Packet &packet, const InteractionInfos &infos);

/**
* \brief Extraction from a packet to an InteractionInfos
* \param[in] packet Packet to extract from
* \param[out] infos InteractionInfos to get from the packet
* \return Updated packet
*/

sf::Packet &operator>>(sf::Packet &packet, InteractionInfos &infos);

/**
* \brief Extraction from a packet to a SentInfosType
* \param[in] packet Packet to extract from
* \param[out] infosType SentInfosType to get from the packet
* \return Updated packet
*/

sf::Packet &operator>>(sf::Packet &packet, SentInfosType &infosType);

/**
* \brief Completion of the packet with a VersionNumber
* \param[out] packet Packet to complete
* \param[in] version version to flux into the packet
* \return Updated packet
*/

sf::Packet &operator<<(sf::Packet &packet, const VersionNumber &version);

/**
* \brief Extraction from a packet to a VersionNumber
* \param[in] packet Packet to extract from
* \param[out] version VersionNumber to get from the packet
* \return Updated packet
*/

sf::Packet &operator>>(sf::Packet &packet, VersionNumber &version);

/**
* \brief Completion of the packet with a CombatEntity vector
* \param[out] packet Packet to complete
* \param[in] team CombatEntity vector to flux into the packet
* \return Updated packet
*/

sf::Packet &operator<<(sf::Packet &packet, const std::vector<CombatEntity> &team);

sf::Packet &operator<<(sf::Packet &packet, const std::vector<EntityInformations> &team);

/**
* \brief Extraction from a packet to a CombatEntity vector
* \param[in] packet Packet to extract from
* \param[out] team CombatEntity vector to get from the packet
* \return Updated packet
* \todo Change the system of dynamic allocation
*/

sf::Packet &operator>>(sf::Packet &packet, std::vector<CombatEntity> &team);

/**
* \brief Completion of the packet with a Time
* \param[out] packet Packet to complete
* \param[in] time Time to flux into the packet
* \return Updated packet
*/

sf::Packet &operator<<(sf::Packet &packet, const sf::Time &time);

/**
* \brief Extraction from a packet to a Time
* \param[in] packet Packet to extract from
* \param[out] time Time to get from the packet
* \return Updated packet
*/

sf::Packet &operator>>(sf::Packet &packet, sf::Time &time);

sf::Packet &operator<<(sf::Packet &packet, const tm &time);

sf::Packet &operator>>(sf::Packet &packet, tm &time);

sf::Packet &operator<<(sf::Packet &packet, const FightAction &action);

sf::Packet &operator>>(sf::Packet &packet, FightAction &action);

/// @}

#endif // OPERATORS_HPP_INCLUDED
