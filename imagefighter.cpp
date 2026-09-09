//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "imagefighter.h"
#include "input.h"
#include "setarrow.h"
#include "sound.h"

//マクロ定義

#define IMAGE_DIAGONAL (300)

#define IMAGEINPUT_TIME_INTERVAL (15) //入力の間隔

//グローバル変数

int g_nSelect;

int g_nImageInputCounter; //プレイヤーのイメージの選択間隔のカウンター

Image g_Image; //イメージ

LPDIRECT3DTEXTURE9 g_pTextureImage[PLAYER_MAX] = {}; //テクスチャのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffImage;

const char* g_aImageTexture_Path[PLAYER_MAX] =
{
	"Data/TEXTURE/PLAYER/player001.png",

	"Data/TEXTURE/PLAYER/player002.png",

	"Data/TEXTURE/PLAYER/player003.png",

	"Data/TEXTURE/PLAYER/player004.png",

	"Data/TEXTURE/PLAYER/player005.png",

	"Data/TEXTURE/PLAYER/player006.png",

	"Data/TEXTURE/PLAYER/player007.png",

	"Data/TEXTURE/PLAYER/player008.png",
};

D3DXCOLOR g_color[PLAYER_MAX] =
{
	D3DXCOLOR(1.0f,0.0f,0.0f,0.25f), //赤

	D3DXCOLOR(0.0f,0.0f,1.0f,0.25f), //青

	D3DXCOLOR(0.0f,1.0f,0.0f,0.25f), //緑

	D3DXCOLOR(1.0f,1.0f,0.0f,0.25f), //黄色

	D3DXCOLOR(1.0f,0.647f,0.0f,0.25f), //オレンジ

	D3DXCOLOR(1.0f,0.0f,1.0f,0.25f), //紫

	D3DXCOLOR(0.0f,1.0f,1.0f,0.25f), //水色

	D3DXCOLOR(0.75f,0.75f,0.75f,0.25f), //灰
}; //色の構造体

//===================
// イメージの初期化処理
//===================
void Initimagefighter(void)
{
	D3DXVECTOR3 pos = 
		
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0); //位置を中央にする

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得

	pDevice = GetDevice();

	//イメージの情報の初期化

	g_Image.tex = PLAYER_1;

	//選択の間隔の初期化

	g_nImageInputCounter = 0;

	//テクスチャの読み込み

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{

		D3DXCreateTextureFromFile(pDevice,

			g_aImageTexture_Path[nCnt], //テクスチャのファイル名

			&g_pTextureImage[nCnt]);
	}
	
	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ（球の数分掛ける）

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffImage,

		NULL
	);

	//頂点情報の設定

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffImage->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = pos.x + sinf(-D3DX_PI * 0.75f) * IMAGE_DIAGONAL;

	pVtx[0].pos.y = pos.y + cosf(-D3DX_PI * 0.75f) * IMAGE_DIAGONAL;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = pos.x + sinf(D3DX_PI * 0.75f) * IMAGE_DIAGONAL;

	pVtx[1].pos.y = pos.y + cosf(D3DX_PI * 0.75f) * IMAGE_DIAGONAL;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = pos.x + sinf(-D3DX_PI * 0.25) * IMAGE_DIAGONAL;

	pVtx[2].pos.y = pos.y + cosf(-D3DX_PI * 0.25) * IMAGE_DIAGONAL;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = pos.x + sinf(D3DX_PI * 0.25) * IMAGE_DIAGONAL;

	pVtx[3].pos.y = pos.y + cosf(D3DX_PI * 0.25) * IMAGE_DIAGONAL;

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

	g_pVtxBuffImage->Unlock();
}

//===================
// イメージの終了処理
//===================
void Uninitimagefighter(void)
{

	//テクスチャの破棄

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{

		if (g_pTextureImage[nCnt] != NULL)
		{
			g_pTextureImage[nCnt]->Release();

			g_pTextureImage[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄

	if (g_pVtxBuffImage != NULL)
	{
		g_pVtxBuffImage->Release();

		g_pVtxBuffImage = NULL;
	}
}

//===================
// イメージの更新処理
//===================
void Updateimagefighter(void)
{
	if (g_nImageInputCounter <= 0)
	{ //前回入力から入力カウント分たったら

		D3DXVECTOR3 stick = GetLeftStick();

		if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) || GetJoypadPress(JOYKEY_LEFT) || stick.x < 0) //Aキーが押された場合
		{
			PlaySound(SOUND_LABEL_SE_ARROW);

			if (PLAYER_1 < g_nSelect) //０より大きい場合
			{
				g_nSelect--; //減らす

				LoadTexture(g_nSelect); //テクスチャを変える

				SetStateSetArrow(0); //矢印の状態の設定
			}
			else //０の場合
			{
				g_nSelect = PLAYER_MAX - 1;

				LoadTexture(g_nSelect); //テクスチャを変える

				SetStateSetArrow(0); //矢印の状態の設定
			}

			g_nImageInputCounter = IMAGEINPUT_TIME_INTERVAL;
		}

		if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) || GetJoypadPress(JOYKEY_RIGHT) || 0 < stick.x) //Aキーが押された場合
		{
			//サウンド

			PlaySound(SOUND_LABEL_SE_ARROW);

			if (g_nSelect < PLAYER_MAX - 1) //最大より小さい場合
			{
				g_nSelect++;

				LoadTexture(g_nSelect); //テクスチャを変える

				SetStateSetArrow(1); //矢印の状態の設定
			}
			else //最大の場合
			{
				g_nSelect = PLAYER_1; //０にする

				LoadTexture(g_nSelect); //テクスチャを変える

				SetStateSetArrow(1); //矢印の状態の設定
			}

			g_nImageInputCounter = IMAGEINPUT_TIME_INTERVAL;

		}
	}
	else
	{
		g_nImageInputCounter--; //選択の間隔のカウンターを減算
	}
}
//===================
// イメージのロード処理
//===================
void LoadTexture(int nSelect)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		g_aImageTexture_Path[nSelect], //テクスチャのファイル名

		&g_pTextureImage[nSelect]);
}

//===================
// イメージの描画処理
//===================
void Drawimagefighter(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffImage, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定(種類に合わせて設定)

	pDevice->SetTexture(0, g_pTextureImage[g_nSelect]);

	//ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//===================
// プレイヤーの獲得処理
//===================
Image GetFighter(void)
{
	g_Image.col = g_color[g_nSelect]; //カラー

	g_Image.tex = (PLAYERCA_TEXTURE)g_nSelect; //テクスチャの番号

	return g_Image;
}