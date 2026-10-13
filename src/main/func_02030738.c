/* func_02030738 @ 0x02030738, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203160c(int);
extern int func_01ffcb2c(int, int);

int func_02030738(int *a, int *b, int *c, int *d)
{
    volatile unsigned char s[24];
    (void) &s;
    if (func_0203160c(0) != 0) {
        int minX = 0x10;
        int maxX = 0;
        int minY = 0x10;
        int maxY = 0;
        int y = 0;
        int x0 = 0;

        do {
            int x = x0;
            do {
                if (func_01ffcb2c(x, y) != 0x15) {
                    if (x < minX) {
                        minX = x;
                    } else if (x > maxX) {
                        maxX = x;
                    }
                    if (y < minY) {
                        minY = y;
                    } else if (y > maxY) {
                        maxY = y;
                    }
                }
                x++;
            } while (x < 0x20);
            y++;
        } while (y < 0x20);

        {
            int temp = (maxY << 13) + 0x1000;
            *a = minX << 13;
            *b = (maxX << 13) + 0x2000;
            *c = minY << 13;
            if (d) {
                *d = temp + 0x1000;
            }
        }
        return 1;
    } else {
        *c = 0;
        *b = *c;
        *a = *b;
        if (d) {
            *d = 0;
        }
        return 0;
    }
}
