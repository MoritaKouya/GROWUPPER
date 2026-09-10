//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "Hptext.h"

//マクロ定義

#define HpRANK_SIZE_X (75) //横の半径

#define HpRANK_SIZE_Y (30) //縦の半径

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureHpText = NULL;

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHpText = NULL;

//=========================
// Hpテキストの初期化処理
//=========================
void InitHpText(void)
{
	//デバイスの獲得

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/HP/hptext.png", //テクスチャのファイル名

		&g_pTextureHpText);

	D3DXVECTOR3 g_posHp =
		D3DXVECTOR3(SCREEN_WIDTH / 4 * 3 + 40, SCREEN_HEIGHT / 7, 0.0f); //テキストの位置

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な頂点数

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffHpText,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffHpText->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = g_posHp.x + sinf(-D3DX_PI * 0.75f) * HpRANK_SIZE_X;

	pVtx[0].pos.y = g_posHp.y + cosf(-D3DX_PI * 0.75f) * HpRANK_SIZE_Y;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_posHp.x + sinf(D3DX_PI * 0.75f) * HpRANK_SIZE_X;

	pVtx[1].pos.y = g_posHp.y + cosf(D3DX_PI * 0.75f) * HpRANK_SIZE_Y;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_posHp.x + sinf(-D3DX_PI * 0.25) * HpRANK_SIZE_X;

	pVtx[2].pos.y = g_posHp.y + cosf(-D3DX_PI * 0.25) * HpRANK_SIZE_Y;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_posHp.x + sinf(D3DX_PI * 0.25) * HpRANK_SIZE_X;

	pVtx[3].pos.y = g_posHp.y + cosf(D3DX_PI * 0.25) * HpRANK_SIZE_Y;

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

	g_pVtxBuffHpText->Unlock();
}

//=========================
// Hpテキストの終了処理
//=========================
void UninitHpText(void)
{
	//テクスチャの破棄

	if (g_pTextureHpText != NULL)
	{
		g_pTextureHpText->Release();

		g_pTextureHpText = NULL;
	}


	//頂点バッファの破棄

	if (g_pVtxBuffHpText != NULL)
	{
		g_pVtxBuffHpText->Release();

		g_pVtxBuffHpText = NULL;
	}
}

//=========================
// Hpテキストの更新処理
//=========================
void UpdateHpText(void)
{

}

//=========================
// Hpテキストの描画処理
//=========================
void DrawHpText(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffHpText, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureHpText);

	///ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}