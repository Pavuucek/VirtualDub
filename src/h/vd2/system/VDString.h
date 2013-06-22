//	VirtualDub - Video processing and capture application
//	System library component
//	Copyright (C) 1998-2004 Avery Lee, All Rights Reserved.
//
//	Beginning with 1.6.0, the VirtualDub system library is licensed
//	differently than the remainder of VirtualDub.  This particular file is
//	thus licensed as follows (the "zlib" license):
//
//	This software is provided 'as-is', without any express or implied
//	warranty.  In no event will the authors be held liable for any
//	damages arising from the use of this software.
//
//	Permission is granted to anyone to use this software for any purpose,
//	including commercial applications, and to alter it and redistribute it
//	freely, subject to the following restrictions:
//
//	1.	The origin of this software must not be misrepresented; you must
//		not claim that you wrote the original software. If you use this
//		software in a product, an acknowledgment in the product
//		documentation would be appreciated but is not required.
//	2.	Altered source versions must be plainly marked as such, and must
//		not be misrepresented as being the original software.
//	3.	This notice may not be removed or altered from any source
//		distribution.

#ifndef f_VD2_SYSTEM_VDSTRING_H
#define f_VD2_SYSTEM_VDSTRING_H

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>

#include <vd2/system/vdtypes.h>
#include <vd2/system/text.h>

///////////////////////////////////////////////////////////////////////////

class VDStringSpanA {
public:
	typedef char					value_type;
	typedef uint32					size_type;
	typedef ptrdiff_t				difference_type;
	typedef value_type&				reference;
	typedef const value_type&		const_reference;
	typedef value_type *			pointer;
	typedef const value_type *		const_pointer;
	typedef pointer					iterator;
	typedef const_pointer			const_iterator;

	static const size_type npos = (size_type)-1;

	VDStringSpanA() 
		: mpBegin(const_cast<value_type *>(sNull))
		, mpEnd(const_cast<value_type *>(sNull))
	{
	}

	VDStringSpanA(const value_type *s, const value_type *t)
		: mpBegin(const_cast<value_type *>(s))
		, mpEnd(const_cast<value_type *>(t))
	{
	}

	// 21.3.2 iterators
	const_iterator		begin() const		{ return mpBegin; }
	const_iterator		end() const			{ return mpEnd; }

	// 21.3.3 capacity
	size_type			size() const		{ return mpEnd - mpBegin; }
	size_type			length() const		{ return mpEnd - mpBegin; }
	bool				empty() const		{ return mpBegin == mpEnd; }

	// 21.3.4 element access
	const_reference		operator[](size_type pos) const	{ VDASSERT(pos < (size_type)(mpEnd - mpBegin)); return mpBegin[pos]; }
	const_reference		at(size_type pos) const			{ VDASSERT(pos < (size_type)(mpEnd - mpBegin)); return mpBegin[pos]; }

	const_reference		front() const		{ VDASSERT(mpBegin != mpEnd); return *mpBegin; }
	const_reference		back() const		{ VDASSERT(mpBegin != mpEnd); return mpEnd[-1]; }

	// 21.3.6 string operations
	const_pointer		data() const		{ return mpBegin; }

	size_type copy(value_type *dst, size_type n, size_type pos = 0) const {
		size_type len = (size_type)(mpEnd - mpBegin);
		VDASSERT(pos <= len);

		len -= pos;
		if (n > len)
			n = len;

		memcpy(dst, mpBegin + pos, n*sizeof(value_type));
		return n;
	}

	size_type find(value_type c, size_type pos = 0) const {
		VDASSERT(pos <= (size_type)(mpEnd - mpBegin));
		const void *p = memchr(mpBegin + pos, c, mpEnd - (mpBegin + pos));

		return p ? (const value_type *)p - mpBegin : npos;
	}

protected:
	value_type *mpBegin;
	value_type *mpEnd;

	static const value_type sNull[1];
};

class VDStringA : public VDStringSpanA {
public:
	typedef VDStringA				this_type;

