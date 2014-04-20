#pragma once

#include "cocos2d.h"
#include "Config.h"

USING_NS_CC;

#define SCORE_LEVEL_INC 80//��������Ҫ�ķ���

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
	
	int score;//����
	int level;//��ʼ�ȼ��������ٶ�)
	int interval_unit;//�漶��������ʱ��������
	int interval_base;//ʱ��������
	int old_interval;//���浱ǰ��ʱ���������ڼ��ٲ���

	int cur_left,cur_top; //��¼���鵱ǰ��λ��
	int width_block,height_block;//����Ŀ�Ⱥ͸߶�

	bool isPause;//��ͣ��ʶ
	
	int curBlock[4][4];//��ǰ���ֵķ���
	//CCArray nexBlock[4][4];//��һ�γ��ֵķ���
	int allBgBlock[ROWS][COLS];//��������

	CCNode* blockNode;//��������
	CCNode* bgNode;

	CCNode* GetCurBlock(int x,int y,int type,int state);//��ȡ��ǰ����
	CCNode* GetBgBlock();//��ʾ�̶�����

	void DoDownShift();//����
	void DoLeftShift();//����
	void DoRightShift();//����
	void DoAccelerate();//����
	void DoRedirection();//�ı䷽��
	void ClearRow();//����
	bool IsTouchBottom();//�ж��Ƿ񵽵ײ�


	void reStartGame();
	void startGame();

	void menuControlRegameCallback(CCObject* pSender);

	void onTimerCallback(float fl);
	void update(float dt);
	void NextBlock();

	CREATE_FUNC(Tetris);

};

