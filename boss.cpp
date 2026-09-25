//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "boss.h"
#include "explosion.h"
#include "bullet.h"
#include "score.h"
#include "energy.h"
#include "player.h"
#include "enemy.h"

//マクロ定義

#define BOSS_DAMAGE_NOMAL (100) //通常時のボスのダメージ

#define BOSS_DAMAGE_ATTACK (150) //攻撃時のボスのダメージ

//行動パターンの列挙型定義

typedef enum
{
	PATTERN_1 = 0, //体当たり

	PATTERN_2, //追尾UFPの呼び出し

	PATTERN_MAX //行動パターンの最大数
}ACTIONPATTERN;

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureBoss = NULL;

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss;

BOSS g_Boss; //ボスの情報

int g_nPattern; //パターンを代入する

//===================
// ボスの初期化処理
//===================
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャ（４枚分）の読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/ENEMY/enemy000.png", //テクスチャのファイル名

		&g_pTextureBoss);

	//ボスの情報の初期化

	g_Boss.pos = D3DXVECTOR3(500.0f, 400.0f, 0.0f); //位置

	g_Boss.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //移動

	g_Boss.state = BossSTATE_NORMAL; //状態

	g_Boss.nCounterState = 0; //状態カウント

	g_Boss.nCounterAction = 0; //行動カウント

	g_Boss.nDamage = BOSS_DAMAGE_NOMAL; //ダメージ量

	g_Boss.fSpeed = 10.0f; //スピード


	g_Boss.fMoveAngle = 0.0f;

	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 , //確保するバッファのサイズ（球の数分掛ける）

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffBoss,

		NULL
	);

	//頂点情報の設定

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定

		pVtx[0].pos.x = g_Boss.pos.x + sinf(-D3DX_PI * 0.75f) * BOSS_DIAGONAL;

		pVtx[0].pos.y = g_Boss.pos.y + cosf(-D3DX_PI * 0.75f) * BOSS_DIAGONAL;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Boss.pos.x + sinf(D3DX_PI * 0.75f) * BOSS_DIAGONAL;

		pVtx[1].pos.y = g_Boss.pos.y + cosf(D3DX_PI * 0.75f) * BOSS_DIAGONAL;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Boss.pos.x + sinf(-D3DX_PI * 0.25) * BOSS_DIAGONAL;

		pVtx[2].pos.y = g_Boss.pos.y + cosf(-D3DX_PI * 0.25) * BOSS_DIAGONAL;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Boss.pos.x + sinf(D3DX_PI * 0.25) * BOSS_DIAGONAL;

		pVtx[3].pos.y = g_Boss.pos.y + cosf(D3DX_PI * 0.25) * BOSS_DIAGONAL;

		pVtx[3].pos.z = 0.0f;

		//rhwの設定 1.0f固定

		pVtx[0].rhw = 1.0f;

		pVtx[1].rhw = 1.0f;

		pVtx[2].rhw = 1.0f;

		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定（０．０f～１．０ｆで設定）

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffBoss->Unlock();
}

//===================
// ボスの終了処理
//===================
void UninitBoss(void)
{
	//テクスチャ（４枚分）の破棄

	if (g_pTextureBoss != NULL)
	{
		g_pTextureBoss->Release();

		g_pTextureBoss = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();

		g_pVtxBuffBoss = NULL;
	}
}