	// 21.3.1 construct/copy/destroy

	VDStringA()
		: mpEOS(const_cast<value_type *>(sNull))
	{
	}

	VDStringA(const this_type& x)
		: mpEOS(const_cast<value_type *>(sNull))
	{
		assign(x);
	}

	explicit VDStringA(const value_type *s)
		: mpEOS(const_cast<value_type *>(sNull))
	{
		assign(s);
	}

	explicit VDStringA(size_type n)
		: mpEOS(const_cast<value_type *>(sNull))
	{
		resize(n);
	}

	VDStringA(const value_type *s, size_type n)
		: mpEOS(const_cast<value_type *>(sNull))
	{
		assign(s, n);
	}

	~VDStringA() {
		if (mpBegin != sNull)
			delete[] mpBegin;
	}

	this_type& operator=(const value_type *s) {
		assign(s);
		return *this;
	}

	this_type& operator=(const this_type& str) {
		assign(str);
		return *this;
	}

	// 21.3.2 iterators
	using VDStringSpanA::begin;
	using VDStringSpanA::end;

	iterator			begin()				{ return mpBegin; }
	iterator			end()				{ return mpEnd; }

	// 21.3.3 capacity (COMPLETE)
	void resize(size_type n) {
		size_type current = (size_type)(mpEnd - mpBegin);

		if (n < current) {
			mpEnd = mpBegin + n;
			mpEnd[0] = 0;
		} else if (n > current)
			resize_slow(n, current);
	}

	void resize(size_type n, value_type v) {
		size_type current = (size_type)(mpEnd - mpBegin);

		if (n < current) {
			mpEnd = mpBegin + n;
			mpEnd[0] = 0;
		} else if (n > current)
			resize_slow(n, current, v);
	}

	size_type			capacity() const	{ return mpEOS - mpBegin; }

	void reserve(size_t n) {
		size_type current = (size_type)(mpEOS - mpBegin);

		if (n > current)
			reserve_slow(n, current);
	}

	void clear() {
		if (mpEnd != mpBegin) {
			mpEnd = mpBegin;
			mpEnd[0] = 0;
		}
	}

	// 21.3.4 element access
	using VDStringSpanA::operator[];
	using VDStringSpanA::at;
	using VDStringSpanA::front;
	using VDStringSpanA::back;

	reference			operator[](size_type pos)		{ VDASSERT(pos < (size_type)(mpEnd - mpBegin)); return mpBegin[pos]; }
	reference			at(size_type pos)				{ VDASSERT(pos < (size_type)(mpEnd - mpBegin)); return mpBegin[pos]; }
	reference			front()				{ VDASSERT(mpBegin != mpEnd); return *mpBegin; }
	reference			back()				{ VDASSERT(mpBegin != mpEnd); return mpEnd[-1]; }

	// 21.3.5 modifiers
	this_type& operator+=(const this_type& str) {
		return append(str.mpBegin, str.mpEnd);
	}

	this_type& operator+=(const value_type *s) {
		return append(s, s+strlen(s));
	}

	this_type& operator+=(value_type c) {
		if (mpEnd == mpEOS)
			push_back_extend();

		*mpEnd++ = c;
		*mpEnd = 0;
		return *this;
	}

	this_type& append(const this_type& str) {
		return append(str.mpBegin, str.mpEnd);
	}

	this_type& append(const this_type& str, size_type pos, size_type n) {
		size_type len = (size_type)(str.mpEnd - str.mpBegin);
		VDASSERT(pos <= len);

		len -= pos;
		if (n > len)
			n = len;

		return append(str.mpBegin + pos, str.mpBegin + pos + n);
	}

	this_type& append(const value_type *s, size_type n) {
		return append(s, s+n);
	}

	this_type& append(const value_type *s) {
		return append(s, s+strlen(s));
	}

