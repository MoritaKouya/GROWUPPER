//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "rankingframe.h"
#include "ranking.h"

//マクロ定義

#define MAX_COLUMN_FRAME (1) //列数 

#define MAX_LINES_FRAME (4) //行数

#define RANKINGFRAME_SIZE_X (855) //フレームの横のサイズ

#define RANKINGFRAME_SIZE_Y (100) //フレームの縦のサイズ

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureRankingFrame = NULL; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingFrame = NULL; //頂点バッファのポインタ

//==================================
//ランキングのフレームの初期化処理 
//==================================
void InitRankingFrame(void)
{

	D3DXVECTOR3 RankingFramepos = D3DXVECTOR3(SCREEN_WIDTH / 2, RANKING_INTERVAL, 0.0f); //フレームの位置
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/RANKING/rankingframe.png", //テクスチャのファイル名

		&g_pTextureRankingFrame);

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_RANKINGPLAYER, //確保するバッファのサイズ
											   //sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffRankingFrame,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffRankingFrame->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_RANKINGPLAYER; nCount++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos.x = RankingFramepos.x + sinf(-D3DX_PI * 0.75f) * RANKINGFRAME_SIZE_X;

		pVtx[0].pos.y = RankingFramepos.y + (nCount * RANKING_INTERVAL) + cosf(-D3DX_PI * 0.75f) * RANKINGFRAME_SIZE_Y;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = RankingFramepos.x + sinf(D3DX_PI * 0.75f) * RANKINGFRAME_SIZE_X;

		pVtx[1].pos.y = RankingFramepos.y + (nCount * RANKING_INTERVAL) + cosf(D3DX_PI * 0.75f) * RANKINGFRAME_SIZE_Y;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = RankingFramepos.x + sinf(-D3DX_PI * 0.25) * RANKINGFRAME_SIZE_X;

		pVtx[2].pos.y = RankingFramepos.y + (nCount * RANKING_INTERVAL) + cosf(-D3DX_PI * 0.25) * RANKINGFRAME_SIZE_Y;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = RankingFramepos.x + sinf(D3DX_PI * 0.25) * RANKINGFRAME_SIZE_X;

		pVtx[3].pos.y = RankingFramepos.y + (nCount * RANKING_INTERVAL) + cosf(D3DX_PI * 0.25) * RANKINGFRAME_SIZE_Y;

		pVtx[3].pos.z = 0.0f;

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

		pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN_FRAME) * (nCount % MAX_COLUMN_FRAME), (1.0f / MAX_LINES_FRAME) * (nCount / MAX_COLUMN_FRAME));

		pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN_FRAME) * ((nCount % MAX_COLUMN_FRAME) + 1.0f), (1.0f / MAX_LINES_FRAME) * (nCount / MAX_COLUMN_FRAME));

		pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN_FRAME) * (nCount % MAX_COLUMN_FRAME), (1.0f / MAX_LINES_FRAME) * (nCount / MAX_COLUMN_FRAME) + (1.0f / MAX_LINES_FRAME));

		pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN_FRAME) * ((nCount % MAX_COLUMN_FRAME) + 1.0f), (1.0f / MAX_LINES_FRAME) * (nCount / MAX_COLUMN_FRAME) + (1.0f / MAX_LINES_FRAME));

	}

	//頂点バッファをアンロックする

	g_pVtxBuffRankingFrame->Unlock();
}

//==================================
//ランキングのフレームの終了処理 
//==================================
void UninitRankingFrame(void)
{
	//テクスチャの破棄

	if (g_pTextureRankingFrame != NULL)
	{
		g_pTextureRankingFrame->Release();

		g_pTextureRankingFrame = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffRankingFrame != NULL)
	{
		g_pVtxBuffRankingFrame->Release();

		g_pVtxBuffRankingFrame = NULL;
	}
}

//==================================
//ランキングのフレームの更新処理 
//==================================
void UpdateRankingFrame(void)
{

}

//==================================
//ランキングのフレームの描画処理 
//==================================
void DrawRankingFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffRankingFrame, 0, sizeof(VERTEX_2D));
	//頂点バッファのポインタ  頂点情報構造体のサイズ

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureRankingFrame);

	for (int nCount = 0; nCount < NUM_RANKINGPLAYER; nCount++)
	{
		//ポリゴンの描画
												  //描画する最初の頂点インデックス
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}
