#include "stdafx.h"
#include "Hud.h"
#include "MathHelper.h"

constexpr auto HUD_HEIGHT = 83;
constexpr auto POWERUP_FLASHING_TIME = 2500;

const auto DEFAULT_PLAYER_DATA = PlayerData{};
const auto DEFAULT_BOSS_HEALTH = Health{ MAX_HEALTH };
const auto DEFAULT_GAMEPLAY_DATA = GameplayData{};

struct Hud::HudData
{
	const PlayerData* playerData;
	const Health* bossHealth;
	const GameplayData* gameplayData;
};

Hud::Hud()
{
	width = GetScreenWidth();
	height = HUD_HEIGHT;
	data = std::make_unique<HudData>();

	data->playerData = &DEFAULT_PLAYER_DATA;
	data->bossHealth = &DEFAULT_BOSS_HEALTH;
	data->gameplayData = &DEFAULT_GAMEPLAY_DATA;

	scoreTextPosition = base::Vector2{ 0, 15 };
	timeTextPosition = base::Vector2{ 210, 15 };
	stageTextPosition = base::Vector2{ 370, 15 };
	playerTextPosition = base::Vector2{ 0, 32 };
	playerHealthPosition = base::Vector2{ 105, 33 };
	enemyTextPosition = base::Vector2{ 2, 49 };
	enemyHealthPosition = base::Vector2{ 105, 49 };
	borderTexturePosition = base::Vector2{ 260, 32 };
	heartTexturePosition = base::Vector2{ 339, 32 };
	heartTextPosition = base::Vector2{ 355, 32 };
	liveTextPosition = base::Vector2{ 340, 49 };
	powerupPosition = base::Vector2{ 432, 48 };
}

int Hud::GetWidth()
{
	return width;
}

int Hud::GetHeight()
{
	return height;
}

void Hud::Register(const PlayerData& playerData)
{
	data->playerData = &playerData;
}

void Hud::Register(const Health& bossHealth)
{
	data->bossHealth = &bossHealth;
}

void Hud::Register(const GameplayData& gameplayData)
{
	data->gameplayData = &gameplayData;
}

template<>
void Hud::Unregister<PlayerData>()
{
	data->playerData = &DEFAULT_PLAYER_DATA;
}

template<>
void Hud::Unregister<int>()
{
	data->bossHealth = &DEFAULT_BOSS_HEALTH;
}

template<>
void Hud::Unregister<GameplayData>()
{
	data->gameplayData = &DEFAULT_GAMEPLAY_DATA;
}

void Hud::LoadContent(ContentManager& content)
{
	hudFont = content.Load<Font>("Fonts/MainFont.font.xml");
	borderTexture = content.Load<Texture>("Hud/Border.png");
	heartTexture = content.Load<Texture>("Hud/Heart.png");

	auto hpBlockAtlas = content.Load<Spritesheet>("Hud/HP_Block.atlas.xml");

	playerFullBlock = std::make_unique<Sprite>(hpBlockAtlas->at("player_full"));
	bossFullBlock = std::make_unique<Sprite>(hpBlockAtlas->at("boss_full"));
	emptyBlock = std::make_unique<Sprite>(hpBlockAtlas->at("empty"));

	axeTexture = content.Load<Texture>("Items/Axe.png");
	daggerTexture = content.Load<Texture>("Items/Dagger.png");
	holyWaterTexture = content.Load<Texture>("Items/Holy_Water.png");
	stopwatchTexture = content.Load<Texture>("Items/Stopwatch.png");
	doubleShotTexture = content.Load<Texture>("Hud/Double_Shot.png");
}

void Hud::Draw(SpriteExtensions& spriteBatch)
{
	spriteBatch.Draw(*heartTexture, heartTexturePosition, base::Color::White(), false);
	spriteBatch.Draw(*borderTexture, borderTexturePosition, base::Color::White(), false);

	spriteBatch.DrawString(*hudFont, GetScoreText(), scoreTextPosition, base::Color::White(), false);
	spriteBatch.DrawString(*hudFont, GetTimeText(), timeTextPosition, base::Color::White(), false);
	spriteBatch.DrawString(*hudFont, GetStageText(), stageTextPosition, base::Color::White(), false);

	spriteBatch.DrawString(*hudFont, "PLAYER", playerTextPosition, base::Color::White(), false);
	spriteBatch.DrawString(*hudFont, "ENEMY", enemyTextPosition, base::Color::White(), false);
	DrawHealthBars(spriteBatch);

	auto weaponTexture = GetWeaponTexture();
	if (weaponTexture != nullptr)
		spriteBatch.Draw(*weaponTexture, GetWeaponPosition(*weaponTexture), base::Color::White(), false);

	spriteBatch.DrawString(*hudFont, GetHeartCountText(), heartTextPosition, base::Color::White(), false);
	spriteBatch.DrawString(*hudFont, GetLiveCountText(), liveTextPosition, base::Color::White(), false);

	DrawPowerup(spriteBatch);
}

