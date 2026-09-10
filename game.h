//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//プロトタイプ宣言

//初期化

void InitGame(void); 

//終了

void UninitGame(void);

//更新

void UpdateGame(void);

//描画

void DrawGame(void); 

//敵が出てくるかどうかを判別する処理

bool FlagEnemy(D3DXVECTOR3 posenemy);

//ポーズの切り替え処理

void SetPause(void);

#endif 