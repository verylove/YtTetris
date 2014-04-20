#ifndef __Config_H__
#define __Config_H__
#pragma once
#include "cocos2d.h"

USING_NS_CC;


int const  ROWS = 15;
int const  COLS = 12;

int const blockHeight = 40;
int const blockWidth = 40;

//BottomHeight = visibleSize.height-ROWS*blockHeight;

int const BottomHeight = 60;	//游戏距离底部的高度



typedef enum LayerOrder{
	LayerBg = 0,
	LayerTetris,
	LayerControl
};



class Config
{
public:
	Config(void);
	~Config(void);
};

#endif