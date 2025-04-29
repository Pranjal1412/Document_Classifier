#pragma once
#include <msXml6.h>

#import <msxml6.dll> 
using namespace MSXML2;

class word_parser {

    char temp_folder_path[MAX_PATH] = "";
    char new_folder_path[MAX_PATH] = "";
    char temp_file_path[MAX_PATH] = "";
    char copy_file_path[MAX_PATH] = "";
    char command[MAX_PATH] = "-xf ";
    char xml_file[MAX_PATH] = "";
    long org_length = 0;

    

public:
    char* all_text;
    char newFolderPath[MAX_PATH] = "";
    char FileMov_path[MAX_PATH] = "";
    char destination[MAX_PATH] = "";
    char Filename[MAX_PATH] = "";

    //the constructor initializes all the file paths
    word_parser(char folder_path[], WIN32_FIND_DATAA FileData) {
        GetTempPathA(MAX_PATH, temp_folder_path);

        strcpy(newFolderPath, folder_path);
        strcpy(destination, folder_path);
        strcpy(Filename, FileData.cFileName);
        
        strcpy(FileMov_path, folder_path);
        strcat(FileMov_path, "\\");
        strcat(FileMov_path, FileData.cFileName);

        strcpy(temp_file_path, temp_folder_path);
        strcat(temp_file_path, FileData.cFileName);

        long length = strlen(temp_file_path);
        temp_file_path[length - 5] = 0;
        strcpy(new_folder_path, temp_file_path);
        strcat(temp_file_path, ".zip");

        strcat(copy_file_path, folder_path);
        strcat(copy_file_path, "\\");
        strcat(copy_file_path, FileData.cFileName);
    }

    
    void data_extraction();
    void parse_data();
    void process_P(MSXML2::IXMLDOMNodePtr node);
    void process_R(MSXML2::IXMLDOMNodePtr node);
    void process_Tbl(MSXML2::IXMLDOMNodePtr node);
    void process_TR(MSXML2::IXMLDOMNodePtr node);
    void process_TC(MSXML2::IXMLDOMNodePtr node);
    void append_text(char*, long);
    void DeleteDirectory(LPCSTR);

    ~word_parser() {
        DeleteDirectory(new_folder_path);
        DeleteFileA(temp_file_path);
    }

};



