/* func_ov102_0229cdb8 @ 0x0229cdb8, 0x3c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229c2a8(void *p, int arg);
extern void func_ov094_0229a6bc(void *p, int a, int b);

void func_ov102_0229cdb8(char *param)
{
    unsigned char b;

    if (func_ov102_0229c2a8(param, 0x40) != 0) {
        return;
    }

    b = *(unsigned char *) (param + 0x259f);
    if (b != 0 && b == 1) {
        func_ov094_0229a6bc(param + 0xcc, *(int *) (param + 0x24e0), *(int *) (param + 0x24e4));
    }
}
