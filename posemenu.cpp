//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "posemenu.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "game.h"

//マクロ定義

#define POSEMENU_SIZE_X (150) //横の半径の半径

#define POSEMENU_SIZE_Y (75) //縦の半径

#define POSEINPUT_TIME_INTERVAL (15) //入力間隔

//ポーズメニューの列挙型定義

typedef enum
{
	POSEMENU_0 = 0, //レジュメ

	POSEMENU_1, //リトライ

	POSEMENU_2, //バッグ

	POSEMENU_MAX //メニューの個数

}POSEMENU;

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTexturePoseMenu[POSEMENU_MAX] = {}; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPoseMenu = NULL; //頂点バッファへのポインタ

const char* g_aPoseMenuTexture_Path[POSEMENU_MAX] =
{
	"Data/TEXTURE/POSE/posetext001.png", //レジュメ

	"Data/TEXTURE/POSE/posetext002.png", //リトライ

	"Data/TEXTURE/POSE/posetext003.png", //バッグ
};

int g_nSelectPoseMenu; //選んでいる項目を代入

int g_nPoseInputCounter; //入力間隔のカウンター

//=========================
// ポーズメニューの初期化処理
//=========================
void InitPoseMenu(void)
{
	int nCount;

	g_nSelectPoseMenu = 0; //ポーズの選択項目を初期化

	g_nPoseInputCounter = 0; //入力間隔のカウンターを初期化

	//位置の設定

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 300, 0.0f);

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	for (nCount = 0; nCount < POSEMENU_MAX; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice,

			g_aPoseMenuTexture_Path[nCount], //テクスチャのファイル名

			&g_pTexturePoseMenu[nCount]);
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * POSEMENU_MAX,

		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffPoseMenu,

		NULL
	);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得

	g_pVtxBuffPoseMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < POSEMENU_MAX; nCount++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos.x = pos.x + sinf(-D3DX_PI * 0.75f) * POSEMENU_SIZE_X;

		pVtx[0].pos.y = pos.y + (nCount * 125) + cosf(-D3DX_PI * 0.75f) * POSEMENU_SIZE_Y;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = pos.x + sinf(D3DX_PI * 0.75f) * POSEMENU_SIZE_X;

		pVtx[1].pos.y = pos.y + (nCount * 125) + cosf(D3DX_PI * 0.75f) * POSEMENU_SIZE_Y;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = pos.x + sinf(-D3DX_PI * 0.25) * POSEMENU_SIZE_X;

		pVtx[2].pos.y = pos.y + (nCount * 125) + cosf(-D3DX_PI * 0.25f) * POSEMENU_SIZE_Y;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = pos.x + sinf(D3DX_PI * 0.25) * POSEMENU_SIZE_X;

		pVtx[3].pos.y = pos.y + (nCount * 125) + cosf(D3DX_PI * 0.25) * POSEMENU_SIZE_Y;

		pVtx[3].pos.z = 0.0f;

		//rhwの設定 1.0f固定

		pVtx[0].rhw = 1.0f;

		pVtx[1].rhw = 1.0f;

		pVtx[2].rhw = 1.0f;

		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定（０．０f～１．０ｆで設定）

		if (nCount == (g_nSelectPoseMenu))
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

	g_pVtxBuffPoseMenu->Unlock();
}

//=========================
// ポーズメニューの終了処理
//=========================
void UninitPoseMenu(void)
{
	//テクスチャの破棄
	for (int nCount = 0; nCount < POSEMENU_MAX; nCount++)
	{
		if (g_pTexturePoseMenu[nCount] != NULL)
		{
			g_pTexturePoseMenu[nCount]->Release();

			g_pTexturePoseMenu[nCount] = NULL;
		}
	}

	//頂点バッファの破棄

	if (g_pVtxBuffPoseMenu != NULL)
	{
		g_pVtxBuffPoseMenu->Release();

		g_pVtxBuffPoseMenu = NULL;
	}
}

//=========================
// ポーズメニューの更新処理
//=========================
void UpdatePoseMenu(void)
{
	int nCount = 0;

	//選択

	if (g_nPoseInputCounter <= 0)
	{ //前回入力から入力間隔分たった場合

		D3DXVECTOR3 stick = GetLeftStick();

		if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) || GetJoypadPress(JOYKEY_UP) || 0 < stick.y)
		{ //上キーが押された場合

			//サウンド

			PlaySound(SOUND_LABEL_SE_ENTER);

			if (g_nSelectPoseMenu == 0)
			{
				g_nSelectPoseMenu = POSEMENU_2;
			}
			else
			{
				g_nSelectPoseMenu--; //ポーズメニューを減算
			}

			g_nPoseInputCounter = POSEINPUT_TIME_INTERVAL;
		}
		else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) || GetJoypadPress(JOYKEY_DOWN) || stick.y < 0)
		{ //下キーが押された場合

			//サウンド

			PlaySound(SOUND_LABEL_SE_ENTER);

			g_nSelectPoseMenu++; //ポーズメニューを加算

			g_nPoseInputCounter = POSEINPUT_TIME_INTERVAL;

		}

		VERTEX_2D* pVtx;

		//頂点バッファをロックし、頂点データへのポインタを取得

		g_pVtxBuffPoseMenu->Lock(0, 0, (void**)&pVtx, 0);

		for (nCount = 0; nCount < POSEMENU_MAX; nCount++, pVtx += 4)
		{

			//頂点カラーの設定（０．０f～１．０ｆで設定）

			if (nCount == (g_nSelectPoseMenu % POSEMENU_MAX))
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

		g_pVtxBuffPoseMenu->Unlock();
	}
	else //前回入力から入力間隔分たっていない場合
	{
		g_nPoseInputCounter--; //入力カウンターを減算
	}

	//決定

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
	{ //決定キーが押された

		switch (g_nSelectPoseMenu % POSEMENU_MAX) //選んでいる項目を比較
		{
		case POSEMENU_0: //レジュメ

			SetPose();

			break;

		case POSEMENU_1: //リトライ

			//モードの設定

			SetFade(MODE_GAME); //もう一度ゲームモード

			break;

		case POSEMENU_2: //バッグ

			//モード設定

			SetFade(MODE_TITLE); //リザルトモードに移動

			break;

		}
	}
}

//=========================
// ポーズメニューの描画処理
//=========================
void DrawPoseMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffPoseMenu, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < POSEMENU_MAX; nCount++)
	{
		//テクスチャの設定

		pDevice->SetTexture(0, g_pTexturePoseMenu[nCount]);

		///ポリゴンの描画

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}