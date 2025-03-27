#include "OverScene.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"

OverScene::OverScene(GameObject* parent)
	:GameObject(parent, "OverScene")
{
}

void OverScene::Initialize()
{
	gPict_ = Image::Load("OverScene.png");
	assert(gPict_ >= 0);
}

void OverScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
		pSM->ChangeScene(SCENE_ID_TITLE);
	}
}

void OverScene::Draw()
{
	Image::Draw(gPict_);
}

void OverScene::Release()
{
}
