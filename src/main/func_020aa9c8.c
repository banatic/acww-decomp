/* func_020aa9c8 @ 0x020aa9c8, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7f34(void);
extern int func_020a7fd4(void);

int func_020aa9c8(void *param)
{
    int result;
    unsigned char *p;
    int r4;
    int r5;

    r5 = (int) param;
    r4 = 0;
    if (*(int *) (r5 + 0x2c) == 1) {
        if (func_020a7f34() != 0) {
            r4 = 1;
            p = (unsigned char *) (r5 + 0x31);
            *p = (unsigned char) r4;
        } else {
            if (func_020a7fd4() != 0) {
                r4 = 1;
            }
        }
    }
    result = r4;
    return result;
}
