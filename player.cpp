//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "player.h"

#include "input.h"

#include "bullet.h"

#include "level.h"

#include "energyber.h"

#include "fade.h"

#include "hpber.h"

#include "playereffect.h"

#include "imagefighter.h"

#include "sound.h"

#include "damagescreen.h"

//マクロ定義

#define MAX_ANIM (1) //アニメーションの最大数

#define MAX_COLUMN (1) //列数 

#define MAX_LINES (1) //行数

#define PLAYER_SPEED (1) //プレイヤーの速度

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL; //頂点バッファへのポインタ

int g_nCountterAnimPlayer; //アニメーションカウンター

int g_nPatternAnimPlayer; //アニメーションパターンNo,

float g_fLengthPlayer; //対角線の長さ

float g_fAnglePlayer; //対角線の角度

Player g_player; //プレイヤーの情報

bool g_rot; //trueで左falseで右

D3DXVECTOR3 g_stick; //スティックの情報を代入する処理

const char* g_aPlayerTexture_Path[PLAYER_MAX] =
{
	"Data/TEXTURE/PLAYER/player001.png",

	"Data/TEXTURE/PLAYER/player002.png",

	"Data/TEXTURE/PLAYER/player003.png",

	"Data/TEXTURE/PLAYER/player004.png",

	"Data/TEXTURE/PLAYER/player005.png",

	"Data/TEXTURE/PLAYER/player006.png",

	"Data/TEXTURE/PLAYER/player007.png",

	"Data/TEXTURE/PLAYER/player008.png",
}; //テクスチャのアドレスの構造体

//==================================
// プレイヤーの初期化処理
//==================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	Image image = GetFighter();

	//テクスチャの読み込み

	PLAYERCA_TEXTURE nTex;

	nTex = image.tex; //テクスチャの種類を代入

	D3DXCreateTextureFromFile(pDevice,

		g_aPlayerTexture_Path[nTex], //テクスチャのファイル名

		&g_pTexturePlayer);

	g_nCountterAnimPlayer = 0; //カウンターを初期化する

	g_nPatternAnimPlayer = 0; //パターンNo,を初期化する

	g_player.pos = D3DXVECTOR3(400.0f, 100.0f, 0.0f);

	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きを初期化する（ｚ値を使用）

	g_player.EffectCol = image.col;

	g_player.state = PLAYERSTATE_NORMAL; //状態

	g_player.nCounterState = 0; //状態カウンター

	g_player.nBulletCounter = 0; //球のカウンター

	g_player.nCntEnergy = 0; //エネルギー

	g_player.nLevel = 1; //レベル

	g_player.nLife = MAX_HP; //体力

	g_player.nAttack = 1; //攻撃力

	g_player.nGguard = 1; //防御力

	g_player.nRate = 1; //連射力

	//向きの初期化

	g_rot = false;

	//対角線の長さを算出する

	g_fLengthPlayer = sqrtf(100 * 100 + 100 * 100) * 0.5f;

	//対角線の角度を算出する

	g_fAnglePlayer = atan2f(100, 100);

	//スティックを初期化

	g_stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
								                       //sizeof(VERTEX_2D)*必要な頂点数

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffPlayer,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (g_fAnglePlayer + D3DX_PI)) * g_fLengthPlayer;

	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (g_fAnglePlayer + D3DX_PI)) * g_fLengthPlayer;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-g_fAnglePlayer + D3DX_PI)) * g_fLengthPlayer;

	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-g_fAnglePlayer + D3DX_PI)) * g_fLengthPlayer;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + -g_fAnglePlayer) * g_fLengthPlayer;

	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + -g_fAnglePlayer) * g_fLengthPlayer;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + g_fAnglePlayer) * g_fLengthPlayer;

	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + g_fAnglePlayer) * g_fLengthPlayer;

	pVtx[3].pos.z = 0.0f;

	//rhwの設定 1.0f固定

	pVtx[0].rhw = 1.0f;

	pVtx[1].rhw = 1.0f;

	pVtx[2].rhw = 1.0f;

	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定

	pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_nPatternAnimPlayer % MAX_COLUMN), (1.0f / MAX_LINES) * (g_nPatternAnimPlayer / MAX_COLUMN));

	pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_nPatternAnimPlayer % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_nPatternAnimPlayer / MAX_COLUMN));

	pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_nPatternAnimPlayer % MAX_COLUMN), (1.0f / MAX_LINES) * (g_nPatternAnimPlayer / MAX_COLUMN) + (1.0f / MAX_LINES));

	pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_nPatternAnimPlayer % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_nPatternAnimPlayer / MAX_COLUMN) + (1.0f / MAX_LINES));

	//頂点バッファをアンロックする

	g_pVtxBuffPlayer->Unlock();
}

//==================================
// プレイヤーの終了処理
//==================================
void UninitPlayer(void)
{
	//テクスチャの破棄

	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();

		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();

		g_pVtxBuffPlayer = NULL;
	}
}

