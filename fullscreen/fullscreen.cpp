#include <iostream>
#include <Windows.h>
#include <WinUser.h>

// #define _WIN32_WINNT 0x0500

void focusThis()
{
    HWND retVal = SetFocus(GetConsoleWindow());
    if (retVal == NULL) std::cout << "Error, could not focus." << std::endl;
}

void sendFullscreenKeys()
{
    std::cout << "Sending 'F11'" << std::endl;
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
}

int main()
{
    std::cout << "Activiation Fullscreen..." << std::endl;
    focusThis();
    sendFullscreenKeys();
    std::cout << "DONE" << std::endl;
    return 0;
}
