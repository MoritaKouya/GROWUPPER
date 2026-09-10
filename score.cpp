//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "score.h"
#include <stdio.h>
#include <time.h>

//マクロ定義

#define NUM_PLACE (8) //スコアの桁数

#define MAX_ANIM (10) //アニメーションの最大数

#define MAX_COLUMN (10) //列数 

#define MAX_LINES (1) //行数

//グローバル変数

LPDIRECT3DTEXTURE9 g_apTextureScore[SCORE_MAX] = {};

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;

D3DXVECTOR3 g_posScore; //スコアの位置

int g_nScore; //スコアの値

SCORETEXTURE g_type; //スコアのタイプを代入する変数

const char* g_aScoreTexture_Path[SCORE_MAX] =
{
	"Data/TEXTURE/NUMBER/number000.png",

	"Data/TEXTURE/NUMBER/number001.png",

	"Data/TEXTURE/NUMBER/number002.png",

	"Data/TEXTURE/NUMBER/number003.png",
}; //テクスチャのアドレスの構造体

//========================
// スコアの初期化処理	
//========================
void InitScore(void)
{
	int nCntTexture;

	int nCntPlace;

	int aTexU[NUM_PLACE] = { 0 }; //各桁の数値を格納

	g_type = SCORE_0; //タイプを初期化

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み

	for (nCntTexture = 0; nCntTexture < SCORE_MAX; nCntTexture++)
	{

		D3DXCreateTextureFromFile(pDevice,

			g_aScoreTexture_Path[nCntTexture], //テクスチャのファイル名

			&g_apTextureScore[nCntTexture]);
	}

	g_posScore = D3DXVECTOR3(25.0f, 50.0f, 0.0f); //位置を初期化

	g_nScore = 0; //値を初期化する

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な頂点数

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffScore,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos.x = g_posScore.x + (nCntPlace * 50.0f) + sinf(-D3DX_PI * 0.75f) * 25.0f;

		pVtx[0].pos.y = g_posScore.y + cosf(-D3DX_PI * 0.75f) * 50.0f;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_posScore.x + (nCntPlace * 50.0f) + sinf(D3DX_PI * 0.75f) * 25.0f;

		pVtx[1].pos.y = g_posScore.y + cosf(D3DX_PI * 0.75f) * 50.0f;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_posScore.x + (nCntPlace * 50.0f) + sinf(-D3DX_PI * 0.25) * 25.0f;

		pVtx[2].pos.y = g_posScore.y + cosf(-D3DX_PI * 0.25) * 50.0f;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_posScore.x + (nCntPlace * 50.0f) + sinf(D3DX_PI * 0.25) * 25.0f;

		pVtx[3].pos.y = g_posScore.y + cosf(D3DX_PI * 0.25) * 50.0f;

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

		pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (0 % MAX_COLUMN), (1.0f / MAX_LINES) * (0 / MAX_COLUMN));

		pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((0 % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (0 / MAX_COLUMN));

		pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (0 % MAX_COLUMN), (1.0f / MAX_LINES) * (0 / MAX_COLUMN) + (1.0f / MAX_LINES));

		pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((0 % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (0 / MAX_COLUMN) + (1.0f / MAX_LINES));
	}

	//頂点バッファをアンロックする

	g_pVtxBuffScore->Unlock();

	srand((unsigned int)time(NULL));
}

//========================
// スコアの終了処理	
//========================
void UninitScore(void)
{
	//テクスチャの破棄

	for (int nCntTexture = 0; nCntTexture < SCORE_MAX; nCntTexture++)
	{
		if (g_apTextureScore[nCntTexture] != NULL)
		{
			g_apTextureScore[nCntTexture]->Release();

			g_apTextureScore[nCntTexture] = NULL;
		}
	}

	//頂点バッファの破棄

	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();

		g_pVtxBuffScore = NULL;
	}
}

//========================
// スコアの更新処理	
//========================
void UpdateScore(void)
{
	
}

//========================
// スコアの描画処理	
//========================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntPlace;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定(種類に合わせて設定)

	pDevice->SetTexture(0, g_apTextureScore[g_type]);

	for (nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		//ポリゴンの描画

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPlace * 4, 2);
	}
}

