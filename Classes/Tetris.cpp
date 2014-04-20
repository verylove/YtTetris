#include "Tetris.h"
#include "Block.h"


Tetris::Tetris(void)
{
		
	
}


Tetris::~Tetris(void)
{

}

void Tetris::reStartGame()
{
	
	this->removeChildByTag(50);
	//CCMenuItemFont* pMenuItemFont = (CCMenuItemFont*)pMenu->getChildByTag(50);

	this->score=0;
	this->level=0;
	this->interval_unit=25;
	this->interval_base=300;
	this->old_interval=0;

	this->cur_left=0;
	this->cur_top=0;

	this->width_block=0;
	this->height_block=0;

	this->isPause=false;


	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			this->curBlock[i][j]=0;
		}
	}

	for(int x=0;x<ROWS;x++){
		for(int y=0;y<COLS;y++){
			this->allBgBlock[x][y]=0;
		}
	}
	this->NextBlock();
	this->schedule(schedule_selector(Tetris::onTimerCallback),1.0);
	
}


void Tetris::startGame()
{

	this->score=0;
	this->level=0;
	this->interval_unit=25;
	this->interval_base=300;
	this->old_interval=0;

	this->cur_left=0;
	this->cur_top=0;

	this->width_block=0;
	this->height_block=0;

	this->isPause=false;


	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			this->curBlock[i][j]=0;
		}
	}

	for(int x=0;x<ROWS;x++){
		for(int y=0;y<COLS;y++){
			this->allBgBlock[x][y]=0;
		}
	}


	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


	int type,state;
	srand(time(NULL));
	type =rand()%7;
	state = 0;//rand()%4;
	this->blockNode =  GetCurBlock(0,0,type,state);
	this->blockNode->setRotation(90);
	this->addChild(this->blockNode,0,10);


	this->bgNode =  this->GetBgBlock();
	this->bgNode->setPosition(ccp(0,visibleSize.height));
	this->bgNode->setRotation(90);
	this->addChild(this->bgNode,0,20);


	this->scheduleUpdate();
	this->schedule(schedule_selector(Tetris::onTimerCallback),1.0);
}



bool Tetris::init()
{
	if(!CCSprite::init()){
		return false;
	}
	
	this->startGame();
	


	return true;
}

void Tetris::update(float dt)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	int x = this->cur_left*blockWidth;
	int y = visibleSize.height-this->cur_top*blockHeight;
	this->blockNode->setPosition(ccp(x,y));	



}

void Tetris::DoDownShift()
{
	if(this->IsTouchBottom()){
		//消除行
		this->ClearRow();
		this->NextBlock();
	}
	this->cur_top++;
}

void Tetris::DoLeftShift(){
	if(0==this->cur_left)return;
	if(this->cur_top<0)return;//方块还没有显示全
	
	if(this->allBgBlock[this->cur_top][this->cur_left-1]==1)
		return;	

	for(int y=0;y<this->height_block;y++){//从最左边开始查询
		for(int x=0;x<this->width_block;x++){
			if(this->curBlock[x][y]==1){
				if(this->allBgBlock[this->cur_top+y][this->cur_left+x-1]==1){
					return;					
				}
				break;
			}
		}
	}


	this->cur_left--;
}

void Tetris::DoRightShift(){
	if(COLS-1==(this->cur_left+this->width_block))return;
	if(this->cur_top<0)return;//方块还没有显示全
	
	if(this->allBgBlock[this->cur_top][this->cur_left+1]==1)
		return;			

	for(int y=0;y<this->height_block;y++){//从最右边开始查询
		for(int x=3;x>=0;x--){
			if(this->curBlock[x][y]==1){
				if(this->allBgBlock[this->cur_top+y][this->cur_left+x+1]==1){
					return;					
				}
				break;
			}
		}
	}

	this->cur_left++;
}


void Tetris::ClearRow()
{
	int x,y,k;
	int count = 0;
	bool isFilled;


	for(x=ROWS-1;x>=0;x--){
		isFilled=true;
		for(y=COLS-1;y>=0;y--){
			if(this->allBgBlock[x][y]==0){
				isFilled=false;
				break;
			}
		}

		if(isFilled){
			//清空满行
			for(y=0;y<COLS;y++){
				this->allBgBlock[x][y]=0;
			}

			//所有方块往下移
			for(k=x-1;k>=0;k--){
				for(y=0;y<COLS;y++){
					this->allBgBlock[k+1][y] = this->allBgBlock[k][y];
				}
			}
			x=x+1;
			count++;
		}

	}

}


