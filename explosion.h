//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _EXPLOSION_H_

#define _EXPLOSION_H_

#include "main.h"

//プロトタイプ宣言

void InitExplosion(void); //初期化

void UninitExplosion(void); //終了

void UpdateExplosion(void); //更新

void DrawExplosion(void); //描画

void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col); //設定

#endif