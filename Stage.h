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

    Data table[12][12];//後で変更する
    
    int hModel_;
    int width;
    int height;

public:

    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize();

    //更新
    void Update();

    //描画
    void Draw();

    //開放
    void Release();

    bool CheckCollision(const XMFLOAT3& pos);

    float GetBlockHeight(int x, int z) const { return table[x][z].height; }
};