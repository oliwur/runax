//
// Created by oliwu on 09/09/2019.
//
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#include "runAsX.h"

void DisplayError(LPWSTR pszAPI) {
    LPVOID lpvMessageBuffer;

    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
                  NULL, GetLastError(),
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPWSTR) &lpvMessageBuffer, 0, NULL);

    wprintf(L"ERROR: API        = %s.\n", pszAPI);
    wprintf(L"       error code = %d.\n", GetLastError());
    wprintf(L"       message    = %s.\n", (LPWSTR) lpvMessageBuffer);

    LocalFree(lpvMessageBuffer);
}

void startProcessAsUser(wchar_t *user,
                        wchar_t *password,
                        wchar_t *domain,
                        bool netonly,
                        wchar_t *executable,
                        wchar_t *args) {
    DWORD logonFlags = 0;
    if (netonly) {
        logonFlags = LOGON_NETCREDENTIALS_ONLY;
    } else {
        logonFlags = LOGON_WITH_PROFILE;
    }

    STARTUPINFOW startupInfo = {0};
    PROCESS_INFORMATION processInfo = {0};

    startupInfo.cb = sizeof(STARTUPINFO);

    if (!CreateProcessWithLogonW(
            user,
            domain,
            password,
            logonFlags,
            executable,
            args,
            0,
            NULL,
            NULL,
            &startupInfo,
            &processInfo
    )) {
        DisplayError(L"CreateProcessWithLogonW");
    }
}
