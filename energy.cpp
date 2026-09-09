//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "energy.h"
#include "effect.h"
#include "player.h"

//マクロ定義

#define ENERGY_HIT (40) //当たり判定 

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureEnergy = NULL; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnergy = NULL; //頂点バッファへのポインタ

Energy g_aEnergy[MAX_ENERGY]; //エネルギーの情報

//===============================
//エネルギーの初期化処理
//===============================
void InitEnergy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntEnergy;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/ENERGY/Energy001.png", //テクスチャのファイル名

		&g_pTextureEnergy);


	//エネルギーの情報の初期化

	for (nCntEnergy = 0; nCntEnergy < MAX_ENERGY; nCntEnergy++)
	{
		g_aEnergy[nCntEnergy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置

		g_aEnergy[nCntEnergy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //移動量

		g_aEnergy[nCntEnergy].nEnergy = 1; //エネルギー量

		g_aEnergy[nCntEnergy].bUse = false; //使用していない状態にする
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_ENERGY, //確保するバッファのサイズ（エネルギーの数分掛ける）

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffEnergy,

		NULL
	);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffEnergy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnergy = 0; nCntEnergy < MAX_ENERGY; nCntEnergy++, pVtx += 4) //頂点データのポインタを4つ分進める
	{
		//頂点座標の設定

		pVtx[0].pos.x = g_aEnergy[nCntEnergy].pos.x + sinf(-D3DX_PI * 0.75f) * ENERGY_SIZE;

		pVtx[0].pos.y = g_aEnergy[nCntEnergy].pos.y + cosf(-D3DX_PI * 0.75f) * ENERGY_SIZE;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aEnergy[nCntEnergy].pos.x + sinf(D3DX_PI * 0.75f) * ENERGY_SIZE;

		pVtx[1].pos.y = g_aEnergy[nCntEnergy].pos.y + cosf(D3DX_PI * 0.75f) * ENERGY_SIZE;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aEnergy[nCntEnergy].pos.x + sinf(-D3DX_PI * 0.25) * ENERGY_SIZE;

		pVtx[2].pos.y = g_aEnergy[nCntEnergy].pos.y + cosf(-D3DX_PI * 0.25) * ENERGY_SIZE;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aEnergy[nCntEnergy].pos.x + sinf(D3DX_PI * 0.25) * ENERGY_SIZE;

		pVtx[3].pos.y = g_aEnergy[nCntEnergy].pos.y + cosf(D3DX_PI * 0.25) * ENERGY_SIZE;

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

	}

	g_pVtxBuffEnergy->Unlock();
}

//===============================
// エネルギーの終了処理
//===============================
void UninitEnergy(void) 
{
	//テクスチャの破棄

	if (g_pTextureEnergy != NULL)
	{
		g_pTextureEnergy->Release();

		g_pTextureEnergy = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffEnergy != NULL)
	{
		g_pVtxBuffEnergy->Release();

		g_pVtxBuffEnergy = NULL;
	}
}

//===============================
// エネルギーの更新処理
//===============================
void UpdateEnergy(void)
{
	int nCntEnergy;

	for (nCntEnergy = 0; nCntEnergy < MAX_ENERGY; nCntEnergy++)
	{
		if (g_aEnergy[nCntEnergy].bUse == true)
		{//球が使用されている場合
			
			CollisionPlayer(&g_aEnergy[nCntEnergy]); //プレイヤーとの当たり判定
		}
	}
}

//===============================
// エネルギーの描画処理
//===============================
void DrawEnergy(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	int nCntEnergy;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffEnergy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureEnergy);

	for (nCntEnergy = 0; nCntEnergy < MAX_ENERGY; nCntEnergy++)
	{
		if (g_aEnergy[nCntEnergy].bUse == true)
		{ //球が使用されている場合

		//ポリゴンの描画
												  //描画を開始する頂点インデックス
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnergy * 4, 2);
		}
	}
}

//===============================
// エネルギーの設定処理
//===============================
void SetEnergy(D3DXVECTOR3 pos, int nEnergy)
{
	int nCntEnergy,
		
		nTrueCntEnergy; //生成されたエネルギーの数

	//ポリゴンの描画

	VERTEX_2D* pVtx; //forの前でロック、後でアンロック

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffEnergy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnergy = 0, nTrueCntEnergy = 0; nCntEnergy < MAX_ENERGY; nCntEnergy++, pVtx += 4)
	{
		if (g_aEnergy[nCntEnergy].bUse == false)
		{
			g_aEnergy[nCntEnergy].pos = pos; //位置

			//頂点座標の設定

			pVtx[0].pos.x = g_aEnergy[nCntEnergy].pos.x + sinf(-D3DX_PI * 0.75f) * ENERGY_SIZE;

			pVtx[0].pos.y = g_aEnergy[nCntEnergy].pos.y + cosf(-D3DX_PI * 0.75f) * ENERGY_SIZE;

			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEnergy[nCntEnergy].pos.x + sinf(D3DX_PI * 0.75f) * ENERGY_SIZE;

			pVtx[1].pos.y = g_aEnergy[nCntEnergy].pos.y + cosf(D3DX_PI * 0.75f) * ENERGY_SIZE;

			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEnergy[nCntEnergy].pos.x + sinf(-D3DX_PI * 0.25f) * ENERGY_SIZE;

			pVtx[2].pos.y = g_aEnergy[nCntEnergy].pos.y + cosf(-D3DX_PI * 0.25f) * ENERGY_SIZE;

			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEnergy[nCntEnergy].pos.x + sinf(D3DX_PI * 0.25f) * ENERGY_SIZE;

			pVtx[3].pos.y = g_aEnergy[nCntEnergy].pos.y + cosf(D3DX_PI * 0.25f) * ENERGY_SIZE;

			pVtx[3].pos.z = 0.0f;

			g_aEnergy[nCntEnergy].nEnergy = nEnergy; //エネルギー量の設定

			g_aEnergy[nCntEnergy].bUse = true; //使用している状態にする

			nTrueCntEnergy++; //使用されたエネルギーの数をカウント

			break;
		}
	}
	g_pVtxBuffEnergy->Unlock();
}

//==================
// プレイヤーとの当たり判定
//==================
void CollisionPlayer(Energy* pEnergy)
{
	//プレイヤーの取得

	Player* pPlayer = GetPlayer(); //敵の情報の先頭アドレスが代入される	
//中心座標の距離（ｘ、ｙ）

	float fDistance_x = pPlayer->pos.x - pEnergy->pos.x, //距離ｘ

		fDistance_y = pPlayer->pos.y - pEnergy->pos.y; //距離y

	//二つの中心中心座標の距離の2乗

	float fDistanceSquared = (fDistance_x * fDistance_x) + (fDistance_y * fDistance_y);

	//２つの円の半径の合計

	float fTotalRadius = (ENERGY_HIT + PLAYER_DIAGONAL); //半径の合計の長さ

	if (fDistanceSquared <= fTotalRadius * fTotalRadius) //半径の合計の２乗より距離の２乗が小さい場合
	{//エネルギーとプレイヤーが当たった

		pEnergy->bUse = false;

		HitPlayer(HIT_ENERGY, pEnergy->nEnergy); //エネルギーのヒット処理
	}
}