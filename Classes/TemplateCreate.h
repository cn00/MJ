#pragma once
#include "stdafx.h"

#define createScene( _T_ )					\
static Scene* scene()						\
{											\
	Scene * scene = NULL;					\
	do{										\
		scene = Scene::create();			\
		CC_BREAK_IF(! scene);				\
		_T_ *layer = _T_::create();			\
		CC_BREAK_IF(! layer);				\
		scene->addChild(layer);				\
	} while (0);							\
	return scene;							\
}

#define addNode(parent, cType, child)		\
{											\
	child = cType::create();				\
	CC_BREAK_IF(! child);					\
	parent->addChild(child);				\
}

#define addNodeP(parent, cType, child, position)		\
{														\
	addNode(parent, cType, child)						\
	child->setPosition(position);						\
}

#define addNodeT(parent, cType, child, tag)				\
{														\
	addNode(parent, cType, child)						\
	child->setTag(tag);									\
}

#define addNodeZ(parent, cType, child, zOrder)			\
{														\
	addNode(parent, cType, child)						\
	child->setZOrder(zOrder);							\
}

#define addNodePT(parent, cType, child, position, tag)		\
{															\
	addNodeP(parent, cType, child, position)				\
	child->setTag(tag);										\
}

#define addNodePZ(parent, cType, child, position, zOrder)	\
{															\
	addNodeP(parent, cType, child, position)				\
	child->setZOrder(zOrder);								\
}

#define addNodeTZ(parent, cType, child, tag, zOrder)		\
{															\
	addNodeT(parent, cType, child, tag)						\
	child->setZOrder(zOrder);								\
}

#define addNodePTZ(parent, cType, child, position, tag, zOrder)	\
{																\
	addNodePT(parent, cType, child, position, tag)				\
	child->setZOrder(zOrder);									\
}

class TpCreate:public VisibleRect
{
public:
	static std::string toString( int i )
	{
		char c[12];
		sprintf(c, "%d", i);
		return string(c);
	}
	static std::string toString( float f )
	{
		char c[12];
		sprintf(c, "%f", f);
		return string(c);
	}
	template< typename T > T* create( Point position = Point::ZERO , Point anchor = Point::ZERO );

	template< typename T > T* frameMenu(const char *normal, const char *over, Ref* target, SEL_MenuHandler selector,
										Point position = Point::ZERO, int tag = -1);
	template< typename T > T* frameMenu(const char *normal, const char *over, const char *disable, Ref* target, SEL_MenuHandler selector,
		Point position = Point::ZERO, int tag = -1);

	template< typename T > T* frameSprite( const char *frameName, Point position = Point::ZERO, Point anchor = Point::ZERO );
	template< typename T > T* fileSprite( const char *fileName, Point position = Point::ZERO, Point anchor = Point::ZERO );
};

template< typename T >
T* TpCreate::create( Point position, Point anchor )
{
	T *p = T::create();
	p->setAnchorPoint(anchor);
	p->setPosition(position);
	return p;
}

template< typename T >
T* TpCreate::frameMenu( const char *normal, const char *over, Ref* target, SEL_MenuHandler selector,
					   Point position, int tag )
{
	return frameMenu<T>( normal, over, over, target, selector, position, tag );
}

template< typename T >
T* TpCreate::frameMenu( const char *normal, const char *over, const char *disable, Ref* target, SEL_MenuHandler selector,
					   Point position, int tag )
{
	T* p = T::create(
		frameSprite<Sprite>(normal,Point::ZERO,Point::ZERO),
		frameSprite<Sprite>(over	,Point::ZERO,Point::ZERO),
		frameSprite<Sprite>(disable,Point::ZERO,Point::ZERO),
		target, selector );
	p->setTag(tag);
	p->setPosition(position);
	return p;
}

template< typename T >
T* TpCreate::fileSprite( const char *fileName, Point position, Point anchor )
{
	T *p = T::create(fileName);
	p->setAnchorPoint(anchor);
	p->setPosition(position);
	return p;
}

template< typename T >
T* TpCreate::frameSprite( const char *frameName, Point position, Point anchor)
{
	T *p = T::createWithSpriteFrameName(frameName);
	p->setPosition(position);
	p->setAnchorPoint(anchor);
	return p;
}
