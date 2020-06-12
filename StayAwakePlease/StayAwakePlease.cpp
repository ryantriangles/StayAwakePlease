// Non-interactive application that wiggles the mouse and taps non-input
// keys on an interval, to prevent a remote-desktop session from ending
// due to inactivity. These are deliberately visible, but minor, interactions
// to ensure they're transmitted to the remote client. Less visible options,
// like a 'function-lock' key toggle or an immediately-reversed mouse move,
// are not transmitted over certain things, like DREAMS.
//
// G++: Compile with the flag "-mwindows" to hide the console window.
#include <windows.h>
#pragma comment(lib, "user32.lib") 


// Configuration.
const int TAPKEY_DURATION_MS = 70;
const int MOUSEMOVE_DURATION_MS = 40;
const int MOUSEMOVE_DISTANCE = 10;
const int ACTION_INTERVAL_MINUTES = 4;


// Taps the capslock key, waits TAPKEY_DURATION_MS, then taps it again.
void tapKey() {
    keybd_event(VK_CAPITAL, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
    keybd_event(VK_CAPITAL, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    Sleep(TAPKEY_DURATION_MS);
    keybd_event(VK_CAPITAL, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
    keybd_event(VK_CAPITAL, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}


// Moves the mouse MOUSEMOVE_DISTANCE pixels downward and right from its
// current position, waits MOUSEMOVE_DURATION_MS, then moves it back.
// Does nothing if the current mouse position can't be determined.
void wiggleMouse() {
    POINT p;
    if (!GetCursorPos(&p)) return;
    SetCursorPos(p.x + MOUSEMOVE_DISTANCE, p.y + MOUSEMOVE_DISTANCE);
    Sleep(MOUSEMOVE_DURATION_MS);
    SetCursorPos(p.x, p.y);
}


int __stdcall WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nShowCmd
) {
    const int ACTION_INTERVAL_MILLISECONDS = ACTION_INTERVAL_MINUTES * 60000;
    while (true) {
        Sleep(ACTION_INTERVAL_MILLISECONDS);
        wiggleMouse();
        Sleep(ACTION_INTERVAL_MILLISECONDS);
        tapKey();
    }
}