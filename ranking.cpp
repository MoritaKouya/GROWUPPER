//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "ranking.h"
#include "input.h"
#include "rankingframe.h"
#include "rankingfighter.h"
#include "rankingname.h"
#include "rankingscore.h"

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL; //頂点バッファのポインタ

//==================================
//ランキング画面の初期化処理 
//==================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/BG/Hangar.png", //テクスチャのファイル名

		&g_pTextureRanking);

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
											   //sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffRanking,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

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

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする

	g_pVtxBuffRanking->Unlock();

	//各オブジェクトの初期化処理

	InitRankingFrame(); //フレーム

	InitRankingfighter(); //機体

	InitRankingName(); //名前

	InitRankingScore(); //スコア
}

//==================================
//ランキング画面の終了処理 
//==================================
void UninitRanking(void)
{
	//テクスチャの破棄

	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();

		g_pTextureRanking = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();

		g_pVtxBuffRanking = NULL;
	}

	//各オブジェクトの終了処理

	UninitRankingFrame(); //フレーム

	UninitRankingfighter(); //機体

	UninitRankingName(); //名前

	UninitRankingScore(); //スコア
}

//==================================
//ランキング画面の更新処理 
//==================================
void UpdateRanking(void)
{
	UpdateRankingScore();
}

//==================================
//ランキング画面の描画処理 
//==================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));
	//頂点バッファのポインタ  頂点情報構造体のサイズ

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureRanking);

	//ポリゴンの描画
											  //描画する最初の頂点インデックス
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//各オブジェクトの描画処理

	DrawRankingFrame(); //フレーム

	DrawRankingfighter(); //機体
	
	DrawRankingName(); //名前

	DrawRankingScore(); //スコア
}