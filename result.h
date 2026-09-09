//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "imagefighter.h"
#include "inputname.h"

//マクロ定義

#define MAX_RANKINGPLAYER (3) //ランキングに記録されるプレイヤーの数

#define NUM_RANKINGPLAYER (4) //ランキング画面にのるプレイヤーの数（１～３位とプレイヤー）

//ランキングの項目の列挙型定義

typedef enum
{
	RANKING_TEX = 0, //テクスチャ

	RANKING_NAME, //名前

	RANKING_SCORE, //スコア

	RANKING_MAX //最大数

}RANKING;

//プレイヤーのランキング情報構造体

typedef struct
{
	PLAYERCA_TEXTURE nPlayerTex; //プレイヤーのテクスチャ番号

	Name nPlayerName[MAX_NAME]; //プレイヤーの名前

	int nScore; //スコア数
}RankingPlayer;

//プロトタイプ宣言

void InitResult(void); //初期化

void UninitResult(void); //終了

void UpdateResult(void); //更新

void DrawResult(void); //描画

void LoadRanking(void); //ランキングを読み込む

void SortRanking(void); //ランキングを並び変える

void SortRankingData(int nCount, int nCount2); //ランキングのデータを入れ替える処理

void SaveRanking(void); //ランキングに書き込む

PLAYERCA_TEXTURE GetRankingTexture(int nCount); //ランキングのテクスチャの番号を獲得する変数

Name GetRankingName(int nCount,int nCount2); //ランキングの名前を獲得する変数

int GetRankingScore(int nCount); //ランキングのスコアを獲得する変数

#endif