//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "outputname.h"
#include "inputname.h"

//マクロ定義

#define NAME_SIZE (45) //文字のサイズ

#define NAME_INTERVAL (NAME_SIZE + 5) //文字と文字の間隔

//グローバル変数

LPDIRECT3DTEXTURE9 g_apTextureAlphabet[ALPHABETCHART_MAX] = {}; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffName2 = NULL; //頂点バッファのポインタ

const char* g_aChartTexture_Path2[ALPHABETCHART_MAX] =
{
	"Data/TEXTURE/SET/alphabetchart000.png",

	"Data/TEXTURE/SET/alphabetchart001.png",

}; //テクスチャのアドレスの構造体

Name g_aName[MAX_NAME]; //名前の情報を代入する変数

D3DXVECTOR3 g_aNamepos; //名前を表しする位置

//==================================
//ゲーム画面の名前の初期化処理 
//==================================
void InitOutputName(void)
{
	int nCount;

	for (nCount = 0; nCount < MAX_NAME; nCount++)
	{
		g_aName[nCount] = GetName(nCount); //名前の情報を代入する
	}

	g_aNamepos = D3DXVECTOR3(SCREEN_WIDTH , 0.0f + NAME_SIZE, 0.0f);

	//文字数によって位置をずらす

	for (nCount = 0; nCount < MAX_NAME; nCount++)
	{ //最大文字数分繰り返す
		if (g_aName[nCount].nName != NAME_NULL) //文字がある場合
		{
			g_aNamepos.x -= NAME_INTERVAL;
		}
	}

	//デバイスの取得

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	pDevice = GetDevice();

	//テクスチャの読み込み

	for (nCount = 0; nCount < ALPHABETCHART_MAX; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice,

			g_aChartTexture_Path2[nCount], //テクスチャのファイル名

			&g_apTextureAlphabet[nCount]);
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NAME, //確保するバッファのサイズ
											   //sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		& g_pVtxBuffName2,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffName2->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_NAME; nCount++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos.x = (g_aNamepos.x + (nCount * NAME_INTERVAL)) + sinf(-D3DX_PI * 0.75f) * NAME_SIZE;

		pVtx[0].pos.y = g_aNamepos.y + cosf(-D3DX_PI * 0.75f) * NAME_SIZE;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = (g_aNamepos.x + (nCount * NAME_INTERVAL)) + sinf(D3DX_PI * 0.75f) * NAME_SIZE;

		pVtx[1].pos.y = g_aNamepos.y + cosf(D3DX_PI * 0.75f) * NAME_SIZE;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = (g_aNamepos.x + (nCount * NAME_INTERVAL)) + sinf(-D3DX_PI * 0.25) * NAME_SIZE;

		pVtx[2].pos.y = g_aNamepos.y + cosf(-D3DX_PI * 0.25) * NAME_SIZE;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = (g_aNamepos.x + (nCount * NAME_INTERVAL)) + sinf(D3DX_PI * 0.25) * NAME_SIZE;

		pVtx[3].pos.y = g_aNamepos.y + cosf(D3DX_PI * 0.25) * NAME_SIZE;

		pVtx[3].pos.z = 0.0f;

		//rhwの設定 1.0f固定

		pVtx[0].rhw = 1.0f;

		pVtx[1].rhw = 1.0f;

		pVtx[2].rhw = 1.0f;

		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定

		pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_aName[nCount].nName % MAX_COLUMN), (1.0f / MAX_LINES) * (g_aName[nCount].nName / MAX_COLUMN));

		pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_aName[nCount].nName % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_aName[nCount].nName / MAX_COLUMN));

		pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_aName[nCount].nName % MAX_COLUMN), (1.0f / MAX_LINES) * (g_aName[nCount].nName / MAX_COLUMN) + (1.0f / MAX_LINES));

		pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_aName[nCount].nName % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_aName[nCount].nName / MAX_COLUMN) + (1.0f / MAX_LINES));
	}

	//頂点バッファをアンロックする

	g_pVtxBuffName2->Unlock();
}

//==================================
//ゲーム画面の名前の終了処理 
//==================================
void UninitOutputName(void)
{
	//テクスチャの破棄

	for (int nCount = 0; nCount < ALPHABETCHART_MAX; nCount++)
	{
		if (g_apTextureAlphabet[nCount] != NULL)
		{
			g_apTextureAlphabet[nCount]->Release();

			g_apTextureAlphabet[nCount] = NULL;
		}
	}

	//頂点バッファの破棄

	if (g_pVtxBuffName2 != NULL)
	{
		g_pVtxBuffName2->Release();

		g_pVtxBuffName2 = NULL;
	}
}

//==================================
//ゲーム画面の名前の更新処理 
//==================================
void UpdateOutputName(void)
{

}

//==================================
//ゲーム画面の名前の描画処理 
//==================================
void DrawOutputName(void)
{

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffName2, 0, sizeof(VERTEX_2D));
	//頂点バッファのポインタ  頂点情報構造体のサイズ

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		//テクスチャの設定

		pDevice->SetTexture(0, g_apTextureAlphabet[g_aName[nCount].ntype]);

		//ポリゴンの描画
												  //描画する最初の頂点インデックス
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}