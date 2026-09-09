//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _TITLEMENU_H_
#define _TITLEMENU_H_

#include "main.h"

//プロトタイプ宣言

void InitTitleMenu(void); //初期化

void UninitTitleMenu(void); //終了

void UpdateTitleMenu(void); //更新

void DrawTitleMenu(void); //描画

int GetTitleMenuSelect(void); //選んだメニューを獲得

#endif