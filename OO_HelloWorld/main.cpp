#include "graphics.h"
#include "log.h"
#include "notifi.h"
#include "png.h"
#include <math.h>
#include <orbis/SystemService.h>
#include <orbis/libkernel.h>
#include <sstream>
#include <stddef.h>
#include <stdio.h>

// Dimensions
#define FRAME_WIDTH  1920
#define FRAME_HEIGHT 1080
#define FRAME_DEPTH  4

// Font information
#define FONT_SIZE_LARGE 128
#define FONT_SIZE_SMALL 64

// Logging
std::stringstream debugLogStream;

// Background and foreground colors
Color bgColor;
Color fgColor;

// Font faces
FT_Face fontLarge;
FT_Face fontSmall;

int frameID = 0;

int main()
{
    int rc;
    int video;
    int curFrame = 0;

    notifi(NULL, "Github 仓库地址：\n%s", "https://github.com/SummerFalls/OO_HelloWorld");
    notifi(NULL, "%s", "通知信息可换行\nJust like this!");
    notifi("cxml://psnotification/tex_icon_champions_league", "通知图标示例...");

    // No buffering
    setvbuf(stdout, NULL, _IONBF, 0);

    DEBUGLOG << "正在创建 2D 场景...";
    auto scene = new Scene2D(FRAME_WIDTH, FRAME_HEIGHT, FRAME_DEPTH);

    if (!scene->Init(0xC000000, 2))
    {
        notifi(NULL, "2D 场景初始化失败...");
        for (;;)
            ;
    }

    // Set colors
    bgColor          = { 0, 0, 0 };
    fgColor          = { 255, 255, 255 };

    const char *font = "/app0/assets/fonts/NotoSans-Regular.ttf";

    notifi(NULL, "Initializing font (%s)", font);

    if (!scene->InitFont(&fontLarge, font, FONT_SIZE_LARGE))
    {
        notifi(NULL, "Failed to initialize large font (%s)", font);
        for (;;)
            ;
    }

    if (!scene->InitFont(&fontSmall, font, FONT_SIZE_SMALL))
    {
        notifi(NULL, "Failed to initialize small font (%s)", font);
        for (;;)
            ;
    }

    DEBUGLOG << "Entering draw loop...";
    notifi(NULL, "进入绘制循环...");

    for (;;)
    {
        const char *textLarge = "SummerFalls\nHello, World!";
        const char *textSmall = "Built with the OpenOrbis toolchain (in C++!)\n\nGithub: https://github.com/SummerFalls/OO_HelloWorld";

        scene->DrawText((char *)textLarge, fontLarge, 150, 400, bgColor, fgColor);
        scene->DrawText((char *)textSmall, fontSmall, 150, 750, bgColor, fgColor);

        // Submit the frame buffer
        scene->SubmitFlip(frameID);
        scene->FrameWait(frameID);

        // Swap to the next buffer
        scene->FrameBufferSwap();
        frameID++;
    }

    return 0;
}