#include <iostream>
#include <Shlobj_core.h>
#include <Shlobj.h>
#include <Windows.h>
#include <msXml6.h>
#include "ExtractText.h"
#include "File_Analysis.h"

using namespace std;

int main()
{
    char folder_path[MAX_PATH] = "";
    BROWSEINFOA info = { 0 };

    info.hwndOwner = NULL;
    info.pszDisplayName = folder_path;
    PIDLIST_ABSOLUTE folder_pid = SHBrowseForFolderA(&info);

    WIN32_FIND_DATAA FileData;

    if (folder_pid != NULL)
    {
        if (SHGetPathFromIDListA(folder_pid, folder_path))
        {
            char copy_folder_path[MAX_PATH] = "";
            strcpy(copy_folder_path, folder_path);

            strcat(folder_path, "\\*.docx");
            HANDLE search_handle = FindFirstFileA(folder_path, &FileData);

            if (search_handle != INVALID_HANDLE_VALUE) {
                do {
                    
                    File_Analyzer sortFile(copy_folder_path, FileData);
                    sortFile.data_extraction();
                    sortFile.set_data();

                    int found_medical = sortFile.Find_Medical();
                    int found_CV = sortFile.Find_CV();
                    int found_report = sortFile.Find_Report();

                    if (found_medical > found_CV && found_medical > found_report) {
                        sortFile.Mov_to_medical();
                    }
                    else if (found_report > found_CV && found_report > found_medical) {
                        sortFile.Mov_to_report();
                    }
                    else if (found_CV > found_medical && found_CV > found_report) {
                        sortFile.Mov_to_CV();
                    }
                    else {
                        sortFile.Mov_to_other();
                    }
                    
                } while (FindNextFileA(search_handle, &FileData));
            }
        }
    }
    cout << "Completed";

    return 0;
}

