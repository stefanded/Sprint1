#pragma once
#include <typeindex>
#include <sstream>
#include <exception>
#include <algorithm>

#include <memory>

class MyAny
{
	//void* ptr = nullptr;
	size_t size_=0;
	std::shared_ptr<void> data_;
	std::type_index type_ = std::type_index(typeid(void));
public:

	MyAny()noexcept = default;

	template<class T>
	MyAny(T value);

	MyAny(const MyAny& any);

	template<class T>
	MyAny& operator =(T value);

	MyAny& operator =(const MyAny& any)noexcept;

	bool has_value() const noexcept;

	const std::type_index& type()const noexcept;

	void reset() noexcept;

	void swap(MyAny& rhs);

	template<class T>
	T get_value()const;

};

template<class T>
MyAny::MyAny(T value) : data_(std::calloc(1,sizeof(T)),std::free), type_(std::type_index(typeid(T))),size_(sizeof(value))
{
	*static_cast<T*>(data_.get()) = value;
	static_assert(std::is_fundamental<T>::value && !std::is_void<T>::value && !std::is_null_pointer<T>::value, "error type");
}

template<class T>
MyAny& MyAny::operator=(T value) 
{
	static_assert(std::is_fundamental<T>::value && !std::is_void<T>::value && !std::is_null_pointer<T>::value, "error type");
	MyAny temp{ value };
	swap(temp);
	return *this;

}

template<class T>
T MyAny::get_value() const
{
	static_assert(std::is_fundamental<T>::value && !std::is_void<T>::value && !std::is_null_pointer<T>::value, "error type");

	if (std::type_index temp_type = std::type_index(typeid(T)); temp_type == type_)
	{
		return *static_cast<T*>(data_.get());
	}
	else
	{
		std::string msg{ std::string{"bad cast " } + type_.name() + std::string{"!="} + temp_type.name() };
		throw std::runtime_error(msg.c_str());
	}
}

MyAny::MyAny(const MyAny& any) :type_(any.type_), size_(any.size_)
{
	
	data_.reset(std::calloc(1, size_),std::free);
	std::memcpy(data_.get(), any.data_.get(), size_);
}

MyAny& MyAny::operator=(const MyAny& any) noexcept
{
	if (&any != this) {
		MyAny temp{any};
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
	data_.reset();
	type_ = std::type_index(typeid(void));;
	size_ = 0;
}

void MyAny::swap(MyAny& rhs)
{
	std::swap(data_, rhs.data_);
	std::swap(type_, rhs.type_);
	std::swap(size_, rhs.size_);

}