	this_type& append(const value_type *s, const value_type *t) {
		if (s != t) {
			size_type current_size = (size_type)(mpEnd - mpBegin);
			size_type current_capacity = (size_type)(mpEOS - mpBegin);
			size_type n = (size_type)(t - s);

			if (current_capacity - current_size < n)
				reserve_amortized_slow(n, current_size, current_capacity);

			memcpy(mpBegin + current_size, s, n*sizeof(value_type));
			mpEnd += n;
			*mpEnd = 0;
		}
		return *this;
	}

	void push_back(const value_type c) {
		if (mpEnd == mpEOS)
			push_back_extend();

		*mpEnd++ = c;
		*mpEnd = 0;
	}

	this_type& assign(const this_type& str) {
		return assign(str.mpBegin, str.mpEnd);
	}

	this_type& assign(const this_type& str, size_type pos, size_type n) {
		size_type len = (size_type)(str.mpEnd - str.mpBegin);
		VDASSERT(pos <= len);

		len -= pos;
		if (n > len)
			n = len;

		return assign(str.mpBegin + pos, str.mpBegin + pos + n);
	}

	this_type& assign(const value_type *s, size_type n) {
		return assign(s, s+n);
	}

	this_type& assign(const value_type *s) {
		return assign(s, s+strlen(s));
	}

	this_type& assign(size_type n, value_type c) {
		size_type current_capacity = (size_type)(mpEOS - mpBegin);

		if (current_capacity < n)
			reserve_slow(n, current_capacity);

		if (mpBegin != sNull) {
			mpEnd = mpBegin;
			while(n--)
				*mpEnd++ = c;
		}

		return *this;
	}

	this_type& assign(const value_type *s, const value_type *t) {
		size_type current_capacity = (size_type)(mpEOS - mpBegin);
		size_type n = (size_type)(t - s);

		if (current_capacity < n)
			reserve_slow(n, current_capacity);

		if (mpBegin != sNull) {
			memcpy(mpBegin, s, sizeof(value_type)*n);
			mpEnd = mpBegin + n;
			*mpEnd = 0;
		}

		return *this;
	}

	this_type& insert(iterator it, value_type c) {
		if (mpEnd == mpEOS) {
			size_type pos = (size_type)(it - mpBegin);
			push_back_extend();
			it = mpBegin + pos;
		}

		memmove(it + 1, it, (mpEnd - it + 1)*sizeof(value_type));
		*it = c;
		++mpEnd;
		return *this;
	}

	this_type& erase(size_type pos = 0, size_type n = npos) {
		size_type len = (size_type)(mpEnd - mpBegin);

		VDASSERT(pos <= len);
		len -= pos;
		if (n > len)
			n = len;

		if (n) {
			size_type pos2 = pos + n;
			memmove(mpBegin + pos, mpBegin + pos2, (len + 1 - n)*sizeof(value_type));
			mpEnd -= n;
		}

		return *this;
	}

	iterator erase(iterator x) {
		VDASSERT(x != mpEnd);

		memmove(x, x+1, (mpEnd - x)*sizeof(value_type));
		--mpEnd;
		return x;
	}

	iterator erase(iterator first, iterator last) {
		VDASSERT(last >= first);

		memmove(first, last, ((mpEnd - last) + 1)*sizeof(value_type));
		mpEnd -= (last - first);
		return first;
	}

	this_type& replace(size_type pos, size_type n1, const value_type *s, size_type n2) {
		size_type len = (size_type)(mpEnd - mpBegin);

		VDASSERT(pos <= len);
		size_type limit = len - pos;
		if (n1 > limit)
			n1 = limit;

		size_type len2 = len - n1 + n2;
		size_type current_capacity = (size_type)(mpEOS - mpBegin);

		if (current_capacity < len2)
			reserve_slow(len2, current_capacity);

		memmove(mpBegin + pos + n2, mpBegin + pos + n1, (limit - n1 + 1) * sizeof(value_type));
		memcpy(mpBegin + pos, s, n2*sizeof(value_type));
		mpEnd = mpBegin + len2;
		return *this;
	}

