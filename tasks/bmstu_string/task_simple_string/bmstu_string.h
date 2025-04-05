// Copyright 2025 Samoylov Daniil
#pragma once

#include <exception>
#include <iostream>

namespace bmstu
{

template <typename T>
class basic_string;

using string = basic_string<char>;
using wstring = basic_string<wchar_t>;
using u16string = basic_string<char16_t>;
using u32string = basic_string<char32_t>;

template <typename T>
class basic_string
{
   public:
	basic_string()
	{  // Конструктор по умолчанию
		size_ = 0;
		ptr_ = new T[1];
		ptr_[0] = 0;
	}

	explicit basic_string(size_t size)
	{
		size_ = size;
		ptr_ = new T[size_ + 1];
		for (size_t i = 0; i < size_; ++i)
		{
			ptr_[i] = ' ';
		}
		ptr_[size_] = 0;
	}

	basic_string(std::initializer_list<T> il)
	{
		size_ = il.size();
		ptr_ = new T[size_ + 1];
		size_t i = 0;
		for (const auto& item : il)
		{
			ptr_[i++] = item;
		}
		ptr_[size_] = 0;
	}

	basic_string(const T* c_str)
	{  // Конструктор Си строки
		size_ = strlen_(c_str);
		ptr_ = new T[size_ + 1];
		copy_data_(c_str);
	}

	basic_string(const basic_string& other)
	{  // Конструктор копирования
		size_ = other.size_;
		ptr_ = new T[size_ + 1];
		copy_data_(other.c_str());
	}

	basic_string(basic_string&& dying)
	{  // Конструктор перемещения
		ptr_ = dying.ptr_;
		size_ = dying.size_;
		dying.ptr_ = nullptr;
		dying.size_ = 0;
	}

	~basic_string()
	{  // Деструктор
		clean_();
	}

	const T* c_str() const
	{  // Возвращение к Си строке
		return (ptr_ != nullptr) ? ptr_ : reinterpret_cast<const T*>("");
	}

	size_t size() const
	{  // Возвращение длины строки
		return size_;
	}

	basic_string& operator=(const basic_string& other)
	{  // Оператор копирующего присваивания
		if (this == &other)
		{
			return *this;
		}
		clean_();
		size_ = other.size_;
		ptr_ = new T[size_ + 1];
		copy_data_(other.c_str());
		return *this;
	}

	basic_string& operator=(basic_string&& other)
	{  // Оператор перемещения
		if (this == &other)
		{
			return *this;
		}
		delete[] ptr_;
		size_ = other.size_;
		ptr_ = other.ptr_;
		other.ptr_ = nullptr;
		other.size_ = 0;
		return *this;
	}

	basic_string& operator=(const T* c_str)
	{  // Оператор присваивания C строки
		clean_();
		size_ = strlen_(c_str);
		ptr_ = new T[size_ + 1];
		for (size_t i = 0; i < size_; ++i)
		{
			ptr_[i] = c_str[i];
		}
		ptr_[size_] = 0;
		return *this;
	}

	basic_string& concat(const T* c_str)
	{
		basic_string<T> other(c_str);
		*this += other;
		return *this;
	}

	friend basic_string operator+(const basic_string& left,
								  const basic_string& right)
	{
		basic_string result;
		result.size_ = left.size_ + right.size_;
		result.ptr_ = new T[result.size_ + 1];
		result.copy_data_(left.c_str());
		for (size_t i = 0; i < right.size_; ++i)
		{
			result.ptr_[i + left.size_] = right.ptr_[i];
		}
		result.ptr_[result.size_] = 0;
		return result;
	}

	template <typename S>
	friend S& operator<<(S& os, const basic_string& obj)
	{  // Оператор вывод
		os << obj.c_str();
		return os;
	}

	template <typename S>
	friend S& operator>>(S& is, basic_string& obj)
	{  // Оператор ввода
		is >> std::noskipws;
		T symbol;
		obj.clean_();
		obj.size_ = 0;
		obj.ptr_ = new T[1];
		obj.ptr_[0] = 0;
		while (is >> symbol)
		{
			obj += symbol;
		}
		return is;
	}

	basic_string& operator+=(const basic_string& other)
	{  // Оператор прибавляем строку к строке
		*this = (*this + other);
		return *this;
	}

	basic_string& operator+=(const T symbol)
	{  // Оператор прибавления  имвола к строке
		T* prev_ptr = ptr_;
		++size_;
		ptr_ = new T[size_ + 1];
		copy_data_(prev_ptr);
		delete[] prev_ptr;
		ptr_[size_ - 1] = symbol;
		ptr_[size_] = 0;
		return *this;
	}

	T& operator[](size_t index) const
	{
		if (index >= size_)
		{
			throw std::out_of_range("Index out of range");
		}
		return ptr_[index];
	}

   private:
	size_t size_ = 0;
	T* ptr_ = nullptr;

	static size_t strlen_(const T* str)
	{
		size_t len = 0;
		while (str[len] != 0)
		{
			++len;
		}
		return len;
	}

	void clean_()
	{
		delete[] ptr_;
		ptr_ = nullptr;
		size_ = 0;
	}

	void copy_data_(const T* c_str)
	{
		for (size_t i = 0; i < size_; ++i)
		{
			ptr_[i] = c_str[i];
		}
		ptr_[size_] = 0;
	}
};
}  // namespace bmstu