//===================
// ボスの更新処理
//===================
void UpdateBoss(void)
{
	//状態処理

	StateBoss();

	//行動処理

	ActionBoss();

	//プレイヤーとの当たり判定

	CollisionPlayer(&g_Boss);	
}
//=========================
// ボスの状態処理
//=========================
void StateBoss(void)
{
	switch (g_Boss.state) //ボスの状態
	{
	case BossSTATE_NORMAL: //通常

		break;

	case BossSTATE_DAMAGE: //ダメージ

		g_Boss.nCounterState--; //カウンターステートを減らす

		if (g_Boss.nCounterState <= 0) //カウンターステートが0になった
		{
			g_Boss.state = BossSTATE_NORMAL; //ボスの状態を通常にする

			//ポリゴンの描画

			VERTEX_2D* pVtx; //forの前でロック、後でアンロック

			//頂点バッファをロックし、頂点データへのポインタを取得

			g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラーの設定

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_pVtxBuffBoss->Unlock();
		}
		break;
	}
}
//=========================
// ボスの状態処理
//=========================
void ActionBoss(void)
{
	g_Boss.nCounterAction++; //行動カウンターをプラス

	if (g_Boss.nCounterAction < 360) //カウンターが３６０以下の場合
	{
		//移動量を初期化

		g_Boss.move.x = 0.0f;

		g_Boss.move.y = 0.0f;

		//ぷかぷかと浮くようにする

		if ((g_Boss.nCounterAction / 60) % 2 == 1) //上昇
		{
			g_Boss.move.y = - 0.5f; 
		}
		else if ((g_Boss.nCounterAction / 60) % 2 == 0) //降下
		{
			g_Boss.move.y = 0.5f;
		}

		//移動

		MoveBoss();

		//プレイヤーとの角度計算

		g_Boss.fMoveAngle = CalcAnglePlayer();
	
	}
	else if(360 <= g_Boss.nCounterAction) //カウンターが360を超えたとき
	{
		if (360 == g_Boss.nCounterAction) //カウンターが360になったとき
		{
			g_nPattern = rand() % PATTERN_MAX; //ランダムで行動パターンを決める
		}

		switch (g_nPattern) //行動パターンを比較
		{
		case PATTERN_1: //パターン1の場合

			ActionBossPattern1(); //パターン1

		case PATTERN_2: //パターン2の場合

			ActionBossPattern2(); //パターン2
		}
	}
}
//=========================
// ボスの行動パターン１
//=========================
void ActionBossPattern1()
{
	//移動量の設定

	g_Boss.move = D3DXVECTOR3(

		cosf(g_Boss.fMoveAngle) * g_Boss.fSpeed,

		sinf(g_Boss.fMoveAngle) * g_Boss.fSpeed,

		0.0f);

	//ダメージを攻撃時のダメージにする

	g_Boss.nDamage = BOSS_DAMAGE_ATTACK;

	//移動処理

	MoveBoss();

	//行動前の状態にリセット

	if (420 <= g_Boss.nCounterAction) //カウンターが420以上の場合	
	{
		g_Boss.nCounterAction = 0; //カウンターを０にする
		
		g_Boss.nDamage = BOSS_DAMAGE_NOMAL; //ダメージ量を通常事にする
	}
}
//=========================
// ボスの行動パターン２
//=========================
void ActionBossPattern2()
{
	if (420 <= g_Boss.nCounterAction ) //カウンターが420以下の場合
	{
		//中央との角度の計算

		g_Boss.fMoveAngle =  CalcAngleCenter();

		//移動量の設定

		g_Boss.move = D3DXVECTOR3(

			cosf(g_Boss.fMoveAngle) * g_Boss.fSpeed,

			sinf(g_Boss.fMoveAngle) * g_Boss.fSpeed,

			0.0f);

		//移動処理

		MoveBoss();

		//追尾ＵＦＯの呼び出し

		if (480 == g_Boss.nCounterAction) //カウンターが480の時
		{
			CallEnemy1();
		}
		
		if (500 == g_Boss.nCounterAction) //カウンターが500の時
		{
			CallEnemy1();
		}

		if (520 == g_Boss.nCounterAction) //カウンターが520の時
		{
			CallEnemy1();
		}

		//カウンターの初期化

		if (540 <= g_Boss.nCounterAction) //カウンターが540以上の場合
		{
			g_Boss.nCounterAction = 0;
		}

	}
	
	
}
//==========================
// 敵の移動処理
//==========================
void MoveBoss(void)
{
	//位置を更新

	g_Boss.pos.x += g_Boss.move.x;

	g_Boss.pos.y += g_Boss.move.y;

	//壁に当たった時

	if (g_Boss.pos.x - BOSS_DIAGONAL < 0) //一番左に当たった場合
	{
		g_Boss.pos.x = BOSS_DIAGONAL; //g_Boss.posを一番左にする
	}
	else if (SCREEN_WIDTH < g_Boss.pos.x + BOSS_DIAGONAL) //一番右に当たった場合
	{
		g_Boss.pos.x = SCREEN_WIDTH - BOSS_DIAGONAL; //g_Boss.posを一番右にする
	}

	if (g_Boss.pos.y - BOSS_DIAGONAL < 0) //一番上にあたった場合
	{
		g_Boss.pos.y = BOSS_DIAGONAL; //g_Boss.posを一番上にする
	}
	else if (SCREEN_HEIGHT < g_Boss.pos.y + BOSS_DIAGONAL) //一番下にあたった場合
	{
		g_Boss.pos.y = SCREEN_HEIGHT - BOSS_DIAGONAL; //g_Boss.posを一番下にする
	}

	//頂点情報の設定

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = g_Boss.pos.x + sinf(-D3DX_PI * 0.75f) * BOSS_DIAGONAL;

	pVtx[0].pos.y = g_Boss.pos.y + cosf(-D3DX_PI * 0.75f) * BOSS_DIAGONAL;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Boss.pos.x + sinf(D3DX_PI * 0.75f) * BOSS_DIAGONAL;

	pVtx[1].pos.y = g_Boss.pos.y + cosf(D3DX_PI * 0.75f) * BOSS_DIAGONAL;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Boss.pos.x + sinf(-D3DX_PI * 0.25) * BOSS_DIAGONAL;

	pVtx[2].pos.y = g_Boss.pos.y + cosf(-D3DX_PI * 0.25) * BOSS_DIAGONAL;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Boss.pos.x + sinf(D3DX_PI * 0.25) * BOSS_DIAGONAL;

	pVtx[3].pos.y = g_Boss.pos.y + cosf(D3DX_PI * 0.25) * BOSS_DIAGONAL;

	pVtx[3].pos.z = 0.0f;
	
	//アンロック

	g_pVtxBuffBoss->Unlock();
}
//=========================
// 敵の呼び出し処理（突撃UFO）
//=========================
void CallEnemy1(void)
{
	//左上端

	SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_3);

	//右上端

	SetEnemy(D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f), ENEMYTYPE_3);

	//左下端

	SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f), ENEMYTYPE_3);

	//右下端

	SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), ENEMYTYPE_3);
}

