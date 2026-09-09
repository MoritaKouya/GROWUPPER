//=============================
// 
// 2Dシューティング_プロトタイプ版
// Author森田煌也
// 
//=============================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//スコアのテクスチャの列挙型定義

typedef enum
{
	SCORE_0 = 0, //普通

	SCORE_1, //銀

	SCORE_2, //金

	SCORE_3, //虹色

	SCORE_MAX //最大

}SCORETEXTURE;

//プロトタイプ

//初期化

void InitScore(void); 

//更新

void UninitScore(void); 

//更新

void UpdateScore(void); 

//描画

void DrawScore(void); 

 //設定

void SetScore();

//加算

void AddScore(int nValue); 

//獲得

int GetScore(void); 

SCORETEXTURE GetScoreRank(void); //スコアランクの獲得処理

#endif