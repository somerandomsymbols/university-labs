#include <bits/stdc++.h>
#include "windows.h"
#include "psapi.h"

using namespace std;

int main()
{
    while (true)
    {
        system("CLS");
        DWORD processes[1024], processes_num, process_id = -1;
        char szProcessName[MAX_PATH] = "<unknown>";

        if (!EnumProcesses( processes, sizeof(processes), &processes_num ))
        {
            return 1;
        }

        processes_num /= sizeof(DWORD);

        for (int i = 0; i < processes_num; ++i)
        {
            HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, processes[i]);

            if (NULL != hProcess )
            {
                HMODULE hMod;
                DWORD cbNeeded;

                if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) )
                {
                    GetModuleBaseName( hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR) );

                    if (!strcmp(szProcessName,
                        "labprocess.exe"))
                    {
                        process_id = processes[i];
                        break;
                    }
                }
            }

            CloseHandle(hProcess);
        }

        if (process_id == -1)
        {
            cout << "Process inactive" << endl;
        }
        else
        {
            HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,process_id);
            DWORD dwExitCode = 0;

            GetExitCodeProcess(hProcess, &dwExitCode);
            CloseHandle(hProcess);

            cout << process_id << "/" << processes_num << " " << szProcessName << " ";

            if (dwExitCode == STILL_ACTIVE)
                cout << "active" << endl;
            else
                cout << "ended with code " << dwExitCode << endl;
        }

        Sleep(1000);
    }
}
