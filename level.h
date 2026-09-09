//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _LEVEL_H_

#define _LEVEL_H_

#include "main.h"

//プロトタイプ

void InitLevel(void); //初期化

void UninitLevel(void); //終了

void UpdateLevel(void); //更新

void DrawLevel(void); //描画

void LevelUpp(int* nLevel); //加算

int LevelGetDigits(int nDigits); //桁数の獲得

//TEXT

void InitLevelText(void); //初期化

void UninitLevelText(void); //終了

void DrawLevelText(void); //描画

#endif