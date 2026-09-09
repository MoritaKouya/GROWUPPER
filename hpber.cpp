//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "hpber.h"
#include "player.h"


//マクロ定義

#define NUM_HP_BER (2) //HPバーのテクスチャ

#define BER_GREEN (50) //緑色のhpの割合

#define BER_YELLOW (25) //黄色のhpの割合

#define BER_RED (0) //赤色のhpの割合

#define SIZE_X (100)

#define SIZE_Y (15)

//グローバル変数

LPDIRECT3DTEXTURE9 g_apTextureHpBer[NUM_HP_BER] = {}; //テクスチャのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHpBer = NULL;  //頂点バッファのポインタ

D3DXVECTOR3 g_posHpBer; //HPバーの位置

//========================
// HPバーの初期化処理	
//========================
void InitHpBer(void)
{
	int nCntHpBer;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/HP/hpber000.png", //バーの背景

		&g_apTextureHpBer[0]);

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/HP/HpBer001.png", //hpバー

		&g_apTextureHpBer[1]);


	g_posHpBer = D3DXVECTOR3(1150.0f, 100.0f, 0.0f); //位置を初期化

	//プレイヤーの取得

	Player* pPlayer = GetPlayer(); //敵の情報の先頭アドレスが代入される	

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_HP_BER, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な超点数

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffHpBer,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffHpBer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHpBer = 0; nCntHpBer < NUM_HP_BER; nCntHpBer++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos = D3DXVECTOR3(g_posHpBer.x - SIZE_X, g_posHpBer.y - SIZE_Y, 0.0f);

		pVtx[1].pos = D3DXVECTOR3(g_posHpBer.x + SIZE_X, g_posHpBer.y - SIZE_Y, 0.0f);

		pVtx[2].pos = D3DXVECTOR3(g_posHpBer.x - SIZE_X, g_posHpBer.y + SIZE_Y, 0.0f);

		pVtx[3].pos = D3DXVECTOR3(g_posHpBer.x + SIZE_X, g_posHpBer.y + SIZE_Y, 0.0f);

		//rhwの設定 1.0f固定

		pVtx[0].rhw = 1.0f;

		pVtx[1].rhw = 1.0f;

		pVtx[2].rhw = 1.0f;

		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定

		if (nCntHpBer == 0) //背景
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else if (nCntHpBer == 1)
		{
			pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

			pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

			pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

			pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		}

		//テクスチャ座標の設定

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//頂点バッファをアンロックする

	g_pVtxBuffHpBer->Unlock();

}

//========================
// HPバーの終了処理	
//========================
void UninitHpBer(void)
{
	//テクスチャの破棄

	int nCntHpBer;

	for (nCntHpBer = 0; nCntHpBer < NUM_HP_BER; nCntHpBer++)
	{
		if (g_apTextureHpBer[nCntHpBer] != NULL)
		{
			g_apTextureHpBer[nCntHpBer]->Release();

			g_apTextureHpBer[nCntHpBer] = NULL;
		}

	}

	//頂点バッファの破棄

	if (g_pVtxBuffHpBer != NULL)
	{
		g_pVtxBuffHpBer->Release();

		g_pVtxBuffHpBer = NULL;
	}
}

//========================
// HPバーの更新処理	
//========================
void UpdateHpBer(void)
{

}

//========================
// HPバーの描画処理	
//========================
void DrawHpBer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntHpBer;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffHpBer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定(種類に合わせて設定)

	for (nCntHpBer = 0; nCntHpBer < NUM_HP_BER; nCntHpBer++)
	{

		pDevice->SetTexture(0, g_apTextureHpBer[nCntHpBer]);

		//ポリゴンの描画

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntHpBer * 4, 2);
	}
}

//========================
// HPバーの変化処理	
//========================
void ModifyHpBer(int nHp)
{
	float nBer;

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffHpBer->Lock(0, 0, (void**)&pVtx, 0);

	//HPバーのX軸の割合

	nBer = (float)nHp / MAX_HP; //バーの割合

	//テクスチャ座標の設定

	pVtx[4].pos = D3DXVECTOR3(g_posHpBer.x - SIZE_X, g_posHpBer.y - SIZE_Y, 0.0f);

	pVtx[5].pos = D3DXVECTOR3(g_posHpBer.x - SIZE_X + ((SIZE_X * 2) * nBer), g_posHpBer.y - SIZE_Y, 0.0f);

	pVtx[6].pos = D3DXVECTOR3(g_posHpBer.x - SIZE_X, g_posHpBer.y + SIZE_Y, 0.0f);

	pVtx[7].pos = D3DXVECTOR3(g_posHpBer.x - SIZE_X + ((SIZE_X * 2) * nBer), g_posHpBer.y + SIZE_Y, 0.0f);

	//頂点カラーの設定

	if (BER_GREEN < nBer * 100) //割合が５０パーセントより高い場合
	{
		//頂点カラーを緑にする

		pVtx[4].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		pVtx[5].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		pVtx[6].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		pVtx[7].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	}
	else if (BER_YELLOW < nBer * 100) //割合が２５パーセントより高い場合
	{
		//頂点カラーを黄色にする

		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	}
	else if(BER_RED < nBer * 100) //割合が０パーセントより高い場合
	{
		//頂点カラーを赤にする

		pVtx[4].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		pVtx[5].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		pVtx[6].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		pVtx[7].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}

	//頂点バッファをアンロックする

	g_pVtxBuffHpBer->Unlock();

}