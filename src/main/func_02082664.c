/* func_02082664 @ 0x02082664, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf74(unsigned int);
extern int func_0208298c(int, int);
extern int func_020826cc(void);
extern int func_020826e0(int, int);
extern int data_021d1d4c;

int func_02082664(int r0)
{
    int r4;
    int r5 = r0;
    r4 = 0;
    if (r5 < 0) {
        goto end;
    }
    if (func_0207cf74(r0) != 0) {
        r4 = func_0208298c((int) &data_021d1d4c, r5);
        goto end;
    }
    if (r5 >= func_020826cc()) {
        goto end;
    }
    r5 -= 8;
    r4 = func_020826e0((int) &data_021d1d4c, r5);
end:
    return r4;
}
