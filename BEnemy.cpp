#include"BEnemy.h"

BEnemy::BEnemy()
{
	Init();
}

BEnemy::~BEnemy()
{

}

void BEnemy::Init()
{
	for (int i = 0; i < BEnemyMaxNum; i++) {
		pos_[i] = Vector2(0, 0);
		isAlive_[i] = true;
		respawnTimer_[i] = 120;
		explodeAnimCount_[i] = 0;
		posXSeed_[i] = 0;
		radius_[i] = 30;
	}

	speed_ = 4.0f;

	frameCount_ = 0;
	animFrameCount_ = 0;

	numChanger_ = 0;

	toPlayer_ = Vector2(0, 0);
	toPlayerLength_ = 0;

	explodeImage = Novice::LoadTexture("./Res/Explosion.png");


	for (int i = 0; i <= BEnemyMaxNum - 1; i++) {
		pos_[i].y = float(rand() % 661 + radius_[i] * 2);
		if (posXSeed_[i] == 0) {
			pos_[i].x = -radius_[i] * 2;
		} else if (posXSeed_[i] == 1) {
			pos_[i].x = 1280 + radius_[i] * 2;
		}
	}

}

void BEnemy::Update(Player& player)
{
	if (numChanger_ != BEnemyMaxNum) {
		frameCount_++;
	}

	animFrameCount_++;

	//時間が経つと敵2の数+1
	if (numChanger_ < 5) {
		if (frameCount_ % 600 == 0) {
			numChanger_ += 1;
			frameCount_ = 0;
		}
	} else if (numChanger_ >= 5 && numChanger_ < 10) {
		if (frameCount_ % 900 == 0) {
			numChanger_ += 1;
			frameCount_ = 0;
		}
	} else if (numChanger_ >= 10 && numChanger_ < numMax_) {
		if (frameCount_ % 1200 == 0) {
			numChanger_ += 1;
			frameCount_ = 0;
		}
	}

	for (int i = 0; i <= numChanger_ - 1; i++) {

		//敵2が生きている時の処理
		if (isAlive_[i]) {

			//敵2の移動角度の計算
			targetAngle_[i] = atan2(static_cast<float>(pos_[i].y) - player.GetPos().y, static_cast<float>(pos_[i].x) - player.GetPos().x);

			moveAngleX_[i] = cos(targetAngle_[i]);
			moveAngleY_[i] = sin(targetAngle_[i]);

			//敵2の移動
			pos_[i].x -= static_cast<float>(moveAngleX_[i]) * speed_;
			pos_[i].y -= static_cast<float>(moveAngleY_[i]) * speed_;

		}

		//敵2のリスポーン
		if (!isAlive_[i]) {

			respawnTimer_[i] -= 1;

			if (respawnTimer_[i] == 0) {
				respawnTimer_[i] = 120;
				explodeAnimCount_[i] = 0;
				posXSeed_[i] = rand() % 2;
				pos_[i].y = float(rand() % 661 + radius_[i] * 2);

				if (posXSeed_[i] == 0) {
					pos_[i].x = -radius_[i] * 2;
				} else if (posXSeed_[i] == 1) {
					pos_[i].x = 1280 + radius_[i] * 2;
				}

				isAlive_[i] = true;

			}
		}


	}
}

void BEnemy::Draw()
{
	for (int i = 0; i <= numChanger_ - 1; i++) {
		if (isAlive_[i]) {
			Novice::DrawEllipse(
				static_cast<int>(pos_[i].x), static_cast<int>(pos_[i].y),
				static_cast<int>(radius_[i]), static_cast<int>(radius_[i]),
				0.0f,
				0xFFFFFFFF,
				kFillModeSolid);

			Novice::DrawEllipse(
				static_cast<int>(pos_[i].x), static_cast<int>(pos_[i].y),
				static_cast<int>(radius_[i] - 5), static_cast<int>(radius_[i] - 5),
				0.0f,
				0x050505FF,
				kFillModeSolid);

		} else if (!isAlive_[i]) {
			if (explodeAnimCount_[i] <= 768) {
				Novice::DrawSpriteRect(
					static_cast<int>(pos_[i].x - radius_[i] * 2), static_cast<int>(pos_[i].y - radius_[i] * 2),
					explodeAnimCount_[i], 0,
					128, 128,
					explodeImage,
					((float)128 / (float)768), 1,
					0,
					0xFFFFFFFF
				);

				if (animFrameCount_ % 4 == 0) {
					explodeAnimCount_[i] += 128;
				}
			}
		}
	}
}

