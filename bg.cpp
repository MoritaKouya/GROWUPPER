//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================

#include "main.h"

#include "bg.h"

//テクスチャ番号の列挙型

typedef enum
{
	TEXTURE_0 = 0, //星１

	TEXTURE_1, //星２

	TEXTURE_2, //星３

	TEXTURE_3, //月

	TEXTURE_MAX //テクスチャの最大数

}TEXTURENAME;

//グローバル変数

LPDIRECT3DTEXTURE9 g_apTextureBG[TEXTURE_MAX]; //テクスチャへのポインタ（３枚分）

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL; //頂点バッファへのポインタ

float g_aTexV[TEXTURE_MAX]; //テクスチャのV座標

//ファイル名

const char* g_aBgTexture_Path[TEXTURE_MAX] =
{
	"Data/TEXTURE/BG/bg100.png", //星１

	"Data/TEXTURE/BG/bg101.png", //星２

	"Data/TEXTURE/BG/bg102.png", //星３

	"Data/TEXTURE/BG/moon.png", //月
};
//==================================
// 背景の初期化処理
//==================================
void InitBg(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	int nCntBG;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	for (nCntBG = 0; nCntBG < TEXTURE_MAX; nCntBG++)
	{
		D3DXCreateTextureFromFile(pDevice,

		g_aBgTexture_Path[nCntBG], //テクスチャのファイル名

		&g_apTextureBG[nCntBG]);
	}

	//テクスチャ座標(v値)の開始位置

	for (nCntBG = 0; nCntBG < TEXTURE_MAX; nCntBG++)
	{
		g_aTexV[nCntBG] = 0.0f;
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TEXTURE_MAX, //確保するバッファのサイズ
											   //sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffBg,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);	

	for (nCntBG = 0; nCntBG < TEXTURE_MAX; nCntBG++ , pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);

		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);

		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		//rhwの設定 1.0f固定

		pVtx[0].rhw = 1.0f;

		pVtx[1].rhw = 1.0f;

		pVtx[2].rhw = 1.0f;

		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定

		pVtx[0].tex = D3DXVECTOR2(0.0f, g_aTexV[nCntBG]);

		pVtx[1].tex = D3DXVECTOR2(1.0f, g_aTexV[nCntBG]);

		pVtx[2].tex = D3DXVECTOR2(0.0f, g_aTexV[nCntBG] + 1.0f);

		pVtx[3].tex = D3DXVECTOR2(1.0f, g_aTexV[nCntBG] + 1.0f);

	}

	//頂点バッファをアンロックする

	g_pVtxBuffBg->Unlock();
}

//==================================
// 背景の終了処理
//==================================
void UninitBg(void)
{
	int nCntBG;

	//テクスチャの破棄

	for (nCntBG = 0; nCntBG < TEXTURE_MAX; nCntBG++)
	{
		if (g_apTextureBG[nCntBG] != NULL)
		{
			g_apTextureBG[nCntBG]->Release();

			g_apTextureBG[nCntBG] = NULL;
		}
	}
	//頂点バッファの破棄

	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();

		g_pVtxBuffBg = NULL;
	}
}

//==================================
// 背景の更新処理
//==================================
void UpdateBg(void)
{
	int nCntBG;

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < TEXTURE_MAX - 1; nCntBG++ , pVtx += 4)
	{
		//テクスチャ座標の開始位置（v値）の更新

		g_aTexV[nCntBG] -= (nCntBG + 1) * 0.002f;

		//テクスチャの更新

		pVtx[0].tex = D3DXVECTOR2(0.0f, g_aTexV[nCntBG]);

		pVtx[1].tex = D3DXVECTOR2(1.0f, g_aTexV[nCntBG]);

		pVtx[2].tex = D3DXVECTOR2(0.0f, g_aTexV[nCntBG] + 1.0f);

		pVtx[3].tex = D3DXVECTOR2(1.0f, g_aTexV[nCntBG] + 1.0f);
	}

	//テクスチャの更新

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする

	g_pVtxBuffBg->Unlock();
}

//==================================
// 背景の描画処理
//==================================
void DrawBg(void)
{

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	int nCntBG;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(VERTEX_2D));
	//頂点バッファのポインタ  頂点情報構造体のサイズ

    //頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < TEXTURE_MAX; nCntBG++)
	{
		//テクスチャの設定

		pDevice->SetTexture(0, g_apTextureBG[nCntBG]);

		//ポリゴンの描画
												  //描画する最初の頂点インデックス
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG * 4, 2);
	}
}