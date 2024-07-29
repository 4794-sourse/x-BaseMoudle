#pragma once

namespace x_err_code
{
    // 成功
    static const int32_t   s_ok = 0;
    // 失败
    static const int32_t   e_fail = -1;
    // 接口不存在
    static const int32_t   e_nointerface = -2;
    // 接口没有实现
    static const int32_t   e_notimpl = -3;

};

#define x64_ASSERT(expr) ((void)0)

// 判断返回值失败
__inline bool x_failed(uint32_t hr)
{
    return ((int32_t)hr) < 0;
}

// 判断返回值成功
__inline bool x_succeeded(uint32_t hr)
{
    return (int32_t)(hr) >= 0;
}

#ifndef STDCALLTYPE
#define  STDCALLTYPE     __stdcall
#endif

#ifndef CDECL_CALLTYPE   
#define  CDECL_CALLTYPE   __cdecl
#endif


//__declspec( selectany ) 是windows的特性，可消除重定义，在使用时选取其中一个定义进行使用
#if _MSC_VER <= 1500
#   define COMPATIBLE_EXTERN_C __declspec( selectany ) extern
#else
#   define COMPATIBLE_EXTERN_C __declspec( selectany ) extern
#endif

#define __x64_uuidof(__interface_name)    IID_ ## __interface_name


