#pragma once

#include "Player.h"
#include "Zombie.h"
#include "Panther.h"
#include "Fishman.h"
#include "VampireBat.h"
#include "GiantBat.h"
#include "BreakableWall.h"
#include "HolyWater.h"
#include "MoneyBag.h"
#include "SpawnArea.h"
#include "SpawnPoint.h"
#include "WaterArea.h"
#include "EffectFactory.h"

constexpr auto ITEM_FALL_SPEED = 150.0f;

class ObjectFactory
{
public:
	ObjectFactory(ContentManager& content);

	std::unique_ptr<GameObject> CreateRectangleObject(ObjectId type, RectF rect);
	std::unique_ptr<GameObject> CreateBlock(RectF rect);
	std::unique_ptr<WaterArea> CreateWaterArea(RectF rect);
	std::unique_ptr<SpawnPoint> CreateSpawnPoint(ObjectId type, RectF rect);
	std::unique_ptr<SpawnArea> CreateSpawnArea(ObjectId type, RectF rect);
	std::unique_ptr<Trigger> CreateTrigger(RectF rect, TriggerType triggerType);

	std::unique_ptr<GameObject> CreateBat(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<GameObject> CreateCloud(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Player> CreatePlayer(base::Vector2 position = base::Vector2::Zero());

	std::unique_ptr<Container> CreateBrazier(ObjectId itemType, base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Container> CreateCandle(ObjectId itemType, base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Container> CreateBreakableBlock(ObjectId itemType, std::string spritePath = "", base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<BreakableWall> CreateBreakableWall(ObjectId itemType, base::Vector2 position = base::Vector2::Zero());

	std::unique_ptr<Enemy> CreateEnemy(ObjectId type, base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Zombie> CreateZombie(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Panther> CreatePanther(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Fishman> CreateFishman(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<VampireBat> CreateVampireBat(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<GiantBat> CreateGiantBat(base::Vector2 position = base::Vector2::Zero());

	std::unique_ptr<Whip> CreateWhip(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Whip> CreateFlashingWhip(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<RangedWeapon> CreateSubWeapon(ObjectId type, base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<RangedWeapon> CreateAxe(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<RangedWeapon> CreateDagger(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<HolyWater> CreateHolyWater(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<RangedWeapon> CreateFireball(base::Vector2 position = base::Vector2::Zero());

	std::unique_ptr<Powerup> CreatePowerup(ObjectId type, base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<MoneyBag> CreateMoneyBag(ObjectId type, base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<MoneyBag> CreateBlueMoneyBag(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<MoneyBag> CreateWhiteMoneyBag(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<MoneyBag> CreateRedMoneyBag(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<MoneyBag> CreateFlashingMoneyBag(base::Vector2 position = base::Vector2::Zero());

	std::unique_ptr<Powerup> CreateAxeItem(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Powerup> CreateCross(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Powerup> CreateDaggerItem(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Powerup> CreateHolyWaterItem(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Powerup> CreateLargeHeart(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Powerup> CreateSmallHeart(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Powerup> CreateInvisibleJar(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Powerup> CreatePorkChop(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Powerup> CreateStopwatch(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Powerup> CreateWhipPowerup(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Powerup> CreateDoubleShot(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<Powerup> CreateCrystalBall(base::Vector2 position = base::Vector2::Zero());

	std::unique_ptr<Door> CreateDoor(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<GameObject> CreateCastle(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<GameObject> CreateBrickBlock(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<GameObject> CreateDirtBlock(base::Vector2 position = base::Vector2::Zero());
	std::unique_ptr<GameObject> CreateWaterZone(base::Vector2 position = base::Vector2::Zero());

private:
	ContentManager& content;
	std::unique_ptr<EffectFactory> effectFactory;

	void ReadEnemyConfig(Enemy& enemy, Dictionary stats);
	void ReadSubWeaponConfig(RangedWeapon& weapon, Dictionary stats);
	void ReadSpawnAreaConfig(SpawnArea& spawnArea, Dictionary stats);

	std::unique_ptr<SpawnArea> ConstructSpawnArea(ObjectId type);
};