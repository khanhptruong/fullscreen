#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <strsafe.h>

//#define _WIN32_WINNT 0x0500 //see SetFocus documentation

void ErrorExit(LPCTSTR lpszFunction)
{
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw);
}

void focusThis()
{
    HWND conWin = GetConsoleWindow();
    if (conWin == NULL)
    {
        std::cout << "No console window associated." << std::endl;
        ErrorExit(TEXT("GetProcessId"));
        return;
    }

    //HWND retVal = SetFocus(conWin);
    //if (retVal == NULL)
    //{
    //    std::cout << "Error SetFocus()" << std::endl;
    //    ErrorExit(TEXT("GetProcessId"));
    //}

    bool retVal = SetForegroundWindow(conWin);
    if (retVal == 0)
    {
        std::cout << "Error SettingForegroundWindow()" << std::endl;
        ErrorExit(TEXT("GetProcessId"));
    }

    std::cout << "Focused Window" << std::endl;
}

void sendFullscreenKeys()
{
    INPUT inputs[2] = {};
    ZeroMemory(inputs, sizeof(inputs));

    //inputs[0].type = INPUT_KEYBOARD;
    //inputs[0].ki.wVk = VK_LMENU;

    //inputs[1].type = INPUT_KEYBOARD;
    //inputs[1].ki.wVk = VK_RETURN;

    //inputs[2].type = INPUT_KEYBOARD;
    //inputs[2].ki.wVk = VK_RETURN;
    //inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

    //inputs[3].type = INPUT_KEYBOARD;
    //inputs[3].ki.wVk = VK_LMENU;
    //inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_F11;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = VK_F11;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (uSent != ARRAYSIZE(inputs))
    {
        std::cout << "SendInput failed: 0x%x" << std::endl;
    }
    std::cout << "Sent 'F11'" << std::endl;
}

int main()
{
    std::cout << "Activating Fullscreen..." << std::endl;
    focusThis();
    sendFullscreenKeys();
    std::cout << "DONE" << std::endl;
    return 0;
}
