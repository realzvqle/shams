#include "headers/warning.h"
#include <winuser.h>



BOOL run_warning(){
    if(MessageBoxW(NULL, L"This Malware Will Damage Your Machine\n\nAre You Sure You Want to Continue?", L"my revenge will come", MB_YESNO | MB_ICONWARNING) == IDYES){
        if(MessageBoxW(NULL, L"This Is Your Last Warning\n\nStill Wanna Continue?", L"you ruined my life, my hopes", MB_YESNO | MB_ICONWARNING) == IDYES){
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else {
        return FALSE;
    }
    return FALSE;
}
