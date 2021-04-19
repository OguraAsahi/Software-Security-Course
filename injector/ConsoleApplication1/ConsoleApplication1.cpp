#include <iostream>
#include <cstdio>
#include <windows.h>
#include "detours.h"
#include "stdio.h"
#include <string>
#pragma comment(lib, "detours.lib")

#include <Shlwapi.h>
#include <string>
#include <vector>
#pragma comment(lib,"shlwapi.lib")					//注意放置的位置
using namespace std;

int temps = 0;

int main()
{
    //std::cout << "Hello World!\n";
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO);
    WCHAR DirPath[MAX_PATH + 1];
    wcscpy_s(DirPath, MAX_PATH, L"C:\\Users\\admin\\Desktop\\software-sec\\code\\Dll1\\Debug");   //DLL的文件夹
    char DLLPath[MAX_PATH + 1] = "C:\\Users\\admin\\Desktop\\software-sec\\code\\Dll1\\Debug\\Dll1.dll";    //DLL的地址
    WCHAR EXE[MAX_PATH + 1] = { 0 };


    wcscpy_s(EXE, MAX_PATH, L"C:\\Users\\admin\\Desktop\\software-sec\\detourks-master\\Release\\MSGbox.exe");       //需要注入的程序地址
    //wcscpy_s(EXE, MAX_PATH, L"C:\\Users\\admin\\Desktop\\software-sec\\CCProxy\\CCProxy.exe");       //需要注入的程序地址

    

    if (DetourCreateProcessWithDllEx(EXE, NULL, NULL, NULL, TRUE, CREATE_DEFAULT_ERROR_MODE | CREATE_SUSPENDED, NULL, DirPath, &si, &pi, DLLPath, NULL))
    {
        //MessageBoxA(NULL, "INJECT", "INJECT", NULL);
        ResumeThread(pi.hThread);
        WaitForSingleObject(pi.hProcess, INFINITE);
    }
    else
    {
        char error[100];
        sprintf_s(error, "%d", GetLastError());
    }
    return 0;
}