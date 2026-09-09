//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "PlayerEffect.h"

//マクロ定義

#define MAX_PLAYEREFFECT (4096) //エフェクトの最大数

//エフェクト構造体

typedef struct
{
	D3DXVECTOR3 pos; //位置

	D3DXCOLOR col; //色

	D3DXVECTOR3 rot; //向き

	float fRadius; //半径

	int nLife; //寿命

	bool bUse; //使用しているかどうか
}PlayerEffect;

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTexturePlayerEffect = NULL; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerEffect = NULL; //頂点バッファへのポインタ

PlayerEffect g_aPlayerEffect[MAX_PLAYEREFFECT]; //エフェクトの情報

//=========================
// エフェクトの初期化処理
//=========================
void InitPlayerEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntPlayerEffect;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/PLAYER/effect.png", //テクスチャのファイル名

		&g_pTexturePlayerEffect);


	//球の情報の初期化

	for (nCntPlayerEffect = 0; nCntPlayerEffect < MAX_PLAYEREFFECT; nCntPlayerEffect++)
	{
		g_aPlayerEffect[nCntPlayerEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置

		g_aPlayerEffect[nCntPlayerEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //色

		g_aPlayerEffect[nCntPlayerEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きを初期化する（ｚ値を使用）

		g_aPlayerEffect[nCntPlayerEffect].fRadius = 0.0f; //半径

		g_aPlayerEffect[nCntPlayerEffect].nLife = 0; //寿命

		g_aPlayerEffect[nCntPlayerEffect].bUse = false; //使用していない状態にする
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_PLAYEREFFECT, //確保するバッファのサイズ（球の数分掛ける）

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffPlayerEffect,

		NULL
	);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffPlayerEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlayerEffect = 0; nCntPlayerEffect < MAX_PLAYEREFFECT; nCntPlayerEffect++, pVtx += 4) //頂点データのポインタを4つ分進める
	{
		//頂点座標の設定

		pVtx[0].pos.x = g_aPlayerEffect[nCntPlayerEffect].pos.x + sinf(-D3DX_PI * 0.75f) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

		pVtx[0].pos.y = g_aPlayerEffect[nCntPlayerEffect].pos.y + cosf(-D3DX_PI * 0.75f) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aPlayerEffect[nCntPlayerEffect].pos.x + sinf(D3DX_PI * 0.75f) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

		pVtx[1].pos.y = g_aPlayerEffect[nCntPlayerEffect].pos.y + cosf(D3DX_PI * 0.75f) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aPlayerEffect[nCntPlayerEffect].pos.x + sinf(-D3DX_PI * 0.25) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

		pVtx[2].pos.y = g_aPlayerEffect[nCntPlayerEffect].pos.y + cosf(-D3DX_PI * 0.25) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aPlayerEffect[nCntPlayerEffect].pos.x + sinf(D3DX_PI * 0.25) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

		pVtx[3].pos.y = g_aPlayerEffect[nCntPlayerEffect].pos.y + cosf(D3DX_PI * 0.25) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

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

	g_pVtxBuffPlayerEffect->Unlock();
}

//=========================
// エフェクトの終了処理
//=========================
void UninitPlayerEffect(void)
{
	//テクスチャの破棄

	if (g_pTexturePlayerEffect != NULL)
	{
		g_pTexturePlayerEffect->Release();

		g_pTexturePlayerEffect = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffPlayerEffect != NULL)
	{
		g_pVtxBuffPlayerEffect->Release();

		g_pVtxBuffPlayerEffect = NULL;
	}
}

//=========================
// エフェクトの更新処理
//=========================
void UpdatePlayerEffect(void)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffPlayerEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPlayerEffect = 0; nCntPlayerEffect < MAX_PLAYEREFFECT; nCntPlayerEffect++, pVtx += 4)
	{
		if (g_aPlayerEffect[nCntPlayerEffect].bUse == true)
		{

			//頂点座標の更新

			pVtx[0].pos.x = g_aPlayerEffect[nCntPlayerEffect].pos.x + sinf(-D3DX_PI * 0.75f) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

			pVtx[0].pos.y = g_aPlayerEffect[nCntPlayerEffect].pos.y + cosf(-D3DX_PI * 0.75f) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aPlayerEffect[nCntPlayerEffect].pos.x + sinf(D3DX_PI * 0.75f) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

			pVtx[1].pos.y = g_aPlayerEffect[nCntPlayerEffect].pos.y + cosf(D3DX_PI * 0.75f) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aPlayerEffect[nCntPlayerEffect].pos.x + sinf(-D3DX_PI * 0.25) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

			pVtx[2].pos.y = g_aPlayerEffect[nCntPlayerEffect].pos.y + cosf(-D3DX_PI * 0.25) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aPlayerEffect[nCntPlayerEffect].pos.x + sinf(D3DX_PI * 0.25) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

			pVtx[3].pos.y = g_aPlayerEffect[nCntPlayerEffect].pos.y + cosf(D3DX_PI * 0.25) * g_aPlayerEffect[nCntPlayerEffect].fRadius;

			pVtx[3].pos.z = 0.0f;

			//頂点カラーの設定

			g_aPlayerEffect[nCntPlayerEffect].col.a -= 0.01f;

			pVtx[0].col = g_aPlayerEffect[nCntPlayerEffect].col;

			pVtx[1].col = g_aPlayerEffect[nCntPlayerEffect].col;

			pVtx[2].col = g_aPlayerEffect[nCntPlayerEffect].col;

			pVtx[3].col = g_aPlayerEffect[nCntPlayerEffect].col;
		}

		//寿命を減らす

		g_aPlayerEffect[nCntPlayerEffect].nLife--;

		if (g_aPlayerEffect[nCntPlayerEffect].nLife <= 0)//寿命が尽きた
		{
			g_aPlayerEffect[nCntPlayerEffect].bUse = false;
		}

	}

	g_pVtxBuffPlayerEffect->Unlock();
}

