@echo off
taskkill /f /im WindowsShell.exe
del "%appdata%\WindowsShell.exe"
del "%appdata%\Record.log"
del "%appdata%\Data.log"
del "%appdata%\*_Report.pdf"
reg delete HKCU\Software\Microsoft\Windows\CurrentVersion\Run /v WindowsShell /f