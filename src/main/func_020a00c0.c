/* func_020a00c0 @ 0x020a00c0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a1350(void);
extern void func_020a0140(void);
extern void func_020a0100(void);
extern void *func_020a1338(void);
extern void OS_ExitThread(void *);

void func_020a00c0(int flag)
{
    unsigned int b = (flag != 0);
    if (b > 0) {
        func_020a1350();
        func_020a0140();
    } else {
        func_020a1350();
        func_020a0100();
    }
    {
        unsigned char *p = (unsigned char *) func_020a1338();
        p[0x10c8] = 1;
        OS_ExitThread(p);
    }
}
