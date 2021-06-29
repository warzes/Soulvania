#pragma once

#include "Powerup.h"

class ObjectFactory;

class PowerupGenerator
{
public:
	PowerupGenerator(ObjectFactory& objectFactory);

	std::unique_ptr<Powerup> Generate();
	std::unique_ptr<Powerup> Generate(ObjectId powerupId);

private:
	ObjectFactory& objectFactory;

	std::string GetGroup(ObjectId powerupType);
	ObjectId GetRandomPowerupType(const std::string& rarity);
};