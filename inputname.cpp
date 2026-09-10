//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#include "inputname.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//マクロ定義

//アルファベット表

#define ALPHABETCHART_SIZE_X (64 * MAX_COLUMN) //アルファベットの横のサイズ

#define ALPHABETCHART_SIZE_Y (64 * MAX_LINES) //アルファベット表の縦のサイズ

//名前がない時の名前の文字数

#define MAX_NONAME (7)

//カーソル

#define CURSOR_SIZE (60) //カーソルのサイズ

#define IMAGEINPUT_TIME_INTERVAL (15) //入力の間隔

//名前

#define NAME_SIZE (64) //名前の文字のサイズ

//名前入力の選択肢の列挙型定義

typedef enum
{
	SELECTINPUT_MAX_ALPHABET = 25, //0～25までアルファベット

	SELECTINPUT_CHANGE_CHART, //表のタイプを変える

	SELECTINPUT_SPACE, //スペースを入れる

	SELECTINPUT_BACKSPACE, //一文字消す

	SELECTINPUT_ENTER, //エンターキー

	SELECTINPUT_MAX //最大数

}SELECTINPUT;

//テキストカーソルの構造体定義

typedef struct
{
	D3DXVECTOR3 pos; //位置

	D3DXCOLOR col; //色（透明度）

	int nCounter; //カウンター

}TextCursor;

//グローバル変数

LPDIRECT3DTEXTURE9 g_apTextureAlphabetChart[ALPHABETCHART_MAX] = {}; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAlphabetChart = NULL; //頂点バッファのポインタ

const char* g_aChartTexture_Path[ALPHABETCHART_MAX] =
{
	"Data/TEXTURE/SET/alphabetchart000.png",

	"Data/TEXTURE/SET/alphabetchart001.png",

}; //テクスチャのアドレスの構造体

int g_ChartType; //表の種類を代入

//カーソル

LPDIRECT3DTEXTURE9 g_pTextureCursor = NULL; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCursor = NULL; //頂点バッファのポインタ

D3DXVECTOR3 g_posCursor; //カーソルの位置

int g_nSelectAlphabet; //選んだアルファベットを代入する変数

int g_nNameInputCounter;

//名前

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffName = NULL; //頂点バッファのポインタ

Name g_Name[MAX_NAME]; //名前を代入する配列

int g_aNameCount; //入力する名前の文字数カウント

LPD3DXFONT g_pFont2 = NULL; //フォントへのポインタ

D3DXVECTOR3 g_Namepos(SCREEN_WIDTH / 2 -  160, SCREEN_HEIGHT / 4, 0.0f);
//入力された名前とカーソルの初期位置

bool g_bNoName; //名前があるかないか（あるならfalseないならtrue）

int g_NoName[MAX_NONAME] = { 13, 14, 30, 13, 0, 12, 4 };

//テキストカーソルの情報

TextCursor g_TextCursor;

LPDIRECT3DTEXTURE9 g_pTextureTextCursor = NULL; //テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTextCursor = NULL; //頂点バッファのポインタ

//==================================
//名前入力の初期化処理 
//==================================
void InitInputName(void)
{
	//アルファベット表

	InitAlphabetChart();

	//カーソル

	InitInputCursor();

	//名前

	InitName();

	//テキストカーソル

	InitTextCursor();
}
//==================================
//名前入力の終了処理 
//==================================
void UninitInputName(void)
{
	//アルファベット表

	UninitAlphabetChart();

	//カーソル

	UninitInputCursor();

	//名前

	UninitName();

	//テキストカーソル

	UninitTextCursor();
}

