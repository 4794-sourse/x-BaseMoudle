#pragma once
#include "x64_error_code.h"

// {404C3E49-97F5-4FF2-BD75-FA890B9FD78B}
COMPATIBLE_EXTERN_C const GUID IID_IxUnknown =
{ 0x404c3e49, 0x97f5, 0x4ff2, { 0xbd, 0x75, 0xfa, 0x89, 0xb, 0x9f, 0xd7, 0x8b } };

struct IxUnknown
{
	virtual int32_t STDCALLTYPE addref(void) = 0;
	
	virtual int32_t STDCALLTYPE release(void) = 0;

    virtual long STDCALLTYPE query_interface(const GUID& guid, void** ppInterface) = 0;
};

#include "x64_ComSmartPtr.h"

X64_SMART_PTR(IxUnknown, IxUnknownPtr);