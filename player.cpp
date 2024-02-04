#include"player.h"


Player::Player()
{
	Player::Init();
}

Player::~Player()
{


}

void Player::Init()
{
	pos_ = Vector2(640, 360);
	insideRadius_ = 25.0f;
	outsideRadius_ = 30.0f;

	speed_ = 6.9f;

	baseColor_ = 0;
	redColor_ = 0xd93f3fff;
	color_[0] = redColor_;
	color_[1] = 0;
	changingColor_ = baseColor_;
	colorChanger_ = 1;

	hp_ = 3;

	state_ = 0;

	invincibleTimer_ = 120;
	isInvincible_ = true;

	isAlive_ = true;

	frameCount_ = 0;

	bgPos_ = Vector2(0, 0);
	sceneNo_ = 0;
	worldChangeRadius_ = 0;

	//hpImage
	hpImage_ = Novice::LoadTexture("./Res/live.png");
	hpWidMove_ = 0;

	//aim
	blackAimHandler = Novice::LoadTexture("./Res/black aim.png");
	whiteAimHandler = Novice::LoadTexture("./Res/white aim.png");


	playerBullet_.Init();

}


void Player::Update(char* keys, char* preKeys, int m_x, int m_y, bool& isGameOver)
{
	frameCount_++;

	if (hp_ <= 0) {
		isAlive_ = false;
		isGameOver = true;
	}

	if (isAlive_) {

		Move(keys);
		Shot(m_x, m_y);
		WorldChange(keys, preKeys);

		//自機が画面外に行けない処理
		if (pos_.x >= 1280 - insideRadius_) {
			pos_.x = 1280 - insideRadius_;
		} else if (pos_.x <= insideRadius_) {
			pos_.x = insideRadius_;
		}

		if (pos_.y >= 720 - insideRadius_) {
			pos_.y = 720 - insideRadius_;
		} else if (pos_.y <= insideRadius_) {
			pos_.y = insideRadius_;
		}

		//色変更アニメーション
		if (state_ == 0) {
			baseColor_ = 0x050505FF;
			changingColor_ = 0xffffffff;

			if (frameCount_ % 2 == 0) {
				if (insideRadius_ < 25) {
					insideRadius_ += 1;
				}
			}
		}

		if (state_ == 1) {
			baseColor_ = 0xffffffff;
			changingColor_ = 0x050505FF;

			if (frameCount_ % 2 == 0) {
				if (insideRadius_ < 25) {
					insideRadius_ += 1;
				}
			}
		}

		//自機の無敵時間
		color_[1] = baseColor_;

		if (isInvincible_) {

			invincibleTimer_--;

			if (frameCount_ % 2 == 0) {
				colorChanger_++;
			}

			if (colorChanger_ > 1) {
				colorChanger_ = 0;
			}

			if (invincibleTimer_ <= 0) {
				invincibleTimer_ = 90;
				isInvincible_ = false;
				colorChanger_ = 1;
			}

		}

	}
}


void Player::Move(char* keys)
{

	if (keys[DIK_W]) {
		pos_.y -= speed_;
	}

	if (keys[DIK_S]) {
		pos_.y += speed_;
	}

	if (keys[DIK_D]) {
		pos_.x += speed_;
	}

	if (keys[DIK_A]) {
		pos_.x -= speed_;
	}
}


void Player::Shot(int m_x, int m_y)
{
	//自機の弾の発射角度の計算
	playerBullet_.targetAngle_ = atan2(static_cast<float>(m_y) - pos_.y, static_cast<float>(m_x) - pos_.x);

	for (int i = 0; i <= kBulletMaxNum - 1; i++) {
		if (!playerBullet_.isShot_[i]) {
			playerBullet_.moveAngleX_[i] = cos(playerBullet_.targetAngle_);
			playerBullet_.moveAngleY_[i] = sin(playerBullet_.targetAngle_);
		}


		playerBullet_.pos_[i].x += static_cast<float>(playerBullet_.moveAngleX_[i]) * playerBullet_.speed_;
		playerBullet_.pos_[i].y += static_cast<float>(playerBullet_.moveAngleY_[i]) * playerBullet_.speed_;

	}

	// マウス左ボタンを押したら弾を発射する
	if (Novice::IsPressMouse(0)) {
		for (int i = 0; i <= kBulletMaxNum - 1; i++) {
			if (!playerBullet_.isShot_[i] && playerBullet_.coolTime_ == 0) {
				playerBullet_.pos_[i] = pos_;
				playerBullet_.isShot_[i] = true;
				playerBullet_.coolTime_ = 6;
				break;
			}
		}
		//自機の弾のcooltime
		if (playerBullet_.coolTime_ > 0) {
			playerBullet_.coolTime_--;
		}
	}


	//自機の弾が画面の端に当たったら消滅する
	for (int i = 0; i <= kBulletMaxNum - 1; i++) {
		if (playerBullet_.isShot_[i]) {
			if (playerBullet_.pos_[i].y <= playerBullet_.radius_ || playerBullet_.pos_[i].y >= 720 - playerBullet_.radius_ || playerBullet_.pos_[i].x <= playerBullet_.radius_ || playerBullet_.pos_[i].x >= 1280 - playerBullet_.radius_) {
				playerBullet_.isShot_[i] = false;
			}
		}
	}
}