std::string Hud::GetScoreText()
{
	return "SCORE-" + PadZero(data->playerData->score, 6);
}

std::string Hud::GetTimeText()
{
	return "TIME " + PadZero(MathHelper::Max(data->gameplayData->timeLeft.GetCounter(), 0), 4);
}

std::string Hud::GetStageText()
{
	return "STAGE " + PadZero(data->gameplayData->stage, 2);
}

std::string Hud::GetHeartCountText()
{
	return "-" + PadZero(data->playerData->hearts, 2);
}

std::string Hud::GetLiveCountText()
{
	return "P-" + PadZero(data->playerData->lives, 2);
}

std::shared_ptr<Texture> Hud::GetWeaponTexture()
{
	switch (data->playerData->subWeapon)
	{
	case ObjectId::AxeItem:
		return axeTexture;

	case ObjectId::DaggerItem:
		return daggerTexture;

	case ObjectId::HolyWaterItem:
		return holyWaterTexture;

	case ObjectId::Stopwatch:
		return stopwatchTexture;

	default:
		return nullptr;
	}
}

std::shared_ptr<Texture> Hud::GetPowerupTexture()
{
	switch (data->playerData->powerup)
	{
	case ObjectId::DoubleShot:
		return doubleShotTexture;

	default:
		return nullptr;
	}
}

base::Vector2 Hud::GetWeaponPosition(Texture& weaponTexture)
{
	auto borderCenter = base::Vector2{
		borderTexturePosition.x + borderTexture->width / 2,
		borderTexturePosition.y + borderTexture->height / 2 };

	auto weaponPosition = base::Vector2{
		borderCenter.x - weaponTexture.width / 2,
		borderCenter.y - weaponTexture.height / 2 };

	return weaponPosition;
}

base::Vector2 Hud::GetPowerupPosition(Texture& powerupTexture)
{
	return base::Vector2{
		powerupPosition.x - powerupTexture.width / 2,
		powerupPosition.y - powerupTexture.height / 2 };
}

void Hud::DrawHealthBars(SpriteExtensions& spriteBatch)
{
	auto playerHealth = data->playerData->health.Value();
	auto bossHealth = data->bossHealth->Value();

	for (auto i = 0; i < MAX_HEALTH; i++)
	{
		if (i + 1 <= playerHealth)
		{
			auto position = base::Vector2{ playerHealthPosition.x + i * 9, playerHealthPosition.y };
			spriteBatch.Draw(*playerFullBlock, position, false);
		}
		else
		{
			auto position = base::Vector2{ playerHealthPosition.x + i * 9, playerHealthPosition.y };
			spriteBatch.Draw(*emptyBlock, position, false);
		}

		if (i + 1 <= bossHealth)
		{
			auto position = base::Vector2{ enemyHealthPosition.x + i * 9, enemyHealthPosition.y };
			spriteBatch.Draw(*bossFullBlock, position, false);
		}
		else
		{
			auto position = base::Vector2{ enemyHealthPosition.x + i * 9, enemyHealthPosition.y };
			spriteBatch.Draw(*emptyBlock, position, false);
		}
	}
}

void Hud::DrawPowerup(SpriteExtensions& spriteBatch)
{
	auto currentPowerupTexture = GetPowerupTexture();

	if (currentPowerupTexture == nullptr)
		return;

	if (powerupTexture == nullptr && currentPowerupTexture != nullptr)
		powerupFlashingTimer.Start();

	if (powerupFlashingTimer.IsRunning())
	{
		if (powerupFlashingTimer.ElapsedMilliseconds() >= POWERUP_FLASHING_TIME)
			powerupFlashingTimer.Reset();
		else
			spriteBatch.Draw(*currentPowerupTexture, GetPowerupPosition(*currentPowerupTexture),
				Stopwatch::Every(60) ? base::Color::White() : base::Color::Transparent(), false);
	}
	else
		spriteBatch.Draw(*currentPowerupTexture, GetPowerupPosition(*currentPowerupTexture), base::Color::White(), false);

	powerupTexture = currentPowerupTexture;
}

std::string Hud::PadZero(int number, int paddingCount)
{
	auto sstream = std::stringstream{};

	sstream << std::setfill('0') << std::setw(paddingCount) << number;

	return sstream.str();
}

Hud::~Hud() = default;