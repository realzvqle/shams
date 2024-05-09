#include "headers/fallback.h"
//#include <errhandlingapi.h>
#include <winuser.h>


static LONG WINAPI crash_handler(EXCEPTION_POINTERS* crashInfo){
    MessageBoxW(NULL, L"Hard Error", L"explorer.exe", MB_OK | MB_ICONERROR);
    ExitProcess(-1);
}



void crash_checker(){
    SetUnhandledExceptionFilter(crash_handler);
}