bool Tetris::IsTouchBottom()
{
	CCLog("cur_top:%d,cur_left:%d",this->cur_top,this->cur_left);
	if(ROWS==(this->cur_top+this->height_block)){
		//固定方块
		
		for(int x=0;x<this->height_block;x++){
			for(int y=0;y<this->width_block;y++){				
				if(this->curBlock[x][y]==1){
					//CCLog("%d,%d",this->cur_top,this->cur_left+i);
					if(this->cur_left<0){
						this->allBgBlock[this->cur_top+x][this->cur_left+y] = 1;			
					}
					else
					{
						this->allBgBlock[this->cur_top+x][this->cur_left+y] = 1;			
					}
				}
				
			}
		}
		return true;
	}
	
	//判断游戏结束
	for(int t=0;t<COLS;t++){
		if(this->allBgBlock[0][t]==1){
			CCMessageBox("Game End","Message");
			this->unschedule(schedule_selector(Tetris::onTimerCallback));

			CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		
			CCMenuItemFont *reGameItemFont = CCMenuItemFont::create("ReStart",this,menu_selector(Tetris::menuControlRegameCallback));
			CCMenu* pMenu = CCMenu::create(reGameItemFont,NULL);
			pMenu->setPosition(visibleSize.width/2,visibleSize.height/2);
			this->addChild(pMenu,999,50);
			return true;
		}
	}


	for(int yy=this->height_block-1;yy>=0;yy--){
		//判断第一个实心方块在背景上临接的下方方格是否为实心，是就代表已经到底部
		for(int xx=0;xx<this->width_block;xx++){
			if(this->cur_top+yy<0)return false;

			if(this->allBgBlock[this->cur_top+xx+1][this->cur_left+yy]==1){
				if(this->curBlock[xx][yy]==1){				
					//固定方块
					for(int x=3;x>=0;x--){
						for(int y=0;y<4;y++){				
							if(this->curBlock[x][y]==1){
								//CCLog("%d,%d",this->cur_top,this->cur_left+i);
								if(this->cur_left<0){
									this->allBgBlock[this->cur_top+x][this->cur_left+y] = 1;			
								}
								else
								{
									this->allBgBlock[this->cur_top+x][this->cur_left+y] = 1;			
								}
							}

						}
					}
					return true;
				}
			}
			
		}
	}

	return false;
}

void Tetris::onTimerCallback(float fl)
{
	DoDownShift();

}


void Tetris::menuControlRegameCallback(CCObject* pSender)
{

	this->reStartGame();
}



void Tetris::NextBlock()
{	
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	this->removeChildByTag(20,false);	

	this->bgNode =  this->GetBgBlock();
	this->bgNode->setPosition(ccp(0,visibleSize.height));
	this->bgNode->setRotation(90);
	this->addChild(this->bgNode,0,20);

	this->removeChildByTag(10,false);
	int type,state;
	srand(time(NULL));
	type = rand()%7;
	state = 0;//rand()%4;
	this->blockNode =  this->GetCurBlock(0,0,type,state);
	this->blockNode->setRotation(90);
	this->addChild(this->blockNode,0,10);
}

CCNode*  Tetris::GetBgBlock()
{

	CCNode* blocks  = CCNode::create();	
	for(int x=0;x<ROWS;x++){
			for(int y=0;y<COLS;y++){
			if(this->allBgBlock[x][y]==1){
				Block* block = Block::create();
				block->setOpacity(255);
				block->setPosition(ccp(x*blockWidth+block->_centerToSides,y*blockHeight+block->_centerToBottom));
				blocks->addChild(block);
			}

		}
	}


	for(int i=0;i<ROWS;i++){
		for(int j=0;j<COLS;j++){

			CCString* str = CCString::createWithFormat("%d,%d",i,j);

			CCLabelTTF* pLabel = CCLabelTTF::create(str->getCString(), "Arial", 12);  
			pLabel->setPosition(ccp(i*blockWidth+20,j*blockHeight+20));
			pLabel->setRotation(270);
			blocks->addChild(pLabel,5);
		}
	}

	return blocks;
}

