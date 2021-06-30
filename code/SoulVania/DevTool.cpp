#include "stdafx.h"
#include "DevTool.h"
#include "MathHelper.h"
#include "CppExtensions.h"
#include "TypeConverter.h"
#include "AudioManager.h"
#include "CollisionGrid.h"
#include "SceneManager.h"
#include "GameplayScene.h"
#include "RenderingSystem.h"

constexpr auto PLAYER = "PLAYER";
constexpr auto ENEMY = "ENEMY";
constexpr auto CONTAINER = "CONTAINER";
constexpr auto POWERUP = "POWERUP";
constexpr auto WEAPON = "WEAPON";
constexpr auto EFFECT = "EFFECT";

std::string DevTool::currentCategory = POWERUP;
int DevTool::currentItemIndex = 0;
int DevTool::currentMapIndex = 0;
bool DevTool::IsDebugging = false;
bool DevTool::drawingGridInfo = false;

DevTool::DevTool(Stage& stage) :
	stage{ stage },
	objectFactory{ stage.objectFactory },
	player{ *stage.player },
	camera{ *stage.camera }
{
}

void DevTool::LoadContent(ContentManager& content)
{
	effectFactory = std::make_unique<EffectFactory>(content);
	debugFont = content.Load<Font>("Fonts/DebugFont.font.xml");
	blockSpritePaths = { "TiledMaps/Stage_01/Block.png", "TiledMaps/Stage_01/Block_01.png", "TiledMaps/Stage_01/Block_02.png" };

	auto playerSprite = content.Load<Spritesheet>("Characters/Players/Simon.atlas.xml")->at("walk_01");
	auto zombieSprite = content.Load<Spritesheet>("Characters/Enemies/Zombie.atlas.xml")->begin()->second;
	auto pantherSprite = content.Load<Spritesheet>("Characters/Enemies/Panther.atlas.xml")->begin()->second;
	auto fishmanSprite = content.Load<Spritesheet>("Characters/Enemies/Fishman.atlas.xml")->begin()->second;
	auto vampireBatSprite = content.Load<Spritesheet>("Characters/Enemies/VampireBat.atlas.xml")->at("fly_01");
	auto giantBatSprite = content.Load<Spritesheet>("Characters/Enemies/GiantBat.atlas.xml")->at("fly_01");

	auto brazierSprite = content.Load<Spritesheet>("Items/Brazier.atlas.xml")->begin()->second;
	auto candleSprite = content.Load<Spritesheet>("Items/Candle.atlas.xml")->begin()->second;
	auto blockSprite = content.Load<Texture>("TiledMaps/Stage_01/Block.png");
	auto wallSprite = content.Load<Texture>("TiledMaps/Breakable_Wall.png");

	auto blueMoneyBagSprite = content.Load<Spritesheet>("Items/Money_Bag.atlas.xml")->at("money_bag_blue");
	auto whiteMoneyBagSprite = content.Load<Spritesheet>("Items/Money_Bag.atlas.xml")->at("money_bag_white");
	auto redMoneyBagSprite = content.Load<Spritesheet>("Items/Money_Bag.atlas.xml")->at("money_bag_red");
	auto axeItemSprite = content.Load<Texture>("Items/Axe.png");
	auto crossSprite = content.Load<Texture>("Items/Cross.png");
	auto daggerItemSprite = content.Load<Texture>("Items/Dagger.png");
	auto holyWaterItemSprite = content.Load<Texture>("Items/Holy_Water.png");
	auto largeHeartSprite = content.Load<Texture>("Items/Large_Heart.png");
	auto smallHeartSprite = content.Load<Texture>("Items/Small_Heart.png");
	auto invisibleJarSprite = content.Load<Texture>("Items/Invisible_Jar.png");
	auto porkChopSprite = content.Load<Texture>("Items/Pork_Chop.png");
	auto stopwatchSprite = content.Load<Texture>("Items/Stopwatch.png");
	auto whipPowerupSprite = content.Load<Texture>("Items/Whip_Powerup.png");
	auto doubleShotSprite = content.Load<Texture>("Items/Double_Shot.png");
	auto crystalBallSprite = content.Load<Spritesheet>("Items/Crystal_Ball.atlas.xml")->begin()->second;

	auto axeSprite = content.Load<Spritesheet>("Weapons/Axe.atlas.xml")->at("axe_01");
	auto holyWaterSprite = content.Load<Spritesheet>("Weapons/Holy_Water.atlas.xml")->at("holy_water_01");
	auto fireballSprite = content.Load<Texture>("Weapons/Fireball.png");

	auto flameSprite = content.Load<Spritesheet>("Effects/Flame.atlas.xml")->at("flame_02");
	auto debrisSprite = content.Load<Texture>("Effects/Debris.png");
	auto waterSprite = content.Load<Texture>("Effects/Water.png");

	items = std::unordered_map<std::string, DevToolItems>{
		{
			PLAYER,
			{
				std::make_pair<std::string, Sprite>("Player", playerSprite),
			},
		},
		{
			ENEMY,
			{
				std::make_pair<std::string, Sprite>("Zombie", zombieSprite),
				std::make_pair<std::string, Sprite>("Panther", pantherSprite),
				std::make_pair<std::string, Sprite>("Fishman", fishmanSprite),
				std::make_pair<std::string, Sprite>("VampireBat", vampireBatSprite),
				std::make_pair<std::string, Sprite>("GiantBat", giantBatSprite),
			},
		},
		{
			CONTAINER,
			{
				std::make_pair<std::string, Sprite>("Brazier", brazierSprite),
				std::make_pair<std::string, Sprite>("Candle", candleSprite),
				std::make_pair<std::string, Sprite>("BreakableBlock", blockSprite),
				std::make_pair<std::string, Sprite>("BreakableWall", wallSprite),
			}
		},
		{
			POWERUP,
			{
				std::make_pair<std::string, Sprite>("BlueMoneyBag", blueMoneyBagSprite),
				std::make_pair<std::string, Sprite>("WhiteMoneyBag", whiteMoneyBagSprite),
				std::make_pair<std::string, Sprite>("RedMoneyBag", redMoneyBagSprite),
				std::make_pair<std::string, Sprite>("FlashingMoneyBag", blueMoneyBagSprite),
				std::make_pair<std::string, Sprite>("AxeItem", axeItemSprite),
				std::make_pair<std::string, Sprite>("Cross", crossSprite),
				std::make_pair<std::string, Sprite>("DaggerItem", daggerItemSprite),
				std::make_pair<std::string, Sprite>("HolyWaterItem", holyWaterItemSprite),
				std::make_pair<std::string, Sprite>("LargeHeart", largeHeartSprite),
				std::make_pair<std::string, Sprite>("SmallHeart", smallHeartSprite),
				std::make_pair<std::string, Sprite>("InvisibleJar", invisibleJarSprite),
				std::make_pair<std::string, Sprite>("PorkChop", porkChopSprite),
				std::make_pair<std::string, Sprite>("Stopwatch", stopwatchSprite),
				std::make_pair<std::string, Sprite>("WhipPowerup", whipPowerupSprite),
				std::make_pair<std::string, Sprite>("DoubleShot", doubleShotSprite),
				std::make_pair<std::string, Sprite>("CrystalBall", crystalBallSprite),
			}
		},
		{
			WEAPON,
			{
				std::make_pair<std::string, Sprite>("Axe", axeSprite),
				std::make_pair<std::string, Sprite>("Dagger", daggerItemSprite),
				std::make_pair<std::string, Sprite>("HolyWater", holyWaterSprite),
				std::make_pair<std::string, Sprite>("Fireball", fireballSprite),
			}
		},
		{
			EFFECT,
			{
				std::make_pair<std::string, Sprite>("FlameEffect", flameSprite),
				std::make_pair<std::string, Sprite>("BigFlameEffect", flameSprite),
				std::make_pair<std::string, Sprite>("DebrisEffect", debrisSprite),
				std::make_pair<std::string, Sprite>("WaterEffect", waterSprite),
			}
		},
	};

	maps = std::vector<Map>{
		Map::INTRO,
		Map::COURTYARD,
		Map::GREAT_HALL,
		Map::UNDERGROUND,
		Map::PLAYGROUND };
}

