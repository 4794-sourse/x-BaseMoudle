// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "CSearchIDInfo.h"
#include <atlbase.h>
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

template < typename T >
class CObjectCreator
{
public:
    __inline static long CheckAndCreate(const GUID& base_id, const GUID& iid, void** ppInterface);
};

template < typename T >
__inline long CObjectCreator<T>::CheckAndCreate(const GUID& base_id, const GUID& iid, void** ppInterface)
{
    if (is_equal_guid(base_id, iid) == false) return x_err_code::e_nointerface;

    IxUnknownPtr spUnknown;

    long hr = T::CreateInstance(&spUnknown);

    spUnknown->query_interface(iid, ppInterface);
    return hr;
}

#define CheckAndCreateObject( base_id, iid, __class_type, __pp_interface )	\
	if(CObjectCreator<__class_type>::CheckAndCreate(base_id, iid,  __pp_interface )) return x_err_code::s_ok;


int32_t STDCALLTYPE Create_x64_Object(const GUID &guid, void** pinterface) {

    CheckAndCreateObject(__x64_uuidof(ISearchIDInfo), guid, CSearchIDInfo, pinterface);
    return 0;
}