CCNode*  Tetris::GetCurBlock(int x,int y,int type,int state)
{
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			this->curBlock[i][j]=0;
		}
	}


	CCNode* blocks  = CCNode::create();//= CCSpriteBatchNode::create("block.png");	
	
	blocks->removeAllChildrenWithCleanup(true);

	CCLog("Type:%d",type);
	switch(type){
		case 0://竖线

			if(state==0 || state==2){
				this->curBlock[0][1]=1;
				this->curBlock[1][0]=1;
				this->curBlock[2][0]=1;
				this->curBlock[3][0]=1;

				this->width_block=1;
				this->height_block=4;

			}else{
				
			}
			this->cur_top = 0-this->height_block;
			this->cur_left = (COLS-1-this->width_block)/2;
			
			break;
		case 1://T形
			if(state==0){
				this->curBlock[0][0]=1;
				this->curBlock[0][1]=1;
				this->curBlock[0][2]=1;
				this->curBlock[1][1]=1;

				this->width_block=3;
				this->height_block=2;
			}else if(state==1){

			}else if(state==2){

			}else if(state==3){

			}
			this->cur_top = 0-this->height_block;
			this->cur_left = (COLS-1-this->width_block)/2;
			break;
		case 2://Z型
			if(state==0){
				this->curBlock[0][0]=1;
				this->curBlock[0][1]=1;
				this->curBlock[1][1]=1;
				this->curBlock[1][2]=1;

				this->width_block=3;
				this->height_block=2;

			}else if(state==1){

			}else if(state==2){

			}else if(state==3){

			}
			this->cur_top = 0-this->height_block;
			this->cur_left = (COLS-1-this->width_block)/2;
			break;
		case 3://反Z
			if(state==0){
				this->curBlock[0][1]=1;
				this->curBlock[0][2]=1;
				this->curBlock[1][0]=1;
				this->curBlock[1][1]=1;

				this->width_block=3;
				this->height_block=2;

			}else if(state==1){

			}else if(state==2){

			}else if(state==3){

			}
			this->cur_top = 0-this->height_block;
			this->cur_left = (COLS-1-this->width_block)/2;
			break;
		case 4://L型
			if(state==0){
				this->curBlock[0][1]=1;
				this->curBlock[1][0]=1;
				this->curBlock[2][0]=1;
				this->curBlock[2][1]=1;

				this->width_block=2;
				this->height_block=3;

			}else if(state==1){

			}else if(state==2){

			}else if(state==3){

			}
			this->cur_top = 0-this->height_block;
			this->cur_left = (COLS-1-this->width_block)/2;
			break;
		case 5://反L
			if(state==0){
				this->curBlock[0][1]=1;
				this->curBlock[1][1]=1;
				this->curBlock[2][0]=1;
				this->curBlock[2][1]=1;

				this->width_block=2;
				this->height_block=3;

			}else if(state==1){

			}else if(state==2){

			}else if(state==3){

			}
			this->cur_top = 0-this->height_block;
			this->cur_left = (COLS-1-this->width_block)/2;
			break;
		case 6://石头
			if(state==0){
				this->curBlock[0][0]=1;
				this->curBlock[0][1]=1;
				this->curBlock[1][0]=1;
				this->curBlock[1][1]=1;

				this->width_block=2;
				this->height_block=2;

			}else if(state==1){

			}else if(state==2){

			}else if(state==3){

			}
			this->cur_top = 0-this->height_block;
			this->cur_left = (COLS-1-this->width_block)/2;

			break;
	}


	for(int x=0;x<4;x++){
		for(int y=0;y<4;y++){
			if(this->curBlock[x][y]==1){
				Block* block = Block::create();

				CCString* str = CCString::createWithFormat("%d,%d",x,y);

				CCLabelTTF* pLabel = CCLabelTTF::create(str->getCString(), "Arial", 12);
				pLabel->setPosition(ccp(x*blockWidth+block->_centerToSides,y*blockHeight+block->_centerToBottom));
				

				block->setPosition(ccp(x*blockWidth+block->_centerToSides,y*blockHeight+block->_centerToBottom));
				blocks->addChild(block);
				blocks->addChild(pLabel);
				
			}
			
		}
	}

	

	return blocks;
}