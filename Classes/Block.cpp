#include "Block.h"
#include "cocos2d.h"
#include "Config.h"

USING_NS_CC;

Block::Block(void)
{
}


Block::~Block(void)
{
}

bool Block::init()
{
	if(!CCSprite::init()){
		return false;
	}

	CCTexture2D* blockTex  = CCTextureCache::sharedTextureCache()->addImage("block.png");	
	CCRect blockRect = CCRect(0.0f,0.0f,(float)blockWidth,(float)blockHeight);

	

	if(!CCSprite::initWithTexture(blockTex,blockRect)){
		return false;
	}
	
	this->_centerToSides = 20;
	this->_centerToBottom = 20;

	return true;
}
