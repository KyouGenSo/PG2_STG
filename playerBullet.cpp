#include"playerBullet.h"

void PlayerBullet::Init()
{
	for (int i = 0; i < kBulletMaxNum; i++) {
		pos_[i] = Vector2(0, 0);
		isShot_[i] = false;

		moveAngleX_[i] = 0;
		moveAngleY_[i] = 0;

	}

	radius_ = 10.0f;

	speed_ = 48.0f;

	coolTime_ = 6;

	targetAngle_ = 0;

}