//========================
// スコアの設定処理	
//========================
void SetScore()
{
	int aTexU[NUM_PLACE]; //各桁の数値を格納

	g_posScore = D3DXVECTOR3((SCREEN_WIDTH / 2) - 350.0f, (SCREEN_HEIGHT / 3), 0.0f);

	aTexU[0] = g_nScore / 10000000;

	aTexU[1] = g_nScore % 10000000 / 1000000;

	aTexU[2] = g_nScore % 1000000 / 100000;

	aTexU[3] = g_nScore % 100000 / 10000;

	aTexU[4] = g_nScore % 10000 / 1000;

	aTexU[5] = g_nScore % 1000 / 100;

	aTexU[6] = g_nScore % 100 / 10;

	aTexU[7] = g_nScore % 10 / 1;

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos.x = g_posScore.x + (nCntPlace * 100.0f) + sinf(-D3DX_PI * 0.75f) * 50.0f;

		pVtx[0].pos.y = g_posScore.y + cosf(-D3DX_PI * 0.75f) * 100.0f;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_posScore.x + (nCntPlace * 100.0f) + sinf(D3DX_PI * 0.75f) * 50.0f;

		pVtx[1].pos.y = g_posScore.y + cosf(D3DX_PI * 0.75f) * 100.0f;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_posScore.x + (nCntPlace * 100.0f) + sinf(-D3DX_PI * 0.25) * 50.0f;

		pVtx[2].pos.y = g_posScore.y + cosf(-D3DX_PI * 0.25) * 100.0f;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_posScore.x + (nCntPlace * 100.0f) + sinf(D3DX_PI * 0.25) * 50.0f;

		pVtx[3].pos.y = g_posScore.y + cosf(D3DX_PI * 0.25) * 100.0f;

		//テクスチャ座標の設定

		pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (aTexU[nCntPlace] % MAX_COLUMN), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN));

		pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((aTexU[nCntPlace] % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN));

		pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (aTexU[nCntPlace] % MAX_COLUMN), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN) + (1.0f / MAX_LINES));

		pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((aTexU[nCntPlace] % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN) + (1.0f / MAX_LINES));

	}

	//頂点バッファをアンロックする

	g_pVtxBuffScore->Unlock();
}

//========================
// スコアの加算処理	
//========================
void AddScore(int nValue)
{
	int nCntPlace;

	int aTexU[NUM_PLACE]; //各桁の数値を格納

	g_nScore += nValue * 100 + rand()%10;

	//最大値を超えたとき

	if (100000000 <= g_nScore)
	{
		g_nScore = 99999999;
	}

	aTexU[0] = g_nScore / 10000000;

	aTexU[1] = g_nScore % 10000000 / 1000000;

	aTexU[2] = g_nScore % 1000000 / 100000;

	aTexU[3] = g_nScore % 100000 / 10000;

	aTexU[4] = g_nScore % 10000 / 1000;

	aTexU[5] = g_nScore % 1000 / 100;

	aTexU[6] = g_nScore % 100 / 10;

	aTexU[7] = g_nScore % 10 / 1;

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
	{
		//テクスチャ座標の設定

		pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (aTexU[nCntPlace] % MAX_COLUMN), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN));

		pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((aTexU[nCntPlace] % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN));

		pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (aTexU[nCntPlace] % MAX_COLUMN), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN) + (1.0f / MAX_LINES));

		pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((aTexU[nCntPlace] % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN) + (1.0f / MAX_LINES));

	}
	
	//頂点バッファをアンロックする

	g_pVtxBuffScore->Unlock();

	//銀色にする

	if (g_nScore >= 2500000) //スコアが5000000以上の場合
	{
		g_type = SCORE_1; //銀色
	}

	//金色にする

	if (g_nScore >= 5000000) //スコアが5000000以上の場合
	{
		g_type = SCORE_2; //銀色
	}

	if (g_nScore >= 10000000) //スコアが10000000以上の場合
	{
		g_type = SCORE_3;//金色
	}
	
}
//========================
// スコアの獲得処理	
//========================
int GetScore(void)
{
	return g_nScore;
}

//========================
// スコアの獲得処理	
//========================
SCORETEXTURE GetScoreRank(void)
{
	return g_type;
}