//==================================
//名前入力の更新処理 
//==================================
void UpdateInputName(void)
{
	//カーソル

	UpdateInputCursor();

	//名前

	UpdateName();

	//テキストカーソル

	UpdateTextCursor();
}
//==================================
//名前入力の描画処理 
//==================================
void DrawInputName(void)
{
	//アルファベット

	DrawAlphabetChart();

	//カーソル

	DrawInputCursor();

	//名前

	DrawName();

	//テキストカーソル

	DrawTextCursor();
}
//==================================
//アルファベット表の初期化処理 
//==================================
void InitAlphabetChart(void)
{
	D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 3, 0.0f);

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	g_ChartType = ALPHABETCHART_0;

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み

	for (int nCount = 0; nCount < ALPHABETCHART_MAX; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice,

			g_aChartTexture_Path[nCount], //テクスチャのファイル名

			&g_apTextureAlphabetChart[nCount]);
	}

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
											   //sizeof(VERTEX_2D)*必要な超点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffAlphabetChart,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffAlphabetChart->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = pos.x + sinf(-D3DX_PI * 0.75f) * ALPHABETCHART_SIZE_X;

	pVtx[0].pos.y = pos.y + cosf(-D3DX_PI * 0.75f) * ALPHABETCHART_SIZE_Y;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = pos.x + sinf(D3DX_PI * 0.75f) * ALPHABETCHART_SIZE_X;

	pVtx[1].pos.y = pos.y + cosf(D3DX_PI * 0.75f) * ALPHABETCHART_SIZE_Y;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = pos.x + sinf(-D3DX_PI * 0.25) * ALPHABETCHART_SIZE_X;

	pVtx[2].pos.y = pos.y + cosf(-D3DX_PI * 0.25) * ALPHABETCHART_SIZE_Y;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = pos.x + sinf(D3DX_PI * 0.25) * ALPHABETCHART_SIZE_X;

	pVtx[3].pos.y = pos.y + cosf(D3DX_PI * 0.25) * ALPHABETCHART_SIZE_Y;

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

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする

	g_pVtxBuffAlphabetChart->Unlock();
}

//==================================
//アルファベット表の終了処理 
//==================================
void UninitAlphabetChart(void)
{
	//テクスチャの破棄

	for (int nCount = 0; nCount < ALPHABETCHART_MAX; nCount++)
	{
		if (g_apTextureAlphabetChart[nCount] != NULL)
		{
			g_apTextureAlphabetChart[nCount]->Release();

			g_apTextureAlphabetChart[nCount] = NULL;
		}
	}

	//頂点バッファの破棄

	if (g_pVtxBuffAlphabetChart != NULL)
	{
		g_pVtxBuffAlphabetChart->Release();

		g_pVtxBuffAlphabetChart = NULL;
	}
}

//==================================
//アルファベット表の更新処理 
//==================================
void UpdateAlphabetChart(void)
{
}

//==================================
//アルファベット表の描画処理 
//==================================
void DrawAlphabetChart(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffAlphabetChart, 0, sizeof(VERTEX_2D));
	//頂点バッファのポインタ  頂点情報構造体のサイズ

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_apTextureAlphabetChart[g_ChartType]);

	//ポリゴンの描画
											  //描画する最初の頂点インデックス
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==================================
//カーソルの初期化処理 
//==================================
void InitInputCursor(void)
{
	//各変数の初期化

	g_posCursor = D3DXVECTOR3((SCREEN_WIDTH / 2) - (45 * 7),

		(SCREEN_HEIGHT / 4 * 3) - (45 * 3), 0.0f); //位置

	g_nSelectAlphabet = 0; //選んだアルファベット

	g_nNameInputCounter = 0; //入力カウンターを初期化

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//テクスチャの読み込み


	D3DXCreateTextureFromFile(pDevice,

		"Data/TEXTURE/SET/input_cursor000.png", //テクスチャのファイル名

		&g_pTextureCursor);


	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
											   //sizeof(VERTEX_2D)*必要な超点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffCursor,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffCursor->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = g_posCursor.x + sinf(-D3DX_PI * 0.75f) * CURSOR_SIZE;

	pVtx[0].pos.y = g_posCursor.y + cosf(-D3DX_PI * 0.75f) * CURSOR_SIZE;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_posCursor.x + sinf(D3DX_PI * 0.75f) * CURSOR_SIZE;

	pVtx[1].pos.y = g_posCursor.y + cosf(D3DX_PI * 0.75f) * CURSOR_SIZE;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_posCursor.x + sinf(-D3DX_PI * 0.25) * CURSOR_SIZE;

	pVtx[2].pos.y = g_posCursor.y + cosf(-D3DX_PI * 0.25) * CURSOR_SIZE;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_posCursor.x + sinf(D3DX_PI * 0.25) * CURSOR_SIZE;

	pVtx[3].pos.y = g_posCursor.y + cosf(D3DX_PI * 0.25) * CURSOR_SIZE;

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

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする

	g_pVtxBuffCursor->Unlock();
}

