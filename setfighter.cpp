//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "setfighter.h"
#include "input.h"
#include "fade.h"
#include "frame.h"
#include "imagefighter.h"
#include "setarrow.h"
#include "sound.h"
#include "inputname.h"
#include "settext.h"

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureSetFighter = NULL; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSetFighter = NULL; //頂点バッファのポインタ

SETMODE g_SetMode;

//==================================
//設定画面の初期化処理 
//==================================
void InitSetFighter(void)
{
	g_SetMode = SETMODE_0;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/BG/Hangar.png", //テクスチャのファイル名

		&g_pTextureSetFighter);

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
											   //sizeof(VERTEX_2D)*必要な超点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffSetFighter,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffSetFighter->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);

	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);

	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

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

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする

	g_pVtxBuffSetFighter->Unlock();

	//各オブジェクトの初期化処理

	InitFrame(); //フレーム

	Initimagefighter(); //自機械イメージ

	InitSetArrow(); //矢印

	InitInputName(); //名前入力

	InitSetText(); //テキスト

}

//==================================
//設定画面の終了処理 
//==================================
void UninitSetFighter(void)
{
	//テクスチャの破棄

	if (g_pTextureSetFighter != NULL)
	{
		g_pTextureSetFighter->Release();

		g_pTextureSetFighter = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffSetFighter != NULL)
	{
		g_pVtxBuffSetFighter->Release();

		g_pVtxBuffSetFighter = NULL;
	}

	//フレーム

	UninitFrame();

	//自機のイメージ

	Uninitimagefighter();

	//矢印

	UninitSetArrow();

	//名前入力

	UninitInputName();

	//テキスト

	UninitSetText();
}

//==================================
//設定画面の更新処理 
//==================================
void UpdateSetFighter(void)
{
	//フェードの取得

	FADE fade = GetFade();

	if (fade == FADE_NONE) //設定のモードを変える
	{

		switch (g_SetMode)
		{
		case SETMODE_0:

			//フレーム

			UpdateFrame();

			//自機のイメージ

			Updateimagefighter();

			//矢印

			UpdateSetArrow();

			//モード設定

			if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A))
			{ //決定キーが押された

				//サウンド

				PlaySound(SOUND_LABEL_SE_ENTER);


				g_SetMode = SETMODE_1;

			}

			break;

		case SETMODE_1:

			//名前入力

			UpdateInputName();
		}
	}

	UpdateSetText();
}

//==================================
//設定画面の描画処理 
//==================================
void DrawSetFighter(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffSetFighter, 0, sizeof(VERTEX_2D));
	//頂点バッファのポインタ  頂点情報構造体のサイズ

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureSetFighter);

	//ポリゴンの描画
											  //描画する最初の頂点インデックス
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	switch (g_SetMode)
	{
	case SETMODE_0:

		//フレーム

		DrawFrame();

		//自機のイメージ

		Drawimagefighter();

		//矢印

		DrawSetArrow();
		
		break;

	case SETMODE_1:

		DrawInputName();
	}

	DrawSetText();
}

//==================================
//設定画面のモード獲得処理 
//==================================
SETMODE GetSetMode(void)
{
	return g_SetMode;
}