void DevTool::Update(SceneManager& sceneManager)
{
	if (IsKeyDown(KEY_KP_1))
	{
		AudioManager::StopAll();
		sceneManager.SetNextScene(Scene::MENU);
	}
	else if (IsKeyDown(KEY_KP_2))
	{
		AudioManager::StopAll();
		auto& scene = sceneManager.SetNextScene(Scene::GAMEPLAY);
		dynamic_cast<GameplayScene&>(scene).NextStage(Map::COURTYARD);
	}
	else if (IsKeyDown(KEY_KP_3))
	{
		AudioManager::StopAll();
		sceneManager.SetNextScene(Scene::GAMEOVER);
	}
}

void DevTool::Update(UpdateData& updatData)
{
	// Update keyboard input
	if (IsKeyDown(KEY_ESCAPE))
		IsDebugging = !IsDebugging;

	if (!IsDebugging)
		return;

	auto checkpoints = stage.stageObject->locations;

	if (IsKeyDown(KEY_TAB))
		SetCategory(PLAYER);
	else if (IsKeyDown(KEY_Q))
		SetCategory(ENEMY);
	else if (IsKeyDown(KEY_W))
		SetCategory(CONTAINER);
	else if (IsKeyDown(KEY_E))
		SetCategory(POWERUP);
	else if (IsKeyDown(KEY_R))
		SetCategory(WEAPON);
	else if (IsKeyDown(KEY_T))
		SetCategory(EFFECT);
	else if (IsKeyDown(KEY_G))
		drawingGridInfo = !drawingGridInfo;

	else if (IsKeyDown(KEY_LEFT_BRACKET))
		PreviousMap();
	else if (IsKeyDown(KEY_RIGHT_BRACKET))
		NextMap();

	else if (IsKeyDown(KEY_ONE))
		player.SetPosition(checkpoints["Checkpoint"]);
	else if (IsKeyDown(KEY_TWO))
		player.SetPosition(checkpoints["Checkpoint_02"]);
	else if (IsKeyDown(KEY_THREE))
		player.SetPosition(checkpoints["Checkpoint_03"]);
	else if (IsKeyDown(KEY_FOUR))
		player.SetPosition(checkpoints["Checkpoint_04"]);
	else if (IsKeyDown(KEY_FIVE))
		player.SetPosition(checkpoints["Checkpoint_05"]);
	else if (IsKeyDown(KEY_SIX))
		player.SetPosition(checkpoints["Checkpoint_06"]);

	else if (IsKeyDown(KEY_EIGHT))
		player.data.hearts += 200;
	else if (IsKeyDown(KEY_NINE))
		player.data.health.Set(1);
	else if (IsKeyDown(KEY_ZERO))
		player.data.health.Set(MAX_HEALTH);
	else if (IsKeyDown(KEY_KP_SUBTRACT))
		player.Die();
	else if (IsKeyDown(KEY_KP_ADD))
		player.data.lives++;
	else if (IsKeyDown(KEY_GRAVE))
		player.ToggleGodMode();

	// Update mouse input
	if (GetMouseWheelMove() > 0)
		PreviousItem();
	else if (GetMouseWheelMove() < 0)
		NextItem();
	else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		SpawnItem();
	else if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
		currentFacing = Opposite(currentFacing);

	UpdateEffects(updatData.gameTime);
}

