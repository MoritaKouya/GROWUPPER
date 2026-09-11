//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================

#include "main.h"

#include "Tutorial.h"

#include "input.h"

#include "fade.h"

#include "sound.h"

#include "tutorialarrow.h"

//マクロ定義

#define TUTORIALINPUT_TIME_INTERVAL (30) //入力の間隔

//テクスチャ番号の列挙型

typedef enum
{
	TUTORIAL_0 = 0, //基本ルール

	TUTORIAL_1, //レベルアップ

	TUTORIAL_2, //ボス１

	TUTORIAL_3, //ボス２

	TUTORIAL_4, //操作方法

	TUTORIAL_MAX //テクスチャの最大数

}TUTORIALNAME;

//グローバル変数

LPDIRECT3DTEXTURE9 g_apTextureTutorial[TUTORIAL_MAX]; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL; //頂点バッファへのポインタ

int g_Tex; //現在のテクスチャを代入する

int g_TutorialInputCounter; //入力間隔のカウンター

//ファイル名

const char* g_aTutorialTexture_Path[TUTORIAL_MAX] =
{
	"Data/TEXTURE/TUTORIAL/tutorial000.png", //基本ルール

	"Data/TEXTURE/TUTORIAL/tutorial001.png", //レベルアップ

	"Data/TEXTURE/TUTORIAL/tutorial002.png", //ボス１

	"Data/TEXTURE/TUTORIAL/tutorial003.png", //ボス２

	"Data/TEXTURE/TUTORIAL/tutorial004.png", //操作方法
};
//==================================
// チュートリアルの初期化処理
//==================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	int nCntTutorial;

	g_Tex = TUTORIAL_0;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	for (nCntTutorial = 0; nCntTutorial < TUTORIAL_MAX; nCntTutorial++)
	{
		D3DXCreateTextureFromFile(pDevice,

			g_aTutorialTexture_Path[nCntTutorial], //テクスチャのファイル名

			&g_apTextureTutorial[nCntTutorial]);
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
											   //sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffTutorial,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);

	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);

	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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

	//各オブジェクトの初期化処理

	InitTutorialArrow(); //矢印

	//頂点バッファをアンロックする

	g_pVtxBuffTutorial->Unlock();
}

//==================================
// チュートリアルの終了処理
//==================================
void UninitTutorial(void)
{
	int nCntTutorial;

	//テクスチャの破棄

	for (nCntTutorial = 0; nCntTutorial < TUTORIAL_MAX; nCntTutorial++)
	{
		if (g_apTextureTutorial[nCntTutorial] != NULL)
		{
			g_apTextureTutorial[nCntTutorial]->Release();

			g_apTextureTutorial[nCntTutorial] = NULL;
		}
	}
	//頂点バッファの破棄

	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();

		g_pVtxBuffTutorial = NULL;
	}

	//各オブジェクトの終了処理

	UninitTutorialArrow(); //矢印

	//サウンドの停止

	StopSound(SOUND_LABEL_BGM000); //再生したいサウンドを指定
}

//==================================
// チュートリアルの更新処理
//==================================
void UpdateTutorial(void)
{
	//フェードの獲得

	FADE fade = GetFade();

	if (fade == FADE_NONE) //フェードしていない場合
	{
		if (g_TutorialInputCounter <= 0)
		{
			D3DXVECTOR3 stick = GetLeftStick();


			if (GetKeyboardPress(DIK_RETURN) == true || GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true
				|| GetJoypadPress(JOYKEY_RIGHT) || GetJoypadPress(JOYKEY_A) || 0 < stick.x )
			{ //進む場合

				//サウンド

				PlaySound(SOUND_LABEL_SE_ENTER);

				//テクスチャの切り替え

				if (g_Tex == TUTORIAL_MAX - 1)
				{ //最後のテクスチャの場合

					//モードの設定

					SetFade(MODE_GAME);
				}
				else
				{ //最後じゃない場合

					//テクスチャを次のものにする

					g_Tex++;
				}

				//矢印の状態設定

				SetStateTutorialArrow(1);

				g_TutorialInputCounter = TUTORIALINPUT_TIME_INTERVAL;
			}
			else if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true
				|| GetJoypadPress(JOYKEY_LEFT) || GetJoypadPress(JOYKEY_B) || stick.x < 0)
			{ //戻る場合

				//矢印の状態設定

				SetStateTutorialArrow(0);

				//サウンド

				PlaySound(SOUND_LABEL_SE_ENTER);

				//テクスチャの切り替え

				if (g_Tex != 0)
				{ //最初のテクスチャじゃない場合

					//テクスチャを前のものにする
					g_Tex--;
				}

				g_TutorialInputCounter = TUTORIALINPUT_TIME_INTERVAL;
			}
		}
		else
		{
			g_TutorialInputCounter--;
		}
	}

	//各オブジェクトの更新処理

	UpdateTutorialArrow(); //矢印
}

//==================================
// チュートリアルの描画処理
//==================================
void DrawTutorial(void)
{

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));
	//頂点バッファのポインタ  頂点情報構造体のサイズ

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	
	pDevice->SetTexture(0, g_apTextureTutorial[g_Tex]);

	//ポリゴンの描画
												  //描画する最初の頂点インデックス
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//各オブジェクトの描画処理

	DrawTutorialArrow(); //矢印

}