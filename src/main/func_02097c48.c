/* func_02097c48 @ 0x02097c48, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02097c24(int a, int b);
extern int func_020b65d0(void);
extern void func_02097c38(int receiver);
extern void func_02097c04(int a, int b);

int func_02097c48(int arg0)
{
    int res1;
    res1 = func_02097c24(arg0, 1);
    if (res1 != 0) {
        int res2;
        res2 = func_020b65d0();
        if (res2 != 0) {
            func_02097c38(arg0);
        }
        func_02097c04(arg0, 1);
    }
    return 1;
}