	void swap(this_type& x) {
		value_type *p;

		p = mpBegin;	mpBegin = x.mpBegin;	x.mpBegin = p;
		p = mpEnd;		mpEnd = x.mpEnd;		x.mpEnd = p;
		p = mpEOS;		mpEOS = x.mpEOS;		x.mpEOS = p;
	}

	// 21.3.6 string operations
	const_pointer		c_str() const		{ return mpBegin; }

	this_type& sprintf(const value_type *format, ...);

protected:
	friend bool operator==(const VDStringA& x, const VDStringA& y);
	friend bool operator==(const VDStringA& x, const char *y);

	void push_back_extend();
	void resize_slow(size_type n, size_type current_size);
	void resize_slow(size_type n, size_type current_size, value_type c);
	void reserve_slow(size_type n, size_type current_capacity);
	void reserve_amortized_slow(size_type n, size_type current_size, size_type current_capacity);

	char *mpEOS;
};

///////////////////////////////////////////////////////////////////////////

inline bool operator==(const VDStringA& x, const VDStringA& y) { VDStringA::size_type len = (VDStringA::size_type)(x.mpEnd - x.mpBegin); return len == (VDStringA::size_type)(y.mpEnd - y.mpBegin) && !memcmp(x.mpBegin, y.mpBegin, len*sizeof(char)); }
inline bool operator==(const VDStringA& x, const char *y) { size_t len = strlen(y); return len == (size_t)(x.mpEnd - x.mpBegin) && !memcmp(x.mpBegin, y, len*sizeof(char)); }
inline bool operator==(const char *x, const VDStringA& y) { return y == x; }

inline bool operator!=(const VDStringA& x, const VDStringA& y) { return !(x == y); }
inline bool operator!=(const VDStringA& x, const char *y) { return !(x == y); }
inline bool operator!=(const char *x, const VDStringA& y) { return !(y == x); }

inline VDStringA operator+(const VDStringA& str, const VDStringA& s) {
	VDStringA result;
	result.reserve(str.size() + s.size());
	result.assign(str);
	result.append(s);
	return result;
}

inline VDStringA operator+(const VDStringA& str, const char *s) {
	VDStringA result;
	result.reserve(str.size() + strlen(s));
	result.assign(str);
	result.append(s);
	return result;
}

inline VDStringA operator+(const VDStringA& str, char c) {
	VDStringA result;
	result.reserve(str.size() + 1);
	result.assign(str);
	result += c;
	return result;
}

///////////////////////////////////////////////////////////////////////////

class VDStringSpanW {
public:
	typedef wchar_t					value_type;
	typedef uint32					size_type;
	typedef ptrdiff_t				difference_type;
	typedef value_type&				reference;
	typedef const value_type&		const_reference;
	typedef value_type *			pointer;
	typedef const value_type *		const_pointer;
	typedef pointer					iterator;
	typedef const_pointer			const_iterator;

	static const size_type npos = (size_type)-1;

	VDStringSpanW() 
		: mpBegin(const_cast<value_type *>(sNull))
		, mpEnd(const_cast<value_type *>(sNull))
	{
	}

	VDStringSpanW(const value_type *s, const value_type *t)
		: mpBegin(const_cast<value_type *>(s))
		, mpEnd(const_cast<value_type *>(t))
	{
	}

	// 21.3.2 iterators
	const_iterator		begin() const		{ return mpBegin; }
	const_iterator		end() const			{ return mpEnd; }

	// 21.3.3 capacity
	size_type			size() const		{ return mpEnd - mpBegin; }
	size_type			length() const		{ return mpEnd - mpBegin; }
	bool				empty() const		{ return mpBegin == mpEnd; }

	// 21.3.4 element access
	const_reference		operator[](size_type pos) const	{ VDASSERT(pos < (size_type)(mpEnd - mpBegin)); return mpBegin[pos]; }
	const_reference		at(size_type pos) const			{ VDASSERT(pos < (size_type)(mpEnd - mpBegin)); return mpBegin[pos]; }

