//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"

//マクロ定義

#define BOSS_DIAGONAL (150) //敵の中心からの対角線の長さ

//敵の状態

typedef enum
{
	BossSTATE_NORMAL = 0, //通常状態

	BossSTATE_DAMAGE, //ダメージ状態

	BossSTATE_MAX
}BOSSSTATE;

//敵構造体の定義

typedef struct
{
	D3DXVECTOR3 pos; //位置

	D3DXVECTOR3 move; //移動

	BOSSSTATE state; //状態

	int nCounterState; //状態カウンター

	int nCounterAction; //行動カウンター

	int nDamage; //ダメージ量

	float fSpeed; //スピード

	float fMoveAngle; //角度

}BOSS;

//プロトタイプ宣言

//初期化

void InitBoss(void);

//終了

void UninitBoss(void);

//更新

void UpdateBoss(void);

void StateBoss(void); //状態

//ボスの動き

void ActionBoss(void);

void ActionBossPattern1(); //行動パターン１

void ActionBossPattern2(); //行動パターン２

void MoveBoss(void); //ボスの移動

void CallEnemy1(void); //敵の呼び出し（突撃UFO）

//描画

void DrawBoss(void); 

//取得

BOSS* GetBoss(void);

float CalcAnglePlayer(void);

float CalcAngleCenter(void);

//命中

void HitBoss(int nDamage); 

//プレイヤーとの当たり判定

void CollisionPlayer(BOSS* Boss);

#endif
