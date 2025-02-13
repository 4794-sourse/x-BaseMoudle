#include "pch.h"
#include <iostream>
#include "CSearchIDInfo.h"


CSearchIDInfo::CSearchIDInfo() {

}
CSearchIDInfo::~CSearchIDInfo() {
}

bool CSearchIDInfo::GetIDInfoToFilePath(const char* ID, std::wstring &Path) {
    
    return GetCommonSearchIDInfo("File", ID, Path);
}

bool CSearchIDInfo::GetIDInfoToMoudlePath(const char* ID, std::wstring& Path) {
    
    return GetCommonSearchIDInfo("Module", ID, Path);
 }

bool CSearchIDInfo::GetIDInfoToUrl(const char* ID, std::wstring &Url) {
    
    return GetCommonSearchIDInfo("Url", ID, Url);
 }

bool CSearchIDInfo::GetIDInfoToCommon(const char* ID, std::wstring &Info) {
    
    return GetCommonSearchIDInfo("Common", ID, Info);
 }

bool CSearchIDInfo::GetCommonSearchIDInfo(const char* Key, const char* ID, std::wstring &Info) {
    
    bool result = false;
    try {
        std::error_code ec;
        std::filesystem::path xml_path(BASECONFIG);
        if (!std::filesystem::exists(xml_path, ec)) {
            return result;
        }
        m_xmlFile = std::make_shared<rapidxml::file<>>(BASECONFIG);
        m_docInfo = std::make_shared<rapidxml::xml_document<>>();
        m_docInfo->parse<0>(m_xmlFile->data());

        rapidxml::xml_node<>* root = m_docInfo->first_node("Value");

        if (root) {

            for (rapidxml::xml_node<>* module = root->first_node(); module; module = module->next_sibling()) {
                
                if (strcmp(Key, module->name()) == 0) {
                    
                    for (rapidxml::xml_node<>* item = module->first_node("Item"); item; item = item->next_sibling("Item")) {
                        
                        auto nodekey = item->first_attribute("Key")->value();
                        auto nodevalue = item->first_attribute("Value")->value();
                        if (nodekey && nodevalue && strcmp(ID, nodekey) == 0) {

                            int bufSize = MultiByteToWideChar(CP_ACP, 0, nodevalue, -1, NULL, 0);
                            if (bufSize <= 0) return result;
                            Info.resize(bufSize - 1);
                            MultiByteToWideChar(CP_ACP, 0, nodevalue, -1, &Info[0], bufSize);
                            return true;
                        }
                    }
                }   
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return result;
 }