	const_reference		front() const		{ VDASSERT(mpBegin != mpEnd); return *mpBegin; }
	const_reference		back() const		{ VDASSERT(mpBegin != mpEnd); return mpEnd[-1]; }

	// 21.3.6 string operations
	const_pointer		data() const		{ return mpBegin; }

	size_type copy(value_type *dst, size_type n, size_type pos = 0) const {
		size_type len = (size_type)(mpEnd - mpBegin);
		VDASSERT(pos <= len);

		len -= pos;
		if (n > len)
			n = len;

		memcpy(dst, mpBegin + pos, n*sizeof(value_type));
		return n;
	}

	size_type find(value_type c, size_type pos = 0) const {
		VDASSERT(pos <= (size_type)(mpEnd - mpBegin));
		const void *p = wmemchr(mpBegin + pos, c, mpEnd - (mpBegin + pos));

		return p ? (const value_type *)p - mpBegin : npos;
	}

protected:
	value_type *mpBegin;
	value_type *mpEnd;

	static const value_type sNull[1];
};

class VDStringW : public VDStringSpanW {
public:
	typedef VDStringW				this_type;

	// 21.3.1 construct/copy/destroy

	VDStringW()
		: mpEOS(const_cast<value_type *>(sNull))
	{
	}

	VDStringW(const this_type& x)
		: mpEOS(const_cast<value_type *>(sNull))
	{
		assign(x);
	}

	explicit VDStringW(const value_type *s)
		: mpEOS(const_cast<value_type *>(sNull))
	{
		assign(s);
	}

	explicit VDStringW(size_type n)
		: mpEOS(const_cast<value_type *>(sNull))
	{
		resize(n);
	}

	VDStringW(const value_type *s, size_type n)
		: mpEOS(const_cast<value_type *>(sNull))
	{
		assign(s, n);
	}

	VDStringW(const value_type *s, const value_type *t)
		: mpEOS(const_cast<value_type *>(sNull))
	{
		assign(s, t);
	}

	~VDStringW() {
		if (mpBegin != sNull)
			delete[] mpBegin;
	}

	this_type& operator=(const wchar_t *s) {
		assign(s);
		return *this;
	}

	this_type& operator=(const this_type& str) {
		assign(str);
		return *this;
	}

	// 21.3.2 iterators
	using VDStringSpanW::begin;
	using VDStringSpanW::end;
	iterator			begin()				{ return mpBegin; }
	iterator			end()				{ return mpEnd; }

	// 21.3.3 capacity (COMPLETE)
	void resize(size_type n) {
		size_type current = (size_type)(mpEnd - mpBegin);

		if (n < current) {
			mpEnd = mpBegin + n;
			mpEnd[0] = 0;
		} else if (n > current)
			resize_slow(n, current);
	}

	void resize(size_type n, value_type v) {
		size_type current = (size_type)(mpEnd - mpBegin);

		if (n < current) {
			mpEnd = mpBegin + n;
			mpEnd[0] = 0;
		} else if (n > current)
			resize_slow(n, current);
		wmemset(mpBegin, v, n);
	}

	size_type			capacity() const	{ return mpEOS - mpBegin; }

	void reserve(size_t n) {
		size_type current = (size_type)(mpEOS - mpBegin);

		if (n > current)
			reserve_slow(n, current);
	}

	void clear() {
		if (mpEnd != mpBegin) {
			mpEnd = mpBegin;
			mpEnd[0] = 0;
		}
	}

	// 21.3.4 element access
	using VDStringSpanW::operator[];
	using VDStringSpanW::at;
	using VDStringSpanW::front;
	using VDStringSpanW::back;
	reference			operator[](size_type pos)		{ VDASSERT(pos < (size_type)(mpEnd - mpBegin)); return mpBegin[pos]; }
	reference			at(size_type pos)				{ VDASSERT(pos < (size_type)(mpEnd - mpBegin)); return mpBegin[pos]; }
	reference			front()				{ VDASSERT(mpBegin != mpEnd); return *mpBegin; }
	reference			back()				{ VDASSERT(mpBegin != mpEnd); return mpEnd[-1]; }