//=========================
// エフェクトの描画処理
//=========================
void DrawPlayerEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffPlayerEffect, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTexturePlayerEffect);

	//aブレンディングを加算合成に設定

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntPlayerEffect = 0; nCntPlayerEffect < MAX_PLAYEREFFECT; nCntPlayerEffect++)
	{
		if (g_aPlayerEffect[nCntPlayerEffect].bUse == true)
		{
			///ポリゴンの描画

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPlayerEffect * 4, 2);
		}
	}

	//aブレンディングを元に戻す

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=========================
// エフェクトの設定処理
//=========================
void SetPlayerEffect(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 rot, float fRadius, int nLife)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffPlayerEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPlayerEffect = 0; nCntPlayerEffect < MAX_PLAYEREFFECT; nCntPlayerEffect++, pVtx += 4)
	{
		if (g_aPlayerEffect[nCntPlayerEffect].bUse == false)
		{
			g_aPlayerEffect[nCntPlayerEffect].pos = pos; //位置

			g_aPlayerEffect[nCntPlayerEffect].col = col; //頂点カラーの設定（更新）

			g_aPlayerEffect[nCntPlayerEffect].fRadius = fRadius; //頂点座標の設定（更新）

			g_aPlayerEffect[nCntPlayerEffect].nLife = nLife; //寿命

			g_aPlayerEffect[nCntPlayerEffect].bUse = true; //使用している状態にする

			g_aPlayerEffect[nCntPlayerEffect].rot = rot; //向きを設定

			if (g_aPlayerEffect[nCntPlayerEffect].rot.z == 0) //向きが左の場合
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else if (g_aPlayerEffect[nCntPlayerEffect].rot.z == D3DX_PI) //向きが右の場合
			{
				pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);

				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);

				pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);

				pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
			}

			break;
		}
	}

	g_pVtxBuffPlayerEffect->Unlock();
}