//==================================
// プレイヤーの更新処理
//==================================
void UpdatePlayer(void)
{
	//移動

	MovePlayer();

	//回転

	RotatePlayer();

	//状態

	StatePlayer();

	//球の発射処理

	ShootBallet();
	
	//プレイヤーのエフェクト

	SetPlayerEffect(g_player.pos, g_player.EffectCol,g_player.rot, 100, 120);
}
//=========================
// プレイヤーの移動処理
//=========================
void MovePlayer(void)
{

	//スティックの入力を獲得

	g_stick = GetLeftStick();

	if (g_stick.x != 0 || g_stick.y != 0) //入力されている場合
	{
		//移動量の更新
	
		g_player.move.x += g_stick.x * PLAYER_SPEED;
		
		g_player.move.y += -g_stick.y * PLAYER_SPEED;
		
	}
	else
	{
		if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true) //Aキーが押された場合
		{
			if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true) //左上移動の場合
			{
				//移動量を更新

				g_player.move.x += sinf(-D3DX_PI * 0.75f) * PLAYER_SPEED;

				g_player.move.y += cosf(-D3DX_PI * 0.75f) * PLAYER_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true) //左下移動の場合
			{
				//移動量を更新

				g_player.move.x += sinf(-D3DX_PI * 0.25f) * PLAYER_SPEED; //上に進む

				g_player.move.y += cosf(-D3DX_PI * 0.25f) * PLAYER_SPEED;
			}
			else //左移動
			{
				//移動量を更新

				if (GetKeyboardPress(DIK_D) != true || GetJoypadPress(JOYKEY_RIGHT) != true) //Dキーが押されていない場合
				{
					g_player.move.x += sinf(-D3DX_PI * 0.5f) * PLAYER_SPEED; //左にすすむ
				}
			}
		}
		else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT) == true) //Dキーが押された場合
		{
			if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true) //右上移動の場合
			{
				//移動量を更新

				g_player.move.x += sinf(D3DX_PI * 0.75f) * PLAYER_SPEED;

				g_player.move.y += cosf(D3DX_PI * 0.75f) * PLAYER_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true) //右下移動の場合
			{
				//移動量を更新

				g_player.move.x += sinf(D3DX_PI * 0.25f) * PLAYER_SPEED;

				g_player.move.y += cosf(D3DX_PI * 0.25f) * PLAYER_SPEED;
			}
			else //右移動の場合
			{
				//移動量を更新

				g_player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true) //Wキーが押された場合
		{

			if (GetKeyboardPress(DIK_S) != true || GetJoypadPress(JOYKEY_DOWN) == true) //Sキーが押されていない場合
			{
				//移動量を更新

				g_player.move.y += cosf(-D3DX_PI) * PLAYER_SPEED; //上にすすむ
			}
		}
		else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true) //Sキーが押された場合
		{
			//移動量を更新

			g_player.move.y += cosf(0) * PLAYER_SPEED; //下にすすむ	
		}
	}

	//位置を更新

	g_player.pos.x += g_player.move.x;

	g_player.pos.y += g_player.move.y;

	//壁に当たった時

	if (g_player.pos.x - PLAYER_DIAGONAL < 0) //一番左に当たった場合
	{
		g_player.pos.x = PLAYER_DIAGONAL; //g_player.posを一番左にする
	}
	else if (SCREEN_WIDTH < g_player.pos.x + PLAYER_DIAGONAL) //一番右に当たった場合
	{
		g_player.pos.x = SCREEN_WIDTH - PLAYER_DIAGONAL; //g_player.posを一番右にする
	}

	if (g_player.pos.y - PLAYER_DIAGONAL < 0) //一番上にあたった場合
	{
		g_player.pos.y = PLAYER_DIAGONAL; //g_player.posを一番上にする
	}
	else if (SCREEN_HEIGHT < g_player.pos.y + PLAYER_DIAGONAL) //一番下にあたった場合
	{
		g_player.pos.y = SCREEN_HEIGHT - PLAYER_DIAGONAL; //g_player.posを一番下にする
	}

	//移動量の更新

	g_player.move.x += (0.0f - g_player.move.x) * 0.1f;

	g_player.move.y += (0.0f - g_player.move.y) * 0.1f;

	//頂点バッファをロックし、頂点情報へのポインタを取得

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (g_fAnglePlayer + D3DX_PI)) * g_fLengthPlayer;

	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (g_fAnglePlayer + D3DX_PI)) * g_fLengthPlayer;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-g_fAnglePlayer + D3DX_PI)) * g_fLengthPlayer;

	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-g_fAnglePlayer + D3DX_PI)) * g_fLengthPlayer;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + -g_fAnglePlayer) * g_fLengthPlayer;

	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + -g_fAnglePlayer) * g_fLengthPlayer;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + g_fAnglePlayer) * g_fLengthPlayer;

	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + g_fAnglePlayer) * g_fLengthPlayer;

	pVtx[3].pos.z = 0.0f;

	//頂点バッファをアンロックする

	g_pVtxBuffPlayer->Unlock();
}
//=========================
// プレイヤーの回転処理
//=========================
void RotatePlayer(void)
{
	//頂点バッファをロックし、頂点情報へのポインタを取得

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_J) == true || GetJoypadTrigger(JOYKEY_X) == true)
	{
		if (g_rot == false)
		{
			//向きを更新（ｚ値を回転させる）

			g_player.rot.z = D3DX_PI;

			g_rot = true;

			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);

			pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);

			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}
		else
		{
			g_rot = false;

			//向きを更新（ｚ値を回転させる）

			g_player.rot.z = 0;

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

	}
	
	//頂点バッファをアンロックする

	g_pVtxBuffPlayer->Unlock();
}
//=========================
// プレイヤーの状態処理
//=========================
void StatePlayer(void)
{
	VERTEX_2D* pVtx; //頂点情報へのポインタ

	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_player.state) //プレイヤーの状態
	{
	case PLAYERSTATE_NORMAL: //通常

		break;

	case PLAYERSTATE_DAMAGE: //ダメージ

		g_player.nCounterState--; //カウンターステートを減らす

		if (g_player.nCounterState <= 0) //カウンターステートが0になった
		{
			g_player.state = PLAYERSTATE_NORMAL; //プレイヤーの状態を通常にする

			//頂点カラーの設定

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		break;
	}

	//頂点バッファをアンロックする

	g_pVtxBuffPlayer->Unlock();
}
//=========================
// 球の発射処理
//=========================
void ShootBallet(void)
{
	g_player.nBulletCounter--; //球のカウンターを減らす

	if (g_player.nBulletCounter <= 0) //カウンターがゼロ以下の場合
	{
		if (GetKeyboardPress(DIK_SPACE) == true || GetRT() == true) //球の発射
		{ //スペースキーが押された

			//球の設定

			SetBullet(D3DXVECTOR3(g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI * 0.5f)) * 50.0f,

				g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI * 0.5f)) * 50.0f,

				0.0f)

				, D3DXVECTOR3(sinf(g_player.rot.z + (D3DX_PI * 0.5f)) * 20.0f, cosf(g_player.rot.z + (D3DX_PI * 0.5f)) * 20.0f, 0.0f),

				100

				,g_player.nAttack

				,BULLETTYPE_PLAYER);

			g_player.nBulletCounter = 30 / g_player.nRate;
		}
	}
}