	// 21.3.5 modifiers
	this_type& operator+=(const this_type& str) {
		return append(str.mpBegin, str.mpEnd);
	}

	this_type& operator+=(const value_type *s) {
		return append(s, s+wcslen(s));
	}

	this_type& operator+=(value_type c) {
		if (mpEnd == mpEOS)
			push_back_extend();

		*mpEnd++ = c;
		*mpEnd = 0;
		return *this;
	}

	this_type& append(const this_type& str) {
		return append(str.mpBegin, str.mpEnd);
	}

	this_type& append(const this_type& str, size_type pos, size_type n) {
		size_type len = (size_type)(str.mpEnd - str.mpBegin);
		VDASSERT(pos <= len);

		len -= pos;
		if (n > len)
			n = len;

		return append(str.mpBegin + pos, str.mpBegin + pos + n);
	}

	this_type& append(const value_type *s, size_type n) {
		return append(s, s+n);
	}

	this_type& append(const value_type *s) {
		return append(s, s+wcslen(s));
	}

	this_type& append(const value_type *s, const value_type *t) {
		if (s != t) {
			size_type current_size = (size_type)(mpEnd - mpBegin);
			size_type current_capacity = (size_type)(mpEOS - mpBegin);
			size_type n = (size_type)(t - s);

			if (current_capacity - current_size < n)
				reserve_amortized_slow(n, current_size, current_capacity);

			memcpy(mpBegin + current_size, s, n*sizeof(value_type));
			mpEnd += n;
			*mpEnd = 0;
		}
		return *this;
	}

	void push_back(const value_type c) {
		if (mpEnd == mpEOS)
			push_back_extend();

		*mpEnd++ = c;
		*mpEnd = 0;
	}

	this_type& assign(const this_type& str) {
		return assign(str.mpBegin, str.mpEnd);
	}

	this_type& assign(const this_type& str, size_type pos, size_type n) {
		size_type len = (size_type)(str.mpEnd - str.mpBegin);
		VDASSERT(pos <= len);

		len -= pos;
		if (n > len)
			n = len;

		return assign(str.mpBegin + pos, str.mpBegin + pos + n);
	}

	this_type& assign(const value_type *s, size_type n) {
		return assign(s, s+n);
	}

	this_type& assign(const value_type *s) {
		return assign(s, s+wcslen(s));
	}

	this_type& assign(size_type n, value_type c) {
		size_type current_capacity = (size_type)(mpEOS - mpBegin);

		if (current_capacity < n)
			reserve_slow(n, current_capacity);

		if (mpBegin != sNull) {
			mpEnd = mpBegin;
			while(n--)
				*mpEnd++ = c;
		}

		return *this;
	}

	this_type& assign(const value_type *s, const value_type *t) {
		size_type current_capacity = (size_type)(mpEOS - mpBegin);
		size_type n = (size_type)(t - s);

		if (current_capacity < n)
			reserve_slow(n, current_capacity);

		if (mpBegin != sNull) {
			memcpy(mpBegin, s, sizeof(value_type)*n);
			mpEnd = mpBegin + n;
			*mpEnd = 0;
		}

		return *this;
	}

	this_type& insert(iterator it, value_type c) {
		if (mpEnd == mpEOS) {
			size_type pos = (size_type)(it - mpBegin);
			push_back_extend();
			it = mpBegin + pos;
		}

		memmove(it + 1, it, (mpEnd - it + 1)*sizeof(value_type));
		*it = c;
		++mpEnd;
		return *this;
	}

	this_type& erase(size_type pos = 0, size_type n = npos) {
		size_type len = (size_type)(mpEnd - mpBegin);

		VDASSERT(pos <= len);
		len -= pos;
		if (n > len)
			n = len;

		if (n) {
			size_type pos2 = pos + n;
			memmove(mpBegin + pos, mpBegin + pos2, (len + 1 - n)*sizeof(value_type));
			mpEnd -= n;
		}

		return *this;
	}

