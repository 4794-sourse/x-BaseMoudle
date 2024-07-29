#pragma once

namespace x_err_code
{
    // �ɹ�
    static const int32_t   s_ok = 0;
    // ʧ��
    static const int32_t   e_fail = -1;
    // �ӿڲ�����
    static const int32_t   e_nointerface = -2;
    // �ӿ�û��ʵ��
    static const int32_t   e_notimpl = -3;

};

#define x64_ASSERT(expr) ((void)0)

// �жϷ���ֵʧ��
__inline bool x_failed(uint32_t hr)
{
    return ((int32_t)hr) < 0;
}

// �жϷ���ֵ�ɹ�
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


//__declspec( selectany ) ��windows�����ԣ��������ض��壬��ʹ��ʱѡȡ����һ���������ʹ��
#if _MSC_VER <= 1500
#   define COMPATIBLE_EXTERN_C __declspec( selectany ) extern
#else
#   define COMPATIBLE_EXTERN_C __declspec( selectany ) extern
#endif

#define __x64_uuidof(__interface_name)    IID_ ## __interface_name