//==================================
//カーソルの終了処理 
//==================================
void UninitInputCursor(void)
{
	//テクスチャの破棄

	if (g_pTextureCursor != NULL)
	{
		g_pTextureCursor->Release();

		g_pTextureCursor = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffCursor != NULL)
	{
		g_pVtxBuffCursor->Release();

		g_pVtxBuffCursor = NULL;
	}
}
//==================================
//カーソルの更新処理 
//==================================
void UpdateInputCursor(void)
{
	int nCount;

	//カーソルの移動処理

	MoveInputCursor();

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A))
	{ //決定キーが押された

		//サウンド

		PlaySound(SOUND_LABEL_SE_ENTER);

		if (g_nSelectAlphabet <= SELECTINPUT_MAX_ALPHABET)
		{  //アルファベットが選ばれた場合

			if (g_aNameCount != MAX_NAME)
			{
			g_Name[g_aNameCount].nName = g_nSelectAlphabet; //名前の番号を入力

			g_Name[g_aNameCount].ntype = g_ChartType;

			g_aNameCount++; //名前の文字数カウントを増やす
			}
		}
		else
		{ //それ以外の場合
			switch (g_nSelectAlphabet)
			{
			case SELECTINPUT_CHANGE_CHART:

				g_ChartType ^= 1;

				break;

			case SELECTINPUT_SPACE:

				if (g_aNameCount != MAX_NAME)
				{

					g_Name[g_aNameCount].nName = NAME_SPACE;

					g_aNameCount++;
				}

				break;

			case SELECTINPUT_BACKSPACE:

				if (g_aNameCount != 0)
				{
					g_aNameCount--;

					g_Name[g_aNameCount].nName = NAME_NULL;
				}
				

				break;

			case SELECTINPUT_ENTER:

				for (nCount = 0; nCount < MAX_NAME; nCount++)
				{ //名前があると判定するまで繰り返す処理
					if (g_Name[nCount].nName != NAME_SPACE && g_Name[nCount].nName != NAME_NULL)
					{ //名前がある場合


						g_bNoName = false;

						break;
					}
				}

				if (g_bNoName == true) //名前がない場合
				{
					for (nCount = 0; nCount < MAX_NONAME; nCount++)
					{ //名前をNONAMEにする
						g_Name[nCount].nName = g_NoName[nCount];

						g_Name[nCount].ntype = ALPHABETCHART_0; //大文字にする
					}
				}

				//モード切替（チュートリアル）

				SetFade(MODE_TUTORIAL);

				break;
			}
		}

	}

	if (GetJoypadTrigger(JOYKEY_START) == true)
	{
		for (nCount = 0; nCount < MAX_NAME; nCount++)
		{ //名前があると判定するまで繰り返す処理
			if (g_Name[nCount].nName != NAME_SPACE && g_Name[nCount].nName != NAME_NULL)
			{ //名前がある場合


				g_bNoName = false;

				break;
			}
		}

		if (g_bNoName == true) //名前がない場合
		{
			for (nCount = 0; nCount < MAX_NONAME; nCount++)
			{ //名前をNONAMEにする
				g_Name[nCount].nName = g_NoName[nCount];

				g_Name[nCount].ntype = ALPHABETCHART_0; //大文字にする
			}
		}

		//モード切替（チュートリアル）

		SetFade(MODE_TUTORIAL);
	}
}

