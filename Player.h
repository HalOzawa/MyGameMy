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

	void UpdateCamera(); //カメラの更新

public:
    //コンストラクタ
	Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};

