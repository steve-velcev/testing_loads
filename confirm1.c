#include <windows.h>

/*
 * Proof-of-execution canary for restricted-desktop breakout testing.
 * Displays a message box only. No payload, no persistence, no network.
 *
 * Build (on your attack host, x64 to match System32\rundll32.exe):
 *   x86_64-w64-mingw32-gcc -shared -o confirm.dll confirm.c
 *
 * Invoke in the target session:
 *   rundll32.exe C:\path\to\confirm.dll,Confirm
 */

/* Exported entry point in the exact signature rundll32 expects. */
__declspec(dllexport) void Confirm(void)
{
    MessageBoxA(NULL, "rundll32 exec confirmed", "Breakout PoC", MB_OK | MB_ICONINFORMATION);
}

/* Optional: also fires on load, regardless of which export is named.
   Simplest confirmation, but keep the body trivial (loader-lock). */
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH) {
        MessageBoxA(NULL,
                    "rundll32 DLL loaded (DllMain)",
                    "Breakout PoC",
                    MB_OK | MB_ICONINFORMATION);
    }
    return TRUE;
}
