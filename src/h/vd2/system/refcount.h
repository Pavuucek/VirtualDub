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

#ifndef f_VD2_SYSTEM_REFCOUNT_H
#define f_VD2_SYSTEM_REFCOUNT_H

#include <vd2/system/vdtypes.h>
#include <vd2/system/atomic.h>

///////////////////////////////////////////////////////////////////////////
//	IVDRefCount
///	Base interface for reference-counted objects.
///
/// Reference counting is a relatively straightforward and simple method
/// of garbage collection. The rules are:
///
/// 1) Objects increment their reference count on an AddRef() and
///    decrement it on a Release().
/// 2) Objects destroy themselves when their reference count is dropped
///    to zero.
/// 3) Clients create references with AddRef() and destroy them with
///    Release().
///
/// One way to interact with refcounted objects is to call AddRef()
/// whenever a pointer is created, and Release() when the pointer is
/// nulled or changed.  The vdrefptr<T> template does this automatically.
/// Reference counting may be "combined" between pointers for optimization
/// reasons, such that fewer reference counts are outstanding than actual
/// pointers; this requires weak (non-refcounted) pointers and explicit
/// refcount management.
///
/// Reference counting has two issues:
///
/// A) It is expensive.  VirtualDub uses it somewhat sparingly.
///
/// B) Reference counting cannot cope with cycles.  This issue is
///    avoided by arranging objects in a clearly ordered tree, such that
///    no class ever holds a pointer to another object of the same class
///    or to a parent in the reference hierarchy.  vdrefptr<T> can
///    implicitly create cycles if you are not careful.
///
///	In VirtualDub, reference counting must be multithread safe, so atomic
///	increment/decrement should be used.  vdrefcounted<T> handles this
///	automatically for the template type class.
///
///	Two final implementation details:
///
///	- Little or no code should be executed after the reference count
///	  drops to zero, preferably nothing more than the destructor implicitly
///	  generated by the compiler.  The reason is that otherwise there is the
///	  potential for an object to be resurrected past its final release by
///	  temporarily creating a new reference on the object.
///
/// - AddRef() and Release() traditionally return the reference count on
///	  the object after increment or decrement, but this is not required.
///	  For Release builds, it is only required that the value for Release()
///	  be zero iff the object is destroyed.  (The same applies for AddRef(),
///	  but since the result of AddRef() is always non-zero, the return of
///	  AddRef() is of no use unless it is the actual count.)
///
class VDINTERFACE IVDRefCount {
public:
	virtual int AddRef()=0;
	virtual int Release()=0;
};

///////////////////////////////////////////////////////////////////////////
//	vdrefcounted<T>
///	Implements thread-safe reference counting on top of a base class.
///
///	vdrefcounted<T> is used to either add reference counting to a base
///	class or to implement it on an interface. Use it by deriving your
///	class from it.
///
template<class T> class vdrefcounted : public T {
public:
	vdrefcounted() : mRefCount(0) {}
	vdrefcounted(const vdrefcounted<T>& src) : mRefCount(0) {}		// do not copy the refcount
	virtual ~vdrefcounted() {}

	vdrefcounted<T>& operator=(const vdrefcounted<T>&) {}			// do not copy the refcount

	inline virtual int AddRef() {
		return mRefCount.inc();
	}

	inline virtual int Release() {
		int rc = --mRefCount;

		if (!rc) {
			delete this;
			return 0;
		}

		VDASSERT(rc > 0);

		return rc;
	}

protected:
	VDAtomicInt		mRefCount;
};

///////////////////////////////////////////////////////////////////////////
//	vdrefptr<T>
///	Reference-counting smart pointer.
///
///	Maintains a strong reference on any object that supports AddRef/Release
///	semantics. This includes any interface including IVDRefCount,
///	IVDRefUnknown, or the IUnknown interface in Microsoft COM. Because
///	references are automatically traded as necessary, smart pointers are
///	very useful for maintaining exception safety.
///
template<class T> class vdrefptr {
protected:
	T *ptr;

public:
	typedef vdrefptr<T> self_type;
	typedef T			element_type;

	/// Creates a new smart pointer and obtains a new reference on the
	/// specified object.
	explicit vdrefptr(T *p = 0) : ptr(p) {
		if (p)
			p->AddRef();
	}

	/// Clones a smart pointer, duplicating any held reference.
	vdrefptr(const self_type& src) {
		ptr = src.ptr;
		if (ptr)
			ptr->AddRef();
	}

	/// Destroys the smart pointer, releasing any held reference.
	~vdrefptr() {
		if (ptr)
			ptr->Release();
	}

	/// Assigns a new object to a smart pointer. Any old object is released
	/// and the new object is addrefed.
	inline self_type& operator=(T *src) {
		if (src)
			src->AddRef();
		if (ptr)
			ptr->Release();
		ptr = src;
		return *this;
	}

	/// Assigns a new object to a smart pointer. Any old object is released
	/// and the new object is addrefed.
	inline self_type& operator=(const vdrefptr& src) {
		if (src.ptr)
			src.ptr->AddRef();
		if (ptr)
			ptr->Release();
		ptr = src.ptr;
		return *this;
	}

	operator T*() const { return ptr; }
	T& operator*() const { return *ptr; }
	T *operator->() const { return ptr; }

	/// Removes any old reference and returns a double-pointer to the nulled
	/// internal pointer. This is useful for passing to IUnknown-derived
	/// interfaces that accept (T **) parameters, like QueryInterface().
	T** operator~() {
		if (ptr) {
			ptr->Release();
			ptr = NULL;
		}
		return &ptr;
	}

	/// Removes any held reference.
	inline void clear() {
		if (ptr)
			ptr->Release();
		ptr = NULL;
	}

	/// Removes any existing reference and moves a reference from another
	/// smart pointer. The source pointer is cleared afterward.
	inline void from(vdrefptr& src) {
		if (ptr)
			ptr->Release();
		ptr = src.ptr;
		src.ptr = NULL;
	}

	/// Removes any existing reference and accepts a reference to a new
	/// object without actually obtaining one. This is useful if someone
	/// has already addrefed an object for you.
	inline void set(T* src) {
		if (ptr)
			ptr->Release();

		ptr = src;
	}

	/// Returns the held reference and clears the smart pointer without
	/// releasing the reference. This is useful for holding onto a reference
	/// in an exception-safe manner up until the last moment.
	inline T *release() {
		T *p = ptr;
		ptr = NULL;
		return p;
	}

	/// Swaps the references between two smart pointers.
	void swap(vdrefptr& r) {
		T *p = ptr;
		ptr = r.ptr;
		r.ptr = p;
	}
};

///////////////////////////////////////////////////////////////////////////

template<class T, class U>
bool VDRefCountObjectFactory(U **pp) {
	T *p = new_nothrow T;
	if (!p)
		return false;

	*pp = static_cast<U *>(p);
	p->AddRef();
	return true;
}

#endif
