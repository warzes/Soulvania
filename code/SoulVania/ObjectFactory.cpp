#include "stdafx.h"
#include "ObjectFactory.h"
#include "CppExtensions.h"
#include "TypeConverter.h"
#include "Audios.h"
#include "SimpleMovementSystem.h"
#include "EntityMovementSystem.h"
#include "WaveMovementSystem.h"
#include "CollisionSystem.h"
#include "SimpleCollisionSystem.h"
#include "StandardCollisionSystem.h"
#include "GroundResponseSystem.h"
#include "AnimationRenderingSystem.h"
#include "BoundingboxRenderingSystem.h"
#include "ItemRenderingSystem.h"
#include "SpriteRenderingSystem.h"
#include "EntityRenderingSystem.h"
#include "WaterAreaRenderingSystem.h"
#include "Controller.h"
#include "PlayerMovementSystem.h"
#include "PlayerCollisionSystem.h"
#include "PlayerResponseSystem.h"
#include "PlayerRenderingSystem.h"
#include "FishmanControlSystem.h"
#include "FishmanResponseSystem.h"
#include "FishmanRenderingSystem.h"
#include "GiantBatControlSystem.h"
#include "GiantBatMovementSystem.h"
#include "GiantBatCollisionSystem.h"
#include "GiantBatResponseSystem.h"
#include "GiantBatRenderingSystem.h"
#include "PantherControlSystem.h"
#include "PantherCollisionSystem.h"
#include "PantherResponseSystem.h"
#include "PantherRenderingSystem.h"
#include "VampireBatRenderingSystem.h"
#include "ZombieResponseSystem.h"
#include "PowerupResponseSystem.h"
#include "DoorRenderingSystem.h"
#include "AreaCollisionSystem.h"
#include "SpawnAreaResponseSystem.h"
#include "HolyWaterResponseSystem.h"
#include "HolyWaterRenderingSystem.h"
#include "WhipRenderingSystem.h"
#include "WhipFlashingRenderingSystem.h"
#include "WeaponCollisionSystem.h"
#include "WeaponResponseSystem.h"
#include "ZombieSpawnArea.h"
#include "VampireBatSpawnArea.h"
#include "FishmanSpawnArea.h"

constexpr auto POWERUP_WEIGHT = 1000.0f;

ObjectFactory::ObjectFactory(ContentManager& content) : content{ content }
{
	effectFactory = std::make_unique<EffectFactory>(content);
	RenderingSystem::LoadContent(content);
}

