#include"WEnemy.h"
#include"playerBullet.h"

WEnemy::WEnemy()
{
	Init();
}

WEnemy::~WEnemy()
{

}

void WEnemy::Init()
{


	for (int i = 0; i < WEnemyMaxNum; i++) {
		pos_[i] = Vector2(0, 0);
		posYSeed_[i] = rand() % 2;

		insideRadius_[i] = 0;

		speed_[i] = 5.0f;

		isAlive_[i] = true;

		respawnTimer_[i] = 120;

		bulletPos_[i] = Vector2(0, 0);
		isBulletShot_[i] = false;

		bulletMoveAngleX_[i] = 0;
		bulletMoveAngleY_[i] = 0;
		bulletTargetAngle_[i] = 0;
		bulletRotateAngle_[i] = 0;

		explodeAnimCount_[i] = 0;
	}

	outsideRadius_ = 30;

	numChanger_ = 1;

	bulletRadius_ = 10.0f;
	bulletSpeed_ = 7.0f;

	bulletCoolTime_ = 15;

	frameCount_ = 0;

	toSelf_ = Vector2(0, 0);
	toSelfLength_ = 0;

	animFrameCount_ = 0;

	explodeImage = Novice::LoadTexture("./Res/Explosion.png");

	//敵1の位置を乱数で初期化
	for (int i = 0; i <= WEnemyMaxNum - 1; i++) {
		pos_[i].x = float(rand() % 1060 + 120);

		if (posYSeed_[i] == 0) {
			pos_[i].y = 720 - outsideRadius_ * 2;
		} else {
			pos_[i].y = outsideRadius_ * 2;
		}

		for (int j = 0; j <= WEnemyMaxNum - 1; j++) {
			if (i == j) {
				continue;
			}
			toSelf_.x = pos_[i].x - pos_[j].x;
			toSelf_.y = pos_[i].y - pos_[j].y;
			toSelfLength_ = sqrtf(toSelf_.x * toSelf_.x + toSelf_.y * toSelf_.y);
			if (pos_[i].y == pos_[j].y) {
				while (toSelfLength_ <= outsideRadius_ * 2) {
					pos_[i].x = float(rand() % 1060 + 120);
					toSelf_.x = pos_[i].x - pos_[j].x;
					toSelf_.y = pos_[i].y - pos_[j].y;
					toSelfLength_ = sqrtf(toSelf_.x * toSelf_.x + toSelf_.y * toSelf_.y);
				}
			}
		}

		if (pos_[i].x >= 1280 - outsideRadius_) {
			pos_[i].x -= outsideRadius_;
		} else if (pos_[i].x <= outsideRadius_) {
			pos_[i].x += outsideRadius_;
		}
	}
}

void WEnemy::Update(Player& player) {

	Shot(player);

	animFrameCount_++;

	if (numChanger_ != WEnemyMaxNum) {
		frameCount_++;
	}

	//時間が経つと敵1の数+1
	if (numChanger_ < 2) {
		if (frameCount_ % 600 == 0) {
			numChanger_ += 1;
			frameCount_ = 0;
		}
	} else if (numChanger_ >= 2 && numChanger_ < 3) {
		if (frameCount_ % 1200 == 0) {
			numChanger_ += 1;
			frameCount_ = 0;
		}
	} else if (numChanger_ >= 3 && numChanger_ < 5) {
		if (frameCount_ % 1800 == 0) {
			numChanger_ += 1;
			frameCount_ = 0;
		}
	} else if (numChanger_ >= 5 && numChanger_ < WEnemyMaxNum) {
		if (frameCount_ % 5500 == 0) {
			numChanger_ += 1;
			frameCount_ = 0;
		}
	}


	for (int i = 0; i <= numChanger_ - 1; i++) {

		if (frameCount_ % 4 == 0) {
			if (insideRadius_[i] < 25) {
				insideRadius_[i] += 5;
			}
		}

		if (isAlive_[i]) {
			//画面外に行っちゃったら消滅する
			if (pos_[i].x > 1280 || pos_[i].x < 0) {
				isAlive_[i] = false;
			}


			if (insideRadius_[i] == 25) {

				//敵1の移動
				pos_[i].x += speed_[i];

				//画面の端に当たったら移動方向を反転する
				if (pos_[i].x >= 1280 - outsideRadius_ || pos_[i].x <= outsideRadius_) {
					speed_[i] = speed_[i] * -1;
				}

				//白い敵同士が当たったら移動方向を反転する
				for (int j = 0; j <= numChanger_ - 1; j++) {

					if (i == j || !isAlive_[i] || !isAlive_[j]) {
						continue;
					}


					toSelf_.x = pos_[i].x - pos_[j].x;
					toSelf_.y = pos_[i].y - pos_[j].y;
					toSelfLength_ = sqrtf(toSelf_.x * toSelf_.x + toSelf_.y * toSelf_.y);

					if (toSelfLength_ < outsideRadius_ * 2) {
						if (pos_[i].y == pos_[j].y) {
							speed_[i] = speed_[i] * -1;
							speed_[j] = speed_[j] * -1;
						}
					}


				}

			}
		}
	}

	Respawn();

}