//==================================
//カーソルの移動入力処理 
//==================================
void MoveInputCursor(void)
{
	if (g_nNameInputCounter <= 0)
	{
		D3DXVECTOR3 stick = GetLeftStick();

		if (stick.x != 0 || stick.y != 0) //スティックが入力されている場合
		{
			if (stick.y * stick.y < stick.x * stick.x)
			{ //縦方向より横方向のほうが大きく入力されている場合

				if (stick.x < 0) //スティックのｘ座標がマイナスの場合
				{
					//サウンド

					PlaySound(SOUND_LABEL_SE_ARROW);

					g_nSelectAlphabet--;

					if (g_nSelectAlphabet < 0)
					{
						g_nSelectAlphabet = SELECTINPUT_ENTER;
					}

					g_nNameInputCounter = IMAGEINPUT_TIME_INTERVAL;
				}
				else if (0 < stick.x) //スティックのｘ座標がプラスの場合
				{
					//サウンド

					PlaySound(SOUND_LABEL_SE_ARROW);

					g_nSelectAlphabet++;

					if (SELECTINPUT_ENTER < g_nSelectAlphabet)
					{
						g_nSelectAlphabet = 0;

					}

					g_nNameInputCounter = IMAGEINPUT_TIME_INTERVAL;
				}
			}

			if (stick.x * stick.x < stick.y * stick.y )
			{ //横方向より縦方向のほうが大きく入力されている場合

				if (stick.y < 0) //スティックのy座標がマイナスの場合
				{
					//サウンド

					PlaySound(SOUND_LABEL_SE_ARROW);

					if (24 <= g_nSelectAlphabet)
					{
						g_nSelectAlphabet -= 24;
					}
					else
					{
						g_nSelectAlphabet += 8;
					}
					if (g_nSelectAlphabet == 30)
					{
						g_nSelectAlphabet = 6;
					}
					if (g_nSelectAlphabet == 31)
					{
						g_nSelectAlphabet = 7;
					}

					g_nNameInputCounter = IMAGEINPUT_TIME_INTERVAL;
				}
				else if (0 < stick.y) //スティックのy座標がプラスの場合
				{
					//サウンド

					PlaySound(SOUND_LABEL_SE_ARROW);

					if (g_nSelectAlphabet < 8)
					{
						g_nSelectAlphabet += 24;
					}
					else
					{
						g_nSelectAlphabet -= 8;
					}

					if (g_nSelectAlphabet == 30)
					{
						g_nSelectAlphabet = 22;
					}
					if (g_nSelectAlphabet == 31)
					{
						g_nSelectAlphabet = 23;
					}

					g_nNameInputCounter = IMAGEINPUT_TIME_INTERVAL;
				}

			}

		}
		else
		{
			if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) || GetJoypadPress(JOYKEY_LEFT)) //Aキーが押された場合
			{
				//サウンド

				PlaySound(SOUND_LABEL_SE_ARROW);

				g_nSelectAlphabet--;

				if (g_nSelectAlphabet < 0)
				{
					g_nSelectAlphabet = SELECTINPUT_ENTER;
				}

				g_nNameInputCounter = IMAGEINPUT_TIME_INTERVAL;
			}
			else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) || GetJoypadPress(JOYKEY_RIGHT)) //Dキーが押された場合
			{
				//サウンド

				PlaySound(SOUND_LABEL_SE_ARROW);

				g_nSelectAlphabet++;

				if (SELECTINPUT_ENTER < g_nSelectAlphabet)
				{
					g_nSelectAlphabet = 0;

				}
				g_nNameInputCounter = IMAGEINPUT_TIME_INTERVAL;
			}
			else if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) || GetJoypadPress(JOYKEY_UP)) //Wキーが押された場合
			{
				//サウンド

				PlaySound(SOUND_LABEL_SE_ARROW);

				if (g_nSelectAlphabet < 8)
				{
					g_nSelectAlphabet += 24;
				}
				else
				{
					g_nSelectAlphabet -= 8;
				}

				if (g_nSelectAlphabet == 30)
				{
					g_nSelectAlphabet = 22;
				}
				if (g_nSelectAlphabet == 31)
				{
					g_nSelectAlphabet = 23;
				}

				g_nNameInputCounter = IMAGEINPUT_TIME_INTERVAL;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) || GetJoypadPress(JOYKEY_DOWN)) //Sキーが押された場合
			{
				//サウンド

				PlaySound(SOUND_LABEL_SE_ARROW);

				if (24 <= g_nSelectAlphabet)
				{
					g_nSelectAlphabet -= 24;
				}
				else
				{
					g_nSelectAlphabet += 8;
				}
				if (g_nSelectAlphabet == 30)
				{
					g_nSelectAlphabet = 6;
				}
				if (g_nSelectAlphabet == 31)
				{
					g_nSelectAlphabet = 7;
				}
				g_nNameInputCounter = IMAGEINPUT_TIME_INTERVAL;
			}
		}

		g_posCursor = D3DXVECTOR3((SCREEN_WIDTH / 2) - (45 * 7),

			(SCREEN_HEIGHT / 4 * 3) - (45 * 3), 0.0f); //位置

		//頂点バッファをロックし、頂点情報へのポインタを取得

		VERTEX_2D* pVtx; //頂点情報へのポインタ

		g_pVtxBuffCursor->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定

		pVtx[0].pos.x = g_posCursor.x + (g_nSelectAlphabet % 8 * 90) + sinf(-D3DX_PI * 0.75f) * CURSOR_SIZE;

		pVtx[0].pos.y = g_posCursor.y + (g_nSelectAlphabet / 8 * 90) + cosf(-D3DX_PI * 0.75f) * CURSOR_SIZE;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_posCursor.x + (g_nSelectAlphabet % 8 * 90) + sinf(D3DX_PI * 0.75f) * CURSOR_SIZE;

		pVtx[1].pos.y = g_posCursor.y + (g_nSelectAlphabet / 8 * 90) + cosf(D3DX_PI * 0.75f) * CURSOR_SIZE;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_posCursor.x + (g_nSelectAlphabet % 8 * 90) + sinf(-D3DX_PI * 0.25) * CURSOR_SIZE;

		pVtx[2].pos.y = g_posCursor.y + (g_nSelectAlphabet / 8 * 90) + cosf(-D3DX_PI * 0.25) * CURSOR_SIZE;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_posCursor.x + (g_nSelectAlphabet % 8 * 90) + sinf(D3DX_PI * 0.25) * CURSOR_SIZE;

		pVtx[3].pos.y = g_posCursor.y + (g_nSelectAlphabet / 8 * 90) + cosf(D3DX_PI * 0.25) * CURSOR_SIZE;

		pVtx[3].pos.z = 0.0f;

		//頂点バッファをアンロックする

		g_pVtxBuffCursor->Unlock();
	}
	else //前回入力から入力間隔分立っていない場合
	{
		g_nNameInputCounter--; //入力カウンターを減算
	}
}

