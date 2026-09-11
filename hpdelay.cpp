//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "hpdelay.h"
#include "player.h"

//マクロ定義

#define DELAYHPBER_SIZE_X (100)

#define DELAYHPBER_SIZE_Y (15)

//グローバル変数

LPDIRECT3DTEXTURE9 g_apTextureDelayHpBer = NULL; //テクスチャのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDelayHpBer = NULL;  //頂点バッファのポインタ

D3DXVECTOR3 g_posDelDelayHpBer; //ディレイHPバーの位置

float g_nDelayHpBer; //ディレイHPバーの割合

//========================
// ディレイHPバーの初期化処理	
//========================
void InitDelayHpBer(void)
{
	//プレイヤーの獲得

	Player* pPlayer = GetPlayer();

	g_nDelayHpBer = (float)pPlayer->nLife;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/HP/DelayHpBer001.png", //hpバー

		&g_apTextureDelayHpBer);


	g_posDelDelayHpBer = D3DXVECTOR3(1150.0f, 100.0f, 0.0f); //位置を初期化

	//プレイヤーの取得

	pPlayer = GetPlayer(); //敵の情報のが代入される	

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な頂点数

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffDelayHpBer,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffDelayHpBer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos = D3DXVECTOR3(g_posDelDelayHpBer.x - DELAYHPBER_SIZE_X, g_posDelDelayHpBer.y - DELAYHPBER_SIZE_Y, 0.0f);

	pVtx[1].pos = D3DXVECTOR3(g_posDelDelayHpBer.x + DELAYHPBER_SIZE_X, g_posDelDelayHpBer.y - DELAYHPBER_SIZE_Y, 0.0f);

	pVtx[2].pos = D3DXVECTOR3(g_posDelDelayHpBer.x - DELAYHPBER_SIZE_X, g_posDelDelayHpBer.y + DELAYHPBER_SIZE_Y, 0.0f);

	pVtx[3].pos = D3DXVECTOR3(g_posDelDelayHpBer.x + DELAYHPBER_SIZE_X, g_posDelDelayHpBer.y + DELAYHPBER_SIZE_Y, 0.0f);

	//rhwの設定 1.0f固定

	pVtx[0].rhw = 1.0f;

	pVtx[1].rhw = 1.0f;

	pVtx[2].rhw = 1.0f;

	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定

	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	//テクスチャ座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする

	g_pVtxBuffDelayHpBer->Unlock();

}

//========================
// ディレイHPバーの終了処理	
//========================
void UninitDelayHpBer(void)
{
	//テクスチャの破棄

	if (g_apTextureDelayHpBer != NULL)
	{
		g_apTextureDelayHpBer->Release();

		g_apTextureDelayHpBer = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffDelayHpBer != NULL)
	{
		g_pVtxBuffDelayHpBer->Release();

		g_pVtxBuffDelayHpBer = NULL;
	}
}

//========================
// ディレイHPバーの更新処理	
//========================
void UpdateDelayHpBer(void)
{
	//プレイヤーの獲得

	Player* pPlayer = GetPlayer();

	if (pPlayer->nLife < g_nDelayHpBer)
	{
		g_nDelayHpBer -= 1.0f
			;

		//ディレイHPバーのX軸の割合

		float fBer = g_nDelayHpBer / MAX_HP; //バーの割合

		VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

		g_pVtxBuffDelayHpBer->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標の設定

		pVtx[0].pos = D3DXVECTOR3(g_posDelDelayHpBer.x - DELAYHPBER_SIZE_X, g_posDelDelayHpBer.y - DELAYHPBER_SIZE_Y, 0.0f);

		pVtx[1].pos = D3DXVECTOR3(g_posDelDelayHpBer.x - DELAYHPBER_SIZE_X + ((DELAYHPBER_SIZE_X * 2) * fBer), g_posDelDelayHpBer.y - DELAYHPBER_SIZE_Y, 0.0f);

		pVtx[2].pos = D3DXVECTOR3(g_posDelDelayHpBer.x - DELAYHPBER_SIZE_X, g_posDelDelayHpBer.y + DELAYHPBER_SIZE_Y, 0.0f);

		pVtx[3].pos = D3DXVECTOR3(g_posDelDelayHpBer.x - DELAYHPBER_SIZE_X + ((DELAYHPBER_SIZE_X * 2) * fBer), g_posDelDelayHpBer.y + DELAYHPBER_SIZE_Y, 0.0f);

		//頂点バッファをアンロックする

		g_pVtxBuffDelayHpBer->Unlock();
	}
}

//========================
// ディレイHPバーの描画処理	
//========================
void DrawDelayHpBer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffDelayHpBer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定(種類に合わせて設定)

	pDevice->SetTexture(0, g_apTextureDelayHpBer);

	//ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}