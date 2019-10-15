#include "singletonBase.h"
#include <time.h>

//====================================
// ## 17.08.07 ## randomFunction ##
//====================================

//                            singletonBase<T>
class randomFunction : public singletonBase < randomFunction >
{
public:

	randomFunction(void)
	{
		srand(GetTickCount());
	}
	~randomFunction(void) {}

	//0 ~ ������ ���� ���̿� ������ ���� �̴´�
	inline int getInt(int num) { return rand() % num; }
	//10 ~ 20 �̷� ������ Ư�� ���� �������� ������ ���� �̴´�.
	inline int getFromIntTo(int fromNum, int toNum) { return rand() % (toNum - fromNum + 1) + fromNum; }

	//�Ǽ��� ����
	inline float getFloat() { return (float)rand() / (float)RAND_MAX; }
	inline float getFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }
	inline float getFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toFloat - fromFloat) + fromFloat);
	}

};