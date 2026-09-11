//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "result.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include <stdio.h>
#include "sound.h"
#include "scorerank.h"
#include "resultbg.h"
#include "ranking.h"
#include "scoretxt.h"

//マクロ定義

#define FILE_RANKING "Data/SAVEDATA/Ranking.csv" //ランキングを保存するテキストファイル

//リザルト画面の表示の列挙型定義

typedef enum
{
	RESULTOUTPUT_0 = 0, //スコアの文字

	RESULTOUTPUT_1, //スコアの値

	RESULTOUTPUT_2, //スコアランク

	RESULTOUTPUT_MAX //最大数

}RESULTOUTPUT;
//リザルトのモードの列挙型定義

typedef enum
{
	RESULTMODE_0 = 0, //リザルト画面

	RESULTMODE_1, //ランキング画面

	RESULTMODE_MAX
}RESULTMODE;

//グローバル変数宣言

int g_OutputResult; //リザルト画面の表示するものを代入する

int g_nResultMode; //現在のモードを代入する変数

RankingPlayer g_aRanking[NUM_RANKINGPLAYER]; //ランキングの情報構造体

//==================================
//リザルト画面の初期化処理 
//==================================
void InitResult(void)
{
	//表示するものの初期化
	
	g_OutputResult = RESULTOUTPUT_0;

	//モードの初期化

	g_nResultMode = RESULTMODE_0;

	//ランキングの情報の初期化

	int nCount,

		nCount2;

	for (nCount = 0; nCount < NUM_RANKINGPLAYER; nCount++)
	{
		g_aRanking[nCount].nPlayerTex = PLAYER_1;

		for (nCount2 = 0; nCount2 < NUM_RANKINGPLAYER; nCount2++)
		{
			g_aRanking[nCount].nPlayerName[nCount2].nName = 0;

			g_aRanking[nCount].nPlayerName[nCount2].ntype = 0;
		}

		g_aRanking[nCount].nScore = 0;
	}

	//各オブジェクトの初期化

	//リザルトの背景

	InitResultBG();

	//スコアのセット

	SetScore();

	InitScoreText(); //スコアの文字

	InitScoreRank(); //スコアランク

	//ランキング画面の初期化処理

	LoadRanking(); //ランキング画面のロード処理

	SortRanking(); //ランキングの入れ替え

	SaveRanking(); //ランキングのセーブ処理

	InitRanking(); //ランキングの初期化
}

//==================================
//リザルト画面の終了処理 
//==================================
void UninitResult(void)
{
	//各オブジェクトの終了処理

	UninitResultBG();//リザルトの背景

	UninitScore(); //スコア

	UninitScoreText(); //スコアの文字

	UninitScoreRank(); //スコアランク

	//ランキング画面の終了処理

	UninitRanking();

	//サウンドの停止

	StopSound(SOUND_LABEL_BGM001);

}

//==================================
//リザルト画面の更新処理 
//==================================
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
	{ //決定キーが押された

		FADE fade = GetFade();

		if (fade == FADE_NONE)
		{
			//サウンド

			PlaySound(SOUND_LABEL_SE_ENTER);

			switch (g_nResultMode) //リザルトモードによって分ける
			{
			case RESULTMODE_0: //リザルト画面の場合

				if (RESULTOUTPUT_MAX - 1 == g_OutputResult)
				{
					g_nResultMode = RESULTMODE_1; //ランキング画面
				}
				else
				{
					g_OutputResult++;
				}			

				break;

			case RESULTMODE_1: //リザルト画面の場合

				//モード設定

				SetFade(MODE_TITLE);

				break;
			}
		}
	}

	//各オブジェクトの更新処理

	switch (g_nResultMode) //モードで判定
	{
	case RESULTMODE_1: //ランキングモード
		
		UpdateRanking(); //ランキングの更新処理

		break;
	}
}

//==================================
//リザルト画面の描画処理 
//==================================
void DrawResult(void)
{
	//各オブジェクトの描画処理

	switch (g_nResultMode) //リザルトモードによって分ける
	{
	case RESULTMODE_0: //リザルト画面の場合

		DrawResultBG(); //リザルトの背景

		DrawScoreText(); //スコアの文字

		if (RESULTOUTPUT_1 <= g_OutputResult)
		{
			DrawScore(); //スコア
		}

		if (RESULTOUTPUT_2 <= g_OutputResult)
		{
			DrawScoreRank(); //スコアランク
		}

		break;

	case RESULTMODE_1: //ランキング画面の場合

		//ランキング画面の描画処理

		DrawRanking();

		break;
	}
	
}

