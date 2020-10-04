// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "pch.h"
#include<my_preprocessing_project/MyAny.h>
TEST(TestAny, TestDefaultConstruct) {
	MyAny Any;
  EXPECT_EQ(Any.type(),typeid(void));
  EXPECT_FALSE(Any.has_value());
}
TEST(TestAny, TestConstructParam) {
	MyAny Any(1);
	EXPECT_EQ(Any.type(), typeid(int));
	EXPECT_TRUE(Any.has_value());
	EXPECT_EQ(Any.cast<int>(),1);
}
TEST(TestAny, TestCopyConstruct) 
{
	MyAny Any(1);
	MyAny copy_Any(Any);
	EXPECT_EQ(copy_Any.type(), typeid(int));
	EXPECT_TRUE(copy_Any.has_value());
	EXPECT_EQ(copy_Any.cast<int>(), 1);
}
TEST(TestAny, TestOperatorEqualType)
{
	MyAny Any(1.4567);
	EXPECT_EQ(Any.type(), typeid(double));
	EXPECT_TRUE(Any.has_value());
	EXPECT_EQ(Any.cast<double>(), 1.4567);
	Any = 0;

	EXPECT_EQ(Any.type(), typeid(int));
	EXPECT_TRUE(Any.has_value());
	EXPECT_EQ(Any.cast<int>(), 0);
}
TEST(TestAny, TestMethodReset)
{
	MyAny Any(1);
	MyAny copy_Any(Any);

	EXPECT_EQ(copy_Any.type(), typeid(int));
	EXPECT_TRUE(copy_Any.has_value());
	EXPECT_EQ(copy_Any.cast<int>(), 1);
	Any.reset();

	EXPECT_EQ(Any.type(), typeid(void));
	EXPECT_FALSE(Any.has_value());
}
TEST(TestAny, TestMethodSwap)
{
	MyAny any(1);
	MyAny any2(1.5465);
	any.swap(any2);

	EXPECT_EQ(any2.type(), typeid(int));
	EXPECT_TRUE(any2.has_value());
	EXPECT_EQ(any2.cast<int>(), 1);

	EXPECT_EQ(any.type(), typeid(double));
	EXPECT_TRUE(any.has_value());
	EXPECT_EQ(any.cast<double>(), 1.5465);
}
TEST(TestAny, TestOperatorEqualAny)
{
	MyAny any(1.4567);
	MyAny any2(1);
	any2 = any;
	EXPECT_EQ(any2.type(), typeid(double));
	EXPECT_TRUE(any2.has_value());
	EXPECT_EQ(any2.cast<double>(), 1.4567);
}
TEST(TestAnyCast, TestCastInt)
{
	MyAny any(5);
	EXPECT_FALSE(TestCast<unsigned short int>(any))<<std::endl;//bad
	EXPECT_TRUE(TestCast<int>(any)) << std::endl;;//bad

	EXPECT_FALSE(TestCast<unsigned int>(any));;//bad
	EXPECT_FALSE(TestCast<unsigned long int>(any));;//bad
	EXPECT_FALSE(TestCast<long long int>(any));//bad
	EXPECT_FALSE(TestCast<long int>(any));//bad
	EXPECT_FALSE(TestCast<unsigned long long int>(any));//bad
	
	EXPECT_FALSE(TestCast<float>(any));//bad
	EXPECT_FALSE(TestCast<double>(any));//bad
	EXPECT_FALSE(TestCast<long double>(any));//bad
	
	EXPECT_FALSE(TestCast<signed char>(any));//bad
	EXPECT_FALSE(TestCast<unsigned char>(any));//bad
	EXPECT_FALSE(TestCast<char>(any));//bad

	
}
