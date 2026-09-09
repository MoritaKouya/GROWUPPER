//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "titlemenu.h"
#include "input.h"
#include "sound.h"

#define NUM_TITLEMENU_TEXT (2) //タイトルメニューの個数

#define TITLEMENU_SIZE_X (150) //横の半径の半径

#define TITLEMENU_SIZE_Y (75) //縦の半径

#define TITLEINPUT_TIME_INTERVAL (15) //入力の間隔

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureTitleMenu[NUM_TITLEMENU_TEXT] = {}; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleMenu = NULL; //頂点バッファへのポインタ

const char* g_aTitleMenuTexture_Path[NUM_TITLEMENU_TEXT] =
{
	"Data/TEXTURE/TITLE/titlemodetext000.png",

	"Data/TEXTURE/TITLE/titlemodetext001.png",
};

int g_nSelectMenu; //選んでいる項目を代入(0がスタート1が終了)

int g_TitleInputMenuCounter; //メニュー選択の間隔のカウンター

//=========================
// タイトルメニューの初期化処理
//=========================
void InitTitleMenu(void)
{
	int nCnt;

	g_nSelectMenu = 0; //選んでいるメニューを初期化

	g_TitleInputMenuCounter = 0; //メニュー選択のカウンターを初期化

	//位置の設定

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 400, 0.0f);	

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	for (nCnt = 0; nCnt < NUM_TITLEMENU_TEXT; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice,

			g_aTitleMenuTexture_Path[nCnt], //テクスチャのファイル名

			&g_pTextureTitleMenu[nCnt]);
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * NUM_TITLEMENU_TEXT,

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffTitleMenu,

		NULL
	);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffTitleMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < NUM_TITLEMENU_TEXT; nCnt++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos.x = pos.x + sinf(-D3DX_PI * 0.75f) * TITLEMENU_SIZE_X;

		pVtx[0].pos.y = pos.y + (nCnt * 125) + cosf(-D3DX_PI * 0.75f) * TITLEMENU_SIZE_Y;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = pos.x + sinf(D3DX_PI * 0.75f) * TITLEMENU_SIZE_X;

		pVtx[1].pos.y = pos.y + (nCnt * 125) + cosf(D3DX_PI * 0.75f) * TITLEMENU_SIZE_Y;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = pos.x + sinf(-D3DX_PI * 0.25) * TITLEMENU_SIZE_X;

		pVtx[2].pos.y = pos.y + (nCnt * 125) + cosf(-D3DX_PI * 0.25f) * TITLEMENU_SIZE_Y;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = pos.x + sinf(D3DX_PI * 0.25) * TITLEMENU_SIZE_X;

		pVtx[3].pos.y = pos.y + (nCnt * 125) + cosf(D3DX_PI * 0.25) * TITLEMENU_SIZE_Y;

		pVtx[3].pos.z = 0.0f;

		//rhwの設定 1.0f固定

		pVtx[0].rhw = 1.0f;

		pVtx[1].rhw = 1.0f;

		pVtx[2].rhw = 1.0f;

		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定（０．０f～１．０ｆで設定）

		if (nCnt == g_nSelectMenu)
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

	g_pVtxBuffTitleMenu->Unlock();

	
}

//=========================
// タイトルメニューの終了処理
//=========================
void UninitTitleMenu(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < NUM_TITLEMENU_TEXT; nCnt++)
	{
		if (g_pTextureTitleMenu[nCnt] != NULL)
		{
			g_pTextureTitleMenu[nCnt]->Release();

			g_pTextureTitleMenu[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄

	if (g_pVtxBuffTitleMenu != NULL)
	{
		g_pVtxBuffTitleMenu->Release();

		g_pVtxBuffTitleMenu = NULL;
	}
}

//=========================
// タイトルメニューの更新処理
//=========================
void UpdateTitleMenu(void)
{
	if (g_TitleInputMenuCounter <= 0)
	{ //前回入力からメニュー選択の間隔分たったら

		D3DXVECTOR3 stick = GetLeftStick();

		if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) || GetJoypadPress(JOYKEY_UP)
			|| GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) || GetJoypadPress(JOYKEY_DOWN)
			|| stick.y != 0)
		{ //上下キーが押された場合

				//サウンド

			PlaySound(SOUND_LABEL_SE_ENTER);

			g_nSelectMenu ^= 1; //0なら1、1なら0にする

			g_TitleInputMenuCounter = TITLEINPUT_TIME_INTERVAL;

				VERTEX_2D* pVtx;

			//頂点バッファをロックし、頂点データへのポインタを取得

			g_pVtxBuffTitleMenu->Lock(0, 0, (void**)&pVtx, 0);

			for (int nCnt = 0; nCnt < NUM_TITLEMENU_TEXT; nCnt++, pVtx += 4)
			{

				//頂点カラーの設定（０．０f～１．０ｆで設定）

				if (nCnt == g_nSelectMenu)
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
			}
		}
	}
	else //メニュー選択の間隔分立っていなかったら
	{
		g_TitleInputMenuCounter--; //カウンターを減算する
	}
}

//=========================
// タイトルメニューの描画処理
//=========================
void DrawTitleMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffTitleMenu, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < NUM_TITLEMENU_TEXT; nCnt++)
	{
		//テクスチャの設定

		pDevice->SetTexture(0, g_pTextureTitleMenu[nCnt]);

		///ポリゴンの描画

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}

//=========================
// タイトルメニューの描画処理
//=========================
int GetTitleMenuSelect(void)
{
	return g_nSelectMenu;
}