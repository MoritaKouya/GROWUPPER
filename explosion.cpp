//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "explosion.h"
#include "sound.h"

//マクロ定義

#define MAX_EXPLOSION (128) //爆発の最大数

#define MAX_ANIM (8) //アニメーションの最大数

#define MAX_COLUMN (8) //列数 

#define MAX_LINES (1) //行数

//爆発構造体の定義
typedef struct
{
	D3DXVECTOR3 pos; //位置

	D3DXCOLOR col; //色

	int nCounterAnim; //アニメーションカウンター

	int nPatternAnim; //アニメーションパターン

	bool bUse; //使用しているかどうか
}Explosion;

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL; //頂点バッファへのポインタ

Explosion g_aExplosion[MAX_EXPLOSION]; //爆発の情報

//=====================
// 爆発の初期化処理
//=====================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntExplosion;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/ENEMY/explosion000.png", //テクスチャのファイル名

		&g_pTextureExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_aExplosion[nCntExplosion].nCounterAnim = 0; //カウンターを初期化する

		g_aExplosion[nCntExplosion].nPatternAnim = 0; //パターンNo,を初期化する

		g_aExplosion[nCntExplosion].bUse = false;
	}
	
	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION, //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な頂点数

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffExplosion,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
	{

		pVtx[0].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(-D3DX_PI * 0.75f) * 10;

		pVtx[0].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(-D3DX_PI * 0.75f) * 10;

		pVtx[0].pos.z = 0.0f;
		
		pVtx[1].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(D3DX_PI * 0.75f) * 10;

		pVtx[1].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(D3DX_PI * 0.75f) * 10;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(-D3DX_PI * 0.25) * 10;

		pVtx[2].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(-D3DX_PI * 0.25) * 10;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(D3DX_PI * 0.25) * 10;

		pVtx[3].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(D3DX_PI * 0.25) * 10;

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

		pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_aExplosion[nCntExplosion].nPatternAnim % MAX_COLUMN), (1.0f / MAX_LINES) * (g_aExplosion[nCntExplosion].nPatternAnim / MAX_COLUMN));

		pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_aExplosion[nCntExplosion].nPatternAnim % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_aExplosion[nCntExplosion].nPatternAnim / MAX_COLUMN));

		pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_aExplosion[nCntExplosion].nPatternAnim % MAX_COLUMN), (1.0f / MAX_LINES) * (g_aExplosion[nCntExplosion].nPatternAnim / MAX_COLUMN) + (1.0f / MAX_LINES));

		pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_aExplosion[nCntExplosion].nPatternAnim % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_aExplosion[nCntExplosion].nPatternAnim / MAX_COLUMN) + (1.0f / MAX_LINES));
	}

	//頂点バッファをアンロックする

	g_pVtxBuffExplosion->Unlock();

}

//=====================
// 爆発の終了処理
//=====================
void UninitExplosion(void)
{
	//テクスチャの破棄

	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();

		g_pTextureExplosion = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();

		g_pVtxBuffExplosion = NULL;
	}
}

//=====================
// 爆発の更新処理
//=====================
void UpdateExplosion(void)
{
	int nCntExplosion;

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{ //爆発が使用されている

			//カウンタを進めて、パターンNo.を更新する

			g_aExplosion[nCntExplosion].nCounterAnim++;

			if ((g_aExplosion[nCntExplosion].nCounterAnim % 5) == 0) //一定時間経過した
			{
				g_aExplosion[nCntExplosion].nCounterAnim = 0; //カウンターを初期値に戻す

				g_aExplosion[nCntExplosion].nPatternAnim++; //パターンNo.を増やす

				pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_aExplosion[nCntExplosion].nPatternAnim % MAX_COLUMN), (1.0f / MAX_LINES) * (g_aExplosion[nCntExplosion].nPatternAnim / MAX_COLUMN));

				pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_aExplosion[nCntExplosion].nPatternAnim % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_aExplosion[nCntExplosion].nPatternAnim / MAX_COLUMN));

				pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_aExplosion[nCntExplosion].nPatternAnim % MAX_COLUMN), (1.0f / MAX_LINES) * (g_aExplosion[nCntExplosion].nPatternAnim / MAX_COLUMN) + (1.0f / MAX_LINES));

				pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_aExplosion[nCntExplosion].nPatternAnim % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_aExplosion[nCntExplosion].nPatternAnim / MAX_COLUMN) + (1.0f / MAX_LINES));
			}

			if (g_aExplosion[nCntExplosion].nPatternAnim > MAX_ANIM)//総パターン数を超えた
			{
				g_aExplosion[nCntExplosion].bUse = false; //使用していない状態にする
			}
		}
	}

	//頂点バッファをアンロックする

	g_pVtxBuffExplosion->Unlock();
}

//=====================
// 爆発の描画処理
//=====================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	int nCntExplosion;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{ //球が使用されている場合

		//ポリゴンの描画
												  //描画を開始する頂点インデックス
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
}

//=====================
// 爆発の設定処理
//=====================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	PlaySound(SOUND_LABEL_SE_EXPLOSION);

	int nCntExplosion;

	//ポリゴンの描画

	VERTEX_2D* pVtx; //forの前でロック、後でアンロック

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//爆発が使用されていない

			//爆発の情報を設定 <アニメーションカウンタ、パターンの初期化など

			g_aExplosion[nCntExplosion].nCounterAnim = 0; //カウンターを初期化する

			g_aExplosion[nCntExplosion].nPatternAnim = 0; //パターンNo,を初期化する

			g_aExplosion[nCntExplosion].pos = pos; //位置

			g_aExplosion[nCntExplosion].col = col; //色

			//頂点情報の設定

			pVtx[0].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(-D3DX_PI * 0.75f) * 100;

			pVtx[0].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(-D3DX_PI * 0.75f) * 100;

			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(D3DX_PI * 0.75f) * 100;

			pVtx[1].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(D3DX_PI * 0.75f) * 100;

			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(-D3DX_PI * 0.25) * 100;

			pVtx[2].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(-D3DX_PI * 0.25) * 100;

			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(D3DX_PI * 0.25) * 100;

			pVtx[3].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(D3DX_PI * 0.25) * 100;

			pVtx[3].pos.z = 0.0f;

			//テクスチャ座標の設定

			pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_aExplosion[nCntExplosion].nPatternAnim % MAX_COLUMN), (1.0f / MAX_LINES) * (g_aExplosion[nCntExplosion].nPatternAnim / MAX_COLUMN));

			pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_aExplosion[nCntExplosion].nPatternAnim % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_aExplosion[nCntExplosion].nPatternAnim / MAX_COLUMN));

			pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_aExplosion[nCntExplosion].nPatternAnim % MAX_COLUMN), (1.0f / MAX_LINES) * (g_aExplosion[nCntExplosion].nPatternAnim / MAX_COLUMN) + (1.0f / MAX_LINES));

			pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_aExplosion[nCntExplosion].nPatternAnim % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_aExplosion[nCntExplosion].nPatternAnim / MAX_COLUMN) + (1.0f / MAX_LINES));

			g_aExplosion[nCntExplosion].bUse = true; //使用している状態にする

			break; //for文を抜ける

		}
	}
	//頂点バッファをアンロックする

	g_pVtxBuffExplosion->Unlock();
}