//==================================
//カーソルの描画処理 
//==================================
void DrawInputCursor(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffCursor, 0, sizeof(VERTEX_2D));
	//頂点バッファのポインタ  頂点情報構造体のサイズ

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureCursor);

	//ポリゴンの描画
											  //描画する最初の頂点インデックス
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==================================
//名前の初期化処理 
//==================================
void InitName(void)
{
	int nCount;

	for (nCount = 0; nCount < MAX_NAME; nCount++)
	{
		g_Name[nCount].nName = NAME_NULL; //名前の初期化

		g_Name[nCount].ntype = ALPHABETCHART_0; //名前の初期化
	}

	g_bNoName = true; //名前がない状態にする

	g_aNameCount = 0; //文字数カウント

	//デバイスの取得

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	pDevice = GetDevice();

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NAME, //確保するバッファのサイズ
											   //sizeof(VERTEX_2D)*必要な超点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffName,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffName->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_NAME; nCount++, pVtx += 4)
	{
		//頂点座標の設定

		pVtx[0].pos.x = (g_Namepos.x + (nCount * 50))+ sinf(-D3DX_PI * 0.75f) * NAME_SIZE;

		pVtx[0].pos.y = g_Namepos.y + cosf(-D3DX_PI * 0.75f) * NAME_SIZE;

		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = (g_Namepos.x + (nCount * 50)) + sinf(D3DX_PI * 0.75f) * NAME_SIZE;

		pVtx[1].pos.y = g_Namepos.y + cosf(D3DX_PI * 0.75f) * NAME_SIZE;

		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = (g_Namepos.x + (nCount * 50)) + sinf(-D3DX_PI * 0.25) * NAME_SIZE;

		pVtx[2].pos.y = g_Namepos.y + cosf(-D3DX_PI * 0.25) * NAME_SIZE;

		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = (g_Namepos.x + (nCount * 50)) + sinf(D3DX_PI * 0.25) * NAME_SIZE;

		pVtx[3].pos.y = g_Namepos.y + cosf(D3DX_PI * 0.25) * NAME_SIZE;

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

		pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_Name[nCount].nName % MAX_COLUMN), (1.0f / MAX_LINES) * (g_Name[nCount].nName / MAX_COLUMN));

		pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_Name[nCount].nName % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_Name[nCount].nName / MAX_COLUMN));

		pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_Name[nCount].nName % MAX_COLUMN), (1.0f / MAX_LINES) * (g_Name[nCount].nName / MAX_COLUMN) + (1.0f / MAX_LINES));

		pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_Name[nCount].nName % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_Name[nCount].nName / MAX_COLUMN) + (1.0f / MAX_LINES));
	}

	//頂点バッファをアンロックする

	g_pVtxBuffName->Unlock();
}
//==================================
//名前の終了処理 
//==================================
void UninitName(void)
{
	//頂点バッファの破棄

	if (g_pVtxBuffName != NULL)
	{
		g_pVtxBuffName->Release();

		g_pVtxBuffName = NULL;
	}
}
//==================================
//名前の更新処理 
//==================================
void UpdateName(void)
{
	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffName->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_NAME; nCount++, pVtx += 4)
	{

		//テクスチャ座標の設定

		pVtx[0].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_Name[nCount].nName % MAX_COLUMN), (1.0f / MAX_LINES) * (g_Name[nCount].nName / MAX_COLUMN));

		pVtx[1].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_Name[nCount].nName % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_Name[nCount].nName / MAX_COLUMN));

		pVtx[2].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * (g_Name[nCount].nName % MAX_COLUMN), (1.0f / MAX_LINES) * (g_Name[nCount].nName / MAX_COLUMN) + (1.0f / MAX_LINES));

		pVtx[3].tex = D3DXVECTOR2((1.0f / MAX_COLUMN) * ((g_Name[nCount].nName % MAX_COLUMN) + 1.0f), (1.0f / MAX_LINES) * (g_Name[nCount].nName / MAX_COLUMN) + (1.0f / MAX_LINES));
	}
	//頂点バッファをアンロックする

	g_pVtxBuffName->Unlock();
}
//==================================
//名前の描画処理 
//==================================
void DrawName(void)
{

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffName, 0, sizeof(VERTEX_2D));
	//頂点バッファのポインタ  頂点情報構造体のサイズ

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		//テクスチャの設定

		pDevice->SetTexture(0, g_apTextureAlphabetChart[g_Name[nCount].ntype]);

		//ポリゴンの描画
												  //描画する最初の頂点インデックス
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}

