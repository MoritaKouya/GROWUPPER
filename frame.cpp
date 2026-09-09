//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "Frame.h"

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureFrame = NULL; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame = NULL; //頂点バッファへのポインタ

//=========================
// エフェクトの初期化処理
//=========================
void InitFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	float fRadius = 500; //半径

	D3DXVECTOR3 pos; //位置

	pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0); //位置を中央にする

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/SET/frame.png", //テクスチャのファイル名

		&g_pTextureFrame);

	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4, 

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffFrame,

		NULL
	);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

	
		//頂点座標の設定

		pVtx[0].pos.x = pos.x + sinf(-D3DX_PI * 0.75f) * fRadius;

		pVtx[0].pos.y = pos.y + cosf(-D3DX_PI * 0.75f) * fRadius;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = pos.x+ sinf(D3DX_PI * 0.75f) * fRadius;

		pVtx[1].pos.y = pos.y + cosf(D3DX_PI * 0.75f) * fRadius;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = pos.x + sinf(-D3DX_PI * 0.25) * fRadius;

		pVtx[2].pos.y = pos.y + cosf(-D3DX_PI * 0.25) * fRadius;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = pos.x + sinf(D3DX_PI * 0.25) * fRadius;

		pVtx[3].pos.y = pos.y + cosf(D3DX_PI * 0.25) * fRadius;

		pVtx[3].pos.z = 0.0f;

		//rhwの設定 1.0f固定

		pVtx[0].rhw = 1.0f;

		pVtx[1].rhw = 1.0f;

		pVtx[2].rhw = 1.0f;

		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定（０．０f～１．０ｆで設定）

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffFrame->Unlock();
}

//=========================
// エフェクトの終了処理
//=========================
void UninitFrame(void)
{
	//テクスチャの破棄

	if (g_pTextureFrame != NULL)
	{
		g_pTextureFrame->Release();

		g_pTextureFrame = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffFrame != NULL)
	{
		g_pVtxBuffFrame->Release();

		g_pVtxBuffFrame = NULL;
	}
}

//=========================
// エフェクトの更新処理
//=========================
void UpdateFrame(void)
{

}

//=========================
// エフェクトの描画処理
//=========================
void DrawFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffFrame, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureFrame);

	///ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


}