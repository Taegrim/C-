#include "stdafx.h"

// 가변길의 템플릿 - Fold Expression (C++ 17 이후)

template <typename... Ints>
int SumAll(Ints... nums)
{
	return (... + nums);	// Fold 형식
							// ((((1+4) + 2) + 3) + 10) 형태로 해석함
}

template <typename Int, typename... Ints>
int DiffFrom(Int Start, Ints... nums)
{
	return (Start - ... - nums);
}


// ,(콤마) 를 사용하면
// 각각의 인자에 원하는 식을 실행할 수 있음
class A {
public:
	void DoSomeThing(int x) const {
		std::cout << "Do Something With " << x << std::endl;
	}
};

template <typename T, typename... Ints>
void DoManyThings(const T& t, Ints... nums)
{
	(t.DoSomeThing(nums), ...);
}

int main()
{
	std::cout << SumAll(1, 4, 2, 3, 10) << std::endl;
	std::cout << DiffFrom(100, 1, 4, 2, 3, 10) << std::endl;

	A a;
	DoManyThings(a, 1, 2, 3, 4);
}