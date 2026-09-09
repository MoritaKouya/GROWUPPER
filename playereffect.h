//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================PLAYEREFFECT
#ifndef _PLAYEREFFECT_H_

#define _PLAYEREFFECT_H_

#include "main.h"

//プロトタイプ宣言

void InitPlayerEffect(void); //初期化

void UninitPlayerEffect(void); //終了

void UpdatePlayerEffect(void); //更新

void DrawPlayerEffect(void); //描画

void SetPlayerEffect(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 rot, float fRadius, int nLife); //設定

#endif
