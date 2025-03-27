#pragma once
#include "Engine/GameObject.h"
class Enemy :
    public GameObject
{
    int hModel_;
	int direction_;
	float moveSpeed_;

    XMFLOAT3 startPosition_; // 移動開始
    XMFLOAT3 endPosition_;   // 移動終了
public:
    //コンストラクタ
    Enemy(GameObject* parent);

    //デストラクタ
    ~Enemy();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    bool CheckCollision(const XMFLOAT3& playerPos, float playerSize);
};

