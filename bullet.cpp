//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================

#include "main.h"

#include "bullet.h"

#include "explosion.h"

#include "enemy.h"

#include "player.h"

#include "effect.h"

#include "boss.h"

#include "sound.h"

//マクロ定義

#define MAX_BULLET (128) //球の最大数

#define BULLET_SIZE (10) //球の半径

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL; //頂点バッファへのポインタ

Bullet g_aBullet[MAX_BULLET]; //球の情報

//================
//球の初期化処理
//================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntBullet;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/BULLET/bullet000.png", //テクスチャのファイル名

		&g_pTextureBullet);


	//球の情報の初期化

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_aBullet[nCntBullet].nLife = 0;

		g_aBullet[nCntBullet].nDamage = 0;

		g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;

		g_aBullet[nCntBullet].bUse = false; //使用していない状態にする
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(	
		sizeof(VERTEX_2D) * 4 * MAX_BULLET, //確保するバッファのサイズ（球の数分掛ける）

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffBullet,

		NULL
	);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pVtx += 4) //頂点データのポインタを4つ分進める
	{
		//頂点座標の設定

		pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x + sinf(-D3DX_PI * 0.75f) * 10;

		pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y + cosf(-D3DX_PI * 0.75f) * 10;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + sinf(D3DX_PI * 0.75f) * 10;

		pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y + cosf(D3DX_PI * 0.75f) * 10;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x + sinf(-D3DX_PI * 0.25) * 10;

		pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + cosf(-D3DX_PI * 0.25) * 10;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + sinf(D3DX_PI * 0.25) * 10;

		pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + cosf(D3DX_PI * 0.25) * 10;

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

	}

	g_pVtxBuffBullet->Unlock();
}

//==============
// 球の終了処理
//==============
void UninitBullet(void)
{
	//テクスチャの破棄

	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();

		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();

		g_pVtxBuffBullet = NULL;
	}	
}

//==============
// 球の更新処理
//==============
void UpdateBullet(void)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//球が使用されている

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{//プレイヤーの球

				//エフェクト

				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.75f), 25.0f, 12);

				//当たり判定

				CollisionEnemy(&g_aBullet[nCntBullet]); //敵

				CollisionBoss(&g_aBullet[nCntBullet]); //ボス
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{//敵の球

				//エフェクト

				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 0.0f, 0.75f, 1.0f), 25.0f, 12);

				//当たり判定

				CollisionPlayer(&g_aBullet[nCntBullet]); //プレイヤー
			}

			//移動

			MoveBullet(nCntBullet);

			//寿命のカウントダウン

			g_aBullet[nCntBullet].nLife--;

			if (g_aBullet[nCntBullet].nLife <= 0) //寿命が尽きた
			{
				//爆発の設定

				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); //位置　色

				g_aBullet[nCntBullet].bUse = false; //使用していない状態にする
			}
		}

		
	}

	
}
//==============
// 球の移動処理
//==============
void MoveBullet(int nCnt)
{
	if (g_aBullet[nCnt].bUse == true)
	{//球が使用されている場合

		VERTEX_2D* pVtx;

		//頂点バッファをロックし、頂点データへのポインタを取得

		g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nCnt * 4;

		//球の位置を更新

		g_aBullet[nCnt].pos.x += g_aBullet[nCnt].move.x;

		g_aBullet[nCnt].pos.y += g_aBullet[nCnt].move.y;

		//頂点座標の更新

		pVtx[0].pos.x = g_aBullet[nCnt].pos.x + sinf(-D3DX_PI * 0.75f) * BULLET_SIZE;

		pVtx[0].pos.y = g_aBullet[nCnt].pos.y + cosf(-D3DX_PI * 0.75f) * BULLET_SIZE;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aBullet[nCnt].pos.x + sinf(D3DX_PI * 0.75f) * BULLET_SIZE;

		pVtx[1].pos.y = g_aBullet[nCnt].pos.y + cosf(D3DX_PI * 0.75f) * BULLET_SIZE;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aBullet[nCnt].pos.x + sinf(-D3DX_PI * 0.25) * BULLET_SIZE;

		pVtx[2].pos.y = g_aBullet[nCnt].pos.y + cosf(-D3DX_PI * 0.25) * BULLET_SIZE;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aBullet[nCnt].pos.x + sinf(D3DX_PI * 0.25) * BULLET_SIZE;

		pVtx[3].pos.y = g_aBullet[nCnt].pos.y + cosf(D3DX_PI * 0.25) * BULLET_SIZE;

		pVtx[3].pos.z = 0.0f;

		if (g_aBullet[nCnt].pos.x < 0 || SCREEN_WIDTH < g_aBullet[nCnt].pos.x)
		{ //球の位置が画面外に出た
			g_aBullet[nCnt].bUse = false; //使用していない状態にする
		}

		if (g_aBullet[nCnt].pos.y < 0 || SCREEN_HEIGHT < g_aBullet[nCnt].pos.y)
		{ //球の位置が画面外に出た
			g_aBullet[nCnt].bUse = false; //使用していない状態にする
		}

		g_pVtxBuffBullet->Unlock();
	}
}

