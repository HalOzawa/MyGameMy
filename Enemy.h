#pragma once
#include "Engine/GameObject.h"
class Enemy :
    public GameObject
{
    int hModel_;
	int direction_;
	float moveSpeed_;

    XMFLOAT3 startPosition_; // �ړ��J�n
    XMFLOAT3 endPosition_;   // �ړ��I��
public:
    //�R���X�g���N�^
    Enemy(GameObject* parent);

    //�f�X�g���N�^
    ~Enemy();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    bool CheckCollision(const XMFLOAT3& playerPos, float playerSize);
};

