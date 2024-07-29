#pragma once

#include <atomic>
#include "x64_IxUnknown.h"

#define is_equal_guid(rguid1, rguid2) (!memcmp(&rguid1, &rguid2, sizeof(GUID)))

class BaseObject {
public:
	__inline BaseObject();
	__inline int32_t BaseObject_addref();
	__inline int32_t BaseObject_release();
	__inline virtual void DestroyInstance() = 0;

private:
	std::atomic_int32_t m_refCount;
};


BaseObject::BaseObject() {

}

int32_t BaseObject::BaseObject_addref() {
	
	return ++m_refCount;
}

int32_t  BaseObject::BaseObject_release() {
	
	--m_refCount;
	if (m_refCount == 0) {
		DestroyInstance();
	}
	return m_refCount;
}

template<typename _class>
class object_creator {
public:
	template< typename ... Args >
	inline static _class* create(Args ... args)
	{
		return new _class(std::forward<Args>(args)...);
	}
	inline static void destroy(_class* p)
	{
		if (p == nullptr) return;
		delete p;
	}
};

template<typename _class, typename object = object_creator<_class>>
class ComObjectImpl :public BaseObject {
public:
	typedef object object_creator;
	_class* GetThis() { return static_cast<_class*>(this); }

	template<typename interface_type>
	inline static long CreatInstance(interface_type** ppInterface) {
		
		if (ppInterface == nullptr) return x_err_code::e_fail;;
		IxUnknown* pUnknown = nullptr;
		auto hr = _class::InternalCreateInstance(&pUnknown);
		*ppInterface = static_cast<interface_type*>(pUnknown);

		return hr;
	}
};

template <typename T, typename object_creator_t = object_creator<T>, typename ... Args >
__inline long internal_create_instance(IxUnknown** ppUnknown, Args ... args)
{
	if (ppUnknown == nullptr) return x_err_code::e_fail;

	auto pThis = object_creator_t::create(std::forward<Args>(args)...);

	if (pThis == nullptr) return x_err_code::e_fail;;

	IxUnknownPtr spUnknown;
	auto hr = pThis->query_interface(__x64_uuidof(IxUnknown), (void**)&spUnknown);

	*ppUnknown = spUnknown.Detach();

	return x_err_code::s_ok;
}


template<typename _class, typename object = object_creator<_class>>
void InternalDestroyInstance(_class* p) {
	
	if (p == nullptr) return;
	object::destroy(p);
}

#define BEGIN_X64_OBJECT_MAP(__class) \
	virtual int32_t STDCALLTYPE addref(void) { return BaseObject::BaseObject_addref(); } \
	virtual int32_t STDCALLTYPE release(void) { return BaseObject::BaseObject_release(); } \
	template < typename ... Args > \
    static long InternalCreateInstance( IxUnknown ** ppUnknown, Args ... args) \
    { \
        return internal_create_instance< __class, __class::object_creator  >(ppUnknown, std::forward<Args>(args)...); \
    } \
    template < typename ... Args > \
    static long CreateInstance( IxUnknown ** ppUnknown, Args ... args) { return InternalCreateInstance(ppUnknown, std::forward<Args>(args)... ); } \
	virtual void DestroyInstance() \
	{ \
		__class* pThis = static_cast<__class*>(this); \
		InternalDestroyInstance<__class, __class::object_creator>(pThis); \
	} \
	virtual long STDCALLTYPE query_interface(const GUID& guid, void** ppInterface) {

#define BEGIN_X64_SINGLETON_OBJECT_MAP(__class) \
	virtual int32_t STDCALLTYPE addref(void) { return BaseObject::BaseObject_addref(); } \
	virtual int32_t STDCALLTYPE release(void) { return BaseObject::BaseObject_release(); } \
	template < typename ... Args > \
    static long InternalCreateInstance( IxUnknown ** ppUnknown, Args ... args) \
    { \
		return internal_create_instance< __class, __class::object_creator  >(ppUnknown, std::forward<Args>(args)...); \
    } \
    template < typename ... Args > \
    static long CreateInstance( IxUnknown ** ppUnknown, Args ... args) { return InternalCreateInstance(ppUnknown, std::forward<Args>(args)... ); } \
	virtual void DestroyInstance() \
	{ \
		__class* pThis = static_cast<__class*>(this); \
		InternalDestroyInstance<__class, __class::object_creator>(pThis); \
	} \
	virtual long STDCALLTYPE query_interface(const GUID& guid, void** ppInterface) {


#define X64_OBJECT_INTERFACE(__interface) \
    if(is_equal_guid(guid, IID_ ## __interface)) \
    { \
        __interface* inter = this; \
        *ppInterface = inter; \
        BaseObject::BaseObject_addref(); \
        return x_err_code::s_ok; \
    }

#define END_QAX_OBJECT_MAP()\
		return x_err_code::e_fail;\
	}

#define END_QAX_SINGLETON_OBJECT_MAP()\
		return x_err_code::e_fail; \
	}