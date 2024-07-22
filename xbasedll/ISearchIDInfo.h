#pragma once
#include "framework.h"

class ISearchIDInfo {
public:
	virtual void GetIDInfoPath(const wchar_t* ID, const wchar_t* path) = 0;
};
// {2500C8D6-AE5B-476D-9087-EAC911628046}
static const GUID IID_SearchIDInfo =
{ 0x2500c8d6, 0xae5b, 0x476d, { 0x90, 0x87, 0xea, 0xc9, 0x11, 0x62, 0x80, 0x46 } };