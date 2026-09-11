//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _ENERGY_H_
#define _ENERGY_H_

#include "main.h"

//マクロ定義

#define MAX_ENERGY (512) //エネルギーの最大数

#define ENERGY_SIZE (20) //エネルギーのサイズ

//敵の状態

typedef enum
{
	EnergySTATE_NORMAL = 0, //通常状態

	EnergySTATE_DAMAGE, //ダメージ状態

	EnergySTATE_MAX
}EnergySTATE;

//敵構造体の定義

typedef struct
{
	D3DXVECTOR3 pos; //位置

	D3DXVECTOR3 move; //移動

	int nEnergy; //エネルギーの量

	float fAnglePlayer; //プレイヤーとの角度

	float fSpeed; //移動速度

	bool bUse; //使用しているかどうか

}Energy;

//プロトタイプ宣言

void InitEnergy(void); //初期化

void UninitEnergy(void); //終了

void UpdateEnergy(void); //更新

float CalcAngleEnergy(D3DXVECTOR3 ppos); //プレイヤーとの角度計算

void MoveEnergy(int nCnt); //移動

void DrawEnergy(void); //描画

void SetEnergy(D3DXVECTOR3 pos, int nDropEnergy); //設定

void CollisionPlayer(Energy* pEnergy); //当たり判定

#endif