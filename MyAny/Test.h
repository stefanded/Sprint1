#pragma once
#include"MyAny.h"

template<class T>
std::string processing_exception(const MyAny& an)
{
	try
	{
		return std::to_string(an.cast<T>());//bad
	}
	catch (std::runtime_error& d)
	{
		return d.what();
	}

}

void test(const MyAny& an)
{

	std::cout << processing_exception<short int>(an) << std::endl;;//bad
	std::cout << processing_exception<unsigned short int>(an)<<std::endl;//bad
	std::cout << processing_exception<int>(an) << std::endl;;//bad

	std::cout << processing_exception<unsigned int>(an) << std::endl;;//bad
	std::cout << processing_exception<unsigned long int>(an) << std::endl;;//bad
	std::cout << processing_exception<long long int>(an) << std::endl;//bad
	std::cout << processing_exception<long int>(an) << std::endl;//bad
	std::cout << processing_exception<unsigned long long int>(an) << std::endl;//bad
	
	std::cout << processing_exception<float>(an) << std::endl;//bad
	std::cout << processing_exception<double>(an) << std::endl;//bad
	std::cout << processing_exception<long double>(an) << std::endl;//bad
	
	std::cout << processing_exception<signed char>(an) << std::endl;//bad
	std::cout << processing_exception<unsigned char>(an) << std::endl;//bad
	std::cout << processing_exception<char>(an) << std::endl;//bad


}
template<class T>
void call_test(MyAny& any,T t) 
{
	std::cout << std::endl;
	any.operator=<T>(t);
	test(any);

}
void all_test(MyAny&any) 
{
	call_test<short int>(any,1);
	call_test<unsigned short int>(any, 2);
	call_test<int>(any, 3);
	call_test<unsigned int>(any, 4);
	call_test<unsigned long int>(any, 5);
	call_test<long long int>(any,6);
	call_test<long int>(any, 7);
	call_test<unsigned long long int>(any, 8);
	call_test<float>(any, 1.5);
	call_test<double>(any, 1.89012);
	call_test<long double>(any, 1.12343123);
	call_test<char>(any, 55);
	call_test<unsigned char>(any, 46);
	call_test<signed char>(any, -1);

}