//===================
// ボスの描画処理
//===================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定(種類に合わせて設定)

	pDevice->SetTexture(0, g_pTextureBoss);

	//ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//===================
// ボスの取得処理
//===================
BOSS* GetBoss(void)
{
	return &g_Boss; //ボスの情報を返す
}

//===================
// プレイヤーとの角度計算
//===================
float CalcAnglePlayer(void)
{
	Player* pPlayer = GetPlayer(); //プレイヤーの情報

	float dx = pPlayer->pos.x - g_Boss.pos.x; //x座標の差

	float dy = pPlayer->pos.y - g_Boss.pos.y; //y座標の差

	float angle = (float)atan2(dy, dx); //角度

	return angle; //角度を返す

}
//===================
// 中央との角度計算
//===================
float CalcAngleCenter(void)
{
	float dx = (SCREEN_WIDTH / 2) - g_Boss.pos.x; //x座標の差

	float dy = (SCREEN_HEIGHT / 2) - g_Boss.pos.y; //y座標の差

	float angle = (float)atan2(dy, dx); //角度

	return angle; //角度を返す

}

//===================
// ボスのヒット処理
//===================
void HitBoss(int nDamage)
{
	g_Boss.state = BossSTATE_DAMAGE; //ダメージを与える

	g_Boss.nCounterState = 5;

	VERTEX_2D* pVtx; //forの前でロック、後でアンロック

//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定

	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	g_pVtxBuffBoss->Unlock();

	//スコアの加算
	
	AddScore(nDamage);

}

//==================
// プレイヤーとの当たり判定
//==================
void CollisionPlayer(BOSS* Boss)
{
	//プレイヤーの取得

	Player* pPlayer = GetPlayer(); //プレイヤーの情報

	//中心座標の距離（ｘ、ｙ）

	float fDistance_x = pPlayer->pos.x - Boss->pos.x, //距離ｘ

		fDistance_y = pPlayer->pos.y - Boss->pos.y; //距離y

	//二つの中心中心座標の距離の2乗

	float fDistanceSquared = (fDistance_x * fDistance_x) + (fDistance_y * fDistance_y);

	//２つの円の半径の合計

	float fTotalRadius = (BOSS_COLLISION + PLAYER_SIZE); //半径の合計の長さ

	if (fDistanceSquared <= fTotalRadius * fTotalRadius) //半径の合計の２乗より距離の２乗が小さい場合
	{//ボスとプレイヤーが当たった

		HitPlayer(HIT_ENEMY, g_Boss.nDamage); //プレイヤーのヒット処理
	}
}