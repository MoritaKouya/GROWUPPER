//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "fade.h"
#include "sound.h"

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureFade = NULL; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL; //頂点バッファのポインタ

FADE g_fade; //フェードの状態

MODE g_modeNext; //次の画面（モード）

float g_fFade_Y; //フェード画面のY座標

int g_nFadeCounter; //フェードのカウンター

//フェードの初期化処理

void InitFade(MODE modeNext)
{
	g_fade = FADE_IN; //フェードイン状態に

	g_modeNext = modeNext; //次の画面を設定

	g_fFade_Y = SCREEN_HEIGHT; //下にしておく

	g_nFadeCounter = 0; //カウンターを初期化

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み

	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/FADE/fade000.png", //テクスチャのファイル名

		&g_pTextureFade);

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 , //確保するバッファのサイズ
													   //sizeof(VERTEX_2D)*必要な頂点数

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffFade,

		NULL);

	//デバイスの取得

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);

	pVtx[2].pos = D3DXVECTOR3(0.0f, g_fFade_Y, 0.0f);

	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, g_fFade_Y, 0.0f);

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

	//テクスチャ座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffFade->Unlock();

	//モードの設定　

	SetMode(g_modeNext);
}

//終了処理
void UninitFade(void)
{
	//テクスチャの破棄

	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();

		g_pTextureFade = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();

		g_pVtxBuffFade = NULL;
	}
}

//更新処理
void UpdateFade(void)
{
	if (g_fade != FADE_NONE)
	{

		if (g_fade == FADE_IN)
		{ //フェードイン状態

			if (0 == g_nFadeCounter) //フェードイン開始時
			{
				//サウンド

				PlaySound(SOUND_LABEL_SE_FADE002);
			}	

			if (g_fFade_Y <= 0.0f) //フェード画面が上に上がったら
			{
				g_fFade_Y = 0.0f; //Ｙ座標を０にする

				g_fade = FADE_NONE; //何もしていない状態にする				

				g_nFadeCounter = 0; //カウンターの初期化
			}
			else if (g_fFade_Y > 0.0f) //上に上がりきっていない場合
			{
				g_nFadeCounter++; //カウンターを増やす

				g_fFade_Y -= (SCREEN_HEIGHT / 15); //フェード画面を上げる
			}


		}
		else if (g_fade == FADE_OUT)
		{ //フェードアウト状態

			if (g_fFade_Y == 0) //フェードアウト開始時
			{ //サウンド

				PlaySound(SOUND_LABEL_SE_FADE001);
			}
			
			if (g_fFade_Y < SCREEN_HEIGHT) //下に下がり切っていない場合
			{
				g_fFade_Y += (SCREEN_HEIGHT / 15); //フェード画面をを下げていく
			}
			else if (g_fFade_Y >= SCREEN_HEIGHT) //下がり切った場合
			{
				g_fFade_Y = SCREEN_HEIGHT; //Ｙ座標を画面下端にする

				g_nFadeCounter++; //カウンターをプラス
	
				if (g_nFadeCounter >= 60) //下に下がり切って１秒たった時
				{
					g_nFadeCounter = 0; //カウンターをリセット

					g_fade = FADE_IN; //フェードイン状態にする

					//モード設定（次の画面に移行）

					SetMode(g_modeNext);
				}
			}
		}
	}
	//デバイスの取得

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定（０．０f～１．０ｆで設定）

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);

	pVtx[2].pos = D3DXVECTOR3(0.0f, g_fFade_Y, 0.0f);

	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, g_fFade_Y, 0.0f);

	g_pVtxBuffFade->Unlock();
}

//フェードの描画処理
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureFade);

	//ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//フェードの設定
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT; //フェードアウト状態に

	g_modeNext = modeNext;

	g_fFade_Y = 0.0f; //上にしておく

	g_nFadeCounter = 0; //カウンターのリセット
}

//フェードの取得
FADE GetFade(void)
{
	return g_fade;
}