std::unique_ptr<GameObject> ObjectFactory::CreateRectangleObject(ObjectId type, RectF rect)
{
	auto object = std::make_unique<GameObject>(type);
	auto renderingSystem = std::make_unique<BoundingBoxRenderingSystem>(*object, rect);

	object->SetPosition(base::Vector2{ rect.left, rect.top });
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateBlock(RectF rect)
{
	return CreateRectangleObject(ObjectId::Block, rect);
}

std::unique_ptr<WaterArea> ObjectFactory::CreateWaterArea(RectF rect)
{
	auto object = std::make_unique<WaterArea>();
	auto renderingSystem = std::make_unique<WaterAreaRenderingSystem>(*object, rect, *effectFactory);

	object->SetPosition(base::Vector2{ rect.left, rect.top });
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<SpawnPoint> ObjectFactory::CreateSpawnPoint(ObjectId type, RectF rect)
{
	auto object = std::make_unique<SpawnPoint>(type, *this);
	auto renderingSystem = std::make_unique<BoundingBoxRenderingSystem>(*object, rect);

	object->SetPosition(base::Vector2{ rect.left, rect.top });
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<SpawnArea> ObjectFactory::CreateSpawnArea(ObjectId type, RectF rect)
{
	auto object = ConstructSpawnArea(type);
	auto collisionSystem = std::make_unique<AreaCollisionSystem>(*object);
	auto responseSystem = std::make_unique<SpawnAreaResponseSystem>(*object);
	auto renderingSystem = std::make_unique<BoundingBoxRenderingSystem>(*object, rect);

	object->SetPosition(base::Vector2{ rect.left, rect.top });
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<Trigger> ObjectFactory::CreateTrigger(RectF rect, TriggerType triggerType)
{
	auto object = std::make_unique<Trigger>(triggerType);
	auto renderingSystem = std::make_unique<BoundingBoxRenderingSystem>(*object, rect);

	object->SetPosition(base::Vector2{ rect.left, rect.top });
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateBat(base::Vector2 position)
{
	auto object = std::make_unique<GameObject>(ObjectId::Bat);
	auto movementSystem = std::make_unique<SimpleMovementSystem>(*object);
	auto renderingSystem = std::make_unique<AnimationRenderingSystem>(*object, "Characters/NPCs/Bat.ani.xml");

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateCloud(base::Vector2 position)
{
	auto object = std::make_unique<GameObject>(ObjectId::Cloud);
	auto movementSystem = std::make_unique<SimpleMovementSystem>(*object);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "Misc/Cloud.png");

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<Player> ObjectFactory::CreatePlayer(base::Vector2 position)
{
	auto object = std::make_unique<Player>();
	auto stats = content.Load<Dictionary>("GameStats/Characters/Simon.xml");

	object->SetSpeed(std::stof(stats->at("Speed")));
	object->SetJumpSpeed(std::stof(stats->at("JumpSpeed")));

	auto controller = std::make_unique<Controller>(*object, *this);
	auto movementSystem = std::make_unique<PlayerMovementSystem>(*object);
	auto collisionSystem = std::make_unique<PlayerCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PlayerResponseSystem>(*object, *this);
	auto renderingSystem = std::make_unique<PlayerRenderingSystem>(*object, "Characters/Players/Simon.ani.xml");

	object->SetPosition(position);
	object->Attach(std::move(controller));
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->SetWhip(CreateWhip());
	object->LoadContent(content);

	return object;
}

std::unique_ptr<Container> ObjectFactory::CreateBrazier(ObjectId itemType, base::Vector2 position)
{
	auto object = std::make_unique<Container>(ObjectId::Brazier, std::make_unique<PowerupGenerator>(*this));

	auto renderingSystem = std::make_unique<EntityRenderingSystem>(*object, "Items/Brazier.ani.xml",
		effectFactory->CreateFlameEffect(),
		effectFactory->CreateSparkEffect());

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->SetSpawnedItem(itemType);
	object->LoadContent(content);

	return object;
}

std::unique_ptr<Container> ObjectFactory::CreateCandle(ObjectId itemType, base::Vector2 position)
{
	auto object = std::make_unique<Container>(ObjectId::Candle, std::make_unique<PowerupGenerator>(*this));
	auto renderingSystem = std::make_unique<EntityRenderingSystem>(*object, "Items/Candle.ani.xml",
		effectFactory->CreateFlameEffect(),
		effectFactory->CreateSparkEffect());

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->SetSpawnedItem(itemType);
	object->LoadContent(content);

	return object;
}

std::unique_ptr<Container> ObjectFactory::CreateBreakableBlock(ObjectId itemType, std::string spritePath, base::Vector2 position)
{
	auto object = std::make_unique<Container>(ObjectId::BreakableBlock, std::make_unique<PowerupGenerator>(*this));

	if (spritePath.empty())
		spritePath = "TiledMaps/Stage_01/Block.png";

	auto renderingSystem = std::make_unique<ItemRenderingSystem>(*object, spritePath,
		effectFactory->CreateDebrisEffect(), nullptr);

	object->SetSpawnedItem(itemType);
	object->SetPosition(position);
	object->SetSpawningState(ObjectState::DYING); // spawn item immediately after being hit
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<BreakableWall> ObjectFactory::CreateBreakableWall(ObjectId itemType, base::Vector2 position)
{
	auto object = std::make_unique<BreakableWall>();
	auto topBlock = CreateBreakableBlock(ObjectId::Unknown, "TiledMaps/Stage_01/Block_01.png");
	auto bottomBlock = CreateBreakableBlock(itemType, "TiledMaps/Stage_01/Block_02.png");

	object->SetTopBlock(std::move(topBlock));
	object->SetBottomBlock(std::move(bottomBlock));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<Enemy> ObjectFactory::CreateEnemy(ObjectId type, base::Vector2 position)
{
	switch (type)
	{
	case ObjectId::Zombie:
		return CreateZombie();

	case ObjectId::Panther:
		return CreatePanther();

	case ObjectId::Fishman:
		return CreateFishman();

	case ObjectId::VampireBat:
		return CreateVampireBat();

	case ObjectId::GiantBat:
		return CreateGiantBat();

	default:
		throw std::runtime_error("Object type not supported");
	}
}

std::unique_ptr<Zombie> ObjectFactory::CreateZombie(base::Vector2 position)
{
	auto object = std::make_unique<Zombie>();
	auto stats = content.Load<Dictionary>("GameStats/Characters/Zombie.xml");

	ReadEnemyConfig(*object.get(), *stats);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, 1000.0f);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<ZombieResponseSystem>(*object);
	auto renderingSystem = std::make_unique<EntityRenderingSystem>(*object, "Characters/Enemies/Zombie.ani.xml",
		effectFactory->CreateFlameEffect(),
		effectFactory->CreateSparkEffect());

	object->SetPosition(position);
	object->SetPowerupGenerator(std::make_unique<PowerupGenerator>(*this));
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Panther> ObjectFactory::CreatePanther(base::Vector2 position)
{
	auto object = std::make_unique<Panther>();
	auto stats = content.Load<Dictionary>("GameStats/Characters/Panther.xml");

	ReadEnemyConfig(*object.get(), *stats);

	auto zoneWidth = std::stoi(stats->at("ActiveZoneWidth"));
	auto zoneHeight = std::stoi(stats->at("ActiveZoneHeight"));
	object->SetActiveZone(Rect{ 0, 0, zoneWidth, zoneHeight });
	object->SetJumpSpeed(std::stof(stats->at("JumpSpeed")));

	auto controlSystem = std::make_unique<PantherControlSystem>(*object);
	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, 1000.0f);
	auto collisionSystem = std::make_unique<PantherCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PantherResponseSystem>(*object);
	auto renderingSystem = std::make_unique<PantherRenderingSystem>(
		*object, "Characters/Enemies/Panther.ani.xml",
		effectFactory->CreateFlameEffect(),
		effectFactory->CreateSparkEffect());

	object->SetPosition(position);
	object->SetPowerupGenerator(std::make_unique<PowerupGenerator>(*this));
	object->Attach(std::move(controlSystem));
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Fishman> ObjectFactory::CreateFishman(base::Vector2 position)
{
	auto object = std::make_unique<Fishman>();
	auto stats = content.Load<Dictionary>("GameStats/Characters/Fishman.xml");

	ReadEnemyConfig(*object.get(), *stats);
	object->SetLaunchSpeed(std::stof(stats->at("LaunchSpeed")));

	auto controlSystem = std::make_unique<FishmanControlSystem>(*object, *this);
	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, 1000.0f);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<FishmanResponseSystem>(*object);
	auto renderingSystem = std::make_unique<FishmanRenderingSystem>(
		*object, "Characters/Enemies/Fishman.ani.xml",
		effectFactory->CreateWaterEffect(),
		effectFactory->CreateFlameEffect(),
		effectFactory->CreateSparkEffect());

	object->SetPosition(position);
	object->SetPowerupGenerator(std::make_unique<PowerupGenerator>(*this));
	object->Attach(std::move(controlSystem));
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<VampireBat> ObjectFactory::CreateVampireBat(base::Vector2 position)
{
	auto object = std::make_unique<VampireBat>();
	auto stats = content.Load<Dictionary>("GameStats/Characters/VampireBat.xml");

	ReadEnemyConfig(*object.get(), *stats);

	auto movementSystem = std::make_unique<WaveMovementSystem>(*object, 0.2f, 1.0f, Axis::X);
	auto renderingSystem = std::make_unique<VampireBatRenderingSystem>(
		*object, "Characters/Enemies/VampireBat.ani.xml",
		effectFactory->CreateFlameEffect(),
		effectFactory->CreateSparkEffect());

	object->SetPosition(position);
	object->SetPowerupGenerator(std::make_unique<PowerupGenerator>(*this));
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<GiantBat> ObjectFactory::CreateGiantBat(base::Vector2 position)
{
	auto object = std::make_unique<GiantBat>();
	auto stats = content.Load<Dictionary>("GameStats/Characters/GiantBat.xml");

	ReadEnemyConfig(*object.get(), *stats);

	auto attackZoneWidth = std::stoi(stats->at("AttackZoneWidth"));
	auto attackZoneHeight = std::stoi(stats->at("AttackZoneHeight"));
	object->SetAttackZone(Rect{ 0, 0, attackZoneWidth, attackZoneHeight });

	auto threatZoneWidth = std::stoi(stats->at("ThreatZoneWidth"));
	auto threatZoneHeight = std::stoi(stats->at("ThreatZoneHeight"));
	object->SetThreatZone(Rect{ 0, 0, threatZoneWidth, threatZoneHeight });

	object->SetDiveSpeed(std::stof(stats->at("DiveSpeed")));

	auto controlSystem = std::make_unique<GiantBatControlSystem>(*object, *this);
	auto movementSystem = std::make_unique<GiantBatMovementSystem>(*object);
	auto collisionSystem = std::make_unique<GiantBatCollisionSystem>(*object);
	auto responseSystem = std::make_unique<GiantBatResponseSystem>(*object);
	auto renderingSystem = std::make_unique<GiantBatRenderingSystem>(
		*object, "Characters/Enemies/GiantBat.ani.xml",
		effectFactory->CreateBigFlameEffect(),
		effectFactory->CreateSparkEffect());

	object->SetPosition(position);
	object->Attach(std::move(controlSystem));
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->Idle();

	return object;
}

std::unique_ptr<Whip> ObjectFactory::CreateWhip(base::Vector2 position)
{
	auto object = std::make_unique<Whip>();

	auto collisionSystem = std::make_unique<WeaponCollisionSystem>(*object);
	auto responseSystem = std::make_unique<WeaponResponseSystem>(*object, false);
	auto renderingSystem = std::make_unique<WhipRenderingSystem>(*object, "Items/Whip.ani.xml");

	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Whip> ObjectFactory::CreateFlashingWhip(base::Vector2 position)
{
	auto object = std::make_unique<Whip>();

	auto collisionSystem = std::make_unique<WeaponCollisionSystem>(*object);
	auto responseSystem = std::make_unique<WeaponResponseSystem>(*object, false);
	auto renderingSystem = std::make_unique<WhipFlashingRenderingSystem>(*object, "Items/Whip.ani.xml");

	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<RangedWeapon> ObjectFactory::CreateSubWeapon(ObjectId type, base::Vector2 position)
{
	switch (type)
	{
	case ObjectId::Axe:
	case ObjectId::AxeItem:
		return CreateAxe(position);

	case ObjectId::Dagger:
	case ObjectId::DaggerItem:
		return CreateDagger(position);

	case ObjectId::HolyWater:
	case ObjectId::HolyWaterItem:
		return CreateHolyWater(position);

	case ObjectId::Fireball:
		return CreateFireball(position);

	default:
		return nullptr;
	}
}

std::unique_ptr<RangedWeapon> ObjectFactory::CreateAxe(base::Vector2 position)
{
	auto object = std::make_unique<RangedWeapon>(ObjectId::Axe);
	auto stats = content.Load<Dictionary>("GameStats/Weapons/Axe.xml");

	ReadSubWeaponConfig(*object.get(), *stats);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, 2000.0f);
	auto collisionSystem = std::make_unique<WeaponCollisionSystem>(*object);
	auto responseSystem = std::make_unique<WeaponResponseSystem>(*object, false);
	auto renderingSystem = std::make_unique<AnimationRenderingSystem>(*object, "Weapons/Axe.ani.xml");

	object->SetPosition(position);
	object->SetThrowSoundEffect(SE_USING_WEAPON);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<RangedWeapon> ObjectFactory::CreateDagger(base::Vector2 position)
{
	auto object = std::make_unique<RangedWeapon>(ObjectId::Dagger);
	auto stats = content.Load<Dictionary>("GameStats/Weapons/Dagger.xml");

	ReadSubWeaponConfig(*object.get(), *stats);

	auto movementSystem = std::make_unique<SimpleMovementSystem>(*object);
	auto collisionSystem = std::make_unique<WeaponCollisionSystem>(*object);
	auto responseSystem = std::make_unique<WeaponResponseSystem>(*object, true);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "Weapons/Dagger.png");

	object->SetPosition(position);
	object->SetThrowSoundEffect(SE_THROWING_DAGGER);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<HolyWater> ObjectFactory::CreateHolyWater(base::Vector2 position)
{
	auto object = std::make_unique<HolyWater>();
	auto stats = content.Load<Dictionary>("GameStats/Weapons/HolyWater.xml");

	ReadSubWeaponConfig(*object.get(), *stats);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, 600.0f);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<HolyWaterResponseSystem>(*object);
	auto renderingSystem = std::make_unique<HolyWaterRenderingSystem>(*object, "Weapons/Holy_Water.ani.xml");

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<RangedWeapon> ObjectFactory::CreateFireball(base::Vector2 position)
{
	auto object = std::make_unique<RangedWeapon>(ObjectId::Fireball);
	auto stats = content.Load<Dictionary>("GameStats/Weapons/Fireball.xml");
	ReadSubWeaponConfig(*object.get(), *stats);

	auto movementSystem = std::make_unique<SimpleMovementSystem>(*object);

	auto spritesheet = content.Load<Spritesheet>("Weapons/Fireball.atlas.xml");
	auto textureRegion = spritesheet->begin()->second;
	auto renderingSystem = std::make_unique<ItemRenderingSystem>(*object, textureRegion,
		effectFactory->CreateFlameEffect(),
		effectFactory->CreateSparkEffect());

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreatePowerup(ObjectId type, base::Vector2 position)
{
	switch (type)
	{
	case ObjectId::BlueMoneyBag:
		return CreateBlueMoneyBag(position);

	case ObjectId::WhiteMoneyBag:
		return CreateWhiteMoneyBag(position);

	case ObjectId::RedMoneyBag:
		return CreateRedMoneyBag(position);

	case ObjectId::FlashingMoneyBag:
		return CreateFlashingMoneyBag(position);

	case ObjectId::AxeItem:
		return CreateAxeItem(position);

	case ObjectId::Cross:
		return CreateCross(position);

	case ObjectId::DaggerItem:
		return CreateDaggerItem(position);

	case ObjectId::HolyWaterItem:
		return CreateHolyWaterItem(position);

	case ObjectId::LargeHeart:
		return CreateLargeHeart(position);

	case ObjectId::SmallHeart:
		return CreateSmallHeart(position);

	case ObjectId::InvisibleJar:
		return CreateInvisibleJar(position);

	case ObjectId::PorkChop:
		return CreatePorkChop(position);

	case ObjectId::Stopwatch:
		return CreateStopwatch(position);

	case ObjectId::WhipPowerup:
		return CreateWhipPowerup(position);

	case ObjectId::DoubleShot:
		return CreateDoubleShot(position);

	case ObjectId::CrystalBall:
		return CreateCrystalBall(position);

	default:
		throw std::invalid_argument("Invalid powerup type");
	}
}

std::unique_ptr<MoneyBag> ObjectFactory::CreateMoneyBag(ObjectId type, base::Vector2 position)
{
	auto money = int{};
	auto spriteId = std::string{};

	switch (type)
	{
	case ObjectId::RedMoneyBag:
		money = 100;
		spriteId = "money_bag_red";
		break;

	case ObjectId::BlueMoneyBag:
		money = 400;
		spriteId = "money_bag_blue";
		break;

	case ObjectId::WhiteMoneyBag:
		money = 700;
		spriteId = "money_bag_white";
		break;
	}

	auto object = std::make_unique<MoneyBag>(money, type);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, POWERUP_WEIGHT);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);

	auto moneyAtlas = content.Load<Spritesheet>("Items/Money_Bag.atlas.xml");
	auto effect = effectFactory->CreateMoneyTextEffect(money);
	auto renderingSystem = std::make_unique<ItemRenderingSystem>(
		*object, moneyAtlas->at(spriteId), std::move(effect), nullptr);

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<MoneyBag> ObjectFactory::CreateBlueMoneyBag(base::Vector2 position)
{
	return CreateMoneyBag(ObjectId::BlueMoneyBag, position);
}

std::unique_ptr<MoneyBag> ObjectFactory::CreateWhiteMoneyBag(base::Vector2 position)
{
	return CreateMoneyBag(ObjectId::WhiteMoneyBag, position);
}

std::unique_ptr<MoneyBag> ObjectFactory::CreateRedMoneyBag(base::Vector2 position)
{
	return CreateMoneyBag(ObjectId::RedMoneyBag, position);
}

std::unique_ptr<MoneyBag> ObjectFactory::CreateFlashingMoneyBag(base::Vector2 position)
{
	auto object = std::make_unique<MoneyBag>(1000, ObjectId::FlashingMoneyBag);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, POWERUP_WEIGHT);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);

	auto renderingSystem = std::make_unique<EntityRenderingSystem>(*object, "Items/Money_Bag.ani.xml",
		effectFactory->CreateFlashingMoneyTextEffect(), nullptr);

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateAxeItem(base::Vector2 position)
{
	auto object = std::make_unique<Powerup>(ObjectId::AxeItem);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, POWERUP_WEIGHT);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);

	auto spritesheet = content.Load<Spritesheet>("Items/Axe.atlas.xml");
	auto textureRegion = spritesheet->begin()->second;
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, textureRegion);

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateCross(base::Vector2 position)
{
	auto object = std::make_unique<Powerup>(ObjectId::Cross, 100000);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, POWERUP_WEIGHT);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);

	auto spritesheet = content.Load<Spritesheet>("Items/Cross.atlas.xml");
	auto textureRegion = spritesheet->begin()->second;
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, textureRegion);

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateDaggerItem(base::Vector2 position)
{
	auto object = std::make_unique<Powerup>(ObjectId::DaggerItem);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, POWERUP_WEIGHT);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);

	auto spritesheet = content.Load<Spritesheet>("Items/Dagger.atlas.xml");
	auto textureRegion = spritesheet->begin()->second;
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, textureRegion);

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateHolyWaterItem(base::Vector2 position)
{
	auto object = std::make_unique<Powerup>(ObjectId::HolyWaterItem);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, POWERUP_WEIGHT);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);

	auto spritesheet = content.Load<Spritesheet>("Items/Holy_Water.atlas.xml");
	auto textureRegion = spritesheet->begin()->second;
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, textureRegion);

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateLargeHeart(base::Vector2 position)
{
	auto object = std::make_unique<Powerup>(ObjectId::LargeHeart);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, POWERUP_WEIGHT);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);

	auto spritesheet = content.Load<Spritesheet>("Items/Large_Heart.atlas.xml");
	auto textureRegion = spritesheet->begin()->second;
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, textureRegion);

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateSmallHeart(base::Vector2 position)
{
	auto object = std::make_unique<Powerup>(ObjectId::SmallHeart);

	auto movementSystem = std::make_unique<WaveMovementSystem>(*object, 0.5f, 1.8f, Axis::Y);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "Items/Small_Heart.png");

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetSpeed(120.0f); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateInvisibleJar(base::Vector2 position)
{
	auto object = std::make_unique<Powerup>(ObjectId::InvisibleJar);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, POWERUP_WEIGHT);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);

	auto spritesheet = content.Load<Spritesheet>("Items/Invisible_Jar.atlas.xml");
	auto textureRegion = spritesheet->begin()->second;
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, textureRegion);

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreatePorkChop(base::Vector2 position)
{
	auto object = std::make_unique<Powerup>(ObjectId::PorkChop);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, POWERUP_WEIGHT);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);

	auto spritesheet = content.Load<Spritesheet>("Items/Pork_Chop.atlas.xml");
	auto textureRegion = spritesheet->begin()->second;
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, textureRegion);

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateStopwatch(base::Vector2 position)
{
	auto object = std::make_unique<Powerup>(ObjectId::Stopwatch);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, POWERUP_WEIGHT);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);

	auto spritesheet = content.Load<Spritesheet>("Items/Stopwatch.atlas.xml");
	auto textureRegion = spritesheet->begin()->second;
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, textureRegion);

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateWhipPowerup(base::Vector2 position)
{
	auto object = std::make_unique<Powerup>(ObjectId::WhipPowerup);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, POWERUP_WEIGHT);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);

	auto spritesheet = content.Load<Spritesheet>("Items/Whip_Powerup.atlas.xml");
	auto textureRegion = spritesheet->begin()->second;
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, textureRegion);

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateDoubleShot(base::Vector2 position)
{
	auto object = std::make_unique<Powerup>(ObjectId::DoubleShot);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, POWERUP_WEIGHT);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);

	auto spritesheet = content.Load<Spritesheet>("Items/Double_Shot.atlas.xml");
	auto textureRegion = spritesheet->begin()->second;
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, textureRegion);

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateCrystalBall(base::Vector2 position)
{
	auto object = std::make_unique<Powerup>(ObjectId::CrystalBall, 100000);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, POWERUP_WEIGHT);
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);
	auto renderingSystem = std::make_unique<AnimationRenderingSystem>(*object, "Items/Crystal_Ball.ani.xml");

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Door> ObjectFactory::CreateDoor(base::Vector2 position)
{
	auto object = std::make_unique<Door>();
	auto renderingSystem = std::make_unique<DoorRenderingSystem>(*object, "Items/Door.ani.xml");

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);
	object->Idle();

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateCastle(base::Vector2 position)
{
	auto object = std::make_unique<GameObject>(ObjectId::Castle);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "TiledMaps/Stage_01/Castle.png");

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateBrickBlock(base::Vector2 position)
{
	auto object = std::make_unique<GameObject>(ObjectId::Unknown);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "TiledMaps/Stage_01/Block.png");

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateDirtBlock(base::Vector2 position)
{
	auto object = std::make_unique<GameObject>(ObjectId::DirtBlock);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "TiledMaps/Stage_01/Dirt_Block.png");

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateWaterZone(base::Vector2 position)
{
	auto object = std::make_unique<GameObject>(ObjectId::Unknown);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "TiledMaps/Stage_01/Water_Area.png");

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

