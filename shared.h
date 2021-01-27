#pragma once
#ifndef SHARED_H
#define SHARED_H
#include <iostream>

class h_co
{
private:
	long count = 1;

public:
	h_co() :
		count(1)
	{ };
	h_co(h_co& tmp)
	{
		count = tmp.count;
	}
	long get_count() const noexcept
	{
		return count;
	}
	void inc_count()
	{
		++count;
	}
	void dec_count()
	{
		--count;
	}
	~h_co()
	{
		delete this;
	}
};

template <class T>
class shared_ptr
{
public:
	using iterator = T*;
	using element_type = T;

	friend class h_co;
	shared_ptr<T>()
	{
		_it = nullptr;               /////  IN case assignments need create object of h_co
		ptr = nullptr;
	}

	shared_ptr<T>(T* it = nullptr) 

	{
		_it = it;
		ptr = new h_co();
	}

	shared_ptr<T>(shared_ptr<T>& sp) :
		_it(sp._it),
		ptr(sp.ptr)
	{
		sp.ptr->inc_count();
	}

	shared_ptr<T>(T& var) :
		_it(var),
		ptr(new h_co())
	{
		ptr->inc_count();
	}

	~shared_ptr()
	{
		ptr = nullptr;
		_it = nullptr;
	}

	shared_ptr& operator= (shared_ptr& x) noexcept
	{
		reset();
		_it = x._it;
		ptr = x.ptr;
		ptr->inc_count();
		return *this;
	}

	shared_ptr& operator= (shared_ptr&& x) noexcept
	{
		reset();
		_it = x._it;
		ptr = x.ptr;
		ptr->inc_count();
		return *this;
	}

	iterator get()
	{
		return _it;
	}

	void reset() noexcept
	{
		delete_check(ptr);
		_it = nullptr;
	}

	template <class U>
	void reset(U* p)
	{
		delete_check(ptr);
		_it = (iterator)p;
		ptr = new h_co();
		*this = p;
	}

	element_type& operator*() const noexcept
	{
		return *_it;
	}

	iterator operator->() const noexcept
	{
		return _it;
	}

	long int use_count() const noexcept
	{
		return ptr->get_count();
	}

	bool unique() const noexcept   ////true if this is a unique shared_ptr, false otherwise.
	{
		return use_count() == 1;
	}

	explicit operator bool() const noexcept	//false if the shared_ptr is a null pointer.   true, otherwise.
	{
		if (_it == nullptr)
			return false;
		return true;
	}

	void swap(shared_ptr& x) noexcept
	{
		shared_ptr tmp(x);
		tmp.ptr->dec_count();
		x = *this;
		*this = tmp;
	}

private:
	iterator _it;
	h_co* ptr;

	void delete_check(h_co*& ptr)
	{
		if (*this)
		{
			ptr->dec_count();
			check();
		}
	}

	void check()
	{
		if (ptr->get_count() == 0)
		{
			~shared_ptr();
		}
	}
};



#endif