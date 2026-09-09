//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "EnergyBer.h"
#include "player.h"

//マクロ定義

#define NUM_ENERGY_BER (2) //エネルギーバーのテクスチャ数

#define SIZE_ENERGY_X (160)

#define SIZE_ENERGY_Y (20)

//グローバル変数

LPDIRECT3DTEXTURE9 g_apTextureEnergyBer[NUM_ENERGY_BER] = {}; //テクスチャのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnergyBer = NULL;  //頂点バッファのポインタ

D3DXVECTOR3 g_posEnergyBer; //エネルギーバーの位置

//========================
// エネルギーバーの初期化処理	
//========================
void InitEnergyBer(void)
{
	int nCntEnergyBer;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/ENERGY/energyber001.png", //テクスチャのファイル名

		&g_apTextureEnergyBer[0]);

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/ENERGY/energyber002.png", //テクスチャのファイル名

		&g_apTextureEnergyBer[1]);

	g_posEnergyBer = D3DXVECTOR3(640.0f, 620.0f, 0.0f); //位置を初期化

	//プレイヤーの取得

	Player* pPlayer = GetPlayer(); //敵の情報の先頭アドレスが代入される	

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_ENERGY_BER, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な超点数

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffEnergyBer,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffEnergyBer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnergyBer = 0; nCntEnergyBer < NUM_ENERGY_BER; nCntEnergyBer++, pVtx += 4)
	{
		//頂点座標の設定

		if (nCntEnergyBer == 0) //裏のバー
		{

			pVtx[0].pos = D3DXVECTOR3(g_posEnergyBer.x - SIZE_ENERGY_X, g_posEnergyBer.y - SIZE_ENERGY_Y, 0.0f);

			pVtx[1].pos = D3DXVECTOR3(g_posEnergyBer.x + SIZE_ENERGY_X, g_posEnergyBer.y - SIZE_ENERGY_Y, 0.0f);

			pVtx[2].pos = D3DXVECTOR3(g_posEnergyBer.x - SIZE_ENERGY_X, g_posEnergyBer.y + SIZE_ENERGY_Y, 0.0f);

			pVtx[3].pos = D3DXVECTOR3(g_posEnergyBer.x + SIZE_ENERGY_X, g_posEnergyBer.y + SIZE_ENERGY_Y, 0.0f);
		}
		else if (nCntEnergyBer == 1) //エネルギーバー
		{
			pVtx[0].pos = D3DXVECTOR3(g_posEnergyBer.x - SIZE_ENERGY_X, g_posEnergyBer.y - SIZE_ENERGY_Y, 0.0f);

			pVtx[1].pos = D3DXVECTOR3(g_posEnergyBer.x - SIZE_ENERGY_X, g_posEnergyBer.y - SIZE_ENERGY_Y, 0.0f);

			pVtx[2].pos = D3DXVECTOR3(g_posEnergyBer.x - SIZE_ENERGY_X, g_posEnergyBer.y + SIZE_ENERGY_Y, 0.0f);

			pVtx[3].pos = D3DXVECTOR3(g_posEnergyBer.x - SIZE_ENERGY_X, g_posEnergyBer.y + SIZE_ENERGY_Y, 0.0f);

		}
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
	}
	//頂点バッファをアンロックする

	g_pVtxBuffEnergyBer->Unlock();

}

//========================
// エネルギーバーの終了処理	
//========================
void UninitEnergyBer(void)
{
	//テクスチャの破棄

	int nCntEnergyBer;

	for (nCntEnergyBer = 0; nCntEnergyBer < NUM_ENERGY_BER; nCntEnergyBer++)
	{
		if (g_apTextureEnergyBer[nCntEnergyBer] != NULL)
		{
			g_apTextureEnergyBer[nCntEnergyBer]->Release();

			g_apTextureEnergyBer[nCntEnergyBer] = NULL;
		}

	}

	//頂点バッファの破棄

	if (g_pVtxBuffEnergyBer != NULL)
	{
		g_pVtxBuffEnergyBer->Release();

		g_pVtxBuffEnergyBer = NULL;
	}
}

//========================
// エネルギーバーの更新処理	
//========================
void UpdateEnergyBer(void)
{

}

//========================
// エネルギーバーの描画処理	
//========================
void DrawEnergyBer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntEnergyBer;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffEnergyBer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定(種類に合わせて設定)

	for (nCntEnergyBer = 0; nCntEnergyBer < NUM_ENERGY_BER; nCntEnergyBer++)
	{

		pDevice->SetTexture(0, g_apTextureEnergyBer[nCntEnergyBer]);

		//ポリゴンの描画

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnergyBer * 4, 2);
	}
}

//========================
// エネルギーバーの加算処理	
//========================
void AddEnergyBer(int nCntEnergy, int nLevel)
{
	float nBer;

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffEnergyBer->Lock(0, 0, (void**)&pVtx, 0);

	//エネルギーバーのX軸の割合

	nBer = (float)nCntEnergy / (REQUIRED_ENERGY * nLevel);

	//テクスチャ座標の設定

	pVtx[4].pos = D3DXVECTOR3(g_posEnergyBer.x - SIZE_ENERGY_X, g_posEnergyBer.y - SIZE_ENERGY_Y, 0.0f);

	pVtx[5].pos = D3DXVECTOR3(g_posEnergyBer.x - SIZE_ENERGY_X + ((SIZE_ENERGY_X * 2) * nBer), g_posEnergyBer.y - 20, 0.0f);

	pVtx[6].pos = D3DXVECTOR3(g_posEnergyBer.x - SIZE_ENERGY_X, g_posEnergyBer.y + SIZE_ENERGY_Y, 0.0f);

	pVtx[7].pos = D3DXVECTOR3(g_posEnergyBer.x - SIZE_ENERGY_X + ((SIZE_ENERGY_X* 2) * nBer), g_posEnergyBer.y + 20, 0.0f);

	//頂点バッファをアンロックする

	g_pVtxBuffEnergyBer->Unlock();

}