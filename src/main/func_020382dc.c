/* func_020382dc @ 0x020382dc, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern int func_020ec1e8(void);
extern int func_020732a8(int);
extern int func_020eba18(void);
extern int func_020732c0(int);
extern void func_020732cc(int, int);
extern int data_020ccf94;
void func_020382dc(void)
{
    int r = func_020ec1e8();
    if (r == 0 || r == 6) {
        return;
    }
    {
        int r4 = func_020732a8(data_020ccf94);
        int r0 = func_020eba18();
        if (r4 == 0) {
            if (r0 != 0 && r0 != 0x800c && r0 != 0x400b) {
                goto do_it;
            }
        }
        if (r4 != 1) {
            return;
        }
        if (r0 == 0) {
            return;
        }
        if (r0 == 0x80ff) {
            return;
        }
        if (r0 == 0x800c) {
            return;
        }
        if (r0 == 0x4006) {
            return;
        }
        if (r0 == 0x400a) {
            return;
        }
        if (r0 == 0x400b) {
            return;
        }
    do_it:
        r4 = data_020ccf94;
        {
            int t = func_020732c0(r4);
            int v = 0x10 | t;
            func_020732cc(r4, v);
        }
    }
}
