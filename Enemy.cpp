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
		direction_ = -1; // �������ֈړ�
	}
	else if (transform_.position_.x <= endPosition_.x)
	{
		direction_ = 1; // �E�����ֈړ�
	}

	Stage* stage = (Stage*)FindObject("Stage");
	if (stage->CheckCollision(transform_.position_))
	{
		direction_ *= -1; // �Փ˂�����t�����Ɉړ�
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
	float enemySize = 0.5f;  // �G�̓����蔻��T�C�Y

	return (abs(transform_.position_.x - playerPos.x) < (enemySize + playerSize) &&
		abs(transform_.position_.y - playerPos.y) < (enemySize + playerSize) &&
		abs(transform_.position_.z - playerPos.z) < (enemySize + playerSize));
}
