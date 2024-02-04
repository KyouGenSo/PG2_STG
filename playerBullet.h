#pragma once
#include <Vector2.h>
#include<math.h>
#define _USE_MATH_DEFINES

const int kBulletMaxNum = 10;

class PlayerBullet
{
public:

	Vector2 pos_[kBulletMaxNum];

	float radius_;

	float speed_;

	bool isShot_[kBulletMaxNum];

	int coolTime_;

	double moveAngleX_[kBulletMaxNum];
	double moveAngleY_[kBulletMaxNum];
	double targetAngle_;

public:

	void Init();

	void GetIsShot(bool isShot, int i) { isShot_[i] = isShot; }
	bool SetIsShot(int i) { return isShot_[i]; }

	void SetPos(Vector2 pos, int i) { pos_[i] = pos; }
	Vector2 GetPos(int i) { return pos_[i]; }

	void SetCoolTime(int coolTime) { coolTime_ = coolTime; }
	int GetCoolTime() { return coolTime_; }

	void SetRadius(float radius) { radius_ = radius; }
	float GetRadius() { return radius_; }

	void SetSpeed(float speed) { speed_ = speed; }
	float GetSpeed() { return speed_; }

	void SetMoveAngleX(double moveAngleX, int i) { moveAngleX_[i] = moveAngleX; }
	double GetMoveAngleX(int i) { return moveAngleX_[i]; }

	void SetMoveAngleY(double moveAngleY, int i) { moveAngleY_[i] = moveAngleY; }
	double GetMoveAngleY(int i) { return moveAngleY_[i]; }

	void SetTargetAngle(double targetAngle) { targetAngle_ = targetAngle; }
	double GetTargetAngle() { return targetAngle_; }

};
