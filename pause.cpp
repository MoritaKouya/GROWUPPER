//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "pause.h"
#include "pausetext.h"
#include "pausemenu.h"

//グローバル変数

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL; //頂点バッファのポインタ

//=========================
//ポーズ画面の初期化処理
//=========================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffPause,

		NULL);

	//デバイスの取得

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

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

	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);

	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);

	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);

	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);

	//テクスチャ座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffPause->Unlock();

	//各オブジェクトの初期化処理

	InitPauseText(); //Pause

	InitPauseMenu(); //ポーズメニュー
}

//=========================
//ポーズ画面の終了処理
//=========================
void UninitPause(void)
{
	//頂点バッファの破棄

	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();

		g_pVtxBuffPause = NULL;
	}

	//各オブジェクトの終了処理

	UninitPauseText(); //Pause

	UninitPauseMenu(); //ポーズメニュー
}

//=========================
//ポーズ画面の更新処理
//=========================
void UpdatePause(void)
{
	//各オブジェクトの更新処理

	UpdatePauseText(); //Pause

	UpdatePauseMenu(); //ポーズメニュー
}

//=========================
//ポーズ画面の描画処理
//=========================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, NULL); //テクスチャを使用しないときはNULLを指定する

	//ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//各オブジェクトの描画処理
	
	DrawPauseText(); //Pause

	DrawPauseMenu(); //ポーズメニュー
}