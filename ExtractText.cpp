#include "ExtractText.h"
#include <string>
#include <tchar.h>


using namespace std;

void word_parser::data_extraction() {
    
    if (CopyFileA(copy_file_path, temp_file_path, false)) {

        CreateDirectoryA(new_folder_path, NULL);
        strcat(command, "\"");
        strcat(command, temp_file_path);
        strcat(command, "\"");
        strcat(command, " -C \"");
        strcat(command, new_folder_path);
        strcat(command, "\"");

        ShellExecuteA(NULL, "open", "C:\\WINDOWS\\system32\\tar.exe", command, NULL, 0);

        for (long i = 0; i < 3; i++)
        {
            Sleep(100);
            this->parse_data();
            if (this->all_text)
                break;
        }
    }
}

void word_parser::parse_data() 
{

    HRESULT hr = CoInitialize(NULL);
    if (SUCCEEDED(hr))
    {
        MSXML2::IXMLDOMDocument2Ptr xmlDoc;
        hr = xmlDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60),
            NULL, CLSCTX_INPROC_SERVER);
        if (SUCCEEDED(hr))
        {
            char xml_file[MAX_PATH] = "";
            strcpy(xml_file, new_folder_path);
            strcat(xml_file, "\\word\\document.xml");
            wchar_t filePathWChar[MAX_PATH] = L"";

            MultiByteToWideChar(CP_UTF8, 0, xml_file, -1, filePathWChar, MAX_PATH);
            if (xmlDoc->load(filePathWChar) == VARIANT_TRUE)
            {
                MSXML2::IXMLDOMElementPtr spRoot = xmlDoc->documentElement; //root node
                _bstr_t node_name = spRoot->GettagName();
                MSXML2::IXMLDOMNodePtr node = spRoot->GetfirstChild();
                if(node)
                {
                    while (node) {
                        node_name = node->GetnodeName();
                        if (!lstrcmpW(node_name, L"w:body")) {
                            break;
                        }
                        node = node->GetnextSibling();
                    }

                    node = node->GetfirstChild();  //BODY 

                    while(node) {
                        node_name = node->GetnodeName();
                         if (!lstrcmpW(node_name, L"w:p")) {
                            process_P(node);
                         }
                         else if (!lstrcmpW(node_name, L"w:tbl")) {
                             process_Tbl(node);
                         }

                         node = node->GetnextSibling();
                     
                     }

                }
            }
            else {
                long a = GetLastError();
                a = 10;
            }
        }
    }
}

void word_parser::process_P(MSXML2::IXMLDOMNodePtr node) {

    _bstr_t node_name;

    node = node->GetfirstChild();

    while(node)
    {
        node_name = node->GetnodeName();

        if (!lstrcmpW(node_name, L"w:r")) {
            process_R(node);
        }
        node = node->GetnextSibling();
    }

}

void word_parser::process_R(MSXML2::IXMLDOMNodePtr node) 
{
    _bstr_t node_name;
    node = node->GetfirstChild();

    while (node)
    {
        node_name = node->GetnodeName();
        
        if (!lstrcmpW(node_name, L"w:t")) {
            _bstr_t text = node->Gettext();
            if (text.length())
            {
                long length = lstrlenW(text);
                char* convert_text = (char*)calloc(2 * length, sizeof(char));

                if (convert_text)
                {
                    WideCharToMultiByte(CP_UTF8, 0, text, length, convert_text, length*2, NULL, NULL);
                    append_text(convert_text, length);
                    free(convert_text);
                }
            }
        }
        node = node->GetnextSibling();
    }
}

void word_parser::append_text(char* converted_txt, long len) {
    if (all_text == NULL) {
        all_text = (char*)calloc(len+1, sizeof(char));
        memmove(all_text, converted_txt, len);
        org_length = len;
    }
    else {
        all_text = (char*)realloc(all_text, org_length + len+1);
        memmove(all_text + org_length, converted_txt, len);
        org_length += len;
    }
    if (all_text)
        *(all_text + org_length) = 0;
}

void word_parser::process_Tbl(MSXML2::IXMLDOMNodePtr node) {

    _bstr_t node_name;
    node = node->GetfirstChild();

    while (node)
    {
        node_name = node->GetnodeName();

        if (!lstrcmpW(node_name, L"w:tr")) {
            process_TR(node);
        }
        node = node->GetnextSibling();
    }
}

void word_parser::process_TR(MSXML2::IXMLDOMNodePtr node) 
{

    _bstr_t node_name;
    node = node->GetfirstChild();

    while (node)
    {
        node_name = node->GetnodeName();

        if (!lstrcmpW(node_name, L"w:tc")) {
            process_TC(node);
        }
        node = node->GetnextSibling();
    };
}
void word_parser::process_TC(MSXML2::IXMLDOMNodePtr node) 
{
    _bstr_t node_name;
    node = node->GetfirstChild();

    while (node)
    {
        node_name = node->GetnodeName();
        if (!lstrcmpW(node_name, L"w:p")) {
            process_P(node);
        }
        node = node->GetnextSibling();
    }
}
void word_parser::DeleteDirectory(LPCSTR FolderPathname) {

    WIN32_FIND_DATAA file;
    char temp_folder_path[MAX_PATH] = "";

    strcpy(temp_folder_path, FolderPathname);
    strcat(temp_folder_path, "\\*");

    HANDLE handle = FindFirstFileA(temp_folder_path, &file);

    do {

        if (!(!strcmp(file.cFileName, ".") || !strcmp(file.cFileName, "..")))
        {
            char path[MAX_PATH] = "";
            strcpy(path, FolderPathname);
            strcat(path, "\\");
            strcat(path, file.cFileName);

            if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                DeleteDirectory(path);
            }
            else {
                DeleteFileA(path);
            }
        }

    } while (FindNextFileA(handle, &file));

    RemoveDirectoryA(FolderPathname);
}