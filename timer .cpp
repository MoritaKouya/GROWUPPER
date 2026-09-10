//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "timer.h"

//マクロ定義

#define NUM_PLACE (4) //タイマーの桁数

#define MAX_ANIM (11) //アニメーションの最大数

#define MAX_COLUMN (11) //列数 

#define MAX_LINES (1) //行数

#define REMAINING_TIME (60 * 3) //タイムリミット

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;

D3DXVECTOR3 g_posTimer; //タイマーの位置

int g_nTimer; //タイマーの値

//========================
// タイマーの初期化処理	
//========================
void InitTimer(void)
{
	int nCntPlace;

	int aTexU[NUM_PLACE] = { 0 }; //各桁の数値を格納

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/NUMBER/timernumber001.png", //テクスチャのファイル名

		&g_pTextureTimer);

	g_posTimer = D3DXVECTOR3((SCREEN_WIDTH / 2) -70, 50.0f, 0.0f); //位置を初期化

	g_nTimer = REMAINING_TIME; //値を初期化する

	aTexU[0] = g_nTimer / 60 / 60;

	aTexU[1] = 10;

	aTexU[2] = g_nTimer / 60 % 60 / 10;

	aTexU[3] = g_nTimer / 60 % 60 % 10;

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な超点数

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffTimer,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos.x = g_posTimer.x + (nCntPlace * 35) + sinf(-D3DX_PI * 0.75f) * 25;

		pVtx[0].pos.y = g_posTimer.y + cosf(-D3DX_PI * 0.75f) * 50;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_posTimer.x + (nCntPlace * 35) + sinf(D3DX_PI * 0.75f) * 25;

		pVtx[1].pos.y = g_posTimer.y + cosf(D3DX_PI * 0.75f) * 50;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_posTimer.x + (nCntPlace * 35) + sinf(-D3DX_PI * 0.25) * 25;

		pVtx[2].pos.y = g_posTimer.y + cosf(-D3DX_PI * 0.25) * 50;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_posTimer.x + (nCntPlace * 35) + sinf(D3DX_PI * 0.25) * 25;

		pVtx[3].pos.y = g_posTimer.y + cosf(D3DX_PI * 0.25) * 50;

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

		pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (aTexU[nCntPlace] % MAX_COLUMN), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN));

		pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((aTexU[nCntPlace] % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN));

		pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (aTexU[nCntPlace] % MAX_COLUMN), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN) + (1.0f / MAX_LINES));

		pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((aTexU[nCntPlace] % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN) + (1.0f / MAX_LINES));
	}

	//頂点バッファをアンロックする

	g_pVtxBuffTimer->Unlock();

}

//========================
// タイマーの終了処理	
//========================
void UninitTimer(void)
{
	//テクスチャの破棄

	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();

		g_pTextureTimer = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();

		g_pVtxBuffTimer = NULL;
	}
}

//========================
// タイマーの更新処理	
//========================
void UpdateTimer(void)
{
		SubTimer(); //タイマーの減算処理
}

//========================
// タイマーの描画処理	
//========================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntPlace;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定(種類に合わせて設定)

	pDevice->SetTexture(0, g_pTextureTimer);

	for (nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		//ポリゴンの描画

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPlace * 4, 2);
	}
}

//========================
// タイマーの減算処理処理	
//========================
void SubTimer()
{
	int nCntPlace;

	int aTexU[NUM_PLACE]; //各桁の数値を格納

	g_nTimer--;

	aTexU[0] = g_nTimer / 60 / 60;

	aTexU[1] = 10;

	aTexU[2] = g_nTimer / 60 % 60 / 10;

	aTexU[3] = g_nTimer / 60 % 60 % 10;

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
	{
		//テクスチャ座標の設定

		pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (aTexU[nCntPlace] % MAX_COLUMN), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN));

		pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((aTexU[nCntPlace] % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN));

		pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (aTexU[nCntPlace] % MAX_COLUMN), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN) + (1.0f / MAX_LINES));

		pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((aTexU[nCntPlace] % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN) + (1.0f / MAX_LINES));

	}

	//頂点バッファをアンロックする

	g_pVtxBuffTimer->Unlock();

}

//========================
// タイマーの取得処理
//========================
int GetTimer()
{
	return g_nTimer;
}