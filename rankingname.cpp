//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "outputname.h"
#include "inputname.h"
#include "ranking.h"

//マクロ定義

#define NAME_SIZE (50) //文字のサイズ

#define RANKINGNAME_INTERVAL (NAME_SIZE + 5) //文字の間隔

//グローバル変数

LPDIRECT3DTEXTURE9 g_apTextureRankingName[ALPHABETCHART_MAX] = {}; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingName = NULL; //頂点バッファのポインタ

const char* g_aRankingNameTexture_Path[ALPHABETCHART_MAX] =
{
	"Data/TEXTURE/SET/alphabetchart000.png",

	"Data/TEXTURE/SET/alphabetchart001.png",

}; //テクスチャのアドレスの構造体

Name g_aRankingName[NUM_RANKINGPLAYER][MAX_NAME]; //名前の情報を代入する変数

//==================================
//ゲーム画面の名前の初期化処理 
//==================================
void InitRankingName(void)
{
	int nCount;

	for (nCount = 0; nCount < NUM_RANKINGPLAYER * MAX_NAME; nCount++)
	{
		g_aRankingName[nCount / 8][nCount % 8] = GetRankingName(nCount / 8, nCount % 8);
	}

	D3DXVECTOR3 g_aRankingNamepos =

		D3DXVECTOR3(400, RANKING_INTERVAL, 0.0f);

	//デバイスの取得

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	pDevice = GetDevice();

	//テクスチャの読み込み

	for (nCount = 0; nCount < ALPHABETCHART_MAX; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice,

			g_aRankingNameTexture_Path[nCount], //テクスチャのファイル名

			&g_apTextureRankingName[nCount]);
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NAME * NUM_RANKINGPLAYER, //確保するバッファのサイズ
											   //sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffRankingName,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffRankingName->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < NUM_RANKINGPLAYER * MAX_NAME; nCount++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos.x = g_aRankingNamepos.x + (nCount % 8 * RANKINGNAME_INTERVAL) + sinf(-D3DX_PI * 0.75f) * NAME_SIZE;

		pVtx[0].pos.y = g_aRankingNamepos.y + (nCount / 8 * RANKING_INTERVAL) + cosf(-D3DX_PI * 0.75f) * NAME_SIZE;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aRankingNamepos.x + (nCount % 8 * RANKINGNAME_INTERVAL) + sinf(D3DX_PI * 0.75f) * NAME_SIZE;

		pVtx[1].pos.y = g_aRankingNamepos.y + (nCount / 8 * RANKING_INTERVAL) + cosf(D3DX_PI * 0.75f) * NAME_SIZE;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aRankingNamepos.x + (nCount % 8 * RANKINGNAME_INTERVAL) + sinf(-D3DX_PI * 0.25) * NAME_SIZE;

		pVtx[2].pos.y = g_aRankingNamepos.y + (nCount / 8 * RANKING_INTERVAL) + cosf(-D3DX_PI * 0.25) * NAME_SIZE;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aRankingNamepos.x + (nCount % 8 * RANKINGNAME_INTERVAL) + sinf(D3DX_PI * 0.25) * NAME_SIZE;

		pVtx[3].pos.y = g_aRankingNamepos.y + (nCount / 8 * RANKING_INTERVAL) + cosf(D3DX_PI * 0.25) * NAME_SIZE;

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

		pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_aRankingName[nCount / 8][nCount % 8].nName % MAX_COLUMN), (1.0f / MAX_LINES) * (g_aRankingName[nCount / 8][nCount % 8].nName / MAX_COLUMN));

		pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_aRankingName[nCount / 8][nCount % 8].nName % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_aRankingName[nCount / 8][nCount % 8].nName / MAX_COLUMN));

		pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_aRankingName[nCount / 8][nCount % 8].nName % MAX_COLUMN), (1.0f / MAX_LINES) * (g_aRankingName[nCount / 8][nCount % 8].nName / MAX_COLUMN) + (1.0f / MAX_LINES));

		pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_aRankingName[nCount / 8][nCount % 8].nName % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_aRankingName[nCount / 8][nCount % 8].nName / MAX_COLUMN) + (1.0f / MAX_LINES));

	}

	//頂点バッファをアンロックする

	g_pVtxBuffRankingName->Unlock();
}

//==================================
//ゲーム画面の名前の終了処理 
//==================================
void UninitRankingName(void)
{
	//テクスチャの破棄

	for (int nCount = 0; nCount < ALPHABETCHART_MAX; nCount++)
	{
		if (g_apTextureRankingName[nCount] != NULL)
		{
			g_apTextureRankingName[nCount]->Release();

			g_apTextureRankingName[nCount] = NULL;
		}
	}

	//頂点バッファの破棄

	if (g_pVtxBuffRankingName != NULL)
	{
		g_pVtxBuffRankingName->Release();

		g_pVtxBuffRankingName = NULL;
	}
}

//==================================
//ゲーム画面の名前の更新処理 
//==================================
void UpdateRankingName(void)
{

}

//==================================
//ゲーム画面の名前の描画処理 
//==================================
void DrawRankingName(void)
{
	int nCount;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffRankingName, 0, sizeof(VERTEX_2D));
	//頂点バッファのポインタ  頂点情報構造体のサイズ

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCount = 0; nCount < NUM_RANKINGPLAYER * MAX_NAME; nCount++)
	{
		//テクスチャの設定

		pDevice->SetTexture(0, g_apTextureRankingName[g_aRankingName[nCount / 8][nCount % 8].ntype]);

		//ポリゴンの描画
												  //描画する最初の頂点インデックス
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);

	}
}