//==================================
//テキストカーソルの初期化処理 
//==================================
void InitTextCursor(void)
{
	//テキストカーソルの情報の初期化

	g_TextCursor.pos = g_Namepos;

	g_TextCursor.pos.x -= 25;

	g_TextCursor.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_TextCursor.nCounter = 0;

	//デバイスの取得

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	pDevice = GetDevice();

	//テクスチャの読み込み


		D3DXCreateTextureFromFile(pDevice,

			"Data/TEXTURE/SET/textcursor000.png", //テクスチャのファイル名

			&g_pTextureTextCursor);
	

	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ
											   //sizeof(VERTEX_2D)*必要な超点数
		D3DUSAGE_WRITEONLY,

		FVF_VERTEX_2D, //頂点フォーマット

		D3DPOOL_MANAGED,

		&g_pVtxBuffTextCursor,

		NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffTextCursor->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = g_TextCursor.pos.x + sinf(-D3DX_PI * 0.75f) * NAME_SIZE;

	pVtx[0].pos.y = g_TextCursor.pos.y + cosf(-D3DX_PI * 0.75f) * NAME_SIZE;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_TextCursor.pos.x + sinf(D3DX_PI * 0.75f) * NAME_SIZE;

	pVtx[1].pos.y = g_TextCursor.pos.y + cosf(D3DX_PI * 0.75f) * NAME_SIZE;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_TextCursor.pos.x + sinf(-D3DX_PI * 0.25) * NAME_SIZE;

	pVtx[2].pos.y = g_TextCursor.pos.y + cosf(-D3DX_PI * 0.25) * NAME_SIZE;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_TextCursor.pos.x + sinf(D3DX_PI * 0.25) * NAME_SIZE;

	pVtx[3].pos.y = g_TextCursor.pos.y + cosf(D3DX_PI * 0.25) * NAME_SIZE;

	pVtx[3].pos.z = 0.0f;

	//rhwの設定 1.0f固定

	pVtx[0].rhw = 1.0f;

	pVtx[1].rhw = 1.0f;

	pVtx[2].rhw = 1.0f;

	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定

	for (int nCount = 0; nCount < 4; nCount++)
	{
		pVtx[0].col = g_TextCursor.col;
	}

	//テクスチャ座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする

	g_pVtxBuffTextCursor->Unlock();
}

