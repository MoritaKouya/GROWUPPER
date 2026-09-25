//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================

#include "main.h"

#include "bomb.h"

#include "player.h"

#include "sound.h"

//マクロ定義

#define MAX_BOMB (12) //ボムの最大数

#define BOMB_DIAGONAL (150) //ボムの半径の最大

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureBomb = NULL; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBomb = NULL; //頂点バッファへのポインタ

Bomb g_aBomb[MAX_BOMB]; //ボムの情報

const char* g_aBombTexture_Path = "Data/TEXTURE/ENEMY/bomb000.png"; //テクスチャの相対パス

//================
//ボムの初期化処理
//================
void InitBomb(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntBomb;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		g_aBombTexture_Path, //テクスチャのファイル名

		&g_pTextureBomb);


	//ボムの情報の初期化

	for (nCntBomb = 0; nCntBomb < MAX_BOMB; nCntBomb++)
	{
		g_aBomb[nCntBomb].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_aBomb[nCntBomb].nLife = 0;

		g_aBomb[nCntBomb].fSize = 0;

		g_aBomb[nCntBomb].bUse = false; //使用していない状態にする
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_BOMB, //確保するバッファのサイズ（ボムの数分掛ける）

		D3DUSAGE_WRITEONLY,
		
		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffBomb,

		NULL
	);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffBomb->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBomb = 0; nCntBomb < MAX_BOMB; nCntBomb++, pVtx += 4) //頂点データのポインタを4つ分進める
	{
		//頂点座標の設定

		pVtx[0].pos.x = g_aBomb[nCntBomb].pos.x + sinf(-D3DX_PI * 0.75f) * 0;

		pVtx[0].pos.y = g_aBomb[nCntBomb].pos.y + cosf(-D3DX_PI * 0.75f) * 0;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aBomb[nCntBomb].pos.x + sinf(D3DX_PI * 0.75f) * 0;

		pVtx[1].pos.y = g_aBomb[nCntBomb].pos.y + cosf(D3DX_PI * 0.75f) * 0;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aBomb[nCntBomb].pos.x + sinf(-D3DX_PI * 0.25) * 0;

		pVtx[2].pos.y = g_aBomb[nCntBomb].pos.y + cosf(-D3DX_PI * 0.25) * 0;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aBomb[nCntBomb].pos.x + sinf(D3DX_PI * 0.25) * 0;

		pVtx[3].pos.y = g_aBomb[nCntBomb].pos.y + cosf(D3DX_PI * 0.25) * 0;

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

	g_pVtxBuffBomb->Unlock();
}

//==============
// ボムの終了処理
//==============
void UninitBomb(void)
{
	//テクスチャの破棄

	if (g_pTextureBomb != NULL)
	{
		g_pTextureBomb->Release();

		g_pTextureBomb = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffBomb != NULL)
	{
		g_pVtxBuffBomb->Release();

		g_pVtxBuffBomb = NULL;
	}
}

//==============
// ボムの更新処理
//==============
void UpdateBomb(void)
{
	int nCntBomb;

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffBomb->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBomb = 0; nCntBomb < MAX_BOMB; nCntBomb++, pVtx += 4)
	{
		if (g_aBomb[nCntBomb].bUse == true)
		{//ボムが使用されている場合

			if (g_aBomb[nCntBomb].fSize <= BOMB_DIAGONAL)
			{ //最大サイズじゃない場合

				g_aBomb[nCntBomb].fSize += 1.0f; //サイズを大きくする
			}

			//頂点座標の更新

			pVtx[0].pos.x = g_aBomb[nCntBomb].pos.x + sinf(-D3DX_PI * 0.75f) * g_aBomb[nCntBomb].fSize;

			pVtx[0].pos.y = g_aBomb[nCntBomb].pos.y + cosf(-D3DX_PI * 0.75f) * g_aBomb[nCntBomb].fSize;

			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aBomb[nCntBomb].pos.x + sinf(D3DX_PI * 0.75f) * g_aBomb[nCntBomb].fSize;

			pVtx[1].pos.y = g_aBomb[nCntBomb].pos.y + cosf(D3DX_PI * 0.75f) * g_aBomb[nCntBomb].fSize;

			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aBomb[nCntBomb].pos.x + sinf(-D3DX_PI * 0.25) * g_aBomb[nCntBomb].fSize;

			pVtx[2].pos.y = g_aBomb[nCntBomb].pos.y + cosf(-D3DX_PI * 0.25) * g_aBomb[nCntBomb].fSize;

			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aBomb[nCntBomb].pos.x + sinf(D3DX_PI * 0.25) * g_aBomb[nCntBomb].fSize;

			pVtx[3].pos.y = g_aBomb[nCntBomb].pos.y + cosf(D3DX_PI * 0.25) * g_aBomb[nCntBomb].fSize;

			pVtx[3].pos.z = 0.0f;

			//当たり判定

			CollisionPlayer(&g_aBomb[nCntBomb]); //ボムとプレイヤーの当たり判定


			//寿命のカウントダウン

			g_aBomb[nCntBomb].nLife--; //寿命を減らす

			if (g_aBomb[nCntBomb].nLife <= 0) //寿命が尽きた
			{
				g_aBomb[nCntBomb].bUse = false; //使用していない状態にする
			}
		}
	}

	g_pVtxBuffBomb->Unlock();
}

