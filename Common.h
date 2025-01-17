﻿#pragma once
#include <iostream>
#include <limits>
#include <vector>
#include <map>
#include <queue>
#include <unordered_map>
#include <cstdio>
#include <string>
#include "math.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"

using namespace std;

// 共通の定数
static const int ScreenWidth            = 1980;                         // 画面の幅
static const int ScreenHeight           = 1080;                         // 画面の高さ
static const int ScreenColorBitNum      = 32;                           // 画面のカラービット数
static const int ScreenWidthHalf        = ScreenWidth / 2;              // 画面の幅の半分
static const int ScreenHeightHalf       = ScreenHeight / 2;             // 画面の高さの半分
const int        DebugFontColor         = GetColor(255, 255, 225);      // デバッグ時のフォントの色(白)
const int        DebugPolygonColorRed   = GetColor(200, 0, 0);          // デバッグ時のポリゴンの色(赤)
const int        DebugPolygonColorBlue  = GetColor(0, 0,200);           // デバッグ時のポリゴンの色(青)
static const int DebugSphereDivision    = 16;                           // デバッグ時のポリゴンの細かさ
