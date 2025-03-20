#include "ClearScene.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"


ClearScene::ClearScene(GameObject* parent)
	:GameObject(parent, "ClearScene")
{
}

void ClearScene::Initialize()
{
	cPict_ = Image::Load("ClearScene.png");
	assert(cPict_ >= 0);
}

void ClearScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
		pSM->ChangeScene(SCENE_ID_TITLE);
	}
}

void ClearScene::Draw()
{
	Image::Draw(cPict_);
}

void ClearScene::Release()
{
}
