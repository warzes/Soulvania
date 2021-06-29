#pragma once

#include "ContentManager.h"
#include "PlayerData.h"
#include "GameplayData.h"

// Head-up display to show current player stats
// (health, weapon...) on top of the screen
class Hud
{
public:
	Hud();

	int GetWidth();
	int GetHeight();

	void Register(const PlayerData& playerData);
	void Register(const Health& bossHealth);
	void Register(const GameplayData& gameplayData);

	template<typename T>
	void Unregister();

	void LoadContent(ContentManager& content);
	void Draw(SpriteExtensions& spriteBatch);

	~Hud();

private:
	struct HudData;

	std::unique_ptr<HudData> data;

	int width;
	int height;

	std::shared_ptr<Font> hudFont;
	std::shared_ptr<Texture> borderTexture;
	std::shared_ptr<Texture> heartTexture;

	std::shared_ptr<Texture> axeTexture;
	std::shared_ptr<Texture> daggerTexture;
	std::shared_ptr<Texture> holyWaterTexture;
	std::shared_ptr<Texture> stopwatchTexture;
	std::shared_ptr<Texture> doubleShotTexture;
	std::shared_ptr<Texture> powerupTexture;

	std::unique_ptr<Sprite> playerFullBlock;
	std::unique_ptr<Sprite> bossFullBlock;
	std::unique_ptr<Sprite> emptyBlock;

	base::Vector2 scoreTextPosition;
	base::Vector2 timeTextPosition;
	base::Vector2 stageTextPosition;
	base::Vector2 playerTextPosition;
	base::Vector2 playerHealthPosition;
	base::Vector2 enemyTextPosition;
	base::Vector2 enemyHealthPosition;
	base::Vector2 borderTexturePosition;
	base::Vector2 heartTexturePosition;
	base::Vector2 heartTextPosition;
	base::Vector2 liveTextPosition;
	base::Vector2 powerupPosition;

	std::string GetScoreText();
	std::string GetTimeText();
	std::string GetStageText();
	std::string GetHeartCountText();
	std::string GetLiveCountText();

	Stopwatch powerupFlashingTimer;

	std::shared_ptr<Texture> GetWeaponTexture();
	std::shared_ptr<Texture> GetPowerupTexture();
	base::Vector2 GetWeaponPosition(Texture& weaponTexture);
	base::Vector2 GetPowerupPosition(Texture& powerupTexture);

	void DrawHealthBars(SpriteExtensions& spriteBatch);
	void DrawPowerup(SpriteExtensions& spriteBatch);

	std::string PadZero(int number, int paddingCount); // (123, 5) -> "00123"
};