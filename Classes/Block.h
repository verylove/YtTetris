#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Block :
	public cocos2d::CCSprite
{
public:
	Block(void);
	~Block(void);

	float _centerToSides;  //中心到边的距离
	float _centerToBottom;  //中心到底部的距离

	virtual bool init();

	CREATE_FUNC(Block);
};

