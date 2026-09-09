//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _Bomb_H_
#define _Bomb_H_

#include "main.h"

//球構造体の定義

typedef struct
{
	D3DXVECTOR3 pos; //位置

	int nLife; //寿命

	int nDamage; //ダメージ

	float fSize; //大きさ

	bool bUse; //使用しているかどうか
}Bomb;

//プロトタイプ宣言

//初期化

void InitBomb(void);

//終了

void UninitBomb(void);

//更新

void UpdateBomb(void);

//描画

void DrawBomb(void);

//設定

void SetBomb(D3DXVECTOR3 pos,int nDamage);

//判定

void CollisionPlayer(Bomb* pBomb);

#endif