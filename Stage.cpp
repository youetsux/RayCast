#include "Stage.h"
#include <string>
#include <vector>
#include "Engine//Model.h"
#include "resource.h"

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

BOOL Stage::localProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {


	switch (message) {
	case WM_COMMAND: //コントロールの操作
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hWnd, IDOK);
			return TRUE;
		case IDCANCEL:
			EndDialog(hWnd, IDCANCEL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

BOOL Stage::manuProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{ //IDC_COMBO1
	switch (message) {
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(hWnd, IDC_RADIO5), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"デフォルト");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"レンガ");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"草地");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"砂地");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"水場");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_SETCURSEL, 0, 0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_RADIO5:
			mode_ = 0;//上げ
			return TRUE;
		case IDC_RADIO6:
			mode_ = 1;//下げ
			return TRUE;
		case IDC_RADIO7:
			mode_ = 2;//種類変更
			return TRUE;
		case IDC_COMBO1:
			select_ = (int)SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_GETCURSEL, 0, 0);
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}

