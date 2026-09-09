//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _EFFECT_H_

#define _EFFECT_H_

#include "main.h"

//プロトタイプ宣言

void InitEffect(void); //初期化

void UninitEffect(void); //終了

void UpdateEffect(void); //更新

void DrawEffect(void); //描画

void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife); //設定

#endif