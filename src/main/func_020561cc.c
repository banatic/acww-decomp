/* func_020561cc @ 0x020561cc, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057a4c(void);
extern int func_020e9948(int a1, int a2);
extern int MI_CpuCopy8(int a1, int a2, int a3);

int func_020561cc(int a1, int a2)
{
    int v1;
    int v2;
    int v3;

    v1 = func_02057a4c();
    v2 = func_020e9948(a2, v1);
    if (v2 == 0) {
        return 0;
    }
    v3 = MI_CpuCopy8(a1, v2, v1);
    return v2;
}
