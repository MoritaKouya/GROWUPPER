//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _TIMER_H_

#define _TIMER_H_

#include "main.h"

//プロトタイプ

void InitTimer(void); //初期化

void UninitTimer(void); //終了

void UpdateTimer(void); //更新

void DrawTimer(void); //描画

void SubTimer(); //減算

int GetTimer(); //獲得

#endif
