//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "rankingscore.h"
#include "ranking.h"
#include "score.h"

//マクロ定義

#define RANKINGSCORE_SIZE_X (25)

#define RANKINGSCORE_SIZE_Y (50)

#define RANKINGSCORE_INTERVAL (RANKINGSCORE_SIZE_X + 10)

#define NUM_PLACE (8) //ランキングスコアの桁数

#define MAX_COLUMN_SCORE (10) //列数 

#define MAX_LINES_SCORE (1) //行数

//グローバル変数

LPDIRECT3DTEXTURE9 g_apTextureRankingScore[SCORE_MAX] = {};

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingScore = NULL;

int g_nRankingScore[NUM_RANKINGPLAYER]; //ランキングスコアの値

int g_aTexU[NUM_RANKINGPLAYER][NUM_PLACE]; //各桁の数値を格納

int g_nBlinkingCounter[NUM_RANKINGPLAYER]; //点滅のカウント

bool g_bBlinkingScore[NUM_RANKINGPLAYER]; //プレイヤーのランキングスコアが点滅するかどうか（trueならするfalseならしない）

SCORERANK g_type[SCORE_MAX]; //ランキングスコアのタイプを代入する変数

const char* g_aRankingSCORERANK_Path[SCORE_MAX] =
{
	"Data/TEXTURE/NUMBER/number000.png",

	"Data/TEXTURE/NUMBER/number001.png",

	"Data/TEXTURE/NUMBER/number002.png",

	"Data/TEXTURE/NUMBER/number003.png",

	"Data/TEXTURE/NUMBER/number004.png",
}; //テクスチャの相対パスの構造体

//========================
// ランキングスコアの初期化処理	
//========================
void InitRankingScore(void)
{
	int nCount;
	
	for (nCount = 0; nCount < NUM_RANKINGPLAYER; nCount++)
	{
		g_nBlinkingCounter[nCount] = 0;

		g_bBlinkingScore[nCount] = false;
	}

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み

	for (nCount = 0; nCount < SCORE_MAX; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice,

			g_aRankingSCORERANK_Path[nCount], //テクスチャのファイル名

			&g_apTextureRankingScore[nCount]);
	}

	D3DXVECTOR3 posRankingScore = D3DXVECTOR3(900, RANKING_INTERVAL, 0.0f); //位置

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE * NUM_RANKINGPLAYER, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffRankingScore,

		NULL);

	//数値を代入する

	for (nCount = 0; nCount < NUM_RANKINGPLAYER; nCount++)
	{
		g_nRankingScore[nCount] = GetRankingScore(nCount);
	}

	//各桁の数値を求める

	for (nCount = 0; nCount < NUM_RANKINGPLAYER; nCount++)
	{
		g_aTexU[nCount][0] = g_nRankingScore[nCount] / 10000000;

		g_aTexU[nCount][1] = g_nRankingScore[nCount] % 10000000 / 1000000;

		g_aTexU[nCount][2] = g_nRankingScore[nCount] % 1000000 / 100000;

		g_aTexU[nCount][3] = g_nRankingScore[nCount] % 100000 / 10000;

		g_aTexU[nCount][4] = g_nRankingScore[nCount] % 10000 / 1000;

		g_aTexU[nCount][5] = g_nRankingScore[nCount] % 1000 / 100;

		g_aTexU[nCount][6] = g_nRankingScore[nCount] % 100 / 10;

		g_aTexU[nCount][7] = g_nRankingScore[nCount] % 10 / 1;

		//銀色にする

		if (g_nRankingScore[nCount] >= SCORERANK_1) //スコアが5000000以上の場合
		{
			g_type[nCount] = SCORE_1; //銀色
		}

		//金色にする

		if (g_nRankingScore[nCount] >= SCORERANK_2) //スコアが5000000以上の場合
		{
			g_type[nCount] = SCORE_2; //金色
		}

		//虹色にする

		if (g_nRankingScore[nCount] >= SCORERANK_3) //スコアが10000000以上の場合
		{
			g_type[nCount] = SCORE_3;//虹色
		}

		//青色にする

		if (g_nRankingScore[nCount] >= SCORERANK_4) //スコアが10000000以上の場合
		{
			g_type[nCount] = SCORE_4;//青色
		}
		
	}

	//点滅する文字の判定

	for (nCount = 0; nCount < NUM_RANKINGPLAYER - 1; nCount++)
	{
		if (g_nRankingScore[3] == g_nRankingScore[nCount])
		{
			g_bBlinkingScore[nCount] = true;

			g_bBlinkingScore[3] = true;

			break;
		}
	}

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < NUM_PLACE * NUM_RANKINGPLAYER; nCount++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos.x = posRankingScore.x + (nCount % 8 * RANKINGSCORE_INTERVAL) + sinf(-D3DX_PI * 0.75f) * RANKINGSCORE_SIZE_X;

		pVtx[0].pos.y = posRankingScore.y + (nCount / 8 * RANKING_INTERVAL) + cosf(-D3DX_PI * 0.75f) * RANKINGSCORE_SIZE_Y;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = posRankingScore.x + (nCount % 8 * RANKINGSCORE_INTERVAL) + sinf(D3DX_PI * 0.75f) * RANKINGSCORE_SIZE_X;

		pVtx[1].pos.y = posRankingScore.y + (nCount / 8 * RANKING_INTERVAL) + cosf(D3DX_PI * 0.75f) * RANKINGSCORE_SIZE_Y;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = posRankingScore.x + (nCount % 8 * RANKINGSCORE_INTERVAL) + sinf(-D3DX_PI * 0.25) * RANKINGSCORE_SIZE_X;

		pVtx[2].pos.y = posRankingScore.y + (nCount / 8 * RANKING_INTERVAL) + cosf(-D3DX_PI * 0.25) * RANKINGSCORE_SIZE_Y;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = posRankingScore.x + (nCount % 8 * RANKINGSCORE_INTERVAL) + sinf(D3DX_PI * 0.25) * RANKINGSCORE_SIZE_X;

		pVtx[3].pos.y = posRankingScore.y + (nCount / 8 * RANKING_INTERVAL) + cosf(D3DX_PI * 0.25) * RANKINGSCORE_SIZE_Y;

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

		//テクスチャ座標の設定

		pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN_SCORE) * (g_aTexU[nCount / 8][nCount % 8] % MAX_COLUMN_SCORE), (1.0f / MAX_LINES_SCORE) * (g_aTexU[nCount / 8][nCount % 8] / MAX_COLUMN_SCORE));

		pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN_SCORE) * ((g_aTexU[nCount / 8][nCount % 8] % MAX_COLUMN_SCORE) + 1.0f), (1.0f / MAX_LINES_SCORE) * (g_aTexU[nCount / 8][nCount % 8] / MAX_COLUMN_SCORE));

		pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN_SCORE) * (g_aTexU[nCount / 8][nCount % 8] % MAX_COLUMN_SCORE), (1.0f / MAX_LINES_SCORE) * (g_aTexU[nCount / 8][nCount % 8] / MAX_COLUMN_SCORE) + (1.0f / MAX_LINES_SCORE));

		pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN_SCORE) * ((g_aTexU[nCount / 8][nCount % 8] % MAX_COLUMN_SCORE) + 1.0f), (1.0f / MAX_LINES_SCORE) * (g_aTexU[nCount / 8][nCount % 8] / MAX_COLUMN_SCORE) + (1.0f / MAX_LINES_SCORE));
	}

	//頂点バッファをアンロックする

	g_pVtxBuffRankingScore->Unlock();
}

