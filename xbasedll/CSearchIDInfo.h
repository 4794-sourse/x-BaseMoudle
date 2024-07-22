#pragma once
#include "ISearchIDInfo.h"

class CSearchIDInfo : public ISearchIDInfo {
public:
	CSearchIDInfo();
	void GetIDInfoPath(const wchar_t* ID, const wchar_t* path);
};