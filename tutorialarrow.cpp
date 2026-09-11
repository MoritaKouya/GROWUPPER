//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "Tutorialarrow.h"

#define NUM_TUTORIALARROW (2) //矢印の個数

//矢印の状態の列挙型定義

typedef enum
{
	TUTORIALSTATE_NORMAL = 0, //通常状態

	TUTORIALSTATE_TRIGGER, //押された状態

	TUTORIALSTATE_MAX
}TutorialArrowSTATE;

//矢印の情報構造体

typedef struct
{
	D3DXVECTOR3 pos; //位置

	D3DXVECTOR3 move; //移動量

	TutorialArrowSTATE State; //状態

	int nStateCounter; //状態カウンター

	float fRadius; //半径
}TutorialArrow;

//グローバル変数

TutorialArrow g_TutorialArrow[NUM_TUTORIALARROW];

LPDIRECT3DTEXTURE9 g_pTextureTutorialArrow[TUTORIALSTATE_MAX] = {}; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialArrow = NULL; //頂点バッファへのポインタ

const char* g_aTutorialArrowTexture_Path[TUTORIALSTATE_MAX] =
{
	"Data/TEXTURE/TUTORIAL/yajirushi001.png",

	"Data/TEXTURE/TUTORIAL/yajirushi002.png",
};

//=========================
// 矢印の初期化処理
//=========================
void InitTutorialArrow(void)
{
	int nCount;

	LPDIRECT3DDEVICE9 pDevice;

	g_TutorialArrow[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 10, SCREEN_HEIGHT / 12 * 11, 0.0f); //位置を左中央にする

	g_TutorialArrow[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 10 * 9, SCREEN_HEIGHT / 12 * 11, 0.0f); //位置を右中央にする

	for (nCount = 0; nCount < NUM_TUTORIALARROW; nCount++)
	{
		g_TutorialArrow[nCount].move = D3DXVECTOR3(0.0f, 5.0f, 0.0f); //移動量

		g_TutorialArrow[nCount].State = TUTORIALSTATE_NORMAL; //状態

		g_TutorialArrow[nCount].nStateCounter = 0; //状態カウント

		g_TutorialArrow[nCount].fRadius = 50; //半径
	}

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	for (nCount = 0; nCount < TUTORIALSTATE_MAX; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice,

			g_aTutorialArrowTexture_Path[nCount], //テクスチャのファイル名

			&g_pTextureTutorialArrow[nCount]);
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * NUM_TUTORIALARROW,

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffTutorialArrow,

		NULL
	);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffTutorialArrow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_TUTORIALARROW; nCnt++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos.x = g_TutorialArrow[nCnt].pos.x + sinf(-D3DX_PI * 0.75f) * g_TutorialArrow[nCnt].fRadius;

		pVtx[0].pos.y = g_TutorialArrow[nCnt].pos.y + cosf(-D3DX_PI * 0.75f) * g_TutorialArrow[nCnt].fRadius;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_TutorialArrow[nCnt].pos.x + sinf(D3DX_PI * 0.75f) * g_TutorialArrow[nCnt].fRadius;

		pVtx[1].pos.y = g_TutorialArrow[nCnt].pos.y + cosf(D3DX_PI * 0.75f) * g_TutorialArrow[nCnt].fRadius;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_TutorialArrow[nCnt].pos.x + sinf(-D3DX_PI * 0.25) * g_TutorialArrow[nCnt].fRadius;

		pVtx[2].pos.y = g_TutorialArrow[nCnt].pos.y + cosf(-D3DX_PI * 0.25) * g_TutorialArrow[nCnt].fRadius;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_TutorialArrow[nCnt].pos.x + sinf(D3DX_PI * 0.25) * g_TutorialArrow[nCnt].fRadius;

		pVtx[3].pos.y = g_TutorialArrow[nCnt].pos.y + cosf(D3DX_PI * 0.25) * g_TutorialArrow[nCnt].fRadius;

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

	g_pVtxBuffTutorialArrow->Unlock();

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffTutorialArrow->Lock(0, 0, (void**)&pVtx, 0);

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

	g_pVtxBuffTutorialArrow->Unlock();
}

//=========================
// 矢印の終了処理
//=========================
void UninitTutorialArrow(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < TUTORIALSTATE_MAX; nCnt++)
	{
		if (g_pTextureTutorialArrow[nCnt] != NULL)
		{
			g_pTextureTutorialArrow[nCnt]->Release();

			g_pTextureTutorialArrow[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄

	if (g_pVtxBuffTutorialArrow != NULL)
	{
		g_pVtxBuffTutorialArrow->Release();

		g_pVtxBuffTutorialArrow = NULL;
	}
}

//=========================
// 矢印の更新処理
//=========================
void UpdateTutorialArrow(void)
{
	for (int nCnt = 0; nCnt < NUM_TUTORIALARROW; nCnt++)
	{
		

		if (g_TutorialArrow[nCnt].nStateCounter <= 0)
		{ //状態カウンターが０以下の場合

			//矢印の状態を通常にする

			g_TutorialArrow[nCnt].State = TUTORIALSTATE_NORMAL;
		}
		else
		{ //状態カウンターが０より大きい場合

			//状態カウンターをマイナス

			g_TutorialArrow[nCnt].nStateCounter--;
		}
	}
}

//=========================
// 矢印の描画処理
//=========================
void DrawTutorialArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffTutorialArrow, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < NUM_TUTORIALARROW; nCnt++)
	{
		//テクスチャの設定

		pDevice->SetTexture(0, g_pTextureTutorialArrow[g_TutorialArrow[nCnt].State]);

		///ポリゴンの描画

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}
//=========================
// 矢印の状態設定処理
//=========================
void SetStateTutorialArrow(int nSelect)
{
	//矢印を押されている状態にする

	g_TutorialArrow[nSelect].State = TUTORIALSTATE_TRIGGER;

	//状態カウンターの設定

	g_TutorialArrow[nSelect].nStateCounter = 10;
}