//========================
// ランキングスコアの終了処理	
//========================
void UninitRankingScore(void)
{
	//テクスチャの破棄

	for (int nCntTexture = 0; nCntTexture < SCORE_MAX; nCntTexture++)
	{
		if (g_apTextureRankingScore[nCntTexture] != NULL)
		{
			g_apTextureRankingScore[nCntTexture]->Release();

			g_apTextureRankingScore[nCntTexture] = NULL;
		}
	}

	//頂点バッファの破棄

	if (g_pVtxBuffRankingScore != NULL)
	{
		g_pVtxBuffRankingScore->Release();

		g_pVtxBuffRankingScore = NULL;
	}
}

//========================
// ランキングスコアの更新処理	
//========================
void UpdateRankingScore(void)
{
	int nCount;

	for (nCount = 0; nCount < NUM_RANKINGPLAYER; nCount++)
	{
		if (g_bBlinkingScore[nCount] == true)
		{
			BlinkingRankingScore(nCount);
		}
	}
}

//========================
// ランキングスコアの点滅処理	
//========================
void BlinkingRankingScore(int nCount)
{
	if (g_nBlinkingCounter[nCount] < 180)
	{

		g_nBlinkingCounter[nCount]++;

		VERTEX_2D* pVtx; //頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得

		g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (32 * nCount);

		for (int nCount2 = 0; nCount2 < NUM_PLACE; nCount2++, pVtx += 4)
		{

			if ((g_nBlinkingCounter[nCount] / 30) % 2 == 1) //上昇
			{
				//頂点カラーの設定

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			else if ((g_nBlinkingCounter[nCount] / 30) % 2 == 0) //下降
			{
				//頂点カラーの設定

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
	}

	//頂点バッファをアンロックする

	g_pVtxBuffRankingScore->Unlock();
}

//========================
// ランキングスコアの描画処理	
//========================
void DrawRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCount;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffRankingScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCount = 0; nCount < NUM_PLACE * NUM_RANKINGPLAYER; nCount++)
	{
		//テクスチャの設定(種類に合わせて設定)

		pDevice->SetTexture(0, g_apTextureRankingScore[g_type[nCount / 8]]);

		//ポリゴンの描画

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}