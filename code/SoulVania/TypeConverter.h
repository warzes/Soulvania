#pragma once

#include "ObjectId.h"
#include "TriggerType.h"
#include "Facing.h"
#include "MapSettings.h"

const auto string2EntityType = std::unordered_map<std::string, ObjectId>
{
	{ "StageArea", ObjectId::StageArea },
	{ "BossFightArea", ObjectId::BossFightArea },
	{ "WaterArea", ObjectId::WaterArea },
	{ "SpawnArea", ObjectId::SpawnArea },
	{ "SpawnPoint", ObjectId::SpawnPoint },
	{ "Player", ObjectId::Player },
	{ "Bat", ObjectId::Bat },
	{ "Cloud", ObjectId::Cloud },
	{ "Brazier", ObjectId::Brazier },
	{ "Candle", ObjectId::Candle },
	{ "BreakableBlock", ObjectId::BreakableBlock },
	{ "BreakableWall", ObjectId::BreakableWall },
	{ "Zombie", ObjectId::Zombie },
	{ "Panther", ObjectId::Panther },
	{ "Fishman", ObjectId::Fishman },
	{ "VampireBat", ObjectId::VampireBat },
	{ "GiantBat", ObjectId::GiantBat },
	{ "Axe", ObjectId::Axe },
	{ "Dagger", ObjectId::Dagger },
	{ "HolyWater", ObjectId::HolyWater },
	{ "Fireball", ObjectId::Fireball },
	{ "Whip", ObjectId::Whip },
	{ "BlueMoneyBag", ObjectId::BlueMoneyBag },
	{ "WhiteMoneyBag", ObjectId::WhiteMoneyBag },
	{ "RedMoneyBag", ObjectId::RedMoneyBag },
	{ "FlashingMoneyBag", ObjectId::FlashingMoneyBag },
	{ "AxeItem", ObjectId::AxeItem },
	{ "Cross", ObjectId::Cross },
	{ "DaggerItem", ObjectId::DaggerItem },
	{ "HolyWaterItem", ObjectId::HolyWaterItem },
	{ "LargeHeart", ObjectId::LargeHeart },
	{ "SmallHeart", ObjectId::SmallHeart },
	{ "InvisibleJar", ObjectId::InvisibleJar },
	{ "PorkChop", ObjectId::PorkChop },
	{ "Stopwatch", ObjectId::Stopwatch },
	{ "WhipPowerup", ObjectId::WhipPowerup },
	{ "DoubleShot", ObjectId::DoubleShot },
	{ "CrystalBall", ObjectId::CrystalBall },
	{ "Door", ObjectId::Door },
	{ "Castle", ObjectId::Castle },
	{ "BrickBlock", ObjectId::BrickBlock },
	{ "DirtBlock", ObjectId::DirtBlock },
};

const auto string2TriggerType = std::unordered_map<std::string, TriggerType>
{
	{ "StairUp", TriggerType::STAIR_UP },
	{ "StairDown", TriggerType::STAIR_DOWN },
	{ "NextMap", TriggerType::NEXT_MAP },
	{ "CastleEntrance", TriggerType::CASTLE_ENTRANCE },
	{ "MoneyBagTrigger", TriggerType::MONEY_BAG_EASTER_EGG },
};

const auto string2Direction = std::unordered_map<std::string, Direction>
{
	{ "Left", Direction::Left },
	{ "Top", Direction::Top },
	{ "Right", Direction::Right },
	{ "Bottom", Direction::Bottom },
	{ "None", Direction::None },
};

const auto string2Facing = std::unordered_map<std::string, Facing>
{
	{ "Left", Facing::Left },
	{ "Right", Facing::Right },
	{ "None", Facing::None },
};

const auto string2Map = std::unordered_map<std::string, Map>
{
	{ "Intro", Map::INTRO },
	{ "Courtyard", Map::COURTYARD },
	{ "GreatHall", Map::GREAT_HALL },
	{ "Underground", Map::UNDERGROUND },
	{ "Playground", Map::PLAYGROUND },
};