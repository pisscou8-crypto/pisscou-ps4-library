#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <orbis/libkernel.h>
#include <orbis/ScePad.h>
#include <orbis/SceVideoOut.h>

int main()
{
    scePadInit();

    int handle = scePadOpen(0, SCE_PAD_PORT_TYPE_LOCAL, 0, NULL);

    printf("Pisscou PS4 Library\n");
    printf("D-Pad: Navigate\n");
    printf("X: Select\n");
    printf("O: Back\n");

    while (1)
    {
        ScePadData data;

        if (handle >= 0)
        {
            int ret = scePadRead(handle, &data, 1);

            if (ret > 0)
            {
                if (data.buttons & SCE_PAD_BUTTON_CROSS)
                    printf("SELECT\n");

                if (data.buttons & SCE_PAD_BUTTON_CIRCLE)
                    printf("BACK\n");

                if (data.buttons & SCE_PAD_BUTTON_UP)
                    printf("UP\n");

                if (data.buttons & SCE_PAD_BUTTON_DOWN)
                    printf("DOWN\n");
            }
        }

        sceKernelUsleep(16000);
    }

    return 0;
}