//==============
// 球の描画処理
//==============
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	int nCntBullet;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{ //球が使用されている場合

		//ポリゴンの描画
												  //描画を開始する頂点インデックス
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}
//==============
// 球の設定処理
//==============
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife,int nDamage, BULLETTYPE type)
{
	//サウンド

	if (type == BULLETTYPE_PLAYER)
	{ //プレイヤーの銃声
		PlaySound(SOUND_LABEL_SE_SHOT000);
	}
	else
	{ //敵の銃声
		PlaySound(SOUND_LABEL_SE_SHOT001);
	}
	int nCntBullet;

	//ポリゴンの描画

	VERTEX_2D* pVtx; //forの前でロック、後でアンロック

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pVtx += 4)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos; //位置

			//頂点座標の更新

			pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x + BULLET_SIZE;

			pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y + BULLET_SIZE;

			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + sinf(D3DX_PI * 0.75f) * BULLET_SIZE;

			pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y + cosf(D3DX_PI * 0.75f) * BULLET_SIZE;

			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x + sinf(-D3DX_PI * 0.25) * BULLET_SIZE;

			pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + cosf(-D3DX_PI * 0.25) * BULLET_SIZE;

			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + sinf(D3DX_PI * 0.25) * BULLET_SIZE;

			pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + cosf(D3DX_PI * 0.25) * BULLET_SIZE;

			pVtx[3].pos.z = 0.0f;

			g_aBullet[nCntBullet].move = move; //移動量

			g_aBullet[nCntBullet].nLife = nLife; //寿命

			g_aBullet[nCntBullet].nDamage = nDamage; //ダメージ

			g_aBullet[nCntBullet].bUse = true; //使用している状態にする

			g_aBullet[nCntBullet].type = type;

			break;
		}
	}

	g_pVtxBuffBullet->Unlock();
}

//==================
// 敵との当たり判定
//==================
void CollisionEnemy(Bullet* pBullet)
{
	int nCntEnemy;

	//敵の取得

	Enemy* pEnemy = GetEnemy(); //敵の情報の先頭アドレスが代入される

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{//敵が使用されている

			if (pEnemy->pos.x - ENEMY_DIAGONAL <= pBullet->pos.x

				&& pBullet->pos.x <= pEnemy->pos.x + ENEMY_DIAGONAL

				&& pEnemy->pos.y - ENEMY_DIAGONAL <= pBullet->pos.y

				&& pBullet->pos.y <= pEnemy->pos.y + ENEMY_DIAGONAL) //敵と弾が当たった
			{
				HitEnemy(nCntEnemy, pBullet->nDamage); //敵のヒット処理

				pBullet->bUse = false; //球を使用していない状態にする

			}

		}
	}
}

//==================
// ボスとの当たり判定
//==================
void CollisionBoss(Bullet* pBullet)
{
	//ボスの取得

	BOSS* pBoss = GetBoss(); //ボスの情報の先頭アドレスが代入される

	Player* pPlayer = GetPlayer();

		if (pBoss->pos.x - BOSS_DIAGONAL <= pBullet->pos.x

			&& pBullet->pos.x <= pBoss->pos.x + BOSS_DIAGONAL

			&& pBoss->pos.y - BOSS_DIAGONAL <= pBullet->pos.y

			&& pBullet->pos.y <= pBoss->pos.y + BOSS_DIAGONAL) //ボスと弾が当たった
		{
			//サウンド

			PlaySound(SOUND_LABEL_SE_HIT);

			HitBoss(pPlayer->nAttack); //ボスのヒット処理

			pBullet->bUse = false; //球を使用していない状態にする

		}

}

//==================
// プレイヤーとの当たり判定
//==================
void CollisionPlayer(Bullet* pBullet)
{
	//プレイヤーの取得

	Player* pPlayer = GetPlayer(); //プレイヤーの情報の先頭アドレスが代入される	

	if (pPlayer->pos.x - PLAYER_DIAGONAL <= pBullet->pos.x

		&& pBullet->pos.x <= pPlayer->pos.x + PLAYER_DIAGONAL

		&& pPlayer->pos.y - PLAYER_DIAGONAL <= pBullet->pos.y

		&& pBullet->pos.y <= pPlayer->pos.y + PLAYER_DIAGONAL) //プレイヤーと弾が当たった
	{
		HitPlayer(HIT_BULLET, pBullet->nDamage); //プレイヤーのヒット処理

		pBullet->bUse = false; //球を使用していない状態にする
	}
}