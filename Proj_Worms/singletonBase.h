#pragma once

template <typename T>
class singletonBase
{
protected:
	static T* singleton;

	singletonBase(void) {};
	~singletonBase(void) {};

public:
	//�̱��� ������
	static T* getSingleton(void);
	//�̱��� ������
	void releaseSingleton(void);

};

//�̱��� �ʱ�ȭ
template<typename T>
T* singletonBase<T>::singleton = 0;

//������
template <typename T>
T* singletonBase<T>::getSingleton(void)
{
	//�̱����� ���ٸ� �Ҵ��ض�
	if (!singleton) singleton = new T;

	return singleton;
}

template <typename T>
void singletonBase<T>::releaseSingleton(void)
{
	if (singleton)
	{
		delete singleton;

		singleton = 0;
	}
}