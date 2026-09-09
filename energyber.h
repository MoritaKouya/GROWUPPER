//=============================
// 
//GROWUPPER_master版
// Author森田煌也
// 
//=============================
#ifndef _ENERGYBER_H_

#define _ENERGYBER_H_

#include "main.h"

//プロトタイプ

void InitEnergyBer(void); //初期化

void UninitEnergyBer(void); //終了

void UpdateEnergyBer(void); //更新

void DrawEnergyBer(void); //描画

void AddEnergyBer(int nCntEnergy, int nLevel); //加算

#endif