#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "ExtractText.h"
using namespace std;

class File_Analyzer : public word_parser{

    string Final_text;

    string toLower(const string& text) {
        string textLower = text;
        transform(textLower.begin(), textLower.end(), textLower.begin(),
            [](unsigned char c) { return tolower(c); });
        return textLower;
    }

    vector<string> Medical = { "hospital",  "medicine",  "doctor",  "treatment",
                              "diagnosis", "surgery",   "blood",   "patient",
                              "referral",  "follow",    "symptom", "medication",
                              "result",    "consult",   "test",    "type",
                              "sample",   "discharge", "history", "disorder"};
    
    vector<string> Report = { "references", "topic",        "members", "Analysis","conclusion", "introduction", "contribution","impact",   "education",    "achievements",
                             "contents",    "summary",      "publication",
                             "abstract", "Bibliography"};

    vector<string> CV = { "education", "club",
        "qualification", "experience", "employment", "achievement", "skills",
        "hobbies",       "interests",  "references",  "email",       "profile",
        "linkedin",      "github",     "cgpa",        "sgpa",        "gpa" };

public:
    File_Analyzer(char folder_path[], WIN32_FIND_DATAA FileData) : word_parser(folder_path, FileData){}
    void set_data();
    int Find_Medical();
    int Find_CV();
    int Find_Report();
    void Mov_to_CV();
    void Mov_to_medical();
    void Mov_to_report();
    void Mov_to_other();

};