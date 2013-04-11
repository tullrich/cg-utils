#ifndef _CG_UTILS_HPP
#define _CG_UTILS_HPP

namespace cgutils
{

struct CallBack
{
	virtual void callback() = 0;
};

template<typename T, void (T::*F)()>
struct CallBackImpl : CallBack
{
	void* p;
	typedef T* obj_ptype;

	CallBackImpl(T& obj)
	{
		p = &obj;
	};

	virtual void callback()
	{
		(((obj_ptype)p)->*F)();
	}
};

template<void (*F)()>
struct StaticCallBackImpl : CallBack
{

	StaticCallBackImpl()
	{};

	virtual void callback()
	{
		(*F)();
	}
};

} /* namespace cgutils */
#endif /* _CG_UTILS_HPP */