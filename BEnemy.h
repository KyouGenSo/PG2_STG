#pragma once
#include <Vector2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Novice.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<player.h>

const int BEnemyMaxNum = 15;

class BEnemy
{
private:

	Vector2 pos_[BEnemyMaxNum];
	int posXSeed_[BEnemyMaxNum];

	float speed_;

	float radius_[BEnemyMaxNum];

	int numChanger_;
	int numMax_ = BEnemyMaxNum;

	int respawnTimer_[BEnemyMaxNum];

	int explodeAnimCount_[BEnemyMaxNum];

	int frameCount_;
	int animFrameCount_;

	Vector2 toPlayer_;
	float toPlayerLength_;

		
	//移動角度計算用変数
	double moveAngleX_[BEnemyMaxNum];
	double moveAngleY_[BEnemyMaxNum];
	double targetAngle_[BEnemyMaxNum];

	//HD
	int explodeImage;

public:

	BEnemy();
	~BEnemy();

	void Init();

	void Update(Player& player);

	void Draw();



	void SetPos(Vector2 pos, int i) { this->pos_[i] = pos; }
	Vector2 GetPos(int i) { return pos_[i]; }

	void SetRadius(float radius, int i) { this->radius_[i] = radius; }
	float GetRadius(int i) { return radius_[i]; }

	void SetSpeed(float speed) { this->speed_ = speed; }
	float GetSpeed() { return speed_; }

	void SetIsAlive(bool isAlive, int i) { this->isAlive_[i] = isAlive; }
	bool GetIsAlive(int i) { return isAlive_[i]; }

	void SetRespawnTimer(int respawnTimer, int i) { this->respawnTimer_[i] = respawnTimer; }
	int GetRespawnTimer(int i) { return respawnTimer_[i]; }

	void SetExplodeAnimCount(int explodeAnimCount, int i) { this->explodeAnimCount_[i] = explodeAnimCount; }
	int GetExplodeAnimCount(int i) { return explodeAnimCount_[i]; }

	void SetFrameCount(int frameCount) { this->frameCount_ = frameCount; }
	int GetFrameCount() { return frameCount_; }

	void SetAnimFrameCount(int animFrameCount) { this->animFrameCount_ = animFrameCount; }
	int GetAnimFrameCount() { return animFrameCount_; }


	void SetNumChanger(int numChanger) { this->numChanger_ = numChanger; }
	int GetNumChanger() { return numChanger_; }

	void SetNumMax(int numMax) { this->numMax_ = numMax; }
	int GetNumMax() { return numMax_; }

	bool isAlive_[BEnemyMaxNum];

};