//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "pausemenu.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "game.h"

//マクロ定義

#define PAUSEMENU_SIZE_X (150) //横の半径の半径

#define PAUSEMENU_SIZE_Y (75) //縦の半径

#define PAUSEINPUT_TIME_INTERVAL (15) //入力間隔

//ポーズメニューの列挙型定義

typedef enum
{
	PAUSEMENU_0 = 0, //レジュメ

	PAUSEMENU_1, //リトライ

	PAUSEMENU_2, //バッグ

	PAUSEMENU_MAX //メニューの個数

}POSEMENU;

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTexturePauseMenu[PAUSEMENU_MAX] = {}; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseMenu = NULL; //頂点バッファへのポインタ

const char* g_aPauseMenuTexture_Path[PAUSEMENU_MAX] =
{
	"Data/TEXTURE/PAUSE/pausetext001.png", //レジュメ

	"Data/TEXTURE/PAUSE/pausetext002.png", //リトライ

	"Data/TEXTURE/PAUSE/pausetext003.png", //バッグ
};

int g_nSelectPauseMenu; //選んでいる項目を代入

int g_nPauseInputCounter; //入力間隔のカウンター

//=========================
// ポーズメニューの初期化処理
//=========================
void InitPauseMenu(void)
{
	int nCount;

	g_nSelectPauseMenu = 0; //ポーズの選択項目を初期化

	g_nPauseInputCounter = 0; //入力間隔のカウンターを初期化

	//位置の設定

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 300, 0.0f);

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	for (nCount = 0; nCount < PAUSEMENU_MAX; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice,

			g_aPauseMenuTexture_Path[nCount], //テクスチャのファイル名

			&g_pTexturePauseMenu[nCount]);
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * PAUSEMENU_MAX,

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffPauseMenu,

		NULL
	);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < PAUSEMENU_MAX; nCount++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos.x = pos.x + sinf(-D3DX_PI * 0.75f) * PAUSEMENU_SIZE_X;

		pVtx[0].pos.y = pos.y + (nCount * 125) + cosf(-D3DX_PI * 0.75f) * PAUSEMENU_SIZE_Y;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = pos.x + sinf(D3DX_PI * 0.75f) * PAUSEMENU_SIZE_X;

		pVtx[1].pos.y = pos.y + (nCount * 125) + cosf(D3DX_PI * 0.75f) * PAUSEMENU_SIZE_Y;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = pos.x + sinf(-D3DX_PI * 0.25) * PAUSEMENU_SIZE_X;

		pVtx[2].pos.y = pos.y + (nCount * 125) + cosf(-D3DX_PI * 0.25f) * PAUSEMENU_SIZE_Y;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = pos.x + sinf(D3DX_PI * 0.25) * PAUSEMENU_SIZE_X;

		pVtx[3].pos.y = pos.y + (nCount * 125) + cosf(D3DX_PI * 0.25) * PAUSEMENU_SIZE_Y;

		pVtx[3].pos.z = 0.0f;

		//rhwの設定 1.0f固定

		pVtx[0].rhw = 1.0f;

		pVtx[1].rhw = 1.0f;

		pVtx[2].rhw = 1.0f;

		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定（０．０f～１．０ｆで設定）

		if (nCount == (g_nSelectPauseMenu))
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		}

		//テクスチャ座標

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	g_pVtxBuffPauseMenu->Unlock();
}

//=========================
// ポーズメニューの終了処理
//=========================
void UninitPauseMenu(void)
{
	//テクスチャの破棄
	for (int nCount = 0; nCount < PAUSEMENU_MAX; nCount++)
	{
		if (g_pTexturePauseMenu[nCount] != NULL)
		{
			g_pTexturePauseMenu[nCount]->Release();

			g_pTexturePauseMenu[nCount] = NULL;
		}
	}

	//頂点バッファの破棄

	if (g_pVtxBuffPauseMenu != NULL)
	{
		g_pVtxBuffPauseMenu->Release();

		g_pVtxBuffPauseMenu = NULL;
	}
}

//=========================
// ポーズメニューの更新処理
//=========================
void UpdatePauseMenu(void)
{
	int nCount = 0;

	//選択

	if (g_nPauseInputCounter <= 0)
	{ //前回入力から入力間隔分たった場合

		D3DXVECTOR3 stick = GetLeftStick();

		if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) || GetJoypadPress(JOYKEY_UP) || 0 < stick.y)
		{ //上キーが押された場合

			//サウンド

			PlaySound(SOUND_LABEL_SE_ENTER);

			if (g_nSelectPauseMenu == 0)
			{
				g_nSelectPauseMenu = PAUSEMENU_2;
			}
			else
			{
				g_nSelectPauseMenu--; //ポーズメニューを減算
			}

			g_nPauseInputCounter = PAUSEINPUT_TIME_INTERVAL;
		}
		else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) || GetJoypadPress(JOYKEY_DOWN) || stick.y < 0)
		{ //下キーが押された場合

			//サウンド

			PlaySound(SOUND_LABEL_SE_ENTER);

			g_nSelectPauseMenu++; //ポーズメニューを加算

			g_nPauseInputCounter = PAUSEINPUT_TIME_INTERVAL;

		}

		VERTEX_2D* pVtx;

		//頂点バッファをロックし、頂点データへのポインタを取得

		g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

		for (nCount = 0; nCount < PAUSEMENU_MAX; nCount++, pVtx += 4)
		{

			//頂点カラーの設定（０．０f～１．０ｆで設定）

			if (nCount == (g_nSelectPauseMenu % PAUSEMENU_MAX))
			{//選ばれている場合

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{ //選ばれていない場合
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			}
		}

		g_pVtxBuffPauseMenu->Unlock();
	}
	else //前回入力から入力間隔分たっていない場合
	{
		g_nPauseInputCounter--; //入力カウンターを減算
	}

	//決定

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
	{ //決定キーが押された

		switch (g_nSelectPauseMenu % PAUSEMENU_MAX) //選んでいる項目を比較
		{
		case PAUSEMENU_0: //レジュメ

			SetPause();

			break;

		case PAUSEMENU_1: //リトライ

			//サウンド

			StopSound(SOUND_LABEL_BGM001);

			//モードの設定

			SetFade(MODE_GAME); //もう一度ゲームモード

			break;

		case PAUSEMENU_2: //バッグ

			//サウンド

			StopSound(SOUND_LABEL_BGM001);

			//モード設定

			SetFade(MODE_TITLE); //リザルトモードに移動

			break;

		}
	}
}

//=========================
// ポーズメニューの描画処理
//=========================
void DrawPauseMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffPauseMenu, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < PAUSEMENU_MAX; nCount++)
	{
		//テクスチャの設定

		pDevice->SetTexture(0, g_pTexturePauseMenu[nCount]);

		///ポリゴンの描画

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}