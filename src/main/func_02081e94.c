/* func_02081e94 @ 0x02081e94, 0x46 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020951bc(void *);
extern void func_02081ef0(void *);
extern void func_02081e14(void *, void *, void *, void *);
extern void *func_020950a8(void *);
extern void MI_CpuCopy8(void *, const void *, unsigned int);

int func_02081e94(void *param0, void *param1, void *param2, void *param3)
{
    int result = 0;

    if (func_020951bc(param1)) {
        void *dst;
        char *src;

        func_02081ef0(param0);
        func_02081e14(param0, param1, param2, param3);

        dst = func_020950a8(param1);
        src = (char *) param0 + 0x1e;
        MI_CpuCopy8(dst, src, 0xc);

        result = 1;
    }

    return result;
}
