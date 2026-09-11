//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "hpber.h"
#include "player.h"

//マクロ定義

#define SIZE_X (100)

#define SIZE_Y (15)

//グローバル変数

LPDIRECT3DTEXTURE9 g_apTextureHpBer = NULL; //テクスチャのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHpBer = NULL;  //頂点バッファのポインタ

D3DXVECTOR3 g_posHpBer; //HPバーの位置

//========================
// HPバーの初期化処理	
//========================
void InitHpBer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/HP/HpBer001.png", //hpバー

		&g_apTextureHpBer);


	g_posHpBer = D3DXVECTOR3(1150.0f, 100.0f, 0.0f); //位置を初期化

	//プレイヤーの取得

	Player* pPlayer = GetPlayer(); //敵の情報の先頭アドレスが代入される	

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な頂点数

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffHpBer,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffHpBer->Lock(0, 0, (void**)&pVtx, 0);


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

	pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	//テクスチャ座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする

	g_pVtxBuffHpBer->Unlock();

}

//========================
// HPバーの終了処理	
//========================
void UninitHpBer(void)
{
	//テクスチャの破棄

	if (g_apTextureHpBer != NULL)
	{
		g_apTextureHpBer->Release();

		g_apTextureHpBer = NULL;
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

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffHpBer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定(種類に合わせて設定)

	pDevice->SetTexture(0, g_apTextureHpBer);

	//ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//========================
// HPバーの変化処理	
//========================
void ModifyHpBer(int nHp)
{
	float fBer;

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffHpBer->Lock(0, 0, (void**)&pVtx, 0);

	//HPバーのX軸の割合

	fBer = (float)nHp / MAX_HP; //バーの割合

	//テクスチャ座標の設定

	pVtx[0].pos = D3DXVECTOR3(g_posHpBer.x - SIZE_X, g_posHpBer.y - SIZE_Y, 0.0f);

	pVtx[1].pos = D3DXVECTOR3(g_posHpBer.x - SIZE_X + ((SIZE_X * 2) * fBer), g_posHpBer.y - SIZE_Y, 0.0f);

	pVtx[2].pos = D3DXVECTOR3(g_posHpBer.x - SIZE_X, g_posHpBer.y + SIZE_Y, 0.0f);

	pVtx[3].pos = D3DXVECTOR3(g_posHpBer.x - SIZE_X + ((SIZE_X * 2) * fBer), g_posHpBer.y + SIZE_Y, 0.0f);


	//頂点バッファをアンロックする

	g_pVtxBuffHpBer->Unlock();

}