#include "Stage.h"
#include "Engine/Model.h"
#include"Engine/Transform.h"
#include"Engine/Input.h"
//#include"Engine/Camera.h"
//#include"resource.h"
#include<locale>
#include<codecvt>
#include <sstream>
#include <iostream>

Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), width(12), height(12)
{
	for (int x = 0; x < width; x++)
	{
		for (int z = 0; z < height; z++)
		{
			table[x][z].height = 1;
			table[x][z].type = 0;
		}
	}
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	std::string fileName = "BoxGrass";
	//pFbx[i] = new FBX();
	std::string path =fileName + ".fbx";
	//pFbx[i]->Load(path);
	hModel_ = Model::Load(path);

	table[4][11] = { 3, 0 };
	table[5][11] = { 3, 0 };
	table[6][11] = { 3, 0 };
	table[4][10] = { 3, 0 };
	table[5][10] = { 3, 0 };
	table[6][10] = { 3, 0 };
	table[5][8] = { 3, 0 };
	table[1][2] = { 2, 0 };
	table[2][2] = { 2, 0 };
	table[1][3] = { 3, 0 };
	table[2][3] = { 3, 0 };
	table[2][4] = { 3, 0 };
	table[3][3] = { 3, 0 };
	table[4][3] = { 3, 0 };
	table[5][4] = { 3, 0 };
	table[5][3] = { 3, 0 };
	table[7][3] = { 3, 0 };
	table[9][3] = { 3, 0 };
	table[10][3] = { 3, 0 };
	table[11][3] = { 3, 0 };
	table[9][4] = { 3, 0 };
	table[10][4] = { 3, 0 };
	table[11][4] = { 3, 0 };
}

void Stage::Update()
{

}

void Stage::Draw()
{
	for (int x = 0; x < width; x++)
	{
		for (int z = 0; z < height; z++)
		{
			for (int y = 0; y < table[x][z].height; y++)
			{
				Transform trs;
				trs.position_.x = x;
				trs.position_.y = y;
				trs.position_.z = z;

				Model::SetTransform(hModel_, trs);
				Model::Draw(hModel_);
				//int type = table[x][z].type;
				//pFbx[type]->Draw(trs);
			}
		}
	}


}

void Stage::Release()
{
}

bool Stage::CheckCollision(const XMFLOAT3& pos)
{
	int x = static_cast<int>(pos.x);
	int z = static_cast<int>(pos.z);

	// 範囲外チェック
	if (x < 0 || x >= width || z < 0 || z >= height)
		return true; // 壁扱い

	// ブロックの高さを取得
	int blockHeight = table[x][z].height;

	// プレイヤーのY座標がブロックの高さ以下なら衝突
	return (pos.y < blockHeight);
	//return (pos.x < blockHeight);
}

