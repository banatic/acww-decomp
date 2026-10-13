/* func_020eee08 @ 0x020eee08, 0x54 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020eef70(void);
extern int NNS_SndHeapAlloc(int, int, void (*)(void), int, int);
extern void func_020eeea0(void);
extern int OS_Terminate(void);
extern int data_021fd050;

int func_020eee08(void)
{
    int ret;

    ret = NNS_SndHeapAlloc(func_020eef70(), 0x1020, func_020eeea0, 0, 0);
    data_021fd050 = ret;
    if (ret != 0) {
        return ret;
    }

    return OS_Terminate();
}
