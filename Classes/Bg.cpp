#include "Bg.h"
#include "Config.h"
#include "cocos2d.h"

USING_NS_CC;


Bg::Bg(void)
{
}


Bg::~Bg(void)
{
}

bool Bg::init()
{
	if(!CCLayerColor::init()){
		return false;
	}

	
	return true;
}

void Bg::draw()
{
	CCLayer::draw();

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	int x = visibleSize.width;
	int y = visibleSize.height;
	
	ccDrawColor4B(0,0,255,10);
	


	for(int i=0;i<ROWS;i++){
		ccDrawLine(ccp(0,(i+1)*blockHeight+BottomHeight),ccp(visibleSize.width,(i+1)*blockHeight+BottomHeight));
		y -=blockHeight;
	}

	for(int j=1;j<COLS;j++){
		ccDrawLine(ccp(j*blockHeight,visibleSize.height-(ROWS*blockHeight)),ccp(j*blockWidth,visibleSize.height));
		x -=blockWidth;
	}
		


}