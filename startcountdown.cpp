//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "startcountdown.h"
#include "startcountdowntext.h"
#include "startcountdownber.h"
#include "sound.h"

//グローバル変数

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStartCountDownScreen = NULL; //頂点バッファのポインタ

int nStartCountDownCounter; //ゲームのスタート画面のカウンター

//=================================
// スタートのカウントダウンの初期化処理
//=================================
void InitStartCountDown(void)
{
	nStartCountDownCounter = 4 * 60;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
													 //sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffStartCountDownScreen,

		NULL);

	//デバイスの取得

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffStartCountDownScreen->Lock(0, 0, (void**)&pVtx, 0);

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

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);

	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);

	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);

	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);

	//テクスチャ座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffStartCountDownScreen->Unlock();

	//各オブジェクトの描画処理

	InitStartCountDownText(); //文字

	InitStartCountDownBer(); //バー
}

//=================================
// スタートのカウントダウンの終了処理
//=================================
void UninitStartCountDown(void)
{
	if (g_pVtxBuffStartCountDownScreen != NULL)
	{
		g_pVtxBuffStartCountDownScreen->Release();

		g_pVtxBuffStartCountDownScreen = NULL;
	}

	//各オブジェクトの描画処理

	UninitStartCountDownText(); //文字

	UninitStartCountDownBer(); //バー
}

//=================================
// スタートのカウントダウンの更新処理
//=================================
void UpdateStartCountDown(void)
{
	if(nStartCountDownCounter == 4 * 60) //最初の場合
	{
		PlaySound(SOUND_LABEL_SE_COUNTDOWN);	
	}

	nStartCountDownCounter--;

	//各オブジェクトの更新処理

	UpdateStartCountDownText(); //文字

	UpdateStartCountDownBer(); //バー
}

//=================================
// スタートのカウントダウンの描画処理
//=================================
void DrawStartCountDown(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffStartCountDownScreen, 0, sizeof(VERTEX_2D));

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

	//各オブジェクトの描画処理

	DrawStartCountDownText(); //文字

	DrawStartCountDownBer(); //バー
}

//=================================
// カウンターの取得処理
//=================================
int GetStartCounter(void)
{
	return nStartCountDownCounter;
}