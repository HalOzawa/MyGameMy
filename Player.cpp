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

	XMFLOAT3 newPos_ = transform_.position_; //�ړ���̈ʒu��ۑ�
	//float moveSpeed_ = 1.0f; //�ړ����x
	float moveSpeed_ = 0.1f;
	float playerSize = 0.2f; //�v���C���[�̃T�C�Y
	float rotateSpeed_ = 2.0f; //��]���x

	//�J�����̉�]
	if (Input::IsKey(DIK_LEFT)) //����]
	{
		yaw_ += rotateSpeed_;
	}
	if (Input::IsKey(DIK_RIGHT)) //�E��]
	{
		yaw_ -= rotateSpeed_;
	}
	if (Input::IsKey(DIK_UP)) //���]
	{
		pitch_ += rotateSpeed_;
	}
	if (Input::IsKey(DIK_DOWN)) //����]
	{
		pitch_ -= rotateSpeed_;
	}
	//�v���C���[�̌����ɃJ���������킹��
	transform_.rotate_.y = yaw_;

	//�ړ�
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

	//�W�����v
	if (Input::IsKeyDown(DIK_SPACE) && !isJumping_)
	{
		isJumping_ = true;
        veclocityY_ = jumpPower_;
	}

    if (isJumping_)
    {
		veclocityY_ += gravity_; //�d�͉����x    
		transform_.position_.y += veclocityY_; //�ʒu�X�V

        //���n����
        if (stage_->CheckCollision(transform_.position_))
        {
			isJumping_ = false;
			transform_.position_.y = round(transform_.position_.y);
			veclocityY_ = 0;

			int groundHeight = stage_->GetBlockHeight(transform_.position_.x, transform_.position_.z);
			transform_.position_.y = static_cast<float>(groundHeight);
        }
    }

    //�ړ��O�ɏՓ˔�����`�F�b�N
	if (!stage_->CheckCollision(newPos_))
	{
		transform_.position_ = newPos_; //�Փ˂��Ȃ���Έړ�
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
		// �Փˎ��̏����i�Q�[���I�[�o�[�Ȃǁj
		SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
		pSM->ChangeScene(SCENE_ID_GAMEOVER);
		return; // �Փ˂����̂ňړ����Ȃ�
	}

	//�J�����̍X�V
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

