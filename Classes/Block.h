#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Block :
	public cocos2d::CCSprite
{
public:
	Block(void);
	~Block(void);

	float _centerToSides;  //���ĵ��ߵľ���
	float _centerToBottom;  //���ĵ��ײ��ľ���

	virtual bool init();

	CREATE_FUNC(Block);
};

