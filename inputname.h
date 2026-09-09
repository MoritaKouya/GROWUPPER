//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _INPUTNAME_H_
#define _INPUTNAME_H_

#include "main.h"

//マクロ定義

//アルファベット表

#define MAX_COLUMN (8) //列数 

#define MAX_LINES (4) //行数

//名前

#define MAX_NAME (8) //名前の最大文字数

#define NAME_SPACE (30) //スペースとして扱う数値

#define NAME_NULL (31) //空白として扱う数値

//アルファベット表の列挙型定義

typedef enum
{
	ALPHABETCHART_0 = 0, //大文字

	ALPHABETCHART_1, //小文字

	ALPHABETCHART_MAX //最大数

}ALPHABETCHART;


//名前の構造体の定義

typedef struct
{
	int nName; //名前の番号

	int ntype; //名前のタイプ（0で大文字1で小文字）
}Name;

//プロトタイプ宣言

//全体の処理

//初期化

void InitInputName(void); 

//終了

void UninitInputName(void); 

 //更新

void UpdateInputName(void);

//描画

void DrawInputName(void);

//アルファベット表の処理

//初期化

void InitAlphabetChart(void); 

//終了

void UninitAlphabetChart(void); 

 //描画

void DrawAlphabetChart(void);

//カーソルの処理

//初期化

void InitInputCursor(void); 

//終了

void UninitInputCursor(void); 

//更新

void UpdateInputCursor(void);

void MoveInputCursor(void); //カーソルの移動入力処理

//描画

void DrawInputCursor(void);

//名前

//初期化

void InitName(void);

//終了

void UninitName(void);

//更新

void UpdateName(void);

//描画

void DrawName(void);

//テキストカーソル

//初期化

void InitTextCursor(void);

//終了

void UninitTextCursor(void);

//更新

void UpdateTextCursor(void);

//描画

void DrawTextCursor(void);

//名前の獲得

Name GetName(int nCount);

#endif
