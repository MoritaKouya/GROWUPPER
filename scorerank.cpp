//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "scorerank.h"
#include "score.h"

//マクロ定義

#define SCORERANK_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3 * 2, 0.0f)) //位置

#define SCORERANK_SIZE_X (450) //横の半径

#define SCORERANK_SIZE_Y (225) //縦の半径

#define SCORERANK_EX (10000000) //EXの範囲

#define SCORERANK_A (5000000) //Aの範囲

#define SCORERANK_B (2500000) //Bの範囲

//スコアランクのテクスチャの列挙型定義

typedef enum
{
	SCORERANK_0 = 0, //C

	SCORERANK_1, //B

	SCORERANK_2, //A

	SCORERANK_3, //EX

	SCORERANK_MAX //最大数
}SCORERANK_TEXTURE;

D3DXVECTOR3 g_pos; //位置

SCORERANK_TEXTURE g_ScoreRank; //ランクを代入

LPDIRECT3DTEXTURE9 g_pTextureScoreRank[SCORERANK_MAX] = {}; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScoreRank = NULL; //頂点バッファへのポインタ

const char* g_aScoreRankTexture_Path[SCORERANK_MAX] =
{
	"Data/TEXTURE/SCORERANK/scorerank000.png",

	"Data/TEXTURE/SCORERANK/scorerank001.png",

	"Data/TEXTURE/SCORERANK/scorerank002.png",

	"Data/TEXTURE/SCORERANK/scorerank003.png",
}; //テクスチャのアドレスの構造体

//=========================
// スコアランクの初期化処理
//=========================
void InitScoreRank(void)
{
	int nCount,
		
		nScore; //スコアを代入する

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得

	pDevice = GetDevice();

	g_pos = SCORERANK_POS;

	//テクスチャの読み込み

	for (nCount = 0; nCount < SCORERANK_MAX; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice,

			g_aScoreRankTexture_Path[nCount], //テクスチャのファイル名

			&g_pTextureScoreRank[nCount]);
	}

	//スコアランクの代入

	nScore = GetScore();

	if (SCORERANK_EX <= nScore)
	{
		g_ScoreRank = SCORERANK_3;
	}
	else if (SCORERANK_A <= nScore)
	{
		g_ScoreRank = SCORERANK_2;
	}
	else if (SCORERANK_B <= nScore)
	{
		g_ScoreRank = SCORERANK_1;
	}
	else
	{
		g_ScoreRank = SCORERANK_0;
	}
	
	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffScoreRank,

		NULL
	);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffScoreRank->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = g_pos.x + sinf(-D3DX_PI * 0.75f) * SCORERANK_SIZE_X;

	pVtx[0].pos.y = g_pos.y + cosf(-D3DX_PI * 0.75f) * SCORERANK_SIZE_Y;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_pos.x + sinf(D3DX_PI * 0.75f) * SCORERANK_SIZE_X;

	pVtx[1].pos.y = g_pos.y + cosf(D3DX_PI * 0.75f) * SCORERANK_SIZE_Y;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_pos.x + sinf(-D3DX_PI * 0.25) * SCORERANK_SIZE_X;

	pVtx[2].pos.y = g_pos.y + cosf(-D3DX_PI * 0.25) * SCORERANK_SIZE_Y;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_pos.x + sinf(D3DX_PI * 0.25) * SCORERANK_SIZE_X;

	pVtx[3].pos.y = g_pos.y + cosf(D3DX_PI * 0.25) * SCORERANK_SIZE_Y;

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

	//テクスチャ座標

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffScoreRank->Unlock();

}

//=========================
// スコアランクの終了処理
//=========================
void UninitScoreRank(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < SCORERANK_MAX; nCnt++)
	{
		if (g_pTextureScoreRank[nCnt] != NULL)
		{
			g_pTextureScoreRank[nCnt]->Release();

			g_pTextureScoreRank[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄

	if (g_pVtxBuffScoreRank != NULL)
	{
		g_pVtxBuffScoreRank->Release();

		g_pVtxBuffScoreRank = NULL;
	}
}

//=========================
// スコアランクの更新処理
//=========================
void UpdateScoreRank(void)
{

}

//=========================
// スコアランクの描画処理
//=========================
void DrawScoreRank(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffScoreRank, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureScoreRank[g_ScoreRank]);

	///ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}