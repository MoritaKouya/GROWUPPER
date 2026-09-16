//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================

#ifndef _PLAYER_H_

#define _PLAYER_H_

#include "main.h"

//マクロ定義

#define REQUIRED_ENERGY (3) //必要エネルギー

#define MAX_HP (600)

//プレイヤーの状態

typedef enum
{
	PLAYERSTATE_NORMAL = 0, //通常状態

	PLAYERSTATE_DAMAGE, //ダメージ状態

	PLAYERSTATE_MAX
}PLAYERSTATE;

//当たり判定

typedef enum
{
	HIT_BULLET = 0,

	HIT_ENEMY,

	HIT_ENERGY
}HIT;

//プレイヤー構造体の定義

typedef struct
{
	D3DXVECTOR3 pos; //位置

	D3DXVECTOR3 move; //移動量

	D3DXVECTOR3 rot; //向き

	PLAYERSTATE state; //状態

	D3DXCOLOR EffectCol; //エフェクトの色

	int nCounterState; //状態カウンター

	int nBulletCounter; //球のカウント

	int nCntEnergy; //エネルギーの個数

	float fLength; //対角線の長さ

	//ステータス

	int nLevel; //レベル

	int nLife; //体力

	int nAttack; //攻撃力

	int nGguard; //防御力

	int nRate; //連射力

}Player;

//プロトタイプ宣言

//初期化

void InitPlayer(void); 

//終了

void UninitPlayer(void); 

//更新

void UpdatePlayer(void);

void MovePlayer(void); //移動

void RotatePlayer(void); //回転

void StatePlayer(void); //状態

void ShootBallet(void); //球の発射

//描画

void DrawPlayer(void); 

//獲得

Player *GetPlayer(void); 

//命中

void HitPlayer(HIT hit,int amount); 

#endif
