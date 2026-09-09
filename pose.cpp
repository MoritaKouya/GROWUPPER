//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "pose.h"
#include "posetext.h"
#include "posemenu.h"

//グローバル変数

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffpose = NULL; //頂点バッファのポインタ

//=========================
//ポーズ画面の初期化処理
//=========================
void InitPose(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な超点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffpose,

		NULL);

	//デバイスの取得

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffpose->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);

	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);

	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定 1.0f固定

	pVtx[0].rhw = 1.0f;

	pVtx[1].rhw = 1.0f;

	pVtx[2].rhw = 1.0f;

	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定（０．０f～１．０ｆで設定）

	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);

	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);

	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);

	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);

	//テクスチャ座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffpose->Unlock();

	//各オブジェクトの初期化処理

	InitPoseText(); //POSE

	InitPoseMenu(); //ポーズメニュー
}

//=========================
//ポーズ画面の終了処理
//=========================
void UninitPose(void)
{
	//頂点バッファの破棄

	if (g_pVtxBuffpose != NULL)
	{
		g_pVtxBuffpose->Release();

		g_pVtxBuffpose = NULL;
	}

	//各オブジェクトの終了処理

	UninitPoseText(); //POSE

	UninitPoseMenu(); //ポーズメニュー
}

//=========================
//ポーズ画面の更新処理
//=========================
void UpdatePose(void)
{
	//各オブジェクトの更新処理

	UpdatePoseText(); //POSE

	UpdatePoseMenu(); //ポーズメニュー
}

//=========================
//ポーズ画面の描画処理
//=========================
void DrawPose(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffpose, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, NULL); //テクスチャを使用しないときはNULLを指定する

	//ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//各オブジェクトの描画処理
	
	DrawPoseText(); //POSE

	DrawPoseMenu(); //ポーズメニュー
}