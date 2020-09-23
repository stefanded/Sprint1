#include<string>
#include<vector>
#include<algorithm>
#include<iostream>
#include <type_traits>

#include<list>
#include<any>
#include<memory>
#include"Test.h"
int main()
{
	
	
	MyAny f{ 5 };
	MyAny f2{f};
	MyAny f3;
	f3 = f;

	all_test(f);
	
}