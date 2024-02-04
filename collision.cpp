#include"collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

void Collision::Init()
{
	PBullet2B = Vector2(0, 0);
	PBullet2BLength = 0;
	PBullet2W = Vector2(0, 0);
	PBullet2WLength = 0;

	WBullet2P = Vector2(0, 0);
	WBullet2PLength = 0;

	enemyDamage_ = 1;

}

void Collision::Update(Player& player, WEnemy& wEnemy, BEnemy& bEnemy)
{
	PlayerToWEnemy(player, wEnemy);
	PlayerToBEnemy(player, bEnemy);
	WEnemyToPlayer(player, wEnemy);
	BEnemyToPlayer(player, bEnemy);
}

void Collision::PlayerToWEnemy(Player& player, WEnemy& wEnemy)
{
	if (player.GetState() == 0) {
		for (int i = 0; i <= kBulletMaxNum - 1; i++) {
			for (int j = 0; j <= wEnemy.GetNumChanger() - 1; j++) {
				if (wEnemy.GetIsAlive(j) && player.playerBullet_.isShot_[i]) {
					//自機の弾と敵1の距離を求める
					PBullet2W.x = player.playerBullet_.pos_[i].x - wEnemy.GetPos(j).x;
					PBullet2W.y = player.playerBullet_.pos_[i].y - wEnemy.GetPos(j).y;
					PBullet2WLength = sqrtf(static_cast<float>(PBullet2W.x) * static_cast<float>(PBullet2W.x) + static_cast<float>(PBullet2W.y) * static_cast<float>(PBullet2W.y));

					//当たり判定
					if (PBullet2WLength <= player.playerBullet_.radius_ + wEnemy.GetOutsideRadius()) {
						if (wEnemy.GetIsAlive(j)) {
							player.playerBullet_.isShot_[i] = false;
							Novice::PlayAudio(WEnemyDamagedSound, false, 0.5f);
						}

						wEnemy.isAlive_[j] = false;
					}
				}
				
			}
		}
	}
}

void Collision::PlayerToBEnemy(Player& player, BEnemy& bEnemy)
{
	if (player.GetState() == 1) {
		for (int i = 0; i <= kBulletMaxNum - 1; i++) {
			for (int j = 0; j <= bEnemy.GetNumChanger() - 1; j++) {
				if (bEnemy.GetIsAlive(j) && player.playerBullet_.isShot_[i]) {
					//自機の弾と敵2の距離を求める
					PBullet2B.x = player.playerBullet_.pos_[i].x - bEnemy.GetPos(j).x;
					PBullet2B.y = player.playerBullet_.pos_[i].y - bEnemy.GetPos(j).y;
					PBullet2BLength = sqrtf(static_cast<float>(PBullet2B.x) * static_cast<float>(PBullet2B.x) + static_cast<float>(PBullet2B.y) * static_cast<float>(PBullet2B.y));

					//当たり判定
					if (PBullet2BLength <= player.playerBullet_.radius_ + bEnemy.GetRadius(j)) {
						if (bEnemy.GetIsAlive(j)) {
							player.playerBullet_.isShot_[i] = false;
							Novice::PlayAudio(BEnemyDamagedSound, false, 0.5f);
						}

						bEnemy.isAlive_[j] = false;
					}
				}
			}
		}
	}
}

void Collision::WEnemyToPlayer(Player& player, WEnemy& wEnemy)
{
	for (int i = 0; i <= wEnemy.GetNumChanger() - 1; i++) {

		//敵1の当たり判定
		if (player.GetIsAlive() && wEnemy.GetIsBulletShot(i) && !player.GetIsInvincible()) {
			//敵の弾と自機の距離を求める
			WBullet2P.x = wEnemy.GetBulletPos(i).x - player.GetPos().x;
			WBullet2P.y = wEnemy.GetBulletPos(i).y - player.GetPos().y;
			WBullet2PLength = sqrtf(static_cast<float>(WBullet2P.x) * static_cast<float>(WBullet2P.x) + static_cast<float>(WBullet2P.y) * static_cast<float>(WBullet2P.y));
			//敵の弾と自機の当たり判定
			if (WBullet2PLength <= wEnemy.GetBulletRadius() + player.GetOutsideRadius()) {
				wEnemy.SetIsBulletShot(i, 0);
				player.SetHp(player.GetHp() - enemyDamage_);
				player.hp_ -= 1;
				player.hpWidMove_ += 32;
				player.SetIsInvincible(true);
				Novice::PlayAudio(playerDamagedSound, false, 1);
			}
		}
	
	}


}

void Collision::BEnemyToPlayer(Player& player, BEnemy& bEnemy) {
	for (int i = 0; i <= bEnemy.GetNumChanger() - 1; i++) {

		//敵2の当たり判定
		if (player.GetIsAlive() && bEnemy.GetIsAlive(i) && !player.GetIsInvincible()) {
			//敵の弾と自機の距離を求める
			BEnemy2P.x = bEnemy.GetPos(i).x - player.GetPos().x;
			BEnemy2P.y = bEnemy.GetPos(i).y - player.GetPos().y;
			BEnemy2PLength = sqrtf(static_cast<float>(BEnemy2P.x) * static_cast<float>(BEnemy2P.x) + static_cast<float>(BEnemy2P.y) * static_cast<float>(BEnemy2P.y));
			//敵の弾と自機の当たり判定
			if (BEnemy2PLength <= bEnemy.GetRadius(i) + player.GetOutsideRadius()) {
				bEnemy.SetIsAlive(i, 0);
				player.SetHp(player.GetHp() - enemyDamage_);
				player.hp_ -= 1;
				player.hpWidMove_ += 32;
				player.SetIsInvincible(true);
				Novice::PlayAudio(playerDamagedSound, false, 1);
			}
		}

	}

}