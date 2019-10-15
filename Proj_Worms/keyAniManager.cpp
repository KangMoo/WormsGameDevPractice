#include "stdafx.h"
#include "keyAniManager.h"
#include "image.h"
#include "animation.h"

keyAniManager::keyAniManager()
{
}


keyAniManager::~keyAniManager()
{

}

HRESULT keyAniManager::init()
{

	return S_OK;
}

void keyAniManager::release()
{
	deleteAll();
}

void keyAniManager::update() 
{
	iterAnimations iter = _mTotalAnimation.begin();

	for (iter; iter != _mTotalAnimation.end(); ++iter)
	{
		//애니메이션이 재생중이지 않으면 재생하지 않는다
		if (!iter->second->isPlay()) continue;

		iter->second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
	}
}

void keyAniManager::render() 
{

}


//디폴트 키 애니메이션
void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop)							  
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));

}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction)			  
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, void* obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}


//배열 키 애니메이션
void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop)								
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop);
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction)			
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}


//구간 키 애니메이션
void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps, bool reverse, bool loop)							   
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction)		   
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}


void keyAniManager::start(string animationKeyName) 
{
	iterAnimations iter = _mTotalAnimation.find(animationKeyName);
	iter->second->start();
}

void keyAniManager::stop(string animationKeyName)  
{
	iterAnimations iter = _mTotalAnimation.find(animationKeyName);
	iter->second->stop();
}

void keyAniManager::pause(string animationKeyName) 
{
	iterAnimations iter = _mTotalAnimation.find(animationKeyName);
	iter->second->pause();
}

void keyAniManager::resume(string animationKeyName)
{
	iterAnimations iter = _mTotalAnimation.find(animationKeyName);
	iter->second->resume();
}


animation* keyAniManager::findAnimation(string animationKeyName)
{
	iterAnimations iter = _mTotalAnimation.find(animationKeyName);

	if (iter != _mTotalAnimation.end())
	{
		return iter->second;
	}

	return NULL;
}


void keyAniManager::deleteAll()
{
	for (iterAnimations iter = _mTotalAnimation.begin(); iter != _mTotalAnimation.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mTotalAnimation.erase(iter);
		}
		else ++iter;
	}

	_mTotalAnimation.clear();
}
