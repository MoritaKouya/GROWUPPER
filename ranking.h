//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "result.h"

//マクロ定義

#define RANKING_INTERVAL (SCREEN_HEIGHT / 5) //フレームの間隔

//プロトタイプ宣言

void InitRanking(void); //初期化

void UninitRanking(void); //終了

void UpdateRanking(void); //更新

void DrawRanking(void); //描画

#endif 