#pragma once

#include "cocos2d.h"
#include "Config.h"

USING_NS_CC;

#define SCORE_LEVEL_INC 80//升级所需要的分数

typedef enum BlockType
{
	block
};

class Tetris :
	public CCSprite
{
public:
	Tetris(void);
	~Tetris(void);
	virtual bool init();
	
	int score;//分数
	int level;//开始等级（下落速度)
	int interval_unit;//随级数递增的时间间隔增量
	int interval_base;//时间间隔基量
	int old_interval;//保存当前的时间间隔，用于加速操作

	int cur_left,cur_top; //记录方块当前的位置
	int width_block,height_block;//方块的宽度和高度

	bool isPause;//暂停标识
	
	int curBlock[4][4];//当前出现的方块
	//CCArray nexBlock[4][4];//下一次出现的方块
	int allBgBlock[ROWS][COLS];//背景数组

	CCNode* blockNode;//单个方块
	CCNode* bgNode;

	CCNode* GetCurBlock(int x,int y,int type,int state);//获取当前方块
	CCNode* GetBgBlock();//显示固定方块

	void DoDownShift();//下移
	void DoLeftShift();//左移
	void DoRightShift();//右移
	void DoAccelerate();//加速
	void DoRedirection();//改变方向
	void ClearRow();//消行
	bool IsTouchBottom();//判断是否到底部


	void reStartGame();
	void startGame();

	void menuControlRegameCallback(CCObject* pSender);

	void onTimerCallback(float fl);
	void update(float dt);
	void NextBlock();

	CREATE_FUNC(Tetris);

};

