#include "Enemy.h"
#include "Stage.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), direction_(1), moveSpeed_(0.1f)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Model\\enemy.fbx");
	transform_.scale_ = { 0.1f, 0.1f, 0.1f };
	transform_.position_ = { 0.0f, 1.0f, 0.0f };

	startPosition_ = { 11.0f, 3.0f, 3.0f };
	endPosition_ = { 0.0f, 3.0f, 3.0f };
	transform_.position_ = startPosition_;


}

void Enemy::Update()
{
	transform_.position_.x += moveSpeed_ * direction_;
	if (transform_.position_.x >= startPosition_.x)
	{
		direction_ = -1; // 左方向へ移動
	}
	else if (transform_.position_.x <= endPosition_.x)
	{
		direction_ = 1; // 右方向へ移動
	}

	Stage* stage = (Stage*)FindObject("Stage");
	if (stage->CheckCollision(transform_.position_))
	{
		direction_ *= -1; // 衝突したら逆方向に移動
	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

bool Enemy::CheckCollision(const XMFLOAT3& playerPos, float playerSize)
{
	float enemySize = 0.5f;  // 敵の当たり判定サイズ

	return (abs(transform_.position_.x - playerPos.x) < (enemySize + playerSize) &&
		abs(transform_.position_.y - playerPos.y) < (enemySize + playerSize) &&
		abs(transform_.position_.z - playerPos.z) < (enemySize + playerSize));
}
