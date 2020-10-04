// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <typeindex>
#include <sstream>
#include <exception>
#include <algorithm>

class MyAny
{
	void* data_ = nullptr;
	size_t size_type_ = 0;
	std::type_index type_ = std::type_index(typeid(void));
public:

	MyAny()noexcept = default;

	template<class T>
	MyAny(T value);

	MyAny(const MyAny& any);

	template<class T>
	MyAny& operator =(T value)noexcept;

	MyAny& operator =(const MyAny& any)noexcept;

	bool has_value() const noexcept;

	const std::type_index& type()const noexcept;

	void reset() noexcept;

	void swap(MyAny& rhs);

	template<class T>
	T get_value()const;

	~MyAny();
};

template<class T>
MyAny::MyAny(T value) : size_type_(sizeof(T)), type_(std::type_index(typeid(T)))
{
	static_assert(std::is_fundamental<T>::value && !std::is_void<T>::value && !std::is_null_pointer<T>::value, "error type");
	T* temp_data = static_cast<T*>(std::calloc(1, size_type_));
	if (!temp_data)
	{
		throw std::bad_alloc{};
	}
	*temp_data = value;
	data_ = temp_data;
}

template<class T>
MyAny& MyAny::operator=(T value) noexcept
{
	static_assert(std::is_fundamental<T>::value && !std::is_void<T>::value && !std::is_null_pointer<T>::value, "error type");
	reset();
	swap(MyAny{ value });
	return *this;

}

template<class T>
T MyAny::get_value() const
{
	static_assert(std::is_fundamental<T>::value && !std::is_void<T>::value && !std::is_null_pointer<T>::value, "error type");

	if (std::type_index temp_type = std::type_index(typeid(T)); temp_type == type_)
	{
		return *static_cast<T*>(data_);
	}
	else
	{

		std::string msg{ std::string{"bad cast " } + type_.name() + std::string{"!="} + temp_type.name() };
		throw std::runtime_error(msg.c_str());
	}
}

MyAny::MyAny(const MyAny& any)
{

	data_ = std::calloc(1, any.size_type_);
	if (!data_)
	{
		throw std::bad_alloc{};
	}
	std::memcpy(data_, any.data_, any.size_type_);

	type_ = any.type_;
	size_type_ = any.size_type_;

}

MyAny& MyAny::operator=(const MyAny& any) noexcept
{
	if (&any != this) {
		this->reset();
		MyAny temp{ any };
		this->swap(temp);
	}
	return *this;
}

bool MyAny::has_value() const noexcept
{
	return data_ ? true : false;
}

const std::type_index& MyAny::type() const noexcept
{
	return type_;
}

void MyAny::reset() noexcept
{
	std::free(data_);
	type_ = std::type_index(typeid(void));;
	data_ = nullptr;
	size_type_ = 0;
}

void MyAny::swap(MyAny& rhs)
{
	std::swap(data_, rhs.data_);
	std::swap(type_, rhs.type_);
	std::swap(size_type_, rhs.size_type_);

}

MyAny::~MyAny()
{
	reset();
}
