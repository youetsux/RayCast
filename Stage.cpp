#include "Stage.h"
#include <string>
#include <vector>
#include "Engine//Model.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage")
{
	for (int j = 0;j < ZSIZE;j++) {
		for (int i = 0;i < XSIZE;i++)
		{
			SetBlock(BLOCK_TYPE::WATER, i, j);
			SetBlockHeight(i, j, 1 + rand() % 14);
		}
	}
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	std::vector<string> modelName
	{
		"BoxDefault.fbx",
		"BoxBrick.fbx",
		"BoxGrass.fbx",
		"BoxSand.fbx",
		"BoxWater.fbx"
	};
	for (int i = 0;i < modelName.size();i++)
	{
		hModel[i] = Model::Load(modelName[i]);
		assert(hModel[i] >= 0);
	}
}

void Stage::Update()
{
}

void Stage::Draw()
{
	//for (int j = 0;j < ZSIZE;j++) {
	//	for (int i = 0;i < XSIZE;i++)
	//	{
	//		for (int k = 0; k < (int)(GetT(i, j).height); k++) {
	//			int type = (int)(GetT(i, j).type);
	//			Transform t;
	//			t.position_.x = i - 15/2.0;
	//			t.position_.z = j;
	//			t.position_.y = k -15;
	//			t.scale_ = { 0.95, 0.95, 0.95 };
	//			Model::SetTransform(hModel[type], t);
	//			Model::Draw(hModel[type]);
	//		}
	//	}
	//}

	Transform t;
	t.position_.x = 5;
	t.position_.z = 5;
	t.position_.y = 0;
	t.scale_ = { 0.95, 0.95, 0.95 };
	int type = BLOCK_TYPE::WATER;
	Model::SetTransform(hModel[type], t);
	Model::Draw(hModel[type]);
	RayCastData rayData{
		{ 0.0f, 0.0f, 5.0f,0.0f },
		{ 0.0f,-1.0f, 0.0f,0.0f },
		false,
		0.0f
	};
	Model::RayCast(hModel[type], rayData);
	if (rayData.isHit)
	{
		MessageBoxA(NULL, "Hit", "Info", MB_OK);
	}

}

void Stage::Release()
{
}