void WEnemy::Shot(Player& player) {
	for (int i = 0; i <= numChanger_ - 1; i++) {
		if (isAlive_[i]) {
			if (insideRadius_[i] == 25) {

				//敵1の弾の発射角度の計算
				bulletTargetAngle_[i] = atan2(static_cast<float>(pos_[i].y) - player.GetPos().y, static_cast<float>(pos_[i].x) - player.GetPos().x);

				//敵1の攻撃
				if (isBulletShot_[i]) {
					if (posYSeed_[i] == 0) {
						bulletPos_[i].x -= static_cast<float>(bulletMoveAngleX_[i]) * bulletSpeed_;
						bulletPos_[i].y -= static_cast<float>(bulletMoveAngleY_[i]) * bulletSpeed_;
					} else if (posYSeed_[i] == 1) {
						bulletPos_[i].x -= static_cast<float>(bulletMoveAngleX_[i]) * bulletSpeed_;
						bulletPos_[i].y -= static_cast<float>(bulletMoveAngleY_[i]) * bulletSpeed_;
					}

					//敵1の弾が画面の端に当たったらもしくは敵1死んだら消滅する
					if (bulletPos_[i].y >= 720 - bulletRadius_ || bulletPos_[i].y <= bulletRadius_ || bulletPos_[i].x >= 1280 - bulletRadius_ || bulletPos_[i].x <= bulletRadius_ || !isAlive_[i]) {
						isBulletShot_[i] = false;
					}

				} else if (!isBulletShot_[i]) {
					bulletMoveAngleX_[i] = cos(bulletTargetAngle_[i]);
					bulletMoveAngleY_[i] = sin(bulletTargetAngle_[i]);

					bulletPos_[i].x = pos_[i].x;
					bulletPos_[i].y = pos_[i].y;

					bulletCoolTime_ -= 1;

					if (bulletCoolTime_ == 0) {
						isBulletShot_[i] = true;
						bulletCoolTime_ = 23;
					}
				}
			
			}

		}
	
	}
}

void WEnemy::Respawn() {
	for (int i = 0; i <= numChanger_ - 1; i++) {

		//敵1のリスポーン
		if (!isAlive_[i]) {
			respawnTimer_[i] -= 1;
			isBulletShot_[i] = false;
			insideRadius_[i] = 0;

			if (respawnTimer_[i] == 0) {
				respawnTimer_[i] = 120;
				explodeAnimCount_[i] = 0;
				posYSeed_[i] = rand() % 2;
				pos_[i].x = float(rand() % 1060 + 120);

				if (posYSeed_[i] == 0) {
					pos_[i].y = 720 - outsideRadius_ * 2;
				} else if (posYSeed_[i] == 1) {
					pos_[i].y = outsideRadius_ * 2;
				}

				for (int j = 0; j <= numChanger_ - 1; j++) {

					if (i == j) {
						continue;
					}

					toSelf_.x = pos_[i].x - pos_[j].x;
					toSelf_.y = pos_[i].y - pos_[j].y;
					toSelfLength_ = sqrtf(toSelf_.x * toSelf_.x + toSelf_.y * toSelf_.y);

					if (pos_[i].y == pos_[j].y) {
						while (toSelfLength_ <= outsideRadius_ * 2) {
							pos_[i].x = float(rand() % 1060 + 120);
							toSelf_.x = pos_[i].x - pos_[j].x;
							toSelf_.y = pos_[i].y - pos_[j].y;
							toSelfLength_ = sqrtf(toSelf_.x * toSelf_.x + toSelf_.y * toSelf_.y);
						}
					}
				}

				if (pos_[i].x >= 1280 - outsideRadius_) {
					pos_[i].x -= outsideRadius_;
				} else if (pos_[i].x <= outsideRadius_) {
					pos_[i].x += outsideRadius_;
				}

				isAlive_[i] = true;
			}
		}
	}
}

void WEnemy::Draw() {
	
	for (int i = 0; i <= numChanger_ - 1; i++) {
		if (isAlive_[i]) {

			//敵1の描画
			Novice::DrawEllipse(
				static_cast<int>(pos_[i].x), static_cast<int>(pos_[i].y),
				static_cast<int>(outsideRadius_), static_cast<int>(outsideRadius_),
				0.0f,
				0x050505FF,
				kFillModeSolid);

			Novice::DrawEllipse(
				static_cast<int>(pos_[i].x), static_cast<int>(pos_[i].y),
				static_cast<int>(insideRadius_[i]), static_cast<int>(insideRadius_[i]),
				0.0f,
				0xFFFFFFFF,
				kFillModeSolid);

		} else if (!isAlive_[i]) {
			if (explodeAnimCount_[i] <= 768) {
				Novice::DrawSpriteRect(
					static_cast<int>(pos_[i].x - outsideRadius_ * 2), static_cast<int>(pos_[i].y - outsideRadius_ * 2),
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

		//敵1の弾
		if (isBulletShot_[i]) {
			Novice::DrawEllipse(
				static_cast<int>(bulletPos_[i].x), static_cast<int>(bulletPos_[i].y),
				static_cast<int>(bulletRadius_), static_cast<int>(bulletRadius_),
				0.0f,
				0xa82532FF,
				kFillModeSolid);
		}
	}

}