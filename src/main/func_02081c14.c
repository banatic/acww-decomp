/* func_02081c14 @ 0x02081c14, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *dst, int val, int size);
extern void MI_CpuCopy8(void *dst, const void *src, int size);

void func_02081c14(void *param0, void *param1, int param2)
{
    int r4;
    void *r5;
    void *r6;

    r5 = param0;
    r6 = param1;
    r4 = param2;

    MI_CpuFill8((char *) r5 + 0x1e, 0, 0xc);

    if (r4 > 6) {
        r4 = 6;
    }

    MI_CpuCopy8(r6, (char *) r5 + 0x1e, r4 << 1);

    return;
}
