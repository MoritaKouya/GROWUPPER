//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _IMAGEFIGHTER_H_
#define _IMAGEFIGHTER_H_

#include "main.h"

//プレイヤーテクスチャの種類列挙型定義

typedef enum
{
	PLAYER_1 = 0, //赤

	PLAYER_2, //青

	PLAYER_3, //緑

	PLAYER_4, //黄色

	PLAYER_5, //橙

	PLAYER_6, //紫

	PLAYER_7, //水色

	Player_8, //グレー

	PLAYER_MAX //色の最大数

}PLAYERCA_TEXTURE;

//イメージの情報構造体

typedef struct
{
	PLAYERCA_TEXTURE tex;

	D3DXCOLOR col;
}Image;

//プロトタイプ宣言

 //初期化

void Initimagefighter(void);

 //終了

void Uninitimagefighter(void);

//更新

void Updateimagefighter(void); 

void LoadTexture(int nSelect); //ロード

//描画

void Drawimagefighter(void);

//取得

Image GetFighter(void);

#endif 