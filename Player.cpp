#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
    hModel_ = Model::Load("Model\\Oden.fbx");
    transform_.scale_ = { 0.2f, 0.2f, 0.2f };
    transform_.position_ = { 0.0f, 1.0f, 0.0f };
    //this->transform_.scale_.x = 0.2;
    //this->transform_.scale_.y = 0.2;
    //this->transform_.scale_.z = 0.2;
    //this->transform_.position_.y = 1;
}

void Player::Update()
{
	Stage* stage_ = (Stage*)FindObject("Stage");
	Enemy* enemy_ = (Enemy*)FindObject("Enemy");

	XMFLOAT3 newPos_ = transform_.position_; //移動後の位置を保存
	//float moveSpeed_ = 1.0f; //移動速度
	float moveSpeed_ = 0.1f;
	float playerSize = 0.2f; //プレイヤーのサイズ
	float rotateSpeed_ = 2.0f; //回転速度

	//カメラの回転
	if (Input::IsKey(DIK_LEFT)) //左回転
	{
		yaw_ += rotateSpeed_;
	}
	if (Input::IsKey(DIK_RIGHT)) //右回転
	{
		yaw_ -= rotateSpeed_;
	}
	if (Input::IsKey(DIK_UP)) //上回転
	{
		pitch_ += rotateSpeed_;
	}
	if (Input::IsKey(DIK_DOWN)) //下回転
	{
		pitch_ -= rotateSpeed_;
	}
	//プレイヤーの向きにカメラを合わせる
	transform_.rotate_.y = yaw_;

	//移動
	XMFLOAT3 forward = { cosf(XMConvertToRadians(yaw_)), 0, sinf(XMConvertToRadians(yaw_)) };

    if (Input::IsKey(DIK_W))
    {
	    //newPos_.z += moveSpeed_;
		newPos_.x += forward.x * moveSpeed_;
		newPos_.z += forward.z * moveSpeed_;
    }
    if (Input::IsKey(DIK_S))
    {
	    //newPos_.z -= moveSpeed_;
		newPos_.x -= forward.x * moveSpeed_;
		newPos_.z -= forward.z * moveSpeed_;
    }
    if (Input::IsKey(DIK_A))
    {
	    //newPos_.x -= moveSpeed_;
		newPos_.x -= forward.z * moveSpeed_;
		newPos_.z += forward.x * moveSpeed_;
    }
    if (Input::IsKey(DIK_D))
    {
	    //newPos_.x += moveSpeed_;
		newPos_.x += forward.z * moveSpeed_;
		newPos_.z -= forward.x * moveSpeed_;
    }

	//ジャンプ
	if (Input::IsKeyDown(DIK_SPACE) && !isJumping_)
	{
		isJumping_ = true;
        veclocityY_ = jumpPower_;
	}

    if (isJumping_)
    {
		veclocityY_ += gravity_; //重力加速度    
		transform_.position_.y += veclocityY_; //位置更新

        //着地判定
        if (stage_->CheckCollision(transform_.position_))
        {
			isJumping_ = false;
			transform_.position_.y = round(transform_.position_.y);
			veclocityY_ = 0;

			int groundHeight = stage_->GetBlockHeight(transform_.position_.x, transform_.position_.z);
			transform_.position_.y = static_cast<float>(groundHeight);
        }
    }

    //移動前に衝突判定をチェック
	if (!stage_->CheckCollision(newPos_))
	{
		transform_.position_ = newPos_; //衝突しなければ移動
	}

	XMFLOAT3 groundCheck = transform_.position_;
	groundCheck.y -= 0.1f;
	if (stage_->CheckCollision(groundCheck))
	{
		transform_.position_.y += veclocityY_;
		//isJumping_ = false;
	}
    else
    {
		transform_.position_.y -= 0.05f;
    }

	if (transform_.position_.x > 10 && transform_.position_.z >= 4)
	{
		SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
		pSM->ChangeScene(SCENE_ID_CLEAR);
	}

	if (enemy_ && enemy_->CheckCollision(newPos_, playerSize))
	{
		// 衝突時の処理（ゲームオーバーなど）
		SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
		pSM->ChangeScene(SCENE_ID_GAMEOVER);
		return; // 衝突したので移動しない
	}

	//カメラの更新
	UpdateCamera();
}

void Player::Draw()
{
    //Model::SetTransform(hModel_, transform_);
    //Model::Draw(hModel_);
}

void Player::Release()
{
}

void Player::UpdateCamera()
{
	XMFLOAT3 forward = { cosf(XMConvertToRadians(yaw_)) * cosf(XMConvertToRadians(pitch_)),
						 sinf(XMConvertToRadians(pitch_)),
						 sinf(XMConvertToRadians(yaw_)) * cosf(XMConvertToRadians(pitch_)) };
	//XMFLOAT3 forward = { cosf(XMConvertToRadians(yaw_)), 0, sinf(XMConvertToRadians(yaw_)) };

	XMFLOAT3 camerePos = transform_.position_;
	Camera::SetPosition(camerePos);
	Camera::SetTarget({ camerePos.x + forward.x, camerePos.y + forward.y, camerePos.z + forward.z });
}

