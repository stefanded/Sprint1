#pragma once
#include <typeinfo>
#include <typeindex>
#include <sstream>

class MyAny
{
	void* data_ = nullptr;
	size_t size_type_ = 0;
	std::type_index type_ = std::type_index(typeid(void));
public:
	
	MyAny()noexcept = default;
	
	template<class T>
	MyAny(T value) noexcept :data_(new T(value)),size_type_(sizeof(T*)), type_(std::type_index(typeid(T))) {}
	
	MyAny(const MyAny& any) 
	{
		if (&any != this) {

			data_ = std::malloc(any.size_type_);
			std::memcpy(data_, any.data_, any.size_type_);

			type_ = any.type_;
			size_type_ = any.size_type_;
		}
	}

	template<class T>
	MyAny& operator =(T value)noexcept
	{
		delete data_;
		data_ = new T(value);
		type_ = std::type_index(typeid(T));
		return *this;
	
	}
	MyAny& operator =(const MyAny& any)noexcept
	{
		if (&any != this) {
			this->reset();
			
			MyAny temp{ any };
			swap(temp);
		}
		return *this;
	}
	bool has_value() const noexcept
	{
		return data_ ? true : false;
	}
	const std::type_index& type()const noexcept
	{
		return type_;
	}
	void reset() noexcept
	{
		delete data_;
		type_ = std::type_index(typeid(void));;
		data_ = nullptr;
		size_type_ = 0;
	}

	void swap(MyAny& rhs)
	{
		std::swap(data_, rhs.data_);
		std::swap(type_, rhs.type_);

	}
	template<class T>
	const T& cast()const 
	{

		if (auto temp_type = std::type_index(typeid(T)); temp_type == type_)
		{
			return *static_cast<T*>(data_);
		}
		else 
		{
			
			std::ostringstream msg;
			msg << "bad cast " << type_.name() << "!=" << temp_type.name();
			throw std::runtime_error(msg.str().c_str());
		}
	}
	~MyAny()
	{
		reset();
	}
};
