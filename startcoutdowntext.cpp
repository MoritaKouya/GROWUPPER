//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "startcountdowntext.h"
#include "startcountdown.h"

//マクロ定義

#define STARTCOUNTDOWNTEXT_SIZE_X (300)

#define STARTCOUNTDOWNTEXT_SIZE_Y (100)

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

LPDIRECT3DTEXTURE9 g_apTextureStartCountDownText[STARTCOUNTDOWNTEXT_MAX] = {};

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStartCountDownText = NULL;

const char* g_aStartCountDownTextTexture_Path[STARTCOUNTDOWNTEXT_MAX] =
{
	"Data/TEXTURE/GAMESTART/gamestart000.png",

	"Data/TEXTURE/GAMESTART/gamestart001.png",

	"Data/TEXTURE/GAMESTART/gamestart002.png",

	"Data/TEXTURE/GAMESTART/gamestart003.png",
}; //テクスチャの相対パスの構造体


//======================================
// スタートのカウントダウンの文字の初期化処理
//======================================
void InitStartCountDownText(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み

	for (int nCount = 0; nCount < STARTCOUNTDOWNTEXT_MAX; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice,

			g_aStartCountDownTextTexture_Path[nCount], //テクスチャのファイル名

			&g_apTextureStartCountDownText[nCount]);
	}

	//テキストの位置

	D3DXVECTOR3 posStartCountDownText = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f); //位置

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffStartCountDownText,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffStartCountDownText->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = posStartCountDownText.x + sinf(-D3DX_PI * 0.75f) * STARTCOUNTDOWNTEXT_SIZE_X;

	pVtx[0].pos.y = posStartCountDownText.y + cosf(-D3DX_PI * 0.75f) * STARTCOUNTDOWNTEXT_SIZE_Y;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = posStartCountDownText.x + sinf(D3DX_PI * 0.75f) * STARTCOUNTDOWNTEXT_SIZE_X;

	pVtx[1].pos.y = posStartCountDownText.y + cosf(D3DX_PI * 0.75f) * STARTCOUNTDOWNTEXT_SIZE_Y;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = posStartCountDownText.x + sinf(-D3DX_PI * 0.25) * STARTCOUNTDOWNTEXT_SIZE_X;

	pVtx[2].pos.y = posStartCountDownText.y + cosf(-D3DX_PI * 0.25) * STARTCOUNTDOWNTEXT_SIZE_Y;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = posStartCountDownText.x + sinf(D3DX_PI * 0.25) * STARTCOUNTDOWNTEXT_SIZE_X;

	pVtx[3].pos.y = posStartCountDownText.y + cosf(D3DX_PI * 0.25) * STARTCOUNTDOWNTEXT_SIZE_Y;

	pVtx[3].pos.z = 0.0f;

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

	//テクスチャ座標

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファをアンロックする

	g_pVtxBuffStartCountDownText->Unlock();
}

//======================================
// スタートのカウントダウンの文字の終了処理
//======================================
void UninitStartCountDownText(void)
{
	//テクスチャの破棄

	for (int nCntTexture = 0; nCntTexture < STARTCOUNTDOWNTEXT_MAX; nCntTexture++)
	{
		if (g_apTextureStartCountDownText[nCntTexture] != NULL)
		{
			g_apTextureStartCountDownText[nCntTexture]->Release();

			g_apTextureStartCountDownText[nCntTexture] = NULL;
		}
	}

	//頂点バッファの破棄

	if (g_pVtxBuffStartCountDownText != NULL)
	{
		g_pVtxBuffStartCountDownText->Release();

		g_pVtxBuffStartCountDownText = NULL;
	}
}


//======================================
// スタートのカウントダウンの文字の更新処理
//======================================
void UpdateStartCountDownText(void)
{

}

//======================================
// スタートのカウントダウンの文字の描画処理
//======================================
void DrawStartCountDownText(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//スタートのカウンターの獲得

	int nCountDown = GetStartCounter();

	//テクスチャのタイプを計算

	int nType = nCountDown / 60;

	if (STARTCOUNTDOWNTEXT_MAX <= nType)
	{ //最大値以上の場合

		//最初のテクスチャを代入

		nType =  STARTCOUNTDOWNTEXT_MAX - 1;
	}

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffStartCountDownText, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定(種類に合わせて設定)

	pDevice->SetTexture(0, g_apTextureStartCountDownText[nType]);

	//ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}