#pragma once
#include"Engine/Fbx.h"
#include"Engine/Transform.h"
#include "Engine/GameObject.h"

class Stage : public GameObject
{

    struct Data
    {
        int height;
        int type;
    };

    Data table[12][12];//��ŕύX����
    
    int hModel_;
    int width;
    int height;

public:

    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize();

    //�X�V
    void Update();

    //�`��
    void Draw();

    //�J��
    void Release();

    bool CheckCollision(const XMFLOAT3& pos);

    float GetBlockHeight(int x, int z) const { return table[x][z].height; }
};