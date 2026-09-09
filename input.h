//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _INPUT_H_

#define _INPUT_H_

#include "main.h"

//ジョイパッドのキーの種類

typedef enum
{
	JOYKEY_UP = 0, //十字キー（上）

	JOYKEY_DOWN, //十字キー（下）

	JOYKEY_LEFT, //十字キー（左）

	JOYKEY_RIGHT, //十字キー（右）

	JOYKEY_START, //オプション（START）ボタン

	JOYKEY_RIGHT_SHOULDER = 9,

	JOYKEY_A = 12, //Aボタン（上）

	JOYKEY_B, //Bボタン（上）

	JOYKEY_X, //Xボタン（上）

	JOYKEY_Y, //Yボタン（上）
	
}JOYKEY;

//プロトタイプ宣言

HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd); //初期化

void UninitKeyboard(void); //終了

void UpdateKeyboard(void); //更新

bool GetKeyboardPress(int nKey); //プレス

bool GetKeyboardTrigger(int nKey); //トリガー

//ジョイパッド

HRESULT InitJoypad(void); //初期化

void UninitJoypad(void); //終了

void UpdateJoypad(void); //更新

bool GetJoypadPress(JOYKEY key); //ジョイパッドプレス

bool GetJoypadTrigger(JOYKEY nKey); //ジョイパッドトリガー

D3DXVECTOR3 GetLeftStick(); //ジョイパッドの左スティック

D3DXVECTOR3 GetLeftStickTrigger(); //ジョイパッドの左スティックのトリガー

bool GetRT(); //RTボタンの獲得処理

#endif