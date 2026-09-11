//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _STARTCOUNTDOWN_H_
#define _STARTCOUNTDOWN_H_

#include "main.h"

//プロトタイプ宣言

void InitStartCountDown(void); //初期化

void UninitStartCountDown(void); //終了

void UpdateStartCountDown(void); //更新

void DrawStartCountDown(void); //描画

int GetStartCounter(void); //スタート画面のカウンターの取得処理

#endif 