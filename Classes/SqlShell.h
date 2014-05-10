//
//  SqlShell.h
//  MJ
//
//  Created by CN on 14-5-8.
//
//

#ifndef __MJ__SqlShell__
#define __MJ__SqlShell__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

#include "VisibleRect.h"
#include "GameManager.h"

using namespace extension;
using namespace ui;

class SqlShell : public Layer, public extension::EditBoxDelegate
{
public:
	virtual bool init();
	virtual void onEnter();
	
	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){
		
	};
	
    virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){
	
	};
	
    virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text){
	
	};
	
    virtual void editBoxReturn(cocos2d::extension::EditBox* editBox){};

	
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){
		return 1;
	};
	
    virtual void onTouchMoved(Touch *touch, Event *unused_event){
	
	};
	
    virtual void onTouchEnded(Touch *touch, Event *unused_event){
	
	};

	void onButtonClick(Ref* obj,ui::TouchEventType type){
		switch (type) {
			case TOUCH_EVENT_BEGAN:
				_displayValueLabel->setText(String::createWithFormat("Touch Down")->getCString());
				break;
				
			case TOUCH_EVENT_MOVED:
				_displayValueLabel->setText(String::createWithFormat("Touch Move")->getCString());
				break;
				
			case TOUCH_EVENT_ENDED:{
				
				std::ostringstream s;
				for(auto it : GameManager::sqlRecords)
				{
					s << it.first << "\t\t";
					for(auto it2 : it.second)s<<it2<<(it2.length()<3*6?"\t\t\t\t":it2.length()<3*8?"\t\t":"\t");
					s << "\n";
				}
				
				_displayValueLabel->setText(s.str().c_str());
				break;}
				
			case TOUCH_EVENT_CANCELED:
				_displayValueLabel->setText(String::createWithFormat("Touch Cancelled")->getCString());
				break;
				
			default:
				break;
		}
	};
	
	void onMenuClick(Ref *obj);
	
    CREATE_FUNC(SqlShell);
	
private:
	EditBox* _edit;
	Text* _displayValueLabel;
};

#endif /* defined(__MJ__SqlShell__) */
