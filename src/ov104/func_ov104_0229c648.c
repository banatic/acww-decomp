/* func_ov104_0229c648 @ 0x0229c648, 0x58 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_020978bc(unsigned char *p, int n);
extern int func_02097900(unsigned char *p);
extern void func_02097a44(unsigned char *p);
extern void func_02066650(unsigned char *p);

int func_ov104_0229c648(int unused, unsigned char *p)
{
    unsigned short flags = 0;
    int count;
    int i;

    count = func_020978bc(p, 0xa);
    if (count == 0) {
        return flags;
    }

    i = 0;
    while (i < count) {
        if (func_02097900(p) >= 0) {
            func_02097a44(p);
            func_02066650(p);
            flags = (unsigned short) (flags | 0x200);
        }
        p += 0x100;
        i++;
    }
    return flags;
}
