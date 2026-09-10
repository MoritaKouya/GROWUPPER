//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "setarrow.h"

#define NUM_SETARROW (2) //矢印の個数

//矢印の状態の列挙型定義

typedef enum
{
	TUTORIALARROWSTATE_NORMAL = 0, //通常状態

	TUTORIALARROWSTATE_TRIGGER, //押された状態

	TUTORIALARROWSTATE_MAX
}TUTORIALARROWSTATE;

//矢印の情報構造体

typedef struct
{
	D3DXVECTOR3 pos; //位置

	D3DXVECTOR3 move; //移動量

	TUTORIALARROWSTATE State; //状態

	int nStateCounter; //状態カウンター

	float fRadius; //半径
}SetArrow;

//グローバル変数

SetArrow g_SetArrow[NUM_SETARROW];

LPDIRECT3DTEXTURE9 g_pTextureSetArrow[NUM_SETARROW] = {}; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSetArrow = NULL; //頂点バッファへのポインタ

const char* g_aSetArrowTexture_Path[TUTORIALARROWSTATE_MAX] =
{
	"Data/TEXTURE/SET/yajirushi001.png",

	"Data/TEXTURE/SET/yajirushi002.png",
};

//=========================
// 矢印の初期化処理
//=========================
void InitSetArrow(void)
{
	int nCount;

	LPDIRECT3DDEVICE9 pDevice;

	g_SetArrow[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f); //位置を左中央にする

	g_SetArrow[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 4) * 3.0f,SCREEN_HEIGHT / 2, 0.0f); //位置を右中央にする

	for (nCount = 0; nCount < NUM_SETARROW; nCount++)
	{
		g_SetArrow[nCount].move = D3DXVECTOR3(0.0f, 5.0f, 0.0f); //移動量

		g_SetArrow[nCount].State = TUTORIALARROWSTATE_NORMAL; //状態

		g_SetArrow[nCount].nStateCounter = 0; //状態カウント

		g_SetArrow[nCount].fRadius = 100; //半径
	}

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	for (nCount = 0; nCount < NUM_SETARROW; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice,

			g_aSetArrowTexture_Path[nCount], //テクスチャのファイル名

			&g_pTextureSetArrow[nCount]);
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * NUM_SETARROW,

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffSetArrow,

		NULL
	);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffSetArrow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_SETARROW; nCnt++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos.x = g_SetArrow[nCnt].pos.x + sinf(-D3DX_PI * 0.75f) * g_SetArrow[nCnt].fRadius;

		pVtx[0].pos.y = g_SetArrow[nCnt].pos.y + cosf(-D3DX_PI * 0.75f) * g_SetArrow[nCnt].fRadius;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_SetArrow[nCnt].pos.x + sinf(D3DX_PI * 0.75f) * g_SetArrow[nCnt].fRadius;

		pVtx[1].pos.y = g_SetArrow[nCnt].pos.y + cosf(D3DX_PI * 0.75f) * g_SetArrow[nCnt].fRadius;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_SetArrow[nCnt].pos.x + sinf(-D3DX_PI * 0.25) * g_SetArrow[nCnt].fRadius;

		pVtx[2].pos.y = g_SetArrow[nCnt].pos.y + cosf(-D3DX_PI * 0.25) * g_SetArrow[nCnt].fRadius;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_SetArrow[nCnt].pos.x + sinf(D3DX_PI * 0.25) * g_SetArrow[nCnt].fRadius;

		pVtx[3].pos.y = g_SetArrow[nCnt].pos.y + cosf(D3DX_PI * 0.25) * g_SetArrow[nCnt].fRadius;

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
	}

	g_pVtxBuffSetArrow->Unlock();

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffSetArrow->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//2つ目のテクスチャの座標

	pVtx[4].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[5].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[7].tex = D3DXVECTOR2(0.0f, 1.0f);

	g_pVtxBuffSetArrow->Unlock();
}

//=========================
// 矢印の終了処理
//=========================
void UninitSetArrow(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < TUTORIALARROWSTATE_MAX; nCnt++)
	{
		if (g_pTextureSetArrow[nCnt] != NULL)
		{
			g_pTextureSetArrow[nCnt]->Release();

			g_pTextureSetArrow[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄

	if (g_pVtxBuffSetArrow != NULL)
	{
		g_pVtxBuffSetArrow->Release();

		g_pVtxBuffSetArrow = NULL;
	}
}

//=========================
// 矢印の更新処理
//=========================
void UpdateSetArrow(void)
{
	for (int nCnt = 0; nCnt < NUM_SETARROW; nCnt++)
	{
		g_SetArrow[nCnt].nStateCounter--;

		if (g_SetArrow[nCnt].nStateCounter <= 0)
		{
			g_SetArrow[nCnt].State = TUTORIALARROWSTATE_NORMAL;
		}
	}
}

//=========================
// 矢印の描画処理
//=========================
void DrawSetArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffSetArrow, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < NUM_SETARROW; nCnt++)
	{
		//テクスチャの設定

		pDevice->SetTexture(0, g_pTextureSetArrow[g_SetArrow[nCnt].State]);

		///ポリゴンの描画

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}
//=========================
// 矢印の状態設定処理
//=========================
void SetStateSetArrow(int nSelect)
{
	g_SetArrow[nSelect].State = TUTORIALARROWSTATE_TRIGGER;

	g_SetArrow[nSelect].nStateCounter = 10; //１秒間
}