//==================================
//ランキング画面のロード処理 
//==================================
void LoadRanking(void)
{
	int nCount,

		nCount2;

	//ファイルを開く

	FILE* pFile = fopen(FILE_RANKING, "r");

	if (pFile != NULL) //開けた場合
	{
		for ( nCount = 0; nCount < MAX_RANKINGPLAYER; nCount++)
		{
			if (fscanf(pFile, "%d,", &g_aRanking[nCount].nPlayerTex) != 1) break;

			for (nCount2 = 0; nCount2 < MAX_NAME; nCount2++)
			{
				if (fscanf(pFile, "%d,", &g_aRanking[nCount].nPlayerName[nCount2].nName) != 1) break;

				if (fscanf(pFile, "%d,", &g_aRanking[nCount].nPlayerName[nCount2].ntype) != 1) break;
			}

			if (fscanf(pFile, "%d,", &g_aRanking[nCount].nScore) != 1) break;
		}

		fclose(pFile);
	}

	//プレイヤーの情報を獲得

	Image image = GetFighter();

	g_aRanking[3].nPlayerTex = image.tex; //テクスチャの番号

	for (nCount = 0; nCount < MAX_NAME; nCount++)
	{
		g_aRanking[3].nPlayerName[nCount] = GetName(nCount); //名前の情報を代入する
	}

	g_aRanking[3].nScore = GetScore();
}

//==================================
//ランキングの並び変え処理 
//==================================
void SortRanking(void)
{
	if (g_aRanking[2].nScore <= g_aRanking[3].nScore)
	{//プレイヤーが３位以上の場合

		g_aRanking[2] = g_aRanking[3]; //３位のデータをプレイヤーのデータに書き換える

		//整数型の変数を宣言

		int nCount,

			nCount2;

		for (nCount = 0; nCount < MAX_RANKINGPLAYER - 1; nCount++) //要素１
		{
			for (nCount2 = nCount + 1; nCount2 < MAX_RANKINGPLAYER; nCount2++) //要素２
			{
				if (g_aRanking[nCount].nScore <= g_aRanking[nCount2].nScore) //要素２が要素１より大きい場合
				{
					//並び替え処理

					SortRankingData(nCount, nCount2);
				}
			}
		}
	}
}

//==================================
//ランキングのデータを入れ替える処理 
//==================================
void SortRankingData(int nCount, int nCount2)
{
	RankingPlayer Data = g_aRanking[nCount]; //Dataに要素１を入れる

	g_aRanking[nCount] = g_aRanking[nCount2]; //要素１を要素２の値にする

	g_aRanking[nCount2] = Data; //要素２の値をDataに入れた要素１の値にする
}

//==================================
//ランキングのセーブ処理 
//==================================
void SaveRanking(void)
{
	int nCount,

		nCount2;

	//ファイルを開く

	FILE* pFile = fopen(FILE_RANKING, "w");

	if (pFile != NULL) //開けた場合
	{
		for (nCount = 0; nCount < MAX_RANKINGPLAYER; nCount++)
		{
			fprintf(pFile, "%d,", g_aRanking[nCount].nPlayerTex);

			for (nCount2 = 0; nCount2 < MAX_NAME; nCount2++)
			{
				fprintf(pFile, "%d,", g_aRanking[nCount].nPlayerName[nCount2].nName);

				fprintf(pFile, "%d,", g_aRanking[nCount].nPlayerName[nCount2].ntype);
			}

			fprintf(pFile, "%d,\n", g_aRanking[nCount].nScore);
		}

		fclose(pFile);
	}

}

//==================================
//ランキングのテクスチャの獲得処理 
//==================================
PLAYERCA_TEXTURE GetRankingTexture(int nCount)
{
	return g_aRanking[nCount].nPlayerTex;
}

//==================================
//ランキングの名前の獲得処理 
//==================================
Name GetRankingName(int nCount, int nCount2)
{
	return g_aRanking[nCount].nPlayerName[nCount2];
}

//==================================
//ランキングのスコアの獲得処理 
//==================================
int GetRankingScore(int nCount)
{
	return g_aRanking[nCount].nScore;
}