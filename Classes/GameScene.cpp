#include "GameScene.h"
#include "Bg.h"
#include "Config.h"
#include "Tetris.h"

USING_NS_CC;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer,-1);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();





	//向左按钮
	CCMenuItemImage *pControlLeftItem = CCMenuItemImage::create(
		"left.png",
		"left-over.png",
		this,
		menu_selector(GameScene::menuControlLeftCallback));

	pControlLeftItem->setPosition(ccp(1*pControlLeftItem->getContentSize().width ,
		blockHeight));

	//向右按钮
	CCMenuItemImage *pControlRightItem = CCMenuItemImage::create(
		"right.png",
		"right-over.png",
		this,
		menu_selector(GameScene::menuControlRightCallback));

	pControlRightItem->setPosition(ccp(3*pControlRightItem->getContentSize().width ,
		blockHeight));

	//向下按钮
	CCMenuItemImage *pControlDownItem = CCMenuItemImage::create(
		"down.png",
		"down-over.png",
		this,
		menu_selector(GameScene::menuControlDownCallback));

	pControlDownItem->setPosition(ccp(5*pControlDownItem->getContentSize().width ,
		blockHeight));

	//旋转按钮
	CCMenuItemImage *pControlRotateItem = CCMenuItemImage::create(
		"rotate.png",
		"rotate-over.png",
		this,
		menu_selector(GameScene::menuControlRotateCallback));

	pControlRotateItem->setPosition(ccp(7*pControlRotateItem->getContentSize().width ,
		blockHeight));

	//关闭按钮
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(GameScene::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		blockHeight));


    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pControlLeftItem,pControlRightItem,pControlDownItem,pControlRotateItem,pCloseItem,NULL);
    pMenu->setPosition(ccp(0,30));
    this->addChild(pMenu, LayerControl,20);

  

	CCSprite* nTetris = Tetris::create();
	this->addChild(nTetris,LayerTetris,10);

	CCSprite* bg = CCSprite::create("bg.png");
	bg->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(bg,0);

	Bg* bgLayer = Bg::create();
	bgLayer->setOpacity(127);
	this->addChild(bgLayer,LayerBg);
	
    return true;
}

void GameScene::update(float dt)
{
	

}

void GameScene::draw()
{
	
}


void GameScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}



void GameScene::menuControlLeftCallback(CCObject* pSender)
{
	Tetris* pTeris = (Tetris*)this->getChildByTag(10);
	pTeris->DoLeftShift();

}

void GameScene::menuControlRightCallback(CCObject* pSender)
{
	Tetris* pTeris = (Tetris*)this->getChildByTag(10);
	pTeris->DoRightShift();
}

void GameScene:: menuControlDownCallback(CCObject* pSender)
{
	Tetris* pTeris = (Tetris*)this->getChildByTag(10);
	pTeris->DoDownShift();
	
}

void GameScene:: menuControlRotateCallback(CCObject* pSender)
{

}
