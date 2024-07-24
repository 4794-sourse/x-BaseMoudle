#pragma once
#include <system_error> 
#include "ISearchIDInfo.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include <filesystem>

#define BASECONFIG "BaseConfig.xml"

class CSearchIDInfo : public ISearchIDInfo {
public:
	CSearchIDInfo();
	virtual bool GetIDInfoToFilePath(const char* ID, std::wstring &Path);
	virtual bool GetIDInfoToMoudlePath(const char* ID, std::wstring &Path);
	virtual bool GetIDInfoToUrl(const char* ID, std::wstring &Url);
	virtual bool GetIDInfoToCommon(const char* ID, std::wstring &Info);
private:
	bool GetCommonSearchIDInfo(const char* Key, const char* ID, std::wstring &Info);
private:
	std::shared_ptr<rapidxml::file<>> m_xmlFile;
	std::shared_ptr<rapidxml::xml_document<>> m_docInfo;
};