	iterator erase(iterator x) {
		VDASSERT(x != mpEnd);

		memmove(x, x+1, (mpEnd - x)*sizeof(value_type));
		--mpEnd;
		return x;
	}

	iterator erase(iterator first, iterator last) {
		VDASSERT(last >= first);

		memmove(first, last, ((mpEnd - last) + 1)*sizeof(value_type));
		mpEnd -= (last - first);
		return first;
	}

	this_type& replace(size_type pos, size_type n1, const value_type *s, size_type n2) {
		size_type len = (size_type)(mpEnd - mpBegin);

		VDASSERT(pos <= len);
		size_type limit = len - pos;
		if (n1 > limit)
			n1 = limit;

		size_type len2 = len - n1 + n2;
		size_type current_capacity = (size_type)(mpEOS - mpBegin);

		if (current_capacity < len2)
			reserve_slow(len2, current_capacity);

		memmove(mpBegin + pos + n2, mpBegin + pos + n1, (limit - n1 + 1) * sizeof(value_type));
		memcpy(mpBegin + pos, s, n2*sizeof(value_type));
		mpEnd = mpBegin + len2;
		return *this;
	}

	void swap(this_type& x) {
		value_type *p;

		p = mpBegin;	mpBegin = x.mpBegin;	x.mpBegin = p;
		p = mpEnd;		mpEnd = x.mpEnd;		x.mpEnd = p;
		p = mpEOS;		mpEOS = x.mpEOS;		x.mpEOS = p;
	}

	// 21.3.6 string operations
	const_pointer		c_str() const		{ return mpBegin; }

	this_type& sprintf(const value_type *format, ...);

protected:
	friend bool operator==(const VDStringW& x, const VDStringW& y);
	friend bool operator==(const VDStringW& x, const wchar_t *y);

	void push_back_extend();
	void resize_slow(size_type n, size_type current_size);
	void reserve_slow(size_type n, size_type current_capacity);
	void reserve_amortized_slow(size_type n, size_type current_size, size_type current_capacity);

	value_type *mpEOS;
};

///////////////////////////////////////////////////////////////////////////

inline bool operator==(const VDStringW& x, const VDStringW& y) { VDStringA::size_type len = (VDStringW::size_type)(x.mpEnd - x.mpBegin); return len == (VDStringW::size_type)(y.mpEnd - y.mpBegin) && !memcmp(x.mpBegin, y.mpBegin, len*sizeof(wchar_t)); }
inline bool operator==(const VDStringW& x, const wchar_t *y) { size_t len = wcslen(y); return len == (size_t)(x.mpEnd - x.mpBegin) && !memcmp(x.mpBegin, y, len*sizeof(wchar_t)); }
inline bool operator==(const wchar_t *x, const VDStringW& y) { return y == x; }

inline bool operator!=(const VDStringW& x, const VDStringW& y) { return !(x == y); }
inline bool operator!=(const VDStringW& x, const wchar_t *y) { return !(x == y); }
inline bool operator!=(const wchar_t *x, const VDStringW& y) { return !(y == x); }

inline VDStringW operator+(const VDStringW& str, const VDStringW& s) {
	VDStringW result;
	result.reserve(str.size() + s.size());
	result.assign(str);
	result.append(s);
	return result;
}

inline VDStringW operator+(const VDStringW& str, const wchar_t *s) {
	VDStringW result;
	result.reserve(str.size() + wcslen(s));
	result.assign(str);
	result.append(s);
	return result;
}

inline VDStringW operator+(const VDStringW& str, wchar_t c) {
	VDStringW result;
	result.reserve(str.size() + 1);
	result.assign(str);
	result += c;
	return result;
}

///////////////////////////////////////////////////////////////////////////

typedef VDStringA				VDString;


#endif