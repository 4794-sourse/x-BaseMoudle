#pragma once
#include "framework.h"
#include "x64_ComObject.h"

struct ISearchIDInfo : IxUnknown {

	virtual bool GetIDInfoToFilePath(const char* ID, std::wstring &Path) = 0;
	virtual bool GetIDInfoToMoudlePath(const char* ID, std::wstring &Path) = 0;
	virtual bool GetIDInfoToUrl(const char* ID, std::wstring &Url) = 0;
	virtual bool GetIDInfoToCommon(const char* ID, std::wstring &Info) = 0;
};
// {2500C8D6-AE5B-476D-9087-EAC911628046}
static const GUID IID_ISearchIDInfo =
{ 0x2500c8d6, 0xae5b, 0x476d, { 0x90, 0x87, 0xea, 0xc9, 0x11, 0x62, 0x80, 0x46 } };

X64_SMART_PTR(ISearchIDInfo, ISearchIDInfoPtr);