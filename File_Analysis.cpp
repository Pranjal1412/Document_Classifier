#include "File_Analysis.h"
#include <algorithm>
#include <iostream>
#include <string>

int File_Analyzer::Find_Medical() {
    long foundMedical = 0;
    string textLower = toLower(Final_text);

    for (const string& word : Medical) {
        if (textLower.find(word) != string::npos) {
            foundMedical++;
        }
    }

    return foundMedical;
}
int File_Analyzer::Find_CV() {
    long foundCV = 0;
    string textLower = toLower(Final_text);
    for (const string& word : CV) {
        if (textLower.find(word) != string::npos) {
            foundCV++;
        }
    }
    
    return foundCV;
}
int File_Analyzer::Find_Report() {
    int foundReport = 0;
    string textLower = toLower(Final_text);
    for (const string& word : Report) {
        if (textLower.find(word) != string::npos) {
            foundReport++;
        }
    }
    return foundReport;
}

void File_Analyzer::set_data() 
{
    if (all_text)
    {
        Final_text = all_text;
        free(all_text);
    }
    
}

void File_Analyzer::Mov_to_CV() {
    strcat(newFolderPath, "\\CV");
    CreateDirectoryA(newFolderPath, NULL);
    strcat(destination, "\\CV\\");
    strcat(destination, Filename);
    MoveFileA(FileMov_path, destination);

}

void File_Analyzer::Mov_to_medical() {
    strcat(newFolderPath, "\\Medical");
    CreateDirectoryA(newFolderPath, NULL);
    strcat(destination, "\\Medical\\");
    strcat(destination, Filename);
    MoveFileA(FileMov_path, destination);
}

void File_Analyzer::Mov_to_report() {
    strcat(newFolderPath, "\\Report");
    CreateDirectoryA(newFolderPath, NULL);
    strcat(destination, "\\Report\\");
    strcat(destination, Filename);
    MoveFileA(FileMov_path, destination);
}

void File_Analyzer::Mov_to_other() {
    strcat(newFolderPath, "\\Others");
    CreateDirectoryA(newFolderPath, NULL);
    strcat(destination, "\\Others\\");
    strcat(destination, Filename);
    MoveFileA(FileMov_path, destination);
}
