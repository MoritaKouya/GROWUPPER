//=============================
// 
// 2Dシューティング_プロトタイプ版
// Author森田煌也
// 
//=============================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//マクロ定義

#define MAX_SCORECOLUMN (10) //列数 

#define MAX_SCORELINES (1) //行数

#define NUM_SCOREPLACE (8) //スコアの桁数

#define SCORERANK_0 (0) //Cランク

#define SCORERANK_1 (2500000) //Bランク

#define SCORERANK_2 (10000000) //Aランク

#define SCORERANK_3 (30000000) //EXランク

#define SCORERANK_4 (55000000) //EX+ランク

//スコアランクの種類定義

typedef enum
{
	SCORE_0 = 0, //普通

	SCORE_1, //銀

	SCORE_2, //金

	SCORE_3, //虹色

	SCORE_4, //青色

	SCORE_MAX //最大

}SCORERANK;

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

SCORERANK GetScoreRank(void); //スコアランクの獲得処理

#endif