#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <orbis/libkernel.h>
#include <orbis/ScePad.h>

static const char* games[] =
{
    "My Game 1",
    "My Game 2",
    "My Game 3",
    "My Game 4"
};

static const int GAME_COUNT = 4;

int main()
{
    scePadInit();

    int handle = scePadOpen(
        0,
        SCE_PAD_PORT_TYPE_LOCAL,
        0,
        NULL
    );

    int selected = 0;

    printf("\n");
    printf("=================================\n");
    printf("       PISSCOU GAME STORE\n");
    printf("=================================\n");
    printf("\n");

    printf("Games:\n\n");

    for (int i = 0; i < GAME_COUNT; i++)
    {
        if (i == selected)
            printf(" > %s\n", games[i]);
        else
            printf("   %s\n", games[i]);
    }

    printf("\n");
    printf("D-Pad : Navigate\n");
    printf("X     : Download\n");
    printf("O     : Back\n");
    printf("\n");

    while (1)
    {
        ScePadData data;

        if (handle >= 0)
        {
            int ret = scePadRead(handle, &data, 1);

            if (ret > 0)
            {
                if (data.buttons & SCE_PAD_BUTTON_UP)
                {
                    if (selected > 0)
                        selected--;

                    printf("Selected: %s\n", games[selected]);
                }

                if (data.buttons & SCE_PAD_BUTTON_DOWN)
                {
                    if (selected < GAME_COUNT - 1)
                        selected++;

                    printf("Selected: %s\n", games[selected]);
                }

                if (data.buttons & SCE_PAD_BUTTON_CROSS)
                {
                    printf("DOWNLOAD: %s\n", games[selected]);
                    printf("Download system will be added next.\n");
                }

                if (data.buttons & SCE_PAD_BUTTON_CIRCLE)
                {
                    printf("BACK\n");
                }
            }
        }

        sceKernelUsleep(16000);
    }

    return 0;
}
