//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//マクロ定義

#define MAX_ENEMY (64) //敵の最大数

#define ENEMY_DIAGONAL (50) //敵の中心からの対角線の長さ

//敵の状態の列挙型定義

typedef enum
{
	ENEMYSTATE_NORMAL = 0, //通常状態

	ENEMYSTATE_DAMAGE, //ダメージ状態

	ENEMYSTATE_MAX
}ENEMYSTATE;

//敵の種類の列挙型定義

typedef enum
{
	ENEMYTYPE_0 = 0, //UFO

	ENEMYTYPE_1, //金UFO

	ENEMYTYPE_2, //突撃UFO

	ENEMYTYPE_3, //追尾UFO

	ENEMYTYPE_4, //ボムUFO

	ENEMYTYPE_MAX
}ENEMYTYPE;

//敵構造体の定義

typedef struct
{
	D3DXVECTOR3 pos; //位置

	D3DXVECTOR3 move; //移動

	ENEMYTYPE type; //種類

	ENEMYSTATE state; //状態

	int nCounterState; //状態カウンター

	int nCounterAction; //行動カウンター

	int nLife; //体力

	int nAttack; //攻撃力

	int nDropEnelgy; //落とすエネルギーの量

	int nEnergy; //獲得するエネルギー

	int nScore; //獲得するスコア
	
	float fSpeed; //移動速度

	float nAnglePlayer; //プレイヤーとの角度

	bool bUse; //使用しているかどうか
}Enemy;

//プロトタイプ宣言

//初期化

void InitEnemy(void); 

//終了

void UninitEnemy(void); 

//更新

void UpdateEnemy(void); 

void StateEnemy(int nCnt); //状態

//行動

void ActionEnemy(int nCnt); //関数呼び出し用

void ActionType1(int nCnt); //行動パターン１

void ActionType2(int nCnt); //行動パターン２

void ActionType3(int nCnt); //行動パターン３

void ActionType4(int nCnt); //行動パターン４

void MoveEnemy(int nCnt);

//描画

void DrawEnemy(void); 

//設定

void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE nType);

//命中

void HitEnemy(int nCntEnemy, int nDamage); //敵の命中処理

void CollisionPlayer(Enemy* Enemy); //プレイヤーとの当たり判定

//情報の取得

Enemy* GetEnemy(void); //敵の情報の取得

float CalcAngle(D3DXVECTOR3 ppos); //プレイヤーとの角度計算

int GetNumEnemy(void); //敵の数の取得

#endif
