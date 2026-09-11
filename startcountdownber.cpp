//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "startcountdowntext.h"
#include "startcountdown.h"

//マクロ定義

#define STARTCOUNTDOWNBER_SIZE_X (SCREEN_WIDTH / 2)

#define STARTCOUNTDOWNBER_SIZE_Y (25)

//スタートのカウントダウンのテクスチャの列挙型定義

typedef enum
{
	STARTCOUNTDOWNTEXT_START = 0, //Start

	STARTCOUNTDOWNTEXT_1, //1

	STARTCOUNTDOWNTEXT_2, //2

	STARTCOUNTDOWNTEXT_3, //3

	STARTCOUNTDOWNTEXT_MAX //最大数

}STARTCOUNTDOWNTEXT;

//グローバル変数

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStartCountDownBer = NULL;

D3DXVECTOR3 g_posStartCountDownBer; //位置

//======================================
// スタートのカウントダウンのバーの初期化処理
//======================================
void InitStartCountDownBer(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テキストの位置

	g_posStartCountDownBer = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 25, 0.0f); //位置

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffStartCountDownBer,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffStartCountDownBer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = g_posStartCountDownBer.x + sinf(-D3DX_PI * 0.75f) * STARTCOUNTDOWNBER_SIZE_X;

	pVtx[0].pos.y = g_posStartCountDownBer.y + cosf(-D3DX_PI * 0.75f) * STARTCOUNTDOWNBER_SIZE_Y;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_posStartCountDownBer.x + sinf(-D3DX_PI * 0.75f) * STARTCOUNTDOWNBER_SIZE_X;

	pVtx[1].pos.y = g_posStartCountDownBer.y + cosf(-D3DX_PI * 0.75f) * STARTCOUNTDOWNBER_SIZE_Y;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_posStartCountDownBer.x + sinf(-D3DX_PI * 0.25f) * STARTCOUNTDOWNBER_SIZE_X;

	pVtx[2].pos.y = g_posStartCountDownBer.y + cosf(-D3DX_PI * 0.25f) * STARTCOUNTDOWNBER_SIZE_Y;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = 0.0f;

	pVtx[3].pos.y = g_posStartCountDownBer.x + sinf(-D3DX_PI * 0.25f) * STARTCOUNTDOWNBER_SIZE_X;

	pVtx[3].pos.z = g_posStartCountDownBer.y + cosf(-D3DX_PI * 0.25f) * STARTCOUNTDOWNBER_SIZE_Y;

	//rhwの設定 1.0f固定

	pVtx[0].rhw = 1.0f;

	pVtx[1].rhw = 1.0f;

	pVtx[2].rhw = 1.0f;

	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定

	pVtx[0].col = D3DXCOLOR(0.627f, 1.0f, 0.69f, 1.0f);

	pVtx[1].col = D3DXCOLOR(0.627f, 1.0f, 0.69f, 1.0f);

	pVtx[2].col = D3DXCOLOR(0.627f, 1.0f, 0.69f, 1.0f);

	pVtx[3].col = D3DXCOLOR(0.627f, 1.0f, 0.69f, 1.0f);

	//頂点バッファをアンロックする

	g_pVtxBuffStartCountDownBer->Unlock();
}

//======================================
// スタートのカウントダウンのバーの終了処理
//======================================
void UninitStartCountDownBer(void)
{
	//頂点バッファの破棄

	if (g_pVtxBuffStartCountDownBer != NULL)
	{
		g_pVtxBuffStartCountDownBer->Release();

		g_pVtxBuffStartCountDownBer = NULL;
	}
}


//======================================
// スタートのカウントダウンのバーの更新処理
//======================================
void UpdateStartCountDownBer(void)
{
	//スタートのカウンターの獲得

	int nCountDown = GetStartCounter();

	//バーの割合を計算

	int nBer = (nCountDown % 60);

	//パーセントに変換

	float fBer = 60 - (float)nBer;

	fBer = fBer / 60;

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffStartCountDownBer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos = D3DXVECTOR3(g_posStartCountDownBer.x - STARTCOUNTDOWNBER_SIZE_X, g_posStartCountDownBer.y - STARTCOUNTDOWNBER_SIZE_Y, 0.0f);

	pVtx[1].pos = D3DXVECTOR3(g_posStartCountDownBer.x - STARTCOUNTDOWNBER_SIZE_X + (STARTCOUNTDOWNBER_SIZE_X * 2 * fBer), g_posStartCountDownBer.y - STARTCOUNTDOWNBER_SIZE_Y, 0.0f);

	pVtx[2].pos = D3DXVECTOR3(g_posStartCountDownBer.x - STARTCOUNTDOWNBER_SIZE_X, g_posStartCountDownBer.y + STARTCOUNTDOWNBER_SIZE_Y, 0.0f);

	pVtx[3].pos = D3DXVECTOR3(g_posStartCountDownBer.x - STARTCOUNTDOWNBER_SIZE_X + (STARTCOUNTDOWNBER_SIZE_X * 2 * fBer), g_posStartCountDownBer.y + STARTCOUNTDOWNBER_SIZE_Y, 0.0f);

	//頂点バッファをアンロックする

	g_pVtxBuffStartCountDownBer->Unlock();
}

//======================================
// スタートのカウントダウンのバーの描画処理
//======================================
void DrawStartCountDownBer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffStartCountDownBer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定(種類に合わせて設定)

	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}