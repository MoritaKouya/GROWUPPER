//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "damagescreen.h"

//グローバル変数

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDamageScreen = NULL; //頂点バッファのポインタ

D3DXCOLOR g_DamageScreenColor; //ダメージスクリーンのカラー

//=============================
// ダメージスクリーンの初期化処理
//=============================
void InitDamageScreen(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_DamageScreenColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な頂点数

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffDamageScreen,

		NULL);

	//デバイスの取得

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffDamageScreen->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);

	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);

	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定 1.0f固定

	pVtx[0].rhw = 1.0f;

	pVtx[1].rhw = 1.0f;

	pVtx[2].rhw = 1.0f;

	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定（０．０f～１．０ｆで設定）

	pVtx[0].col = g_DamageScreenColor;

	pVtx[1].col = g_DamageScreenColor;

	pVtx[2].col = g_DamageScreenColor;

	pVtx[3].col = g_DamageScreenColor;

	//テクスチャ座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffDamageScreen->Unlock();
}

//=============================
// ダメージスクリーンの終了処理
//=============================
void UninitDamageScreen(void)
{
	//頂点バッファの破棄

	if (g_pVtxBuffDamageScreen != NULL)
	{
		g_pVtxBuffDamageScreen->Release();

		g_pVtxBuffDamageScreen = NULL;
	}
}

//=============================
// ダメージスクリーンの更新処理
//=============================
void UpdateDamageScreen(void)
{
	if (0.0f < g_DamageScreenColor.a)
	{ //ダメージスクリーンが見える場合

		g_DamageScreenColor.a -= 0.01f;

		//デバイスの取得

		VERTEX_2D* pVtx;

		//頂点バッファをロックし、頂点データへのポインタを取得

		g_pVtxBuffDamageScreen->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = g_DamageScreenColor;

		pVtx[1].col = g_DamageScreenColor;

		pVtx[2].col = g_DamageScreenColor;

		pVtx[3].col = g_DamageScreenColor;

		g_pVtxBuffDamageScreen->Unlock();
	}
}

//=============================
// ダメージスクリーンの描画処理
//=============================
void DrawDamageScreen(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffDamageScreen, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, NULL);

	//aブレンディングを加算合成に設定

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//aブレンディングを元に戻す

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================
// ダメージスクリーンの設定処理
//=============================
void SetDamageScreen(void)
{
	g_DamageScreenColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);

	//デバイスの取得

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffDamageScreen->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定（０．０f～１．０ｆで設定）

	pVtx[0].col = g_DamageScreenColor;

	pVtx[1].col = g_DamageScreenColor;

	pVtx[2].col = g_DamageScreenColor;

	pVtx[3].col = g_DamageScreenColor;

	g_pVtxBuffDamageScreen->Unlock();
}