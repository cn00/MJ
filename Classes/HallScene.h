//
//  HallScene.h
//  HeroMJ
//
//  Created by CN on 14-5-13.
//
//

#ifndef __HeroMJ__HallScene__
#define __HeroMJ__HallScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

#include "Card.h"
#include "TemplateCreate.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class HallScene : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
	virtual bool init(){
		if(!Layer::init())return false;
		bool ret = false;
		do{
			Size winSize = Director::getInstance()->getWinSize();

			auto tableView = TableView::create(this, Size(60, 250));
			tableView->setDirection(extension::ScrollView::Direction::VERTICAL);
			tableView->setPosition(Point(150,winSize.height/2-120));
			tableView->setDelegate(this);
			tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
			this->addChild(tableView);
			tableView->reloadData();
			ret = true;
		}while(0);
		return ret;
	}
	
	virtual void scrollViewDidScroll(extension::ScrollView* view) {
	
	}
	
    virtual void scrollViewDidZoom(extension::ScrollView* view) {
	
	}
	
    virtual void tableCellTouched(TableView* table, TableViewCell* cell){
	
	}
	
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx){
		TableViewCell *cell = table->dequeueCell();
		const string cardpk[] = {
			"🂠",
			"🂡", "🂢", "🂣", "🂤", "🂥", "🂦", "🂧", "🂨", "🂩", "🂪", "🂫", "🂬", "🂭", "🂮",
			"🂱", "🂲", "🂳", "🂴", "🂵", "🂶", "🂷", "🂸", "🂹", "🂺", "🂻", "🂼", "🂽", "🂾",
			"🃁", "🃂", "🃃", "🃄", "🃅", "🃆", "🃇", "🃈", "🃉", "🃊", "🃋", "🃌", "🃍", "🃎", "🃏",
			"🃑", "🃒", "🃓", "🃔", "🃕", "🃖", "🃗", "🃘", "🃙", "🃚", "🃛", "🃜", "🃝", "🃞", "🃟"
		};

		if (!cell) {
			cell = new TableViewCell();
			cell->autorelease();
			Card* card = Card::create(cardpk[rand()%(sizeof(cardpk)/sizeof(cardpk[0]))]);
			cell->addChild(card);
			
			auto label = Label::create("daf", "Helvetica", 20.0);
			label->setPosition(Point::ZERO);
			label->setAnchorPoint(Point::ZERO);
			cell->addChild(label);
		}
		else
		{
			cell->removeAllChildren();
//			Card* card = Card::create(cardpk[rand()%(sizeof(cardpk)/sizeof(cardpk[0]))]);
//			cell->addChild(card);
			auto label = Label::create(cardpk[rand()%(sizeof(cardpk)/sizeof(cardpk[0]))], "Helvetica", 20.0);
			label->setPosition(Point::ZERO);
			label->setAnchorPoint(Point::ZERO);
			cell->addChild(label);

		}
		return cell;
	}
	
    virtual ssize_t numberOfCellsInTableView(TableView *table){
		return 15;
	}
	
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx) {
        return cellSizeForTable(table);
    }

    virtual Size cellSizeForTable(TableView *table) {
        return Size(100,50);
    }

    createScene(HallScene);
	CREATE_FUNC(HallScene);
private:
	
};
#endif /* defined(__HeroMJ__HallScene__) */
