#include "notifi.h"

#include <orbis/SystemService.h>
#include <orbis/libkernel.h>

#include <stdio.h>
#include <stddef.h>

// This function will display p_Message, then "cleanly" close the application
void fail(const char *p_Message)
{
    // logKernel(LL_Fatal, "%s", p_Message);
    notifi(NULL, "%s", p_Message);
    sceSystemServiceLoadExec("exit", NULL);
}

int main()
{
    int sleepTime = 20;

    notifi(NULL, "%i 秒后自动退出本示例程序...", sleepTime);

    notifi(NULL, "%s", "通知信息可换行\nJust like this!");

    notifi("cxml://psnotification/tex_icon_champions_league", "%s", "If you missed the \"Original\" icon");

    sceKernelSleep(sleepTime);

    // "Clean" close
    sceSystemServiceLoadExec("exit", NULL);

    // We should never get here
    for (;;) {
    }

    return 0;
}