///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Mathematics (glm.g-truc.net)
///
/// Copyright (c) 2005 - 2012 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file glm/core/type_vec3.hpp
/// @date 2008-08-22 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

/*
	This is a modified version of GLM's vector swizzling impl.
*/

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

#define _SWIZZLE3_2_MEMBERS(T,P2,E0,E1,E2) \
	struct { swizzle<2,T,P2,0,0,-1,-2> E0 ## E0; }; \
	struct { swizzle<2,T,P2,0,1,-1,-2> E0 ## E1; }; \
	struct { swizzle<2,T,P2,0,2,-1,-2> E0 ## E2; }; \
	struct { swizzle<2,T,P2,1,0,-1,-2> E1 ## E0; }; \
	struct { swizzle<2,T,P2,1,1,-1,-2> E1 ## E1; }; \
	struct { swizzle<2,T,P2,1,2,-1,-2> E1 ## E2; }; \
	struct { swizzle<2,T,P2,2,0,-1,-2> E2 ## E0; }; \
	struct { swizzle<2,T,P2,2,1,-1,-2> E2 ## E1; }; \
	struct { swizzle<2,T,P2,2,2,-1,-2> E2 ## E2; }; 

#define _SWIZZLE3_3_MEMBERS(T,P,E0,E1,E2) \
	struct { swizzle<3,T,P,0,0,0,-1> E0 ## E0 ## E0; }; \
	struct { swizzle<3,T,P,0,0,1,-1> E0 ## E0 ## E1; }; \
	struct { swizzle<3,T,P,0,0,2,-1> E0 ## E0 ## E2; }; \
	struct { swizzle<3,T,P,0,1,0,-1> E0 ## E1 ## E0; }; \
	struct { swizzle<3,T,P,0,1,1,-1> E0 ## E1 ## E1; }; \
	struct { swizzle<3,T,P,0,1,2,-1> E0 ## E1 ## E2; }; \
	struct { swizzle<3,T,P,0,2,0,-1> E0 ## E2 ## E0; }; \
	struct { swizzle<3,T,P,0,2,1,-1> E0 ## E2 ## E1; }; \
	struct { swizzle<3,T,P,0,2,2,-1> E0 ## E2 ## E2; }; \
	struct { swizzle<3,T,P,1,0,0,-1> E1 ## E0 ## E0; }; \
	struct { swizzle<3,T,P,1,0,1,-1> E1 ## E0 ## E1; }; \
	struct { swizzle<3,T,P,1,0,2,-1> E1 ## E0 ## E2; }; \
	struct { swizzle<3,T,P,1,1,0,-1> E1 ## E1 ## E0; }; \
	struct { swizzle<3,T,P,1,1,1,-1> E1 ## E1 ## E1; }; \
	struct { swizzle<3,T,P,1,1,2,-1> E1 ## E1 ## E2; }; \
	struct { swizzle<3,T,P,1,2,0,-1> E1 ## E2 ## E0; }; \
	struct { swizzle<3,T,P,1,2,1,-1> E1 ## E2 ## E1; }; \
	struct { swizzle<3,T,P,1,2,2,-1> E1 ## E2 ## E2; }; \
	struct { swizzle<3,T,P,2,0,0,-1> E2 ## E0 ## E0; }; \
	struct { swizzle<3,T,P,2,0,1,-1> E2 ## E0 ## E1; }; \
	struct { swizzle<3,T,P,2,0,2,-1> E2 ## E0 ## E2; }; \
	struct { swizzle<3,T,P,2,1,0,-1> E2 ## E1 ## E0; }; \
	struct { swizzle<3,T,P,2,1,1,-1> E2 ## E1 ## E1; }; \
	struct { swizzle<3,T,P,2,1,2,-1> E2 ## E1 ## E2; }; \
	struct { swizzle<3,T,P,2,2,0,-1> E2 ## E2 ## E0; }; \
	struct { swizzle<3,T,P,2,2,1,-1> E2 ## E2 ## E1; }; \
	struct { swizzle<3,T,P,2,2,2,-1> E2 ## E2 ## E2; };


template <int N,typename ValueType, typename VecType, int E0,int E1,int E2,int E3, int F0,int F1,int F2,int F3>
VecType operator+(const swizzle<N, ValueType, VecType, E0, E1, E2, E3>& v1, const swizzle<N, ValueType, VecType, F0, F1, F2, F3>& v2)
{
	return v1() + v2();
}


} /* namespace cgutils */
#endif /* _SWIZZLE_H */