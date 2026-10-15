/* func_020a0100 @ 0x020a0100, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a13b8(void);
extern void MI_InitUncompContextLZ(void *buf, int ret, void *param4);
extern int MI_ReadUncompLZ8(void *buf, void *param8, int value);
extern void MI_CpuCopy8(void *param4, int ret, unsigned int constant);

void func_020a0100(void *param)
{
    char buf[16];
    int ret = func_020a13b8();
    if (*(int *) param != 0) {
        MI_InitUncompContextLZ(buf, ret, (char *) param + 4);
        {
            char *p8 = (char *) param;
            p8 += 8;
            MI_ReadUncompLZ8(buf, p8, *(int *) param - 4);
        }
    } else {
        MI_CpuCopy8((char *) param + 4, ret, 0x000173fc);
    }
}
