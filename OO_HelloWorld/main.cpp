#include "notifi.h"

#include <orbis/SystemService.h>
#include <orbis/libkernel.h>

#include <stdio.h>
#include <stddef.h>

// This function will display p_Message, then "cleanly" close the application
void fail(const char *p_Message) {
    //logKernel(LL_Fatal, "%s", p_Message);
    notifi(NULL, "%s", p_Message);
    sceSystemServiceLoadExec("exit", NULL);
}

int main()
{
    int percent = 0;

    notifi(NULL, "We are %i%% complete", percent);

    notifi(NULL, "%s", "Having \"NULL\" in the first arg means the default image will be used");

    notifi(NULL, "%s", "We can use line breaks too\nJust like this!");

    notifi("cxml://psnotification/tex_icon_champions_league", "%s", "If you missed the \"Original\" icon");

    // Sleep for 10 seconds so the system has time to display the notification
    sceKernelSleep(10);

    // "Clean" close
    sceSystemServiceLoadExec("exit", NULL);

    // We should never get here
    for (;;) {
    }

    return 0;
}