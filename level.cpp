//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "Level.h"
#include "player.h"

//マクロ定義

#define NUM_PLACE (2) //レベルの桁数

#define MAX_ANIM (10) //アニメーションの最大数

#define MAX_COLUMN (10) //列数 

#define MAX_LINES (1) //行数

#define LENEL_SIZE_X (35) //レベルの横の半径

#define LENEL_SIZE_Y (70) //レベルの縦の半径

#define LENELTEXT_SIZE_X (50) //横の半径

#define LENELTEXT_SIZE_Y (50) //縦の半径

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureLevel = NULL;

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLevel = NULL;

D3DXVECTOR3 g_posLevel; //レベルの位置

int g_nLevel; //レベルの値

bool g_abUse[NUM_PLACE]; //使用しているかどうか

LPDIRECT3DTEXTURE9 g_pTextureLevelText = NULL;

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLevelText = NULL;

//========================
// レベルの初期化処理	
//========================
void InitLevel(void)
{
	int nCntPlace;

	int aTexU[NUM_PLACE] = { 0 }; //各桁の数値を格納

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/NUMBER/levelNumber.png", //テクスチャのファイル名

		&g_pTextureLevel);

	g_posLevel = D3DXVECTOR3(SCREEN_WIDTH / 2, 520.0f, 0.0f); //位置を初期化

	//プレイヤーの取得

	Player* pPlayer = GetPlayer(); //敵の情報のが代入される	

	//レベルをグローバル変数に代入

	g_nLevel = pPlayer->nLevel;

	g_nLevel = pPlayer->nLevel;

	//テクスチャの座標の設定

	aTexU[0] = g_nLevel % 10; //１の位

	aTexU[1] = g_nLevel / 10; //１０の位

	//使用しているかどうかの設定

	g_abUse[0] = true; //１の位

	g_abUse[1] = false;//１０の位

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な頂点数

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffLevel,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffLevel->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos.x = g_posLevel.x - (nCntPlace * (LENEL_SIZE_X * 2)) + sinf(-D3DX_PI * 0.75f) * LENEL_SIZE_X;

		pVtx[0].pos.y = g_posLevel.y + cosf(-D3DX_PI * 0.75f) * LENEL_SIZE_Y;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_posLevel.x - (nCntPlace * (LENEL_SIZE_X * 2)) + sinf(D3DX_PI * 0.75f) * LENEL_SIZE_X;

		pVtx[1].pos.y = g_posLevel.y + cosf(D3DX_PI * 0.75f) * LENEL_SIZE_Y;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_posLevel.x - (nCntPlace * (LENEL_SIZE_X * 2)) + sinf(-D3DX_PI * 0.25) * LENEL_SIZE_X;

		pVtx[2].pos.y = g_posLevel.y + cosf(-D3DX_PI * 0.25) * LENEL_SIZE_Y;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_posLevel.x - (nCntPlace * (LENEL_SIZE_X * 2)) + sinf(D3DX_PI * 0.25) * LENEL_SIZE_X;

		pVtx[3].pos.y = g_posLevel.y + cosf(D3DX_PI * 0.25) * LENEL_SIZE_Y;

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

		pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (aTexU[nCntPlace] % MAX_COLUMN), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN));

		pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((aTexU[nCntPlace] % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN));

		pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (aTexU[nCntPlace] % MAX_COLUMN), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN) + (1.0f / MAX_LINES));

		pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((aTexU[nCntPlace] % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN) + (1.0f / MAX_LINES));
	}

	//頂点バッファをアンロックする

	g_pVtxBuffLevel->Unlock();

	//レベルテキストの初期化

	InitLevelText();

}

//========================
// レベルの終了処理	
//========================
void UninitLevel(void)
{
	//テクスチャの破棄

	if (g_pTextureLevel != NULL)
	{
		g_pTextureLevel->Release();

		g_pTextureLevel = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffLevel != NULL)
	{
		g_pVtxBuffLevel->Release();

		g_pVtxBuffLevel = NULL;
	}

	UninitLevelText();
}

//========================
// レベルの更新処理	
//========================
void UpdateLevel(void)
{

}

//========================
// レベルの描画処理	
//========================
void DrawLevel(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntPlace;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffLevel, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定(種類に合わせて設定)

	pDevice->SetTexture(0, g_pTextureLevel);

	for (nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		if (g_abUse[nCntPlace] == true)
		{

			//ポリゴンの描画

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPlace * 4, 2);
		}
	}

	DrawLevelText(); //レベルの文字
}