//==================================
// プレイヤーの描画処理
//==================================
void DrawPlayer(void)
{

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));
	                          //頂点バッファのポインタ  頂点情報構造体のサイズ
	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	
	pDevice->SetTexture(0, g_pTexturePlayer);

	//ポリゴンの描画
	                                          //描画する最初の頂点インデックス
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                                                 //描画するプリミティブ数
} 

//===================
// プレイヤーの取得処理
//===================
Player* GetPlayer(void)
{
	return &g_player; //敵の情報の先頭アドレスを返す
}

//===================
// プレイヤーヒット処理
//===================
void HitPlayer(HIT hit, int amount)
{
	switch (hit)
	{
	case HIT_BULLET: //球の場合

	case HIT_ENEMY: //敵の場合

		if (g_player.nCounterState == 0)
		{
			//サウンド

			PlaySound(SOUND_LABEL_SE_PLAYERHIT);

			//ダメージスクリーン

			SetDamageScreen();

			//プレイヤーのライフを減らす

			g_player.nLife -= (amount / g_player.nGguard);

			//HPバーを減らす

			ModifyHpBer(g_player.nLife);

			if (g_player.nLife <= 0) //プレイヤーの体力がなくなった
			{
				//リザルト画面

				SetFade(MODE_RESULT);
			}
			else
			{
				//カウンターを加算

				g_player.nCounterState = 75;

				VERTEX_2D* pVtx;

				g_player.state = PLAYERSTATE_DAMAGE;

				//頂点バッファをロックし、頂点データへのポインタを取得

				g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

				//頂点カラーの設定

				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				g_pVtxBuffPlayer->Unlock();
			}
		}

		break;

	case HIT_ENERGY: //エネルギーの場合

		PlaySound(SOUND_LABEL_SE_ENERGY);

		g_player.nCntEnergy += amount; //エネルギーを加算

		if (REQUIRED_ENERGY * g_player.nLevel <= g_player.nCntEnergy)
		{ //エネルギーがレベルアップに必要なエネルギー量を超えた場合

			PlaySound(SOUND_LABEL_SE_LEVELUP);

			g_player.nCntEnergy -= (REQUIRED_ENERGY * g_player.nLevel); //エネルギーをリセット

			LevelUpp(&g_player.nLevel); //レベル

			g_player.nAttack += g_player.nLevel;

			g_player.nGguard += 1;

			if (g_player.nLevel % 5 == 0)
			{
				g_player.nRate += 1;
			}
		}

		//エネルギーバーの加算処理

		AddEnergyBer(g_player.nCntEnergy, g_player.nLevel); //エネルギーバーの加算処理

		break;
	}
}