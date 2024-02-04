#pragma once
#include <Vector2.h>
#include"Novice.h"
#include<playerBullet.h>

class Player
{
private:
	Vector2 pos_;
	float insideRadius_;
	float outsideRadius_;

	float speed_;

	int baseColor_;
	int color_[2];
	int redColor_;
	int changingColor_;
	int colorChanger_;

	int frameCount_;

	int state_;

	float invincibleTimer_;

	bool isAlive_;
	bool isInvincible_;

	//Imagehandler
	int hpImage_;
	int blackAimHandler;
	int whiteAimHandler;

	//BG
	Vector2 bgPos_;
	int sceneNo_;
	int worldChangeRadius_;


public:

	//Bullet包含
	PlayerBullet playerBullet_;

	Player();
	~Player();

	void Init();

	void Update(char* keys, char* preKeys, int m_x, int m_y, bool& isGameOver);

	void Move(char* keys);

	void Shot(int m_x, int m_y);

	void WorldChange(char* keys, char* preKeys);

	void Draw(int m_x, int m_y);

	void BGDraw();



	void SetPos(Vector2 pos) { this->pos_ = pos; }
	Vector2 GetPos() { return pos_; }

	void SetInsideRadius(float insideRadius) { this->insideRadius_ = insideRadius; }
	float GetInsideRadius() { return insideRadius_; }

	void SetOutsideRadius(float outsideRadius) { this->outsideRadius_ = outsideRadius; }
	float GetOutsideRadius() { return outsideRadius_; }

	void SetSpeed(float speed) { this->speed_ = speed; }
	float GetSpeed() { return speed_; }

	void SetBaseColor(int baseColor) { this->baseColor_ = baseColor; }
	int GetBaseColor() { return baseColor_; }

	void SetChangingColor(int changingColor) { this->changingColor_ = changingColor; }
	int GetChangingColor() { return changingColor_; }

	void SetHp(int hp) { this->hp_ = hp; }
	int GetHp() { return hp_; }

	void SetState(int state) { this->state_ = state; }
	int GetState() { return state_; }

	void SetInvincibleTimer(float invincibleTimer) { this->invincibleTimer_ = invincibleTimer; }
	float GetInvincibleTimer() { return invincibleTimer_; }

	void SetIsAlive(bool isAlive) { this->isAlive_ = isAlive; }
	bool GetIsAlive() { return isAlive_; }

	void SetIsInvincible(bool isInvincible) { this->isInvincible_ = isInvincible; }
	bool GetIsInvincible() { return isInvincible_; }

	int hp_;
	int hpWidMove_;


};