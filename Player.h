#pragma once
#include "Engine/GameObject.h"
//#include "Stage.h"

class Fbx;

class Player :
	public GameObject
{
    int hModel_;

	bool isJumping_;
	float jumpPower_ = 2.0f;
	float gravity_ = -0.2f;
    float veclocityY_;
    
    float yaw_ = 0.0f;
	float pitch_ = 0.0f;

	void UpdateCamera(); //�J�����̍X�V

public:
    //�R���X�g���N�^
	Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};