void DevTool::Draw(SpriteExtensions& spriteBatch)
{
	if (!IsDebugging)
		return;

	for (auto effect : activeEffects)
		effect->Draw(spriteBatch);

	auto objectPosition = GetCurrentItemPosition();
	auto textPosition = base::Vector2{ objectPosition.x, objectPosition.y - 20 };
	auto effect = currentFacing == Facing::Left ? SpriteEffects::FlipHorizontally : SpriteEffects::None;
	auto itemName = items[currentCategory][currentItemIndex].first;
	auto sprite = items[currentCategory][currentItemIndex].second;

	sprite.SetEffect(effect);

	DrawCollisionGridInfo(spriteBatch);
	spriteBatch.DrawString(*debugFont, itemName, textPosition, base::Color::White());
	spriteBatch.Draw(sprite, objectPosition);
}

base::Vector2 DevTool::GetCurrentItemPosition()
{
	auto mousePosition = camera.ScreenToWorld({ GetMousePosition().x, GetMousePosition().y }); // TODO:
	auto sprite = items[currentCategory][currentItemIndex].second;
	auto spriteWidth = sprite.GetFrameRectangle(mousePosition).Width();

	return base::Vector2{ mousePosition.x - spriteWidth, mousePosition.y };
}

std::unique_ptr<IEffect> DevTool::CreateEffect(std::string name)
{
	if (name == "FlameEffect")
		return effectFactory->CreateFlameEffect();
	else if (name == "BigFlameEffect")
		return effectFactory->CreateBigFlameEffect();
	else if (name == "DebrisEffect")
		return effectFactory->CreateDebrisEffect();
	else if (name == "WaterEffect")
		return effectFactory->CreateWaterEffect();
	else
		throw std::runtime_error("Effect name is invalid");
}

