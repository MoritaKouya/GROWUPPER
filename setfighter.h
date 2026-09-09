//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _SETFIGHTER_H_
#define _SETFIGHTER_H_

#include "main.h"

//設定のモードの列挙型定義

typedef enum
{
	SETMODE_0 = 0, //色選択

	SETMODE_1, //名前入力

	SETMODE_MAX
}SETMODE;

//プロトタイプ宣言

void InitSetFighter(void); //初期化

void UninitSetFighter(void); //終了

void UpdateSetFighter(void); //更新

void DrawSetFighter(void); //描画

SETMODE GetSetMode(void);

#endif 