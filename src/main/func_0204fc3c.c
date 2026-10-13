/* func_0204fc3c @ 0x0204fc3c, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020dc8b4[];

void *func_0204fc3c(unsigned int a, unsigned int b)
{
    if (a >= 1 && a <= 7) {
        return &data_020dc8b4[a - 1];
    }
    if (a == 8) {
        if (b == 0) {
            return &data_020dc8b4[a - 1];
        }
        if (b == 1) {
            return &data_020dc8b4[a];
        }
        return 0;
    }
    if (a == 9) {
        if (b == 0) {
            return &data_020dc8b4[a];
        }
        if (b == 1) {
            return &data_020dc8b4[a + 1];
        }
        return 0;
    }
    if (a >= 10 && a <= 12) {
        return &data_020dc8b4[a + 1];
    }
    return 0;
}
