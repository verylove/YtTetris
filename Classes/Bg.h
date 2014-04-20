#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Bg :
	public cocos2d::CCLayerColor
{
public:
	Bg(void);
	~Bg(void);
	void draw();
	virtual bool init();
	CREATE_FUNC(Bg);
};

