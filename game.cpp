//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "game.h"
#include "player.h"
#include "bg.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "input.h"
#include "timer.h"
#include "energy.h"
#include "level.h"
#include "fade.h"
#include "energyber.h"
#include "hpber.h"
#include "playereffect.h"
#include "boss.h"
#include "bomb.h"
#include "sound.h"
#include <time.h>
#include "inputname.h"
#include "outputname.h"
#include "pose.h"

//マクロ定義

#define SAFETY_RANGE (300 * 300) //敵がわくことのない範囲の2乗

//グローバル変数

bool g_bPause; //ポーズ状態のON/OFF

//=========================
//ゲーム画面の初期化処理
//=========================
void InitGame(void)
{
	//サウンドの再生

	PlaySound(SOUND_LABEL_BGM001); //再生したいサウンドを指定

	//+--------------------------------+
	//|  各種オブジェクトの初期化処理  |
	//+--------------------------------+

	//プレイヤーの初期化処理

	InitPlayer();

	InitPlayerEffect(); //プレイヤーエフェクト処理

	InitHpBer(); //hpバーの初期化

	//レベルの初期化

	InitLevel();

	//爆発の初期化処理

	InitExplosion();

	//球の初期化処理

	InitBullet();

	//エフェクトの初期化処理

	InitEffect();

	//敵の初期化処理

	InitBoss(); //ボス

	InitEnemy(); //敵

	InitBomb(); //ボム

	//スコアの初期化処理

	InitScore();

	//背景の初期化処理

	InitBg();

	//タイマーの初期化処理

	InitTimer();

	//エネルギーの初期化処理

	InitEnergy();

	InitEnergyBer(); //エネルギーバーの初期化

	//名前の表示

	InitOutputName();

	//ポーズの初期化

	g_bPause = false; //ポーズの状態を初期化

	InitPose();

	srand((unsigned int)time(NULL));
	
	SetEnemy(D3DXVECTOR3(1000.0f,500.0f , 0.0f), ENEMYTYPE_1); //金UFOを確定で呼び出す

}

//=========================
//ゲーム画面の終了処理
//=========================
void UninitGame(void)
{
	//+--------------------------------+
	//|   各種オブジェクトの終了処理   |
	//+--------------------------------+


	//プレイヤーの終了処理

	UninitPlayer();

	UninitPlayerEffect(); //プレイヤーエフェクトの終了処理

	UninitHpBer(); //hpバーの終了処理

	//レベルの終了処理

	UninitLevel();

	//爆発の終了処理

	UninitExplosion();

	//球の終了処理

	UninitBullet();

	//エフェクトの終了処理

	UninitEffect();

	//敵の終了処理

	UninitBoss(); //ボス

	UninitEnemy(); //敵

	UninitBomb(); //ボム

	//背景の終了処理

	UninitBg();

	//タイマーの終了処理

	UninitTimer();

	//エネルギーの終了処理

	UninitEnergy();

	UninitEnergyBer(); //エネルギーバー

	//名前の表示の終了処理

	InitOutputName();

	//ポーズの終了処理

	UninitPose();
}

//=========================
//ゲーム画面の更新処理
//=========================
void UpdateGame(void)
{
	//+--------------------------------+
	//|   各種オブジェクトの更新処理   |
	//+--------------------------------+

	//フェードの獲得処理

	FADE fade = GetFade();

	if (fade == FADE_NONE) //フェードしていない場合
	{
		//ポーズ

		if (GetKeyboardTrigger(DIK_P) || GetJoypadTrigger(JOYKEY_START) == true)
		{
			//ポーズの切り替え

			SetPose();
		}

		if (g_bPause == false)
		{
			//背景の更新処理

			UpdateBg();

			//プレイヤーの更新処理

			UpdatePlayer();

			UpdatePlayerEffect(); //プレイヤーエフェクトの更新処理

			UpdateHpBer(); //hpバーの更新処理

			//レベルの更新

			UpdateLevel();

			//敵の更新処理

			UpdateBoss(); //ボス

			UpdateBomb(); //ボム

			UpdateEnemy(); //敵

			//球の更新処理

			UpdateBullet();

			//エフェクトの更新処理

			UpdateEffect();

			//爆発の更新処理

			UpdateExplosion();

			//スコアの更新処理

			UpdateScore();

			//タイマーの更新処理

			UpdateTimer();

			//エネルギーの更新処理

			UpdateEnergy();

			UpdateEnergyBer(); //エネルギーバー

			//敵を増やす

			if (GetNumEnemy() < 5)
			{
				int nType = rand() % ENEMYTYPE_MAX; //ランダムで敵のタイプを決める

				ENEMYTYPE type = (ENEMYTYPE)nType; //タイプを代入する

				float fX = (float)(rand() % 980 + 150 + 1); //縦

				float fY = (float)(rand() % 420 + 150 + 1); //横

				bool bFlagEnemy = FlagEnemy(D3DXVECTOR3(fX, fY, 0.0f));

				if (bFlagEnemy == true)
				{ //敵が出て来ていい場合

					SetEnemy(D3DXVECTOR3(fX, fY, 0.0f), type);
				}
			}

			if (GetTimer() == 0)//ゲーム終了処理
			{ //ゲーム終了条件

				//モード設定

				SetFade(MODE_RESULT);

			}

		}
		else if (g_bPause == true) //ポーズ画面の場合
		{
			//ポーズ画面の更新処理

			UpdatePose();

		}
	}
}

//=========================
//ゲーム画面の描画処理
//=========================
void DrawGame(void)
{

	//背景の描画処理

	DrawBg();

	//エフェクトの描画処理

	DrawEffect();

	//爆発の描画処理

	DrawExplosion();

	//敵の描画処理

	DrawBoss(); //ボス

	DrawEnemy(); //敵

	DrawBomb(); //ボム

	//球の描画処理

	DrawBullet();

	//エネルギーの描画処理

	DrawEnergy();

	//プレイヤーの描画処理

	DrawPlayerEffect();

	DrawPlayer();

	//UI

	//スコアの描画処理

	DrawScore();

	//タイマーの描画処理

	DrawTimer();

	//レベルの描画処理

	DrawLevel();

	DrawEnergyBer();

	//hpバーの描画処理

	DrawHpBer();

	//名前の表示の描画処理

	DrawOutputName();

	if (g_bPause == true)
	{
		//ポーズ画面

		DrawPose();
	}
}

//=========================
//敵が出てくるかどうかの判別処理
//=========================
bool FlagEnemy(D3DXVECTOR3 posenemy)
{
	bool bFlagEnemy = false; //敵が出てくるかの判別

	//プレイヤーの取得

	Player* pPlayer = GetPlayer(); //プレイヤーの情報の先頭アドレスが代入される

	//中心座標の距離（ｘ、ｙ）

	float fDistance_x = pPlayer->pos.x - posenemy.x, //距離ｘ

		fDistance_y = pPlayer->pos.y - posenemy.y; //距離y

	//二つの中心座標の距離の2乗

	float fDistanceSquared = (fDistance_x * fDistance_x) + (fDistance_y * fDistance_y);

	if (SAFETY_RANGE < fDistanceSquared) //安全範囲より敵が離れていたら
	{//敵が出現する

		bFlagEnemy = true;
	}
	else //安全範囲内の場合
	{ //敵が出現しない
		bFlagEnemy = false;
	}

	return bFlagEnemy;
}

//=========================
//ポーズの切り替え処理
//=========================
void SetPose(void)
{
	g_bPause = g_bPause ^ 1;
}