//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "rankingfighter.h"
#include "imagefighter.h"
#include "ranking.h"

//マクロ定義

#define RANKINGFIGHTER_SIZE (75) //ランキングの機体のサイズ

//グローバル変数

PLAYERCA_TEXTURE g_aRankingFighter[NUM_RANKINGPLAYER]; //ランキングの機体のタイプ

LPDIRECT3DTEXTURE9 g_pTextureRankingFighter[PLAYER_MAX] = {}; //テクスチャのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingFighter = NULL; //頂点バッファのポインタ

const char* g_aRankingFighterTexture_Path[PLAYER_MAX] =
{ 
	"Data/TEXTURE/PLAYER/player001.png",

	"Data/TEXTURE/PLAYER/player002.png",

	"Data/TEXTURE/PLAYER/player003.png",

	"Data/TEXTURE/PLAYER/player004.png",

	"Data/TEXTURE/PLAYER/player005.png",

	"Data/TEXTURE/PLAYER/player006.png",

	"Data/TEXTURE/PLAYER/player007.png",

	"Data/TEXTURE/PLAYER/player008.png",
}; //プレイヤーの画像のアドレスの配列

//==================================
//ランキングの機体の描画処理 
//==================================
void InitRankingfighter(void)
{
	int nCount;

	for (nCount = 0; nCount < NUM_RANKINGPLAYER; nCount++)
	{
		g_aRankingFighter[nCount] = GetRankingTexture(nCount);
	}

	D3DXVECTOR3 RankingFramepos = D3DXVECTOR3(315, 
		
		RANKING_INTERVAL, 0.0f); //機体の位置

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	for (nCount = 0; nCount < PLAYER_MAX; nCount++)
	{

		D3DXCreateTextureFromFile(pDevice,

			g_aRankingFighterTexture_Path[nCount], //テクスチャのファイル名

			&g_pTextureRankingFighter[nCount]);
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * NUM_RANKINGPLAYER, //確保するバッファのサイズ（球の数分掛ける）

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffRankingFighter,

		NULL
	);

	//頂点情報の設定

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffRankingFighter->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	for (nCount = 0; nCount < NUM_RANKINGPLAYER; nCount++, pVtx += 4)
	{

		pVtx[0].pos.x = RankingFramepos.x + sinf(-D3DX_PI * 0.75f) * RANKINGFIGHTER_SIZE;

		pVtx[0].pos.y = RankingFramepos.y + (nCount * RANKING_INTERVAL) + cosf(-D3DX_PI * 0.75f) * RANKINGFIGHTER_SIZE;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = RankingFramepos.x + sinf(D3DX_PI * 0.75f) * RANKINGFIGHTER_SIZE;

		pVtx[1].pos.y = RankingFramepos.y + (nCount * RANKING_INTERVAL) + cosf(D3DX_PI * 0.75f) * RANKINGFIGHTER_SIZE;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = RankingFramepos.x + sinf(-D3DX_PI * 0.25) * RANKINGFIGHTER_SIZE;

		pVtx[2].pos.y = RankingFramepos.y + (nCount * RANKING_INTERVAL) + cosf(-D3DX_PI * 0.25) * RANKINGFIGHTER_SIZE;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = RankingFramepos.x + sinf(D3DX_PI * 0.25) * RANKINGFIGHTER_SIZE;

		pVtx[3].pos.y = RankingFramepos.y + (nCount * RANKING_INTERVAL) + cosf(D3DX_PI * 0.25) * RANKINGFIGHTER_SIZE;

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
	}

	g_pVtxBuffRankingFighter->Unlock();
}

//==================================
//ランキングの機体の描画処理 
//==================================
void UninitRankingfighter(void)
{
	//テクスチャの破棄

	for(int nCount = 0; nCount < PLAYER_MAX; nCount++)

	if (g_pTextureRankingFighter[nCount] != NULL)
	{
		g_pTextureRankingFighter[nCount]->Release();

		g_pTextureRankingFighter[nCount] = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffRankingFighter != NULL)
	{
		g_pVtxBuffRankingFighter->Release();

		g_pVtxBuffRankingFighter = NULL;
	}
}

//更新

void UpdateRankingfighter(void)
{

}

//==================================
//ランキングの機体の描画処理 
//==================================
void DrawRankingfighter(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffRankingFighter, 0, sizeof(VERTEX_2D));
	//頂点バッファのポインタ  頂点情報構造体のサイズ

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < NUM_RANKINGPLAYER; nCount++)
	{
		//テクスチャの設定

		pDevice->SetTexture(0, g_pTextureRankingFighter[g_aRankingFighter[nCount]]);

		//ポリゴンの描画
												  //描画する最初の頂点インデックス
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}