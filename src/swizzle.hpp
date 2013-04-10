#ifndef _SWIZZLE_H
#define _SWIZZLE_H

#include <cstddef>

namespace cgutils
{

/* Base swizzle that is unique per vec1, vec2, vec3, vec4
*/
template <typename T, int N>
struct _swizzle_base0
{
    typedef T       value_type;

protected:
    value_type&         elem   (size_t i)       { return (reinterpret_cast<value_type*>(_buffer))[i]; }
    const value_type&   elem   (size_t i) const { return (reinterpret_cast<const value_type*>(_buffer))[i]; }

    char    _buffer[1];
};


/* swizzle no () 
*/
template <typename T, typename V, int E0, int E1, int E2, int E3, int N>
struct _swizzle_base1 : public _swizzle_base0<T,N>
{
};

/* swizzle create vec2 with ()
*/
template <typename T, typename V, int E0, int E1>
struct _swizzle_base1<T,V,E0,E1,-1,-2,2> : public _swizzle_base0<T,2>
{
    V operator ()()  const { return V(this->elem(E0), this->elem(E1)); }
};


/* swizzle create vec3 with ()
*/
template <typename T, typename V, int E0, int E1, int E2>
struct _swizzle_base1<T,V,E0,E1,E2,-1,3> : public _swizzle_base0<T,3>
{
    V operator ()()  const { return V(this->elem(E0), this->elem(E1), this->elem(E2)); }
};


/* swizzle create vec4 with ()
*/
template <typename T, typename V, int E0, int E1, int E2, int E3>
struct _swizzle_base1<T,V,E0,E1,E2,E3,4> : public _swizzle_base0<T,4>
{ 
    V operator ()()  const { return V(this->elem(E0), this->elem(E1), this->elem(E2), this->elem(E3)); }
};



template <typename ValueType, typename VecType, int N, int E0, int E1, int E2, int E3, int DUPLICATE_ELEMENTS>
struct _swizzle_base2 : public _swizzle_base1<ValueType,VecType,E0,E1,E2,E3,N>
{
	typedef VecType vec_type;
	typedef ValueType value_type;

	/* 
		set all members equal to a scalar
	*/
	_swizzle_base2& operator= (const ValueType& t)
	{
		for (int i = 0; i < N; ++i)
			(*this)[i] = t;
		return *this;
	}

	/* 
		set all members equal to a vector
	*/
	_swizzle_base2& operator= (const VecType& that)
	{
		struct op { 
			void operator() (value_type& e, value_type& t) { e = t; } 
		};
		_apply_op(that, op());
		return *this;
	}

	value_type& operator[]  (size_t i)
	{
		static const int offset_dst[4] = { E0, E1, E2, E3 };
		return this->elem(offset_dst[i]);
	}
	value_type  operator[]  (size_t i) const
	{
		static const int offset_dst[4] = { E0, E1, E2, E3 };
		return this->elem(offset_dst[i]);
	}

protected:
	template <typename T>
	void _apply_op(const VecType& that, T op)
	{
		// Make a copy of the data in this == &that.
		// The copier should optimize out the copy in cases where the function is
		// properly inlined and the copy is not necessary.
		ValueType t[N];
		for (int i = 0; i < N; ++i)
			t[i] = that[i];
		for (int i = 0; i < N; ++i)
			op( (*this)[i], t[i] );
	}
};

template <int N,typename ValueType, typename VecType, int E0,int E1,int E2,int E3>
struct swizzle : public _swizzle_base2<ValueType,VecType,N,E0,E1,E2,E3,(E0==E1||E0==E2||E0==E3||E1==E2||E1==E3||E2==E3)>
{
	typedef _swizzle_base2<ValueType,VecType,N,E0,E1,E2,E3,(E0==E1||E0==E2||E0==E3||E1==E2||E1==E3||E2==E3)> base_type;

	using base_type::operator=;

	operator VecType () const { return (*this)(); }
};



} /* namespace cgutils */
#endif /* _SWIZZLE_H */