/* func_0205a370 @ 0x0205a370, 0xaa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204ee7c(void *data, int x, int y);

int func_0205a370(int *left, int *right, int *top, int *bottom, void *data)
{
    *top = 16;
    *left = *top;
    *bottom = -16;
    *right = *bottom;

    {
        int changedL = 0;
        int changedR = 0;
        int changedT = 0;
        int changedB = 0;
        int y;
        int x;

        for (y = 0; y < 16; y++) {
            for (x = 0; x < 16; x++) {
                if (func_0204ee7c(data, x, y)) {
                    if (x <= *left) {
                        *left = x;
                        changedL = 1;
                    }
                    if (x >= *right) {
                        *right = x;
                        changedR = 1;
                    }
                    if (y <= *top) {
                        *top = y;
                        changedT = 1;
                    }
                    if (y >= *bottom) {
                        *bottom = y;
                        changedB = 1;
                    }
                }
            }
        }

        changedL &= changedR;
        changedT &= changedL;
        changedB &= changedT;

        return changedB != 0;
    }
}