void DevTool::UpdateEffects(GameTime gameTime)
{
	for (int i = activeEffects.size() - 1; i >= 0; i--)
	{
		activeEffects[i]->Update(gameTime);

		if (activeEffects[i]->IsFinished())
			RemoveByValue(activeEffects, activeEffects[i]);
	}
}

void DevTool::DrawCollisionGridInfo(SpriteExtensions& spriteBatch)
{
	if (!drawingGridInfo)
		return;

	auto& grid = *stage.grid;

	grid.GetCellsFromBoundingBox(camera.GetBounds(), [&](CollisionCell& cell, int col, int row)
		{
			auto& objects = cell.GetObjects();
			auto gridInfoText = std::stringstream{};

			// another O(n) from grid.GetCollisionObjects(), but it's debugging code so...
			gridInfoText
				<< "S:" << objects.staticObjects.size() << "\n"
				<< "E:" << objects.entities.size() << "\n"
				<< "CoObjs:" << grid.GetCollisionObjects(col, row).size();

			auto cellBbox = cell.GetBoundingBox();
			auto gridInfoTextPosition = base::Vector2{
				cellBbox.X() + cellBbox.Width() / 2 - 25,
				cellBbox.Y() + cellBbox.Height() / 2 - 25 };

			auto rightLine = RectF{ cellBbox.right, cellBbox.top, 1, cellBbox.Height() };
			auto bottomLine = RectF{ cellBbox.left, cellBbox.bottom, cellBbox.Width(), 1 };
			auto textBackground = RectF{ gridInfoTextPosition.x - 5, gridInfoTextPosition.y - 2, 70, 47 };

			RenderingSystem::DrawBoundingBox(spriteBatch, rightLine, base::Color::DimGray());
			RenderingSystem::DrawBoundingBox(spriteBatch, bottomLine, base::Color::DimGray());
			RenderingSystem::DrawBoundingBox(spriteBatch, textBackground, base::Color::DimGray() * 0.7f);

			spriteBatch.DrawString(*debugFont, gridInfoText.str(), gridInfoTextPosition, base::Color::White());
		});
}

void DevTool::SetCategory(std::string category)
{
	this->currentCategory = category;
	this->currentItemIndex = 0;
}

void DevTool::NextItem()
{
	if (++currentItemIndex > (int)items[currentCategory].size() - 1)
		currentItemIndex = 0;
}

