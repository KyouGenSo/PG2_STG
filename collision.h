#pragma once
#include"player.h"
#include"WEnemy.h"
#include"Benemy.h"
#include"Novice.h"

class Collision
{
public:
	Vector2 PBullet2W;
	float PBullet2WLength;
	Vector2 PBullet2B;
	float PBullet2BLength;

	Vector2 WBullet2P;
	float WBullet2PLength;

	Vector2 BEnemy2P;
	float BEnemy2PLength;

	int enemyDamage_;

	//SE
	int WEnemyDamagedSound = Novice::LoadAudio("./Res/enemy1Damaged.wav");
	int BEnemyDamagedSound = Novice::LoadAudio("./Res/enemy2Damaged.wav");
	int playerDamagedSound = Novice::LoadAudio("./Res/playerDamaged.wav");

public:
	Collision();
	~Collision();

	void Init();

	void Update(Player& player, WEnemy& wEnemy, BEnemy& bEnemy);

	void PlayerToWEnemy(Player& player, WEnemy& wEnemy);

	void PlayerToBEnemy(Player& player, BEnemy& bEnemy);

	void WEnemyToPlayer(Player& player, WEnemy& wEnemy);

	void BEnemyToPlayer(Player& player, BEnemy& bEnemy);
};