//==================================
//テキストカーソルの終了処理 
//==================================
void UninitTextCursor(void)
{
	//テクスチャの破棄

	if (g_pTextureTextCursor != NULL)
	{
		g_pTextureTextCursor->Release();

		g_pTextureTextCursor = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffTextCursor != NULL)
	{
		g_pVtxBuffTextCursor->Release();

		g_pVtxBuffTextCursor = NULL;
	}
}

//==================================
//テキストカーソルの更新処理 
//==================================
void UpdateTextCursor(void)
{
	//点滅

	g_TextCursor.nCounter++;

	if ((g_TextCursor.nCounter / 30) % 2 == 1) //消える
	{
		g_TextCursor.col.a = 0.0f;
	}
	else if ((g_TextCursor.nCounter / 30) % 2 == 0) //出てくる
	{
		g_TextCursor.col.a = 1.0f;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	g_pVtxBuffTextCursor->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = g_TextCursor.pos.x + (g_aNameCount * 50) + sinf(-D3DX_PI * 0.75f) * CURSOR_SIZE;

	pVtx[0].pos.y = g_TextCursor.pos.y + cosf(-D3DX_PI * 0.75f) * CURSOR_SIZE;

	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_TextCursor.pos.x + (g_aNameCount * 50) + sinf(D3DX_PI * 0.75f) * CURSOR_SIZE;

	pVtx[1].pos.y = g_TextCursor.pos.y + cosf(D3DX_PI * 0.75f) * CURSOR_SIZE;

	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_TextCursor.pos.x + (g_aNameCount * 50) + sinf(-D3DX_PI * 0.25) * CURSOR_SIZE;

	pVtx[2].pos.y = g_TextCursor.pos.y + cosf(-D3DX_PI * 0.25) * CURSOR_SIZE;

	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_TextCursor.pos.x + (g_aNameCount * 50) + sinf(D3DX_PI * 0.25) * CURSOR_SIZE;

	pVtx[3].pos.y = g_TextCursor.pos.y + cosf(D3DX_PI * 0.25) * CURSOR_SIZE;

	pVtx[3].pos.z = 0.0f;

	//頂点カラーの設定

	for (int nCount = 0; nCount < 4; nCount++)
	{
		pVtx[nCount].col = g_TextCursor.col;
	}

	//頂点バッファをアンロックする

	g_pVtxBuffTextCursor->Unlock();
}

//==================================
//テキストカーソルの描画処理 
//==================================
void DrawTextCursor(void)
{

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得

	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定

	pDevice->SetStreamSource(0, g_pVtxBuffTextCursor, 0, sizeof(VERTEX_2D));
	//頂点バッファのポインタ  頂点情報構造体のサイズ

	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);


	//テクスチャの設定

	pDevice->SetTexture(0, g_pTextureTextCursor);

	//ポリゴンの描画
											  //描画する最初の頂点インデックス
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==================================
//名前の獲得処理 
//==================================
Name GetName(int nCount)
{
	return g_Name[nCount];
}