void DevTool::PreviousItem()
{
	if (--currentItemIndex < 0)
		currentItemIndex = items[currentCategory].size() - 1;
}

void DevTool::SpawnItem()
{
	if (currentCategory == EFFECT)
		SpawnEffect();
	else
		SpawnObject();
}

void DevTool::SpawnObject()
{
	auto type = string2EntityType.at(items[currentCategory][currentItemIndex].first);
	auto objectPosition = GetCurrentItemPosition();
	auto object = std::unique_ptr<GameObject>{};

	if (currentCategory == PLAYER)
	{
		player.SetPosition(GetCurrentItemPosition());
		player.SetFacing(currentFacing);
		player.IdleOnGround();
		return;
	}
	else if (currentCategory == ENEMY)
	{
		object = objectFactory.CreateEnemy(type);

		if (object->GetId() == ObjectId::GiantBat)
		{
			auto giantBat = dynamic_cast<GiantBat*>(object.get());
			giantBat->SetPosition(objectPosition);
			giantBat->SetMoveArea((Rect)camera.GetBounds());
			giantBat->SetActive();
		}
	}
	else if (currentCategory == POWERUP)
	{
		object = objectFactory.CreatePowerup(type);
		dynamic_cast<Powerup&>(*object).Spawn();
	}
	else if (currentCategory == CONTAINER)
	{
		auto powerupItem = *MathHelper::RandomItem(items[POWERUP].begin(), items[POWERUP].end());
		auto powerupType = string2EntityType.at(powerupItem.first);
		switch (type)
		{
		case ObjectId::Brazier:
			object = objectFactory.CreateBrazier(powerupType);
			break;
		case ObjectId::Candle:
			object = objectFactory.CreateCandle(powerupType);
			break;
		case ObjectId::BreakableBlock:
		{
			auto blockSprite = *MathHelper::RandomItem(blockSpritePaths.begin(), blockSpritePaths.end());
			object = objectFactory.CreateBreakableBlock(powerupType, blockSprite);
			break;
		}
		case ObjectId::BreakableWall:
			object = objectFactory.CreateBreakableWall(powerupType);
			break;
		}
	}
	else if (currentCategory == WEAPON)
	{
		switch (type)
		{
		case ObjectId::Axe:
		case ObjectId::Dagger:
		case ObjectId::HolyWater:
		case ObjectId::Fireball:
		{
			object = objectFactory.CreateSubWeapon(type);
			object->SetFacing(currentFacing);
			dynamic_cast<RangedWeapon&>(*object).Throw({ GetMousePosition().x, GetMousePosition().y });
			break;
		}
		}
	}

	object->SetPosition(objectPosition);
	object->SetFacing(currentFacing);
	stage.grid->Add(std::move(object), CollisionObjectType::Entity);
}

void DevTool::SpawnEffect()
{
	auto effectName = items[EFFECT][currentItemIndex].first;
	auto effect = CreateEffect(effectName);

	effect->Show(GetCurrentItemPosition());
	activeEffects.push_back(std::move(effect));
}

void DevTool::OnChangingMap()
{
	if (maps[currentMapIndex] != stage.currentMap)
	{
		for (int i = 0; i < maps.size() - 1; i++)
			if (maps[i] == stage.currentMap)
			{
				currentMapIndex = i;
				break;
			}
	}

	if (maps[currentMapIndex] == Map::INTRO)
	{
		player.EnableControl(true);
		player.SetSpeed(125);
		player.Idle();
		AudioManager::StopAll();
	}
}

void DevTool::NextMap()
{
	OnChangingMap();

	if (++currentMapIndex > (int)maps.size() - 1)
		currentMapIndex = 0;

	stage.gameplayScene.NextStage(maps[currentMapIndex]);
}

void DevTool::PreviousMap()
{
	OnChangingMap();

	if (--currentMapIndex < 0)
		currentMapIndex = maps.size() - 1;

	stage.gameplayScene.NextStage(maps[currentMapIndex]);
}