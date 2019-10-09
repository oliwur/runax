//
// Created by oliwu on 09/10/2019.
//

#include <windows.h>
#include <psapi.h>
#include <stdio.h>

void printProcIdAndName(DWORD procId) {
    wchar_t procName[MAX_PATH] = L"<unknown>";

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                  FALSE,
                                  procId
    );

    if (NULL != hProcess) {
        HMODULE hmod;
        DWORD needed;

        if (EnumProcessModules(hProcess, &hmod, sizeof(hmod), &needed)) {
            GetModuleBaseNameW(hProcess, hmod, procName, sizeof(procName) / sizeof(wchar_t));
        }
    }

    wprintf(L"%lu\t\t%s\n", procId, &procName);

    CloseHandle(hProcess);
}

int main(int argc, char **argv) {
    DWORD processes[1024];
    DWORD needed;
    DWORD procCount = 0;

    if (!EnumProcesses(processes, sizeof(processes), &needed)) {
        DWORD error = GetLastError();
        printf("shit happens %lu\n", error);
    }

    procCount = needed / sizeof(DWORD);

    for (unsigned int i = 0; i < procCount; i++) {
        if (processes[i] != 0) {
            printProcIdAndName(processes[i]);
        }
    }
}
