//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "effect.h"

//マクロ定義

#define MAX_EFFECT (4096) //エフェクトの最大数

//エフェクト構造体

typedef struct
{
	D3DXVECTOR3 pos; //位置

	D3DXCOLOR col; //色

	float fRadius; //半径

	int nLife; //寿命

	bool bUse; //使用しているかどうか
}Effect;

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL; //頂点バッファへのポインタ

Effect g_aEffect[MAX_EFFECT]; //エフェクトの情報

//=========================
// エフェクトの初期化処理
//=========================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntEffect;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/BULLET/effect000.jpg", //テクスチャのファイル名

		&g_pTextureEffect);


	//球の情報の初期化

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_aEffect[nCntEffect].fRadius = 0.0f;

		g_aEffect[nCntEffect].nLife = 0;

		g_aEffect[nCntEffect].bUse = false; //使用していない状態にする
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_EFFECT, //確保するバッファのサイズ（球の数分掛ける）

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffEffect,

		NULL
	);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4) //頂点データのポインタを4つ分進める
	{
		//頂点座標の設定

		pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x + sinf(-D3DX_PI * 0.75f) * g_aEffect[nCntEffect].fRadius;

		pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y + cosf(-D3DX_PI * 0.75f) * g_aEffect[nCntEffect].fRadius;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + sinf(D3DX_PI * 0.75f) * g_aEffect[nCntEffect].fRadius;

		pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y + cosf(D3DX_PI * 0.75f) * g_aEffect[nCntEffect].fRadius;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x + sinf(-D3DX_PI * 0.25) * g_aEffect[nCntEffect].fRadius;

		pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + cosf(-D3DX_PI * 0.25) * g_aEffect[nCntEffect].fRadius;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + sinf(D3DX_PI * 0.25) * g_aEffect[nCntEffect].fRadius;

		pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + cosf(D3DX_PI * 0.25) * g_aEffect[nCntEffect].fRadius;

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

	g_pVtxBuffEffect->Unlock();
}

//=========================
// エフェクトの終了処理
//=========================
void UninitEffect(void)
{
	//テクスチャの破棄

	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();

		g_pTextureEffect = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();

		g_pVtxBuffEffect = NULL;
	}
}

//=========================
// エフェクトの更新処理
//=========================
void UpdateEffect(void)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++ , pVtx += 4)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			g_aEffect[nCntEffect].fRadius -= 0.2f;

			//頂点座標の更新

			pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x + sinf(-D3DX_PI * 0.75f) * g_aEffect[nCntEffect].fRadius;

			pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y + cosf(-D3DX_PI * 0.75f) * g_aEffect[nCntEffect].fRadius;

			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + sinf(D3DX_PI * 0.75f) * g_aEffect[nCntEffect].fRadius;

			pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y + cosf(D3DX_PI * 0.75f) * g_aEffect[nCntEffect].fRadius;

			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x + sinf(-D3DX_PI * 0.25) * g_aEffect[nCntEffect].fRadius;

			pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + cosf(-D3DX_PI * 0.25) * g_aEffect[nCntEffect].fRadius;

			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + sinf(D3DX_PI * 0.25) * g_aEffect[nCntEffect].fRadius;

			pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + cosf(D3DX_PI * 0.25) * g_aEffect[nCntEffect].fRadius;

			pVtx[3].pos.z = 0.0f;

			//頂点カラーの設定

			g_aEffect[nCntEffect].col.a -= 0.02f;

			pVtx[0].col = g_aEffect[nCntEffect].col;

			pVtx[1].col = g_aEffect[nCntEffect].col;

			pVtx[2].col = g_aEffect[nCntEffect].col;

			pVtx[3].col = g_aEffect[nCntEffect].col;
		}

		//寿命を減らす

		g_aEffect[nCntEffect].nLife--;

		if (g_aEffect[nCntEffect].nLife <= 0)//寿命が尽きた
		{
			g_aEffect[nCntEffect].bUse = false;
		}

	}

	g_pVtxBuffEffect->Unlock();
}

//=========================
// エフェクトの描画処理
//=========================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureEffect);

	//aブレンディングを加算合成に設定

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			///ポリゴンの描画

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
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
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos; //位置

			g_aEffect[nCntEffect].col = col; //頂点カラーの設定（更新）

			g_aEffect[nCntEffect].fRadius = fRadius; //頂点座標の設定（更新）

			g_aEffect[nCntEffect].nLife = nLife; //寿命

			g_aEffect[nCntEffect].bUse = true; //使用している状態にする
		
			break;
		}
	}
}