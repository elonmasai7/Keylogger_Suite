#include <windows.h>
#include <fstream>
#include <string>

void GeneratePDF() {
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);
    GetComputerNameA(computerName, &size);
    
    std::string cmd = "powershell -Command \""
        "$log = Get-Content -Path $env:APPDATA\\Data.log -Raw; "
        "Add-Type -AssemblyName System.Drawing; "
        "$font = New-Object System.Drawing.Font('Arial', 12); "
        "$bmp = New-Object System.Drawing.Bitmap(1, 1); "
        "$graphics = [System.Drawing.Graphics]::FromImage($bmp); "
        "$width = $graphics.MeasureString($log, $font).Width; "
        "$height = $graphics.MeasureString($log, $font).Height; "
        "$bmp.Dispose(); "
        "$bmp = New-Object System.Drawing.Bitmap([int]$width, [int]$height); "
        "$graphics = [System.Drawing.Graphics]::FromImage($bmp); "
        "$graphics.Clear([System.Drawing.Color]::White); "
        "$graphics.DrawString($log, $font, [System.Drawing.Brushes]::Black, 0, 0); "
        "$bmp.Save('$env:APPDATA\\" + std::string(computerName) + ".pdf', [System.Drawing.Imaging.ImageFormat]::Pdf);\"";
    
    system(cmd.c_str());
}