void Player::WorldChange(char* keys, char* preKeys)
{
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		if (insideRadius_ == 25.0f) {
			sceneNo_ += 1;
			state_ += 1;
			insideRadius_ = 0.0f;
			worldChangeRadius_ = 0;

			if (sceneNo_ >= 2) {
				sceneNo_ = 0;
			}

			if (state_ >= 2) {
				state_ = 0;
			}
		}
	}

	if (worldChangeRadius_ < 2000) {
		worldChangeRadius_ += 20;
	}
}

void Player::Draw(int m_x, int m_y)
{
	if (isAlive_) {
		//自機
		Novice::DrawEllipse(
			static_cast<int>(pos_.x),
			static_cast<int>(pos_.y),
			static_cast<int>(outsideRadius_),
			static_cast<int>(outsideRadius_),
			0.0f,
			color_[colorChanger_],
			kFillModeSolid);

		Novice::DrawEllipse(
			static_cast<int>(pos_.x),
			static_cast<int>(pos_.y),
			static_cast<int>(outsideRadius_ - 5),
			static_cast<int>(outsideRadius_ - 5),
			0.0f,
			changingColor_,
			kFillModeSolid);

		Novice::DrawEllipse(
			static_cast<int>(pos_.x),
			static_cast<int>(pos_.y),
			static_cast<int>(insideRadius_),
			static_cast<int>(insideRadius_),
			0.0f,
			baseColor_,
			kFillModeSolid);

		//自機の弾
		for (int i = 0; i <= kBulletMaxNum - 1; i++) {
			if (playerBullet_.isShot_[i]) {
				Novice::DrawEllipse(
					static_cast<int>(playerBullet_.pos_[i].x), static_cast<int>(playerBullet_.pos_[i].y),
					static_cast<int>(playerBullet_.radius_), static_cast<int>(playerBullet_.radius_),
					0.0f,
					baseColor_,
					kFillModeSolid);
			}
		}

		//HP
		Novice::DrawSpriteRect(
			static_cast<int>(pos_.x - outsideRadius_ - 17), static_cast<int>(pos_.y - outsideRadius_ - 33),
			hpWidMove_, 0,
			96, 32,
			hpImage_,
			1, 1,
			0.0f,
			0xffffffff);

		//aim画像描画
		if (state_ == 0) {
			Novice::DrawSprite(
				m_x - 7, m_y - 7,
				blackAimHandler,
				1, 1,
				0.0f,
				0xffffffff);
		}

		if (state_ == 1) {
			Novice::DrawSprite(
				m_x - 7, m_y - 7,
				whiteAimHandler,
				1, 1,
				0.0f,
				0xffffffff);
		}
	}
}

void Player::BGDraw()
{
	if (sceneNo_ == 0) {
		Novice::DrawBox(
			static_cast<int>(bgPos_.x), static_cast<int>(bgPos_.y),
			1280, 720,
			0.0f,
			0x050505FF,
			kFillModeSolid);

		Novice::DrawEllipse(
			static_cast<int>(pos_.x), static_cast<int>(pos_.y),
			worldChangeRadius_, worldChangeRadius_,
			0.0f,
			0xffffffff,
			kFillModeSolid);

	}

	if (sceneNo_ == 1) {
		Novice::DrawBox(
			static_cast<int>(bgPos_.x), static_cast<int>(bgPos_.y),
			1280, 720,
			0.0f,
			0xffffffff,
			kFillModeSolid);

		Novice::DrawEllipse(
			static_cast<int>(pos_.x), static_cast<int>(pos_.y),
			worldChangeRadius_, worldChangeRadius_,
			0.0f,
			0x050505FF,
			kFillModeSolid);

	}
}

