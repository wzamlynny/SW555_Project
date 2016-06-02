/**
 * Weronika Zamlynny
 * CS 555 - Project 02
 * Reading from a GEDCOM File
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/**
 * Splits the input string by spaces, removing '\r'
 */
vector<string> parseLine(string line) {
    vector<string> res;
    string buffer = "";
    for (int i = 0, j = 0 ; i < line.length(); i++) {
        if (line[i] == ' ') {
            // Add to vector and clear buffer
            res.push_back(buffer);
            buffer = "";
        }
        else if (line[i] != '\r') {
            buffer += line[i];
        }
    }
    if (buffer != "") {
        res.push_back(buffer);
    }
    return res;
}

/**
 * Checks that the tag is in the list of valid tags for its level 
 */
string validTag(string level, string tag) {
    string error = "Invalid Tag";
    if (level == "0") {
        string validTags [] = {"INDI","FAM","HEAD","TRLR","NOTE"};
        for (int i = 0; i < sizeof(validTags)/sizeof(validTags[0]); i++) {
            if (tag == validTags[i]){
                return tag;
            }
        }
        return error;
    }
    if (level == "1") {
        string validTags [] = {"NAME","SEX","BIRT","DEAT","FAMC","FAMS","MARR","HUSB","WIFE","CHIL","DIV"};
        for (int i = 0; i < sizeof(validTags)/sizeof(validTags[0]); i++) {
            if (tag == validTags[i]){
                return tag;
            }
        }
        return error;
    }
    if (level == "2") {
        string validTags [] = {"DATE"};
        for (int i = 0; i < sizeof(validTags)/sizeof(validTags[0]); i++) {
            if (tag == validTags[i]){
                return tag;
            }
        }
        return error;
        
    }
    else {
        return error;
    }
}
 
int main() {
    ifstream gedFile ("Project01_Zamlynny.ged");
    ofstream outputFile;
    
    string line, level, tag;
    
    if (gedFile.is_open()) {
        outputFile.open("project02_output.txt", ios::out);
        if (outputFile.is_open()) {
            
            while ( getline (gedFile,line) ) {
                // Print the original line
                outputFile << line << "\n";
                
                // Parse Line for details
                vector<string> parsed = parseLine (line);
                level = parsed[0];
                tag = parsed[1];
                if (level == "0") {
                    // If a unique Identifier
                    if (tag[0] == '@') {
                        tag = parsed[2];
                    }
                }
                
                // Print the level number of each line
                outputFile << level << "\r\n";
                // Print the tag of each line and check if valid
                outputFile << validTag(level, tag) << "\r\n";
            }
            
            outputFile.close();
        }
        else cout << "Unable to open output file.";
        gedFile.close();
    }
    else cout << "Unable to open GEDCOM file."; 
    
    return 0;
}