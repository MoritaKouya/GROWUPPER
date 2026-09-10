//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "scoretxt.h"
#include "score.h"

//マクロ定義

#define SCORERANK_SIZE_X (150) //横の半径

#define SCORERANK_SIZE_Y (75) //縦の半径

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureScoreText = NULL;

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScoreText = NULL;

//=========================
// スコアテキストの初期化処理
//=========================
void InitScoreText(void)
{
	//デバイスの獲得

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/SCORERANK/scorertext000.png",  //テクスチャのファイル名

		&g_pTextureScoreText);

	D3DXVECTOR3 g_posScore =
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 7, 0.0f); //テキストの位置

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な超点数

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffScoreText,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffScoreText->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = g_posScore.x + sinf(-D3DX_PI * 0.75f) * SCORERANK_SIZE_X;

	pVtx[0].pos.y = g_posScore.y + cosf(-D3DX_PI * 0.75f) * SCORERANK_SIZE_Y;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_posScore.x + sinf(D3DX_PI * 0.75f) * SCORERANK_SIZE_X;

	pVtx[1].pos.y = g_posScore.y + cosf(D3DX_PI * 0.75f) * SCORERANK_SIZE_Y;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_posScore.x + sinf(-D3DX_PI * 0.25) * SCORERANK_SIZE_X;

	pVtx[2].pos.y = g_posScore.y + cosf(-D3DX_PI * 0.25) * SCORERANK_SIZE_Y;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_posScore.x + sinf(D3DX_PI * 0.25) * SCORERANK_SIZE_X;

	pVtx[3].pos.y = g_posScore.y + cosf(D3DX_PI * 0.25) * SCORERANK_SIZE_Y;

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

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffScoreText->Unlock();
}

//=========================
// スコアテキストの終了処理
//=========================
void UninitScoreText(void)
{
	//テクスチャの破棄


	if (g_pTextureScoreText != NULL)
	{
		g_pTextureScoreText->Release();

		g_pTextureScoreText = NULL;
	}


	//頂点バッファの破棄

	if (g_pVtxBuffScoreText != NULL)
	{
		g_pVtxBuffScoreText->Release();

		g_pVtxBuffScoreText = NULL;
	}
}

//=========================
// スコアテキストの更新処理
//=========================
void UpdateScoreText(void)
{

}

//=========================
// スコアテキストの描画処理
//=========================
void DrawScoreText(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffScoreText, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureScoreText);

	///ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}