//==============
// ボムの描画処理
//==============
void DrawBomb(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	int nCntBomb;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffBomb, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureBomb);

	for (nCntBomb = 0; nCntBomb < MAX_BOMB; nCntBomb++)
	{
		if (g_aBomb[nCntBomb].bUse == true)
		{ //ボムが使用されている場合

		//ポリゴンの描画
												  //描画を開始する頂点インデックス
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBomb * 4, 2);
		}
	}
}
//==============
// ボムの設定処理
//==============
void SetBomb(D3DXVECTOR3 pos,int nDamage)
{
	//サウンド

	PlaySound(SOUND_LABEL_SE_EXPLOSION);

	int nCntBomb;

	//ポリゴンの描画

	VERTEX_2D* pVtx; //forの前でロック、後でアンロック

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffBomb->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBomb = 0; nCntBomb < MAX_BOMB; nCntBomb++, pVtx += 4)
	{
		if (g_aBomb[nCntBomb].bUse == false)
		{
			//情報の初期化

			g_aBomb[nCntBomb].pos = pos;

			//頂点座標の更新

			pVtx[0].pos.x = g_aBomb[nCntBomb].pos.x + 0;

			pVtx[0].pos.y = g_aBomb[nCntBomb].pos.y + 0;

			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aBomb[nCntBomb].pos.x + sinf(D3DX_PI * 0.75f) * 0;

			pVtx[1].pos.y = g_aBomb[nCntBomb].pos.y + cosf(D3DX_PI * 0.75f) * 0;

			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aBomb[nCntBomb].pos.x + sinf(-D3DX_PI * 0.25) * 0;

			pVtx[2].pos.y = g_aBomb[nCntBomb].pos.y + cosf(-D3DX_PI * 0.25) * 0;

			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aBomb[nCntBomb].pos.x + sinf(D3DX_PI * 0.25) * 0;

			pVtx[3].pos.y = g_aBomb[nCntBomb].pos.y + cosf(D3DX_PI * 0.25) * 0;

			pVtx[3].pos.z = 0.0f;

			g_aBomb[nCntBomb].nLife = 120; //寿命

			g_aBomb[nCntBomb].nDamage = nDamage; //ダメージ量	

			g_aBomb[nCntBomb].fSize = 50; //大きさ

			g_aBomb[nCntBomb].bUse = true; //使用している状態にする

			break;
		}
	}

	g_pVtxBuffBomb->Unlock();
}

//==================
// プレイヤーとの当たり判定
//==================
void CollisionPlayer(Bomb* pBomb)
{
	//プレイヤーの取得

	Player* pPlayer = GetPlayer(); //敵の情報のが代入される

	//中心座標の距離（ｘ、ｙ）

	float fDistance_x = pPlayer->pos.x - pBomb->pos.x, //距離ｘ

		fDistance_y = pPlayer->pos.y - pBomb->pos.y; //距離y

	//二つの中心座標の距離

	float fDistanceSquared = (fDistance_x * fDistance_x) + (fDistance_y * fDistance_y);

	//２つの円の半径の合計

	float fTotalRadius = (pBomb->fSize + PLAYER_SIZE); //半径の合計の長さ

	if (fDistanceSquared <= fTotalRadius * fTotalRadius) //半径の合計の２乗より距離の２乗が小さい場合
	{//敵とプレイヤーが当たった

		HitPlayer(HIT_ENEMY, pBomb->nDamage); //敵のヒット処理
	}
}