//========================
// レベルの加算処理
//========================
void LevelUpp(int* nLevel)
{
	int nCntPlace,

		nBeforePlace = LevelGetDigits(g_nLevel), //レベルが上がる前の桁数

		aTexU[NUM_PLACE]; //各桁の数値を格納

	//レベルアップ

	*nLevel += 1;

	if (100 <= *nLevel)
	{
		*nLevel = 99;
	}

	//レベルをグローバル変数に代入

	g_nLevel = *nLevel;

	int nAfterPlace = LevelGetDigits(g_nLevel); //桁数の計算

	aTexU[0] = g_nLevel % 10; //１の位

	aTexU[1] = g_nLevel / 10; //１０の位

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffLevel->Lock(0, 0, (void**)&pVtx, 0);

	if (nBeforePlace < nAfterPlace) //桁が上がったら
	{
		g_abUse[g_nLevel / 10] = true;

		g_posLevel.x += LENEL_SIZE_X; //桁が座標を中央になるようにずらす
	}

	for (nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos.x = g_posLevel.x - (nCntPlace * (LENEL_SIZE_X * 2)) + sinf(-D3DX_PI * 0.75f) * LENEL_SIZE_X;

		pVtx[0].pos.y = g_posLevel.y + cosf(-D3DX_PI * 0.75f) * LENEL_SIZE_Y;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_posLevel.x - (nCntPlace * (LENEL_SIZE_X * 2)) + sinf(D3DX_PI * 0.75f) * LENEL_SIZE_X;

		pVtx[1].pos.y = g_posLevel.y + cosf(D3DX_PI * 0.75f) * LENEL_SIZE_Y;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_posLevel.x - (nCntPlace * (LENEL_SIZE_X * 2)) + sinf(-D3DX_PI * 0.25) * LENEL_SIZE_X;

		pVtx[2].pos.y = g_posLevel.y + cosf(-D3DX_PI * 0.25) * LENEL_SIZE_Y;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_posLevel.x - (nCntPlace * (LENEL_SIZE_X * 2)) + sinf(D3DX_PI * 0.25) * LENEL_SIZE_X;

		pVtx[3].pos.y = g_posLevel.y + cosf(D3DX_PI * 0.25) * LENEL_SIZE_Y;

		pVtx[3].pos.z = 0.0f;

		//テクスチャ座標の設定

		pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (aTexU[nCntPlace] % MAX_COLUMN), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN));

		pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((aTexU[nCntPlace] % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN));

		pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (aTexU[nCntPlace] % MAX_COLUMN), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN) + (1.0f / MAX_LINES));

		pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((aTexU[nCntPlace] % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (aTexU[nCntPlace] / MAX_COLUMN) + (1.0f / MAX_LINES));

	}

	//頂点バッファをアンロックする

	g_pVtxBuffLevel->Unlock();

}

//========================
// レベルの桁数計算処理	
//========================
int LevelGetDigits(int nDigits)
{
	int digits = 0; //桁数を代入する処理

		while (nDigits > 0)
		{
			nDigits /= 10;

			digits++; //桁数をプラス
		}
	
	return digits; //桁数を返す
}

//========================
// レベルのテキストの初期化処理	
//========================
void InitLevelText(void)
{
	//位置の初期化

	D3DXVECTOR3 posLevelText; //レベルの位置

	posLevelText = D3DXVECTOR3(500.0f, 550.0f, 0.0f);

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/ENERGY/levelUI.png", //テクスチャのファイル名

		& g_pTextureLevelText);

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
											   //sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffLevelText,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffLevelText->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = posLevelText.x + sinf(-D3DX_PI * 0.75f) * LENELTEXT_SIZE_X;

	pVtx[0].pos.y = posLevelText.y + cosf(-D3DX_PI * 0.75f) * LENELTEXT_SIZE_Y;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = posLevelText.x + sinf(D3DX_PI * 0.75f) * LENELTEXT_SIZE_X;

	pVtx[1].pos.y = posLevelText.y + cosf(D3DX_PI * 0.75f) * LENELTEXT_SIZE_Y;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = posLevelText.x + sinf(-D3DX_PI * 0.25) * LENELTEXT_SIZE_X;

	pVtx[2].pos.y = posLevelText.y + cosf(-D3DX_PI * 0.25) * LENELTEXT_SIZE_Y;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = posLevelText.x + sinf(D3DX_PI * 0.25) * LENELTEXT_SIZE_X;

	pVtx[3].pos.y = posLevelText.y + cosf(D3DX_PI * 0.25) * LENELTEXT_SIZE_Y;

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

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする

	g_pVtxBuffLevelText->Unlock();
}

//========================
// レベルのテキストの終了処理	
//========================
void UninitLevelText(void)
{
	//テクスチャの破棄

	if (g_pTextureLevelText != NULL)
	{
		g_pTextureLevelText->Release();

		g_pTextureLevelText = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffLevelText != NULL)
	{
		g_pVtxBuffLevelText->Release();

		g_pVtxBuffLevelText = NULL;
	}
}

//========================
// レベルのテキストの描画処理	
//========================
void DrawLevelText(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffLevelText, 0, sizeof(VERTEX_2D));
	//頂点バッファのポインタ  頂点情報構造体のサイズ

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureLevelText);

	//ポリゴンの描画
											  //描画する最初の頂点インデックス
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}