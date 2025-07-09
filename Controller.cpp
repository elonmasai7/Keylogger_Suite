#include <windows.h>
#include <ctime>

int main() {
    // Daily schedule
    time_t lastRun = 0;
    
    while(true) {
        time_t now = time(0);
        if((now - lastRun) > 86400) { // 24 hours
            lastRun = now;
            
            // Process logs
            system("RecordDecoder.exe");
            
            // Create PDF
            system("CreatePDF.exe");
            
            // Send email
            system("SendEmail.exe");
        }
        Sleep(60000); // Check every minute
    }
    return 0;
}