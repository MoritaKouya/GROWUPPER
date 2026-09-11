//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "hp.h"
#include "hpber.h"
#include "hptext.h"
#include "hpdelay.h"

//マクロ定義

#define SIZE_X (100) //hpバーの横のサイズ

#define SIZE_Y (15) //hpバーの縦のサイズ

//グローバル変数

LPDIRECT3DTEXTURE9 g_apTextureHp = NULL; //テクスチャのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHp = NULL;  //頂点バッファのポインタ

D3DXVECTOR3 g_posHp; //HPの位置

//========================
// HPの初期化処理	
//========================
void InitHp(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/HP/hpber000.png", //バーの背景

		&g_apTextureHp);

	g_posHp = D3DXVECTOR3(1150.0f, 100.0f, 0.0f); //位置を初期化

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な頂点数

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffHp,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffHp->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos = D3DXVECTOR3(g_posHp.x - SIZE_X, g_posHp.y - SIZE_Y, 0.0f);

	pVtx[1].pos = D3DXVECTOR3(g_posHp.x + SIZE_X, g_posHp.y - SIZE_Y, 0.0f);

	pVtx[2].pos = D3DXVECTOR3(g_posHp.x - SIZE_X, g_posHp.y + SIZE_Y, 0.0f);

	pVtx[3].pos = D3DXVECTOR3(g_posHp.x + SIZE_X, g_posHp.y + SIZE_Y, 0.0f);

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

	//頂点バッファをアンロックする

	g_pVtxBuffHp->Unlock();

	//各オブジェクトの初期化処理

	InitHpText(); //HPの文字

	InitDelayHpBer(); //ディレイHpバー

	InitHpBer(); //hpバーの初期化

}

//========================
// HPの終了処理	
//========================
void UninitHp(void)
{
	//テクスチャの破棄

	if (g_apTextureHp != NULL)
	{
		g_apTextureHp->Release();

		g_apTextureHp = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffHp != NULL)
	{
		g_pVtxBuffHp->Release();

		g_pVtxBuffHp = NULL;
	}

	//各オブジェクトの終了処理

	UninitHpText(); //HPの文字

	UninitDelayHpBer(); //ディレイHpバー

	UninitHpBer(); //hpバーの終了処理
}

//========================
// HPの更新処理	
//========================
void UpdateHp(void)
{
	//各オブジェクトの更新処理

	UpdateHpText(); //HPの文字

	UpdateHpBer(); //hpバーの更新処理

	UpdateDelayHpBer(); //ディレイHpバー
}

//========================
// HPの描画処理	
//========================
void DrawHp(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffHp, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定(種類に合わせて設定)

	pDevice->SetTexture(0, g_apTextureHp);

	//ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//各オブジェクトの描画処理

	DrawHpText(); //HPの文字

	DrawDelayHpBer(); //ディレイHpバー

	DrawHpBer(); //Hpバーの描画処理
}