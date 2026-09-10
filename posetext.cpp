//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "pausetext.h"

//マクロ定義

#define PAUSETEXT_SIZE_X (400)

#define PAUSETEXT_SIZE_Y (100)

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTexturePauseText = NULL; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseText = NULL; //頂点バッファのポインタ

//=========================
//ポーズ画面の初期化処理
//=========================
void InitPauseText(void)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5, 0.0f);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/PAUSE/pausetext.png", //テクスチャのファイル名

		&g_pTexturePauseText);

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffPauseText,

		NULL);

	//デバイスの取得

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffPauseText->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = pos.x + sinf(-D3DX_PI * 0.75f) * PAUSETEXT_SIZE_X;

	pVtx[0].pos.y = pos.y + cosf(-D3DX_PI * 0.75f) * PAUSETEXT_SIZE_Y;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = pos.x + sinf(D3DX_PI * 0.75f) * PAUSETEXT_SIZE_X;

	pVtx[1].pos.y = pos.y + cosf(D3DX_PI * 0.75f) * PAUSETEXT_SIZE_Y;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = pos.x + sinf(-D3DX_PI * 0.25) * PAUSETEXT_SIZE_X;

	pVtx[2].pos.y = pos.y + cosf(-D3DX_PI * 0.25) * PAUSETEXT_SIZE_Y;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = pos.x + sinf(D3DX_PI * 0.25) * PAUSETEXT_SIZE_X;

	pVtx[3].pos.y = pos.y + cosf(D3DX_PI * 0.25) * PAUSETEXT_SIZE_Y;

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

	//テクスチャ座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffPauseText->Unlock();
}

//=========================
//ポーズ画面の終了処理
//=========================
void UninitPauseText(void)
{
	if (g_pTexturePauseText != NULL)
	{
		g_pTexturePauseText->Release();

		g_pTexturePauseText = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffPauseText != NULL)
	{
		g_pVtxBuffPauseText->Release();

		g_pVtxBuffPauseText = NULL;
	}
}

//=========================
//ポーズ画面の更新処理
//=========================
void UpdatePauseText(void)
{

}

//=========================
//ポーズ画面の描画処理
//=========================
void DrawPauseText(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffPauseText, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTexturePauseText); //テクスチャを使用しないときはNULLを指定する

	//ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}