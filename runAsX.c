//
// Created by oliwu on 09/09/2019.
//
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <userenv.h>

#include "runAsX.h"

void DisplayError(LPWSTR pszAPI) {
    LPVOID lpvMessageBuffer;

    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
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
    DWORD logonType = 0;
    DWORD logonFlags = 0;
    if (netonly) {
        logonType = LOGON32_LOGON_NEW_CREDENTIALS;
        logonFlags = LOGON_NETCREDENTIALS_ONLY;
    } else {
        logonType = LOGON32_LOGON_INTERACTIVE;
        logonFlags = LOGON_WITH_PROFILE;
    }

    HANDLE hToken;
    LPVOID lpvEnv;
    STARTUPINFOW startupInfo = {0};
    PROCESS_INFORMATION processInfo = {0};

    if (!LogonUserW(user,
                    domain,
                    password,
                    logonType,
                    LOGON32_PROVIDER_DEFAULT,
                    &hToken)
            ) {
        DisplayError(L"LogonUser");
    }

    if (!CreateEnvironmentBlock(&lpvEnv,
                                hToken,
                                TRUE)
            ) {
        DisplayError(L"CreateEnvironmentBlock");
    }

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

    printf("proc id:     %ld\n", processInfo.dwProcessId);
    printf("proc handle: %p\n", processInfo.hProcess);

    WaitForSingleObject(processInfo.hProcess, 5000);

    TerminateProcess(processInfo.hProcess, 0);

    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);
    CloseHandle(hToken);
}
