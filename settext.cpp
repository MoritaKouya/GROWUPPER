//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "settext.h"
#include "setfighter.h"

#define SETTEXT_SIZE_X (550) //横の半径の半径

#define SETTEXT_SIZE_Y (50) //縦の半径

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureSetText[SETMODE_MAX] = {}; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSetText = NULL; //頂点バッファへのポインタ

const char* g_aSetText_Path[SETMODE_MAX] =
{
	"Data/TEXTURE/SET/settext000.png",

	"Data/TEXTURE/SET/settext001.png",
};

SETMODE g_SetTextMode;

//=========================
// タイトルメニューの初期化処理
//=========================
void InitSetText(void)
{
	int nCnt;

	//位置の設定

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 75, 0.0f);

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	for (nCnt = 0; nCnt < SETMODE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice,

			g_aSetText_Path[nCnt], //テクスチャのファイル名

			&g_pTextureSetText[nCnt]);
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffSetText,

		NULL
	);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffSetText->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = pos.x + sinf(-D3DX_PI * 0.75f) * SETTEXT_SIZE_X;

	pVtx[0].pos.y = pos.y + cosf(-D3DX_PI * 0.75f) * SETTEXT_SIZE_Y;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = pos.x + sinf(D3DX_PI * 0.75f) * SETTEXT_SIZE_X;

	pVtx[1].pos.y = pos.y + cosf(D3DX_PI * 0.75f) * SETTEXT_SIZE_Y;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = pos.x + sinf(-D3DX_PI * 0.25) * SETTEXT_SIZE_X;

	pVtx[2].pos.y = pos.y + cosf(-D3DX_PI * 0.25f) * SETTEXT_SIZE_Y;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = pos.x + sinf(D3DX_PI * 0.25) * SETTEXT_SIZE_X;

	pVtx[3].pos.y = pos.y + cosf(D3DX_PI * 0.25) * SETTEXT_SIZE_Y;

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

	g_pVtxBuffSetText->Unlock();
}

//=========================
// タイトルメニューの終了処理
//=========================
void UninitSetText(void)
{
	//テクスチャの破棄

	for (int nCount = 0; nCount < SETMODE_MAX; nCount++)
	{
		if (g_pTextureSetText[nCount] != NULL)
		{
			g_pTextureSetText[nCount]->Release();

			g_pTextureSetText[nCount] = NULL;
		}
	}


	//頂点バッファの破棄

	if (g_pVtxBuffSetText != NULL)
	{
		g_pVtxBuffSetText->Release();

		g_pVtxBuffSetText = NULL;
	}
}

//=========================
// タイトルメニューの更新処理
//=========================
void UpdateSetText(void)
{
	g_SetTextMode = GetSetMode();
}

//=========================
// タイトルメニューの描画処理
//=========================
void DrawSetText(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffSetText, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

\
		//テクスチャの設定

		pDevice->SetTexture(0, g_pTextureSetText[g_SetTextMode]);

		///ポリゴンの描画

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
