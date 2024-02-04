#pragma once
#include <Vector2.h>
#include"Novice.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
#define _USE_MATH_DEFINES
#include"player.h"

const int WEnemyMaxNum = 6;

class WEnemy {
private:
	Vector2 pos_[WEnemyMaxNum];
	int posYSeed_[WEnemyMaxNum];

	float speed_[WEnemyMaxNum];

	float insideRadius_[WEnemyMaxNum];
	float outsideRadius_;

	int numChanger_;

	int respawnTimer_[WEnemyMaxNum];

	int explodeAnimCount_[WEnemyMaxNum];

	int frameCount_;
	int animFrameCount_;

	Vector2 toSelf_;
	float toSelfLength_;

	//弾
	Vector2 bulletPos_[WEnemyMaxNum];
	float bulletRadius_;
	float bulletSpeed_;
	bool isBulletShot_[WEnemyMaxNum];
	int bulletCoolTime_;

	//弾の角度
	double bulletMoveAngleX_[WEnemyMaxNum];
	double bulletMoveAngleY_[WEnemyMaxNum];
	double bulletTargetAngle_[WEnemyMaxNum];
	double bulletRotateAngle_[WEnemyMaxNum];

	//HD
	int explodeImage;

public:

	WEnemy();
	~WEnemy();

	void Init();

	void Update(Player& player);

	void Draw();

	void Respawn();

	void Shot(Player& player);



	void SetPos(Vector2 pos, int i) { this->pos_[i] = pos; }
	Vector2 GetPos(int i) { return pos_[i]; }

	void SetInsideRadius(float insideRadius, int i) { this->insideRadius_[i] = insideRadius; }
	float GetInsideRadius(int i) { return insideRadius_[i]; }

	void SetOutsideRadius(float outsideRadius) { this->outsideRadius_ = outsideRadius; }
	float GetOutsideRadius() { return outsideRadius_; }

	void SetIsAlive(bool isAlive, int i) { this->isAlive_[i] = isAlive; }
	bool GetIsAlive(int i) { return isAlive_[i]; }

	void SetRespawnTimer(int respawnTimer, int i) { this->respawnTimer_[i] = respawnTimer; }
	int GetRespawnTimer(int i) { return respawnTimer_[i]; }

	void SetFrameCount(int frameCount) { this->frameCount_ = frameCount; }
	int GetFrameCount() { return frameCount_; }

	void SetBulletPos(Vector2 bulletPos, int i) { this->bulletPos_[i] = bulletPos; }
	Vector2 GetBulletPos(int i) { return bulletPos_[i]; }

	void SetIsBulletShot(bool isBulletShot, int i) { this->isBulletShot_[i] = isBulletShot; }
	bool GetIsBulletShot(int i) { return isBulletShot_[i]; }

	void SetBulletCoolTime(int bulletCoolTime) { this->bulletCoolTime_ = bulletCoolTime; }
	int GetBulletCoolTime() { return bulletCoolTime_; }

	void SetBulletRadius(float bulletRadius) { this->bulletRadius_ = bulletRadius; }
	float GetBulletRadius() { return bulletRadius_; }

	void SetBulletSpeed(float bulletSpeed) { this->bulletSpeed_ = bulletSpeed; }
	float GetBulletSpeed() { return bulletSpeed_; }

	void SetExplodeAnimCount(int explodeAnimCount, int i) { this->explodeAnimCount_[i] = explodeAnimCount; }
	int GetExplodeAnimCount(int i) { return explodeAnimCount_[i]; }

	void SetAnimFrameCount(int animFrameCount) { this->animFrameCount_ = animFrameCount; }
	int GetAnimFrameCount() { return animFrameCount_; }

	void SetToSelf(Vector2 toSelf) { this->toSelf_ = toSelf; }
	Vector2 GetToSelf() { return toSelf_; }

	void SetToSelfLength(float toSelfLength) { this->toSelfLength_ = toSelfLength; }
	float GetToSelfLength() { return toSelfLength_; }

	void SetSpeed(float speed, int i) { this->speed_[i] = speed; }
	float GetSpeed(int i) { return speed_[i]; }

	void SetNumChanger(int numChanger) { this->numChanger_ = numChanger; }
	int GetNumChanger() { return numChanger_; }

	bool isAlive_[WEnemyMaxNum];
};