void ObjectFactory::ReadEnemyConfig(Enemy& enemy, Dictionary stats)
{
	enemy.SetSpeed(std::stof(stats.at("Speed")));
	enemy.SetHealth(std::stoi(stats.at("Health")));
	enemy.SetAttack(std::stoi(stats.at("Attack")));
	enemy.SetExp(std::stoi(stats.at("Exp")));
}

void ObjectFactory::ReadSubWeaponConfig(RangedWeapon& weapon, Dictionary stats)
{
	auto x = std::stof(stats.at("ThrowSpeed_X"));
	auto y = std::stof(stats.at("ThrowSpeed_Y"));
	auto attack = std::stoi(stats.at("Attack"));

	weapon.SetThrowVelocity(base::Vector2{ x, y });
	weapon.SetAttack(attack);
}

void ObjectFactory::ReadSpawnAreaConfig(SpawnArea& spawnArea, Dictionary stats)
{
	auto spawnType = string2EntityType.at(stats.at("Spawn"));
	auto groupSpawnTime = std::stoi(stats.at("GroupSpawnTime"));
	auto spawnTime = std::stoi(stats.at("SpawnTime"));
	auto spawnGroup = stats.at("SpawnGroup");
	auto spawnDirection = stats.at("SpawnDirection");

	spawnArea.SetGroupCountChances(spawnGroup);
	spawnArea.SetDirectionChances(spawnDirection);
	spawnArea.SetGroupSpawnTime(groupSpawnTime);
	spawnArea.SetSpawnTime(spawnTime);
}

std::unique_ptr<SpawnArea> ObjectFactory::ConstructSpawnArea(ObjectId type)
{
	auto object = std::unique_ptr<SpawnArea>{};
	auto stats = std::shared_ptr<Dictionary>{};

	switch (type)
	{
	case ObjectId::Zombie:
	{
		object = std::make_unique<ZombieSpawnArea>(*this);
		stats = content.Load<Dictionary>("GameStats/SpawnAreas/ZombieSpawnArea.xml");
		break;
	}

	case ObjectId::VampireBat:
	{
		object = std::make_unique<VampireBatSpawnArea>(*this);
		stats = content.Load<Dictionary>("GameStats/SpawnAreas/BatSpawnArea.xml");
		break;
	}

	case ObjectId::Fishman:
	{
		object = std::make_unique<FishmanSpawnArea>(*this);
		stats = content.Load<Dictionary>("GameStats/SpawnAreas/FishmanSpawnArea.xml");
		break;
	}

	default:
		throw std::runtime_error("Spawn area for this type of object is not supported");
	}

	ReadSpawnAreaConfig